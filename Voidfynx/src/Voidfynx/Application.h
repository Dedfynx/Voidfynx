#pragma once
#include "Voidfynx/Core.h"
#include "Voidfynx/Window.h"
#include <memory>

namespace Voidfynx {
    class VF_API Application {
       public:
        Application();
        virtual ~Application();

        void Run();

       private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined in client
    Application* CreateApplication();
}  // namespace Voidfynx
