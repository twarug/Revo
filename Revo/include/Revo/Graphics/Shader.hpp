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
        Vertex,
        Geometry,
        Fragment,
        TessControl,
        TessEvaluation,
        Compute
    };

    namespace impl
    {
        ///
        int32_t GetNativeHandle(ShaderType type);
    }

    ///
    class Shader
    {
    public:

        using NativeHandle_t = GLuint;

        ///
        Shader() = default;

        ///
        Shader(Shader const&) = delete;

        ///
        Shader& operator = (Shader const&) = delete;

        ///
        Shader(Shader&& rhs) noexcept;

        ///
        Shader& operator = (Shader&& rhs) noexcept;

        ///
        ~Shader();

        ///
        bool LoadFromFile(ShaderType type, char const* filePath);

        ///
        bool LoadFromMemory(ShaderType type, void const* data, GLint size = -1);

        ///
        bool IsValid() const;

        ///
        NativeHandle_t GetNativeHandle() const;

    private:

        ///
        void M_Destroy();

        ///
        bool M_Compile(ShaderType type, char const* data, GLint size);

        NativeHandle_t m_shader = 0;
    };
}
