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
    }
    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}  // namespace Voidfynx