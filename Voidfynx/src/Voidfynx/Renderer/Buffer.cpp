//
// Created by Dedfynx on 04/08/2026.
//

#include "vf_pch.h"
#include "Voidfynx/Renderer/Buffer.h"
#include "Voidfynx/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Voidfynx {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:
                VF_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            default:
                VF_CORE_ASSERT(false, "Unknown RendererAPI!");
                return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:
                VF_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, count);
            default:
                VF_CORE_ASSERT(false, "Unknown RendererAPI!");
                return nullptr;
        }
    }
}  // namespace Voidfynx