#pragma once
#include "Voidfynx/Core.h"

namespace Voidfynx {
    class VF_API Application {
       public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in client
    Application* CreateApplication();
}  // namespace Voidfynx
