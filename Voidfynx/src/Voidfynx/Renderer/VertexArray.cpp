//
// Created by Dedfynx on 07/08/2026.
//
#include "vf_pch.h"
#include "Voidfynx/Renderer/VertexArray.h"
#include "Voidfynx/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Voidfynx {
    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                VF_CORE_ASSERT(false, "RendererAPI::API::None is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexArray();
            default:
                VF_CORE_ASSERT(false, "Unknown RendererAPI!");
                return nullptr;
        }
    }
}  // namespace Voidfynx