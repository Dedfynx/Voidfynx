#include "vf_pch.h"  // IWYU pragma: keep
#include "Voidfynx/Application.h"
#include <GLFW/glfw3.h>

namespace Voidfynx {
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
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

}  // namespace Voidfynx
