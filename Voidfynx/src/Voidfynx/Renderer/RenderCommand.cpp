//
// Created by Dedfynx on 10/08/2026.
//

#include "vf_pch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "RenderCommand.h"

namespace Voidfynx {
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}  // namespace Voidfynx