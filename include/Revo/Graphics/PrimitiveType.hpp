#pragma once

// Revo
#include <Revo/Graphics/OpenGL.hpp>

namespace rv
{
    ///
    enum class PrimitiveType : int32_t
    {
        Points = GL_POINTS,
        Lines = GL_LINES,
        LineLoop = GL_LINE_LOOP,
        LineStrip = GL_LINE_STRIP,
        Triangles = GL_TRIANGLES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleFan = GL_TRIANGLE_FAN
    };
}
