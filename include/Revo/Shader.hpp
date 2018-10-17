#pragma once

// Revo
#include <Revo/OpenGL.hpp>

#ifdef M2_DEBUG
#   include <string>
#endif // M2_DEBUG

namespace rv
{

class Shader
{
public:

    using NativeHandle_t = GLuint;

    enum ShaderType
    {
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

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

    #ifdef M2_DEBUG

    ShaderType d_type;
    std::string d_filePath;
    const void* d_dataPtr = nullptr;
    GLint d_dataSize = 0;

    ///
    bool D_Reload();

    #endif // M2_DEBUG

private:

    ///
    void M_Destroy();

    ///
    bool M_Compile(ShaderType type, const char* data, GLint size);

    NativeHandle_t m_shader = 0;

};

}
