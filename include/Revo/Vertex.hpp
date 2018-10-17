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
    glm::vec3 position; ///< Position in pixels
    glm::vec4 color;    ///< rgba color in [ 0.0 - 1.0 ] range
    glm::vec2 texCoord; ///< Texture coordinates in pixels

};

}
