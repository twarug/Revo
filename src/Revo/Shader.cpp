#include <Revo/Shader.hpp>

// C++
#include <fstream>
#include <memory>

namespace rv
{

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
        auto ptr = GetFileContents(filePath);

        return ptr && M_Compile(type, ptr.get(), -1);
    }

    bool Shader::LoadFromMemory(ShaderType type, const void* data, GLint size)
    {
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

    void Shader::M_Destroy()
    {
        if (m_shader)
        {
            glDeleteShader(m_shader);
        }
    }

    bool Shader::M_Compile(ShaderType type, const char* data, GLint size)
    {
        NativeHandle_t shader = glCreateShader(static_cast<int32_t>(type));
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
            #if defined(M2_DEBUG)
            {
                GLchar infoLog[512];
                glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

                // TODO better logging
                std::printf("%s", infoLog);
            }
            #endif

            glDeleteShader(shader);

            return false;
        }
    }

}
