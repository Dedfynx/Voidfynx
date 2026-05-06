#include "vf_pch.h"  // IWYU pragma: keep

#include "Voidfynx/Core/Layer.h"

namespace Voidfynx {

    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName) {
    }
    Layer::~Layer() {}

}  // namespace Voidfynx
