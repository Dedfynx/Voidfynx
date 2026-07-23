#pragma once
#include "Voidfynx/Core/Core.h"
#include "Voidfynx/Core/Window.h"
#include "Voidfynx/Event/Event.h"
#include "Voidfynx/Event/ApplicationEvent.h"
#include "Voidfynx/Core/LayerStack.h"

#include "Voidfynx/ImGui/ImGuiLayer.h"

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

            inline Window& GetWindow() { return *m_Window; }
            inline static Application& Get() { return *s_Instance; }

        private:
            bool OnWindowClosed(WindowCloseEvent& e);

            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;

            bool m_Running = true;

            LayerStack m_LayerStack;

            static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
} // namespace Voidfynx
