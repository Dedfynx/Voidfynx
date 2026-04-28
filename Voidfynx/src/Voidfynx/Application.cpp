#include "Application.h"
#include "Voidfynx/Log.h"

namespace Voidfynx {
    Application::Application() {}
    Application::~Application() {}

    void Application::Run() {
        // test logger
        VF_CORE_INFO("RUN");
        VF_CORE_DEBUG("Debug");
        VF_CORE_WARN("Warn");
        VF_CORE_ERROR("Erreur");
        //
    }

}  // namespace Voidfynx
