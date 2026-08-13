//
// Created by Dedfynx on 13/08/2026.
//

#pragma once

#include <glm/glm.hpp>

namespace Voidfynx {

    class OrthographicCamera {
       public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetPosition(glm::vec3 position) {
            m_Position = position;
            RecalculateViewMatrix();
        }
        void SetRotation(float rotation) {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

        float GetRotation() const { return m_Rotation; }
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }

       private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjection;

        glm::vec3 m_Position = glm::vec3(0, 0, 0);
        float m_Rotation = 0.f;

        void RecalculateViewMatrix();
    };

}  // namespace Voidfynx
