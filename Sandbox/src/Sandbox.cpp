#include "Voidfynx.h"

class Sandbox : public Voidfynx::Application {
   public:
    Sandbox() {
    }
    ~Sandbox() {}
};

Voidfynx::Application* Voidfynx::CreateApplication() {
    return new Sandbox();
}
