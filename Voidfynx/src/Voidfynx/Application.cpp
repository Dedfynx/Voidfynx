#include "vf_pch.h"

#include "Voidfynx/Application.h"
#include "Voidfynx/Event/ApplicationEvent.h"
#include "Voidfynx/Log.h"

namespace Voidfynx {
    Application::Application() {}
    Application::~Application() {}

    void Application::Run() {
        // test logger
        VF_CORE_INFO("Info");
        VF_CORE_DEBUG("Debug");
        VF_CORE_WARN("Warn");
        VF_CORE_ERROR("Erreur");
        WindowResizeEvent e(1280, 720);
        VF_INFO("{}", e.ToString());
        //
    }

}  // namespace Voidfynx
