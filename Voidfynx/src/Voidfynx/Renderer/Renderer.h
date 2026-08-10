//
// Created by Dedfynx on 04/08/2026.
//

#pragma once

#include "Voidfynx\Renderer\RenderCommand.h"

namespace Voidfynx {
    class Renderer {
       public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

       private:
    };

}  // namespace Voidfynx
