#pragma once

#include "Voidfynx/Core/Layer.h"
#include "Voidfynx/Event/ApplicationEvent.h"
#include "Voidfynx/Event/KeyEvent.h"
#include "Voidfynx/Event/MouseEvent.h"

namespace Voidfynx {

    class VF_API ImGuiLayer : public Layer {
       public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

       private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);

        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);

        bool OnWindowResizeEvent(WindowResizeEvent& e);

        float m_Time = 0;
    };

}  // namespace Voidfynx
