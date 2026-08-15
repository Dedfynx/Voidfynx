//
// Created by Dedfynx on 15/08/2026.
//

#pragma once

namespace Voidfynx {

    struct Timestep {
        Timestep(float time = 0.f) : m_Time(time) {
        }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.f; }

        operator float() const { return m_Time; }

       private:
        float m_Time;
    };

}  // namespace Voidfynx
