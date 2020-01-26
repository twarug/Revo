#include <Revo/Graphics/Backend.hpp>

// Revo
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Shader.hpp>

// glad
#include <glad/glad.h>

namespace rv
{
    namespace impl
    {
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

        int32_t GetNativeHandle(PrimitiveType type)
        {
            switch (type)
            {
                case PrimitiveType::Points:        return GL_POINTS;
                case PrimitiveType::Lines:         return GL_LINES;
                case PrimitiveType::LineLoop:      return GL_LINE_LOOP;
                case PrimitiveType::LineStrip:     return GL_LINE_STRIP;
                case PrimitiveType::Triangles:     return GL_TRIANGLES;
                case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
                case PrimitiveType::TriangleFan:   return GL_TRIANGLE_FAN;
            }

            RV_ASSERT("Invalid PrimitiveType value", false);

            return -1;
        }

        int32_t GetNativeHandle(ShaderType type)
        {
            switch (type)
            {
                case ShaderType::Vertex:         return GL_VERTEX_SHADER;
                case ShaderType::Geometry:       return GL_GEOMETRY_SHADER;
                case ShaderType::Fragment:       return GL_FRAGMENT_SHADER;
                case ShaderType::TessControl:    return GL_TESS_CONTROL_SHADER;
                case ShaderType::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
                case ShaderType::Compute:        return GL_COMPUTE_SHADER;
            }

            RV_ASSERT("Invalid ShaderType value", false);

            return -1;
        }
    }
}
