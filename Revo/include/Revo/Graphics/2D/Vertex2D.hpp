#pragma once

// Revo
#include <Revo/Math/Vector.hpp>

namespace rv
{
    /// Simple 2D { position, color } vertex structure
    struct Vertex2D
    {
        Vec2f position;
        Vec4f color;
    };

    /// Simple 2D { position, color, texCoord } vertex structure
    struct TexVertex2D
    {
        Vec2f position;
        Vec4f color;
        Vec2f texCoord;
    };
}
