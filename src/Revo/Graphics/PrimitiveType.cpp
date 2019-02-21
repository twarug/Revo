#include <Revo/Graphics/PrimitiveType.hpp>

// Revo
#include <Revo/Graphics/Backend.hpp>

namespace rv
{
    namespace impl
    {
        ///
        int32_t GetNativeHandle(PrimitiveType type)
        {
            switch (type)
            {
                case PrimitiveType::Points: return GL_POINTS;
                case PrimitiveType::Lines: return GL_LINES;
                case PrimitiveType::LineLoop: return GL_LINE_LOOP;
                case PrimitiveType::LineStrip: return GL_LINE_STRIP;
                case PrimitiveType::Triangles: return GL_TRIANGLES;
                case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
                case PrimitiveType::TriangleFan: return GL_TRIANGLE_FAN;
            }

            return -1;
        }
    }
}
