#include <Revo/Graphics/Shader.hpp>

// Revo
#include <Revo/Graphics/Backend.hpp>

// C++
#include <fstream>
#include <memory>

namespace rv
{
    std::unique_ptr<char const[]> GetFileContents(char const* filePath)
    {
        std::ifstream file{ filePath, std::ios_base::binary };

        if (file)
        {
            file.seekg(0, std::ios_base::end);

            auto const size = file.tellg();

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

    Shader::Shader()
        : m_shader { 0 }
    {

    }

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

    bool Shader::LoadFromFile(ShaderType type, char const* filePath)
    {
        auto ptr = GetFileContents(filePath);

        return ptr && M_Compile(type, ptr.get(), -1);
    }
    
    bool Shader::LoadFromMemory(ShaderType type, void const* data, int32_t size)
    {
        return M_Compile(type, reinterpret_cast<char const*>(data), size);
    }

    bool Shader::IsValid() const
    {
        return m_shader;
    }

    Shader::NativeHandle_t Shader::GetNativeHandle() const
    {
        return m_shader;
    }

    void Shader::M_Destroy()
    {
        glDeleteShader(m_shader);
    }

    bool Shader::M_Compile(ShaderType type, char const* data, int32_t size)
    {
        NativeHandle_t shader = glCreateShader(impl::GetNativeHandle(type));
        glShaderSource(shader, 1, &data, &size);
        glCompileShader(shader);

        int32_t success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success)
        {
            M_Destroy();

            m_shader = shader;

            return true;
        }
        else
        {
            #if defined(RV_DEBUG)
            {
                char infoLog[512];
                glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

                // TODO better logging
                std::fprintf(stderr, "%s", infoLog);
            }
            #endif

            glDeleteShader(shader);

            return false;
        }
    }
}
