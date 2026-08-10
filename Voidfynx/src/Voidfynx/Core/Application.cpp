#include "vf_pch.h"  // IWYU pragma: keep
#include "glad/glad.h"
#include "Voidfynx/Core/Application.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

#include "Voidfynx/Core/Input.h"
#include "Voidfynx/Renderer/Renderer.h"

namespace Voidfynx {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        VF_CORE_ASSERT(!s_Instance, "Application already exist");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(VF_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3][7] = {
            {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        };

        std::shared_ptr<VertexBuffer> triangleVB(VertexBuffer::Create(*vertices, sizeof(vertices)));

        BufferLayout layout = {
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float4, "color"}};

        triangleVB->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(triangleVB);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> triangleIB(IndexBuffer::Create(indices, std::size(indices)));
        m_VertexArray->AddIndexBuffer(triangleIB);

        m_SquareVertexArray.reset(VertexArray::Create());
        float squareVertices[4][7] = {
            {-0.75f, -0.75f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f},
            {0.75f, -0.75f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f},
            {0.75f, 0.75f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f},
            {-0.75f, 0.75f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f},

        };
        std::shared_ptr<VertexBuffer> squareVB(VertexBuffer::Create(*squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout(layout);
        m_SquareVertexArray->AddVertexBuffer(squareVB);
        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->AddIndexBuffer(squareIB);

        const std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 color;
            out vec3 vPosition;
            out vec4 vColor;
            void main(){
                gl_Position = vec4(position,1.0);
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

        m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }
    Application::~Application() {}

    void Application::Run() {
        // test logger
        VF_CORE_INFO("Info");
        VF_CORE_DEBUG("Debug");
        VF_CORE_WARN("Warn");
        VF_CORE_ERROR("Erreur");
        //
        while (m_Running) {
            RenderCommand::SetClearColor({0.1f, 0.6f, 0.1f, 1});
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_Shader->bind();
            Renderer::Submit(m_SquareVertexArray);

            m_Shader->bind();
            Renderer::Submit(m_VertexArray);

            Renderer::EndScene();

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
        //
    }

    void Application::OnEvent(Event& e) {
        // VF_CORE_INFO("{}", e.ToString());
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(VF_BIND_EVENT_FN(Application::OnWindowClosed));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

}  // namespace Voidfynx
