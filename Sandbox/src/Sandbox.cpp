#include "Voidfynx.h"

#include "ExampleLayer.h"

class Sandbox : public Voidfynx::Application {
   public:
    Sandbox() {
        VF_INFO("Sandbox");
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() {}
};

Voidfynx::Application* Voidfynx::CreateApplication() {
    return new Sandbox();
}
