#include "vf_pch.h"  // IWYU pragma: keep
#include "Voidfynx/Application.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace Voidfynx {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application() {
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
        while (m_Running) {
            glClearColor(1, 1, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
        //
    }

    void Application::OnEvent(Event& e) {
        // VF_CORE_INFO("{}", e.ToString());
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

}  // namespace Voidfynx
