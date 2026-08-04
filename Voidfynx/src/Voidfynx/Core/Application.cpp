#include "vf_pch.h"  // IWYU pragma: keep
#include "glad/glad.h"
#include "Voidfynx/Core/Application.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

#include "Voidfynx/Core/Input.h"

namespace Voidfynx {

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGL(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            default:
                VF_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
        }
    }

    Application::Application() {
        VF_CORE_ASSERT(!s_Instance, "Application already exist");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(VF_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3][7] = {
            {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        };

        m_VertexBuffer.reset(VertexBuffer::Create(*vertices, sizeof(vertices)));

        BufferLayout layout = {
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float4, "color"}};

        uint32_t index = 0;
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGL(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<const void*>(element.offset));

            index++;
        }

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->bind();

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
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
