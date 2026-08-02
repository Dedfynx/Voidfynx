//
// Created by Dedfynx on 31/07/2026.
//

#include "vf_pch.h"

#include "glad/glad.h"
#include "OpenGLContext.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Voidfynx {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
        VF_CORE_ASSERT(m_WindowHandle, "Window handle is null");
    }
    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        VF_CORE_ASSERT(status, "Failed to initialize GLAD!");

        VF_CORE_INFO("OpenGL Info:");
        VF_CORE_INFO("- Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        VF_CORE_INFO("- Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        VF_CORE_INFO("- Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }
    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}  // namespace Voidfynx