#pragma once

// m2
#include <m2/Config.hpp>

// glm
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace rv
{

    /// Simple trivial vertex structure
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
    };

}
