#pragma once

// Revo
#include <Revo/Config.hpp>

// glm
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace rv
{
    /// Simple 3-component vertex structure
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
    };
}
