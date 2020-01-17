#include <Revo/Graphics/Backend.hpp>

// C++
#include <cstdio>
#include <type_traits>

// glad
#include <glad/glad.h>

#if defined(RV_DEBUG)
#   define RV_GFX_CALL(__f, ...) GfxCall(RV_HERE, #__f "(" #__VA_ARGS__ ")", __f, __VA_ARGS__)
#else
#   define RV_GFX_CALL(__f, ...) __f(__VA_ARGS__)
#endif

namespace rv
{
    namespace impl
    {
        #if defined(RV_DEBUG)

        auto TranslateErrorCode(GLenum errorCode) -> char const*
        {
            switch (errorCode)
            {
                case GL_INVALID_ENUM:                  return "Invalid enum";
                case GL_INVALID_VALUE:                 return "Invalid value";
                case GL_INVALID_OPERATION:             return "Invalid operation";
                case GL_STACK_OVERFLOW:                return "Stack overflow";
                case GL_STACK_UNDERFLOW:               return "Stack underflow";
                case GL_OUT_OF_MEMORY:                 return "Out of memory";
                case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
                case GL_CONTEXT_LOST:                  return "Context lost";
                default:                               return "Unknown error";
            }
        }

        template <typename Function, typename... Args>
        auto GfxCall(char const* where, char const* which, Function function, Args... args)
        {
            while (glGetError() != GL_NO_ERROR);

            if constexpr (std::is_void_v<std::invoke_result_t<Function, Args...>>)
            {
                (*function)(args...);

                while (GLenum const errorCode = glGetError())
                {
                    // TODO logging
                    std::fprintf(stderr, "[OpenGL error] (%s) at %s with %s\n", TranslateErrorCode(errorCode), where, which);
                }

                return;
            }
            else
            {
                auto const result = (*function)(args...);

                while (GLenum const errorCode = glGetError())
                {
                    // TODO logging
                    std::fprintf(stderr, "[OpenGL error] (%s) at %s with %s\n", TranslateErrorCode(errorCode), where, which);
                }

                return result;
            }
        }

        #endif

        void CreateVao(uint32_t* vao)
        {
            glGenVertexArrays(1, vao);
        }

        void DestroyVao(uint32_t vao)
        {
            glDeleteVertexArrays(1, &vao);
        }

        void BindVao(uint32_t vao)
        {
            glBindVertexArray(vao);
        }
        void CreateVbo(uint32_t* vbo)
        {
            glGenBuffers(1, vbo);
        }

        void DestroyVbo(uint32_t vbo)
        {
            glDeleteBuffers(1, &vbo);
        }

        void BindVbo(uint32_t vbo)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
        }

        void DrawArrays(int32_t type, size_t startIndex, size_t size)
        {
            glDrawArrays(type, startIndex, size);
        }
        
        void CreateArrayBuffer(void const* data, size_t sizeInBytes)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_DYNAMIC_DRAW);
        }

        void UpdateArrayBuffer(void const* data, size_t offsetInBytes, size_t sizeInBytes)
        {
            glBufferSubData(GL_ARRAY_BUFFER, offsetInBytes, sizeInBytes, data);
        }

        void SetVertexAtrribPointer(uint32_t vao, size_t index, size_t elemCount, size_t sizeInBytes, void const* offsetPtr)
        {
            glEnableVertexArrayAttrib(vao, index);
            glVertexAttribPointer(index, elemCount, GL_FLOAT, GL_FALSE, sizeInBytes, offsetPtr);
        }
    }
}
