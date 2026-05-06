#pragma once
#include "Voidfynx/Core/Core.h"
#include "Voidfynx/Core/Window.h"
#include "Voidfynx/Event/Event.h"
#include "Voidfynx/Event/ApplicationEvent.h"
#include "Voidfynx/Core/LayerStack.h"

#include <memory>

namespace Voidfynx {
    class VF_API Application {
       public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

       private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        LayerStack m_LayerStack;
    };

    // To be defined in client
    Application* CreateApplication();
}  // namespace Voidfynx
