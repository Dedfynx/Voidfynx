//
// Created by Dedfynx on 04/08/2026.
//
#include "vf_pch.h"
#include "Voidfynx/Renderer/Renderer.h"

namespace Voidfynx {
    void Renderer::BeginScene() {
    }
    void Renderer::EndScene() {
    }
    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndex(vertexArray);
    }
}  // namespace Voidfynx