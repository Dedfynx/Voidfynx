#include "vf_pch.h"  // IWYU pragma: keep
#include "glad/glad.h"
#include "Voidfynx/Core/Application.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

#include "Voidfynx/Core/Input.h"
#include "Voidfynx/Renderer/Renderer.h"

namespace Voidfynx {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        VF_CORE_ASSERT(!s_Instance, "Application already exist");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(VF_BIND_EVENT_FN(Application::OnEvent));
        m_Window->SetVSync(true);

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }
    Application::~Application() {}

    void Application::Run() {
        // test logger
        VF_CORE_INFO("Info");
        VF_CORE_DEBUG("Debug");
        VF_CORE_WARN("Warn");
        VF_CORE_ERROR("Erreur");
        //
        while (m_Running) {
            float time = static_cast<float>(glfwGetTime());  // todo Platform::GetTIme()
            Timestep delta = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(delta);
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
        //
    }

    void Application::OnEvent(Event& e) {
        // VF_CORE_INFO("{}", e.ToString());
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(VF_BIND_EVENT_FN(Application::OnWindowClosed));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

}  // namespace Voidfynx
