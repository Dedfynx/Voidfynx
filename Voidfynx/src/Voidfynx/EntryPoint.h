#pragma once

#include "Voidfynx/Application.h"

#ifdef VF_PLATFORM_WINDOWS
// TODO: winmain plutot que main
extern Voidfynx::Application* Voidfynx::CreateApplication();

int main(int argc, char** argv) {
    auto app = Voidfynx::CreateApplication();
    app->Run();
    delete app;
}
#else
extern Voidfynx::Application* Voidfynx::CreateApplication();

int main(int argc, char** argv) {
    auto app = Voidfynx::CreateApplication();
    app->Run();
    delete app;
}
#endif
