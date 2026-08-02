//
// Created by Dedfynx on 02/08/2026.
//

#pragma once
#include <cstdint>
#include <string>

namespace Voidfynx {
    class Shader {
       public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void bind() const;
        void unbind() const;

       private:
        uint32_t m_RendererID;
    };
}  // namespace Voidfynx
