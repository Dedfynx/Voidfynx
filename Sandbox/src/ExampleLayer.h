#pragma once

#include "imgui.h"
#include "Voidfynx.h"

class ExampleLayer : public Voidfynx::Layer {
   public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // VF_INFO("ExampleLayer::Update");
    }

    void OnEvent(Voidfynx::Event& event) override {
        // VF_INFO("{}", event.ToString());
    }
    void OnAttach() override {
        // ImGui::SetCurrentContext(ImGui::GetCurrentContext());
    }

    void OnImGuiRender() override {
        // VF_INFO("OnImguiRender");
        ImGui::Begin("Test");
        ImGui::Text("Hello");
        ImGui::End();
    }
};
