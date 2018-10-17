#include <Revo/Shader.hpp>

// C++
#include <fstream>
#include <memory>

std::unique_ptr<const char[]> GetFileContents(const char* filePath)
{
    std::ifstream file{ filePath, std::ios_base::binary };

    if (file)
    {
        file.seekg(0, std::ios_base::end);

        auto size = file.tellg();

        std::unique_ptr<char[]> ptr;

        if (size > 0)
        {
            file.seekg(0, std::ios_base::beg);

            ptr.reset(new char[static_cast<size_t>(size) + 1]);

            file.read(ptr.get(), size);
            ptr[size] = '\0';
        }

        return ptr;
    }

    return nullptr;
}

namespace rv
{

Shader::Shader(Shader&& rhs) noexcept
    : m_shader { rhs.m_shader }
{
    rhs.m_shader = 0;
}

Shader& Shader::operator = (Shader&& rhs) noexcept
{
    if (this != &rhs)
    {
        M_Destroy();

        m_shader = rhs.m_shader;
        rhs.m_shader = 0;
    }

    return *this;
}

Shader::~Shader()
{
    M_Destroy();
}

bool Shader::LoadFromFile(ShaderType type, const char* filePath)
{
    #ifdef M2_DEBUG
    {
        d_type = type;
        d_filePath = filePath;
        d_dataPtr = nullptr;
        d_dataSize = 0;
    }
    #endif // M2_DEBUG

    auto ptr = GetFileContents(filePath);

    return ptr && M_Compile(type, ptr.get(), -1);
}

bool Shader::LoadFromMemory(ShaderType type, const void* data, GLint size)
{
    #ifdef M2_DEBUG
    {
        d_type = type;
        d_filePath.clear();
        d_dataPtr = data;
        d_dataSize = size;
    }
    #endif // M2_DEBUG

    return M_Compile(type, reinterpret_cast<const char*>(data), size);
}

bool Shader::IsValid() const
{
    return m_shader;
}

Shader::NativeHandle_t Shader::GetNativeHandle() const
{
    return m_shader;
}

#ifdef M2_DEBUG

bool Shader::D_Reload()
{
    if (!d_filePath.empty())
    {
        auto ptr = GetFileContents(d_filePath.data());

        return ptr && M_Compile(d_type, ptr.get(), -1);
    }
    else if (d_dataPtr != nullptr)
    {
        return M_Compile(d_type, reinterpret_cast<const char*>(d_dataPtr), d_dataSize);
    }

    return false;
}

#endif // M2_DEBUG

void Shader::M_Destroy()
{
    if (m_shader)
    {
        glDeleteShader(m_shader);
    }
}

bool Shader::M_Compile(ShaderType type, const char* data, GLint size)
{
    NativeHandle_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &data, &size);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success)
    {
        M_Destroy();

        m_shader = shader;

        return true;
    }
    else
    {
        #ifdef M2_DEBUG
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

            // TODO better log 'infoLog'
            std::printf("%s", infoLog);
        }
        #endif // M2_DEBUG

        glDeleteShader(shader);

        return false;
    }
}

}
