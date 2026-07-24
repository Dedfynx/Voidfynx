//
// Created by Dedfynx on 24/07/2026.
//

#pragma once

#include <utility>

#include "Voidfynx/Core/KeyCode.h"
#include "Voidfynx/Core/MouseCode.h"

namespace Voidfynx {

    class Input
    {
        public:
            static bool IsKeyPressed(KeyCode key);
            static bool IsMouseButtonPressed(MouseCode button);
            static std::pair<float, float> GetMousePosition();
            static float GetMouseX();
            static float GetMouseY();
    };

}