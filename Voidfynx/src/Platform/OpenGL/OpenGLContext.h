//
// Created by Dedfynx on 31/07/2026.
//

#pragma once
#include "Voidfynx/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Voidfynx {

    class OpenGLContext : public GraphicsContext {
       public:
        OpenGLContext(GLFWwindow* windowHandle);
        ~OpenGLContext();

        virtual void Init() override;
        virtual void SwapBuffers() override;

       private:
        GLFWwindow* m_WindowHandle;
    };

}  // namespace Voidfynx
