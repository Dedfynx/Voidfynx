#include "Application.h"

namespace Voidfynx {
    Application::Application() {}
    Application::~Application() {}

    void Application::Run() {
        // test logger
        LOG_INFO("RUN");
        LOG_DEBUG("Debug");
        LOG_WARN("Warn");
        LOG_ERROR("Erreur");
        //
        while (true) {
        }
    }

}  // namespace Voidfynx
