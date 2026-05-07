#include "vf_pch.h"  // IWYU pragma: keep
#include "Voidfynx/Core/Application.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace Voidfynx {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        VF_CORE_ASSERT(!s_Instance, "Application already exist");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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
            glClearColor(1, 1, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }
        //
    }

    void Application::OnEvent(Event& e) {
        // VF_CORE_INFO("{}", e.ToString());
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

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
