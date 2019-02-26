#pragma once

// Revo
#include <Revo/Graphics/Transformable.hpp>

namespace rv
{
    // FWD
    class ShaderProgram;
    class Camera;

    ///
    struct RenderStates
    {
        ShaderProgram const* shaderProgram = nullptr;
        Camera const* camera = nullptr;
    };
}
