#pragma once

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
};
