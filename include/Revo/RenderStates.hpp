#pragma once

// Revo
#include <Revo/Transformable.hpp>

namespace rv
{

    // FWD
    class ShaderProgram;
    class Camera;

    ///
    struct RenderStates
    {
        const ShaderProgram* shaderProgram = nullptr;
        const Camera* camera = nullptr;
    };

}
