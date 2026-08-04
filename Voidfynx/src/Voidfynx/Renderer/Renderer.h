//
// Created by Dedfynx on 04/08/2026.
//

#pragma once

namespace Voidfynx {

    enum class RendererAPI {
        None = 0,
        OpenGL = 1
    };

    class Renderer {
       public:
        inline static RendererAPI GetAPI() { return Renderer::CurrentRendererAPI; }

       private:
        static RendererAPI CurrentRendererAPI;
    };

}  // namespace Voidfynx
