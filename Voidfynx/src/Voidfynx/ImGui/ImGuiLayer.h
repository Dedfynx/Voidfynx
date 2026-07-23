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

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnImGuiRender() override;

            void Begin();
            void End();

        private:
            float m_Time = 0;
    };
} // namespace Voidfynx
