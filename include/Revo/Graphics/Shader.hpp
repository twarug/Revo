#pragma once

// Revo
#include <Revo/Graphics/Backend.hpp>

// C++
#include <cstdint>

namespace rv
{
    ///
    enum class ShaderType : int32_t
    {
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    ///
    class Shader
    {
    public:

        using NativeHandle_t = GLuint;

        ///
        Shader() = default;

        ///
        Shader(const Shader&) = delete;

        ///
        Shader& operator = (const Shader&) = delete;

        ///
        Shader(Shader&& rhs) noexcept;

        ///
        Shader& operator = (Shader&& rhs) noexcept;

        ///
        ~Shader();

        ///
        bool LoadFromFile(ShaderType type, const char* filePath);

        ///
        bool LoadFromMemory(ShaderType type, const void* data, GLint size = -1);

        ///
        bool IsValid() const;

        ///
        NativeHandle_t GetNativeHandle() const;

    private:

        ///
        void M_Destroy();

        ///
        bool M_Compile(ShaderType type, const char* data, GLint size);

        NativeHandle_t m_shader = 0;
    };
}
