#pragma once

// Revo
#include <Revo/Core.hpp>

namespace rv
{
    ///
    enum class ShaderType
    {
        Vertex,
        Geometry,
        Fragment,
        TessControl,
        TessEvaluation,
        Compute
    };

    ///
    class Shader
    {
    public:

        using NativeHandle_t = uint32_t;

        ///
        Shader();

        ///
        Shader(Shader const&) = delete;

        ///
        Shader& operator = (Shader const&) = delete;

        ///
        Shader(Shader&& rhs) noexcept;

        ///
        Shader& operator = (Shader&& rhs) noexcept;

        ///
        Shader(Shader const&&) = delete;

        ///
        Shader& operator = (Shader const&&) = delete;

        ///
        ~Shader();

        ///
        bool LoadFromFile(ShaderType type, char const* filePath);

        ///
        bool LoadFromMemory(ShaderType type, void const* data, int32_t size = -1);

        ///
        bool IsValid() const;

        ///
        NativeHandle_t GetNativeHandle() const;

    private:

        ///
        void M_Destroy();

        ///
        bool M_Compile(ShaderType type, char const* data, int32_t size);

        NativeHandle_t m_shader;
    };
}
