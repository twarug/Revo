#pragma once

// m2
#include <m2/Config.hpp>

// glad
#include <glad/glad.h>

#define M2_GL(__expr)\
    while (glGetError() != GL_NO_ERROR);\
    __expr; while (GLenum error = glGetError()) { std::printf("[OpenGL error] (%d) - %s:%d", error, __FILE__, __LINE__); }
    // TODO better logging
