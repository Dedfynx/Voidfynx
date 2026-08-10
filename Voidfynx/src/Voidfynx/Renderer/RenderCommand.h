//
// Created by Dedfynx on 10/08/2026.
//

#pragma once

#include "Voidfynx/Renderer/RendererAPI.h"

namespace Voidfynx {

    class RenderCommand {
       public:
        inline static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        };
        inline static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        };

       private:
        static RendererAPI* s_RendererAPI;
    };

}  // namespace Voidfynx
