#pragma once

#include "imgui.h"
#include "Voidfynx.h"

class ExampleLayer : public Voidfynx::Layer {
   public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f) {
        Voidfynx::BufferLayout layout = {
            {Voidfynx::ShaderDataType::Float3, "position"},
            {Voidfynx::ShaderDataType::Float4, "color"}};

        m_VertexArray.reset(Voidfynx::VertexArray::Create());

        float vertices[3][7] = {
            {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        };

        std::shared_ptr<Voidfynx::VertexBuffer> triangleVB(Voidfynx::VertexBuffer::Create(*vertices, sizeof(vertices)));

        triangleVB->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(triangleVB);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<Voidfynx::IndexBuffer> triangleIB(Voidfynx::IndexBuffer::Create(indices, std::size(indices)));
        m_VertexArray->AddIndexBuffer(triangleIB);

        m_SquareVertexArray.reset(Voidfynx::VertexArray::Create());
        float squareVertices[4][7] = {
            {-0.75f, -0.75f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f},
            {0.75f, -0.75f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f},
            {0.75f, 0.75f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f},
            {-0.75f, 0.75f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f},

        };
        std::shared_ptr<Voidfynx::VertexBuffer> squareVB(Voidfynx::VertexBuffer::Create(*squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout(layout);
        m_SquareVertexArray->AddVertexBuffer(squareVB);
        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Voidfynx::IndexBuffer> squareIB(Voidfynx::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->AddIndexBuffer(squareIB);

        m_cubeVertexArray.reset(Voidfynx::VertexArray::Create());
        float cubeVertices[8][7] = {
            // Front
            {-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f},
            {0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f},
            {0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f},
            {-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f},
            // Back
            {-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},
            {0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f},
            {0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f},
            {-0.5f, 0.5f, -0.5f, 0.2f, 0.2f, 0.2f, 1.0f}};
        std::shared_ptr<Voidfynx::VertexBuffer> cubeVB(Voidfynx::VertexBuffer::Create(*cubeVertices, sizeof(cubeVertices)));
        cubeVB->SetLayout(layout);
        m_cubeVertexArray->AddVertexBuffer(cubeVB);
        uint32_t cubeIndices[6][6] = {
            {0, 1, 2, 2, 3, 0},
            {1, 5, 6, 6, 2, 1},
            {5, 4, 7, 7, 6, 5},
            {4, 0, 3, 3, 7, 4},
            {3, 2, 6, 6, 7, 3},
            {4, 5, 1, 1, 0, 4},
        };

        std::shared_ptr<Voidfynx::IndexBuffer> cubeIB(Voidfynx::IndexBuffer::Create(*cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
        m_cubeVertexArray->AddIndexBuffer(cubeIB);

        const std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 color;

            uniform mat4 u_ViewProjection;

            out vec3 vPosition;
            out vec4 vColor;
            void main(){
                gl_Position = u_ViewProjection * vec4(position,1.0);
                vPosition = position;
                vColor = color;
            }
        )";

        const std::string fragmentSource = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;
            in vec4 vColor;

            void main(){
                color = vColor;
            }
        )";

        m_Shader = std::make_unique<Voidfynx::Shader>(vertexSource, fragmentSource);
    }

    void OnUpdate() override {
        if (Voidfynx::Input::IsKeyPressed(Voidfynx::Key::A)) {
            m_CameraPosition.x -= m_CameraMoveSpeed;
        } else if (Voidfynx::Input::IsKeyPressed(Voidfynx::Key::D)) {
            m_CameraPosition.x += m_CameraMoveSpeed;
        }
        if (Voidfynx::Input::IsKeyPressed(Voidfynx::Key::W)) {
            m_CameraPosition.y += m_CameraMoveSpeed;
        } else if (Voidfynx::Input::IsKeyPressed(Voidfynx::Key::S)) {
            m_CameraPosition.y -= m_CameraMoveSpeed;
        }
        if (Voidfynx::Input::IsKeyPressed(Voidfynx::Key::Q)) {
            m_CameraRotation += m_CameraRotationSpeed;
        } else if (Voidfynx::Input::IsKeyPressed(Voidfynx::Key::E)) {
            m_CameraRotation -= m_CameraRotationSpeed;
        }

        Voidfynx::RenderCommand::SetClearColor({0.1f, 0.6f, 0.1f, 1});
        Voidfynx::RenderCommand::Clear();

        // m_Camera.SetPosition({0.5f, 0.5f, -0.5f});
        // m_Camera.SetRotation(45.f);
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
        Voidfynx::Renderer::BeginScene(m_Camera);

        // Renderer::Submit(m_SquareVertexArray);
        // Renderer::Submit(m_VertexArray);
        Voidfynx::Renderer::Submit(m_cubeVertexArray, m_Shader);

        Voidfynx::Renderer::EndScene();
    }

    void OnEvent(Voidfynx::Event& event) override {
    }

    void OnAttach() override {
    }

    void OnImGuiRender() override {
    }

   private:
    std::shared_ptr<Voidfynx::Shader> m_Shader;
    std::shared_ptr<Voidfynx::VertexArray> m_VertexArray;
    std::shared_ptr<Voidfynx::VertexArray> m_SquareVertexArray;
    std::shared_ptr<Voidfynx::VertexArray> m_cubeVertexArray;

    Voidfynx::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = .1f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 2.f;
};
