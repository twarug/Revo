#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <cstdint>

namespace rv
{
    ///
    enum class PrimitiveType : int32_t
    {
        Points,
        Lines,
        LineLoop,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan
    };

    namespace impl
    {
        ///
        int32_t GetNativeHandle(PrimitiveType type);        
    }
}
