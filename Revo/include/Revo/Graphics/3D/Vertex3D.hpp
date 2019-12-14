#pragma once

// Revo
#include <Revo/Math/Vector.hpp>

namespace rv
{
    /// Simple 3D { position, color } vertex structure
    struct Vertex3D
    {
        Vec3f position;
        Vec4f color;
    };

    /// Simple 3D { position, color, texCoord } vertex structure
    struct TexVertex3D
    {
        Vec3f position;
        Vec4f color;
        Vec2f texCoord;
    };
}
