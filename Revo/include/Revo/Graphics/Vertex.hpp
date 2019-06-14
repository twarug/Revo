#pragma once

// Revo
#include <Revo/Math/Vector.hpp>

namespace rv
{
    /// Simple 3-component vertex structure
    struct Vertex
    {
        Vec3f position;
        Vec4f color;
        Vec2f texCoord;
    };
}
