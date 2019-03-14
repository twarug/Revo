#pragma once

// Revo
#include <Revo/Config.hpp>

#if defined(RV_DEBUG)

#if defined(RV_OPENGL)

// C++
#include <cstdio>
#include <functional>

// glad
#include <glad/glad.h>

namespace rv
{
    namespace impl
    {
        template <typename F, typename... Args>
        auto GfxCall(char const* where, char const* which, F f, Args&&... args)
        {
            constexpr auto translateErrorCode = [](GLenum error) -> char const* {
                switch (error)
                {
                    case GL_INVALID_ENUM: return "Invalid enum";
                    case GL_INVALID_VALUE: return "Invalid value";
                    case GL_INVALID_OPERATION: return "Invalid operation";
                    case GL_STACK_OVERFLOW: return "Stack overflow";
                    case GL_STACK_UNDERFLOW: return "Stack underflow";
                    case GL_OUT_OF_MEMORY: return "Out of memory";
                    case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
                    case GL_CONTEXT_LOST: return "Context lost";
                    default: return "Unknown";
                }
            };

            while (glGetError() != GL_NO_ERROR);

            if constexpr (std::is_void_v<std::invoke_result_t<F, Args...>>)
            {
                (*f)(std::forward<Args>(args)...);

                while (GLenum error = glGetError())
                {
                    // TODO logging
                    std::fprintf(stderr, "[OpenGL error] (%i -> %s) at %s with %s\n", error, translateErrorCode(error), where, which);
                }

                return;
            }
            else
            {
                auto result = (*f)(std::forward<Args>(args)...);

                while (GLenum error = glGetError())
                {
                    // TODO logging
                    std::fprintf(stderr, "[OpenGL error] (%i -> %s) at %s with %s\n", error, translateErrorCode(error), where, which);
                }

                return result;
            }
        }
    }
}

#endif

#endif
