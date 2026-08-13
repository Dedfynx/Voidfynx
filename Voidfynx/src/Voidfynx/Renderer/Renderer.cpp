//
// Created by Dedfynx on 04/08/2026.
//
#include "vf_pch.h"
#include "Voidfynx/Renderer/Renderer.h"

namespace Voidfynx {
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera) {
        m_SceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }
    void Renderer::EndScene() {
    }
    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
        shader->bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->viewProjectionMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndex(vertexArray);
    }
}  // namespace Voidfynx