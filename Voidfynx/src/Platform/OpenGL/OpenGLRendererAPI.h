//
// Created by Dedfynx on 10/08/2026.
//

#pragma once
#include "Voidfynx/Renderer/RendererAPI.h"

namespace Voidfynx {

    class OpenGLRendererAPI : public RendererAPI {
       public:
        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

}  // namespace Voidfynx
