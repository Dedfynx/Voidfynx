#pragma once
#include "Voidfynx/Core.h"
#include "Voidfynx/Window.h"
#include "Voidfynx/Event/Event.h"
#include "Voidfynx/Event/ApplicationEvent.h"
#include <memory>

namespace Voidfynx {
    class VF_API Application {
       public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

       private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined in client
    Application* CreateApplication();
}  // namespace Voidfynx
