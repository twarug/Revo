#include <Revo/Graphics/ShaderProgram.hpp>

// Revo
#include <Revo/Utility/FNV.hpp>
#include <Revo/Utility/Overloaded.hpp>
#include <Revo/glmSerializers.hpp>

// C++
#include <fstream>

// glm
#include <glm/gtc/type_ptr.hpp>

#if defined(RV_DEBUG)
#   include <Revo/Graphics/ImGuiContext.hpp>
#endif

namespace rv
{
    class UniformBinder
    {
    public:

        UniformBinder(GLuint program, const char* name)
            : m_program { program }
            , m_savedProgram { 0 }
            , m_location { -1 }
        {
            if (m_program)
            {
                GLint currentProgram;
                glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

                m_savedProgram = currentProgram;

                if (m_program != m_savedProgram)
                {
                    glUseProgram(m_program);
                }

                m_location = glGetUniformLocation(m_program, name);
            }
        }

        UniformBinder(const UniformBinder&) = delete;

        UniformBinder& operator = (const UniformBinder&) = delete;

        UniformBinder(UniformBinder&& rhs) = delete;

        UniformBinder& operator = (UniformBinder&& rhs) = delete;

        ~UniformBinder()
        {
            if (m_program && (m_program != m_savedProgram))
            {
                glUseProgram(m_savedProgram);
            }
        }

        GLint GetLocation() const
        {
            return m_location;
        }

        bool HasValidLocation() const
        {
            return m_location != -1;
        }

    private:

        const GLuint m_program;
        GLuint m_savedProgram;
        GLint m_location;
    };

    ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept
        : m_program { rhs.m_program }
    {
        rhs.m_program = 0;
    }

    ShaderProgram& ShaderProgram::operator = (ShaderProgram&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_program = rhs.m_program;
            rhs.m_program = 0;
        }

        return *this;
    }

    ShaderProgram::~ShaderProgram()
    {
        M_Destroy();
    }

    void ShaderProgram::UseProgram() const
    {
        GLint currentProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

        if (m_program != static_cast<GLuint>(currentProgram))
        {
            glUseProgram(m_program);
        }
    }

    bool ShaderProgram::SetUniform(const char* name, bool value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1i(binder.GetLocation(), value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::bvec2& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2i(binder.GetLocation(), value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::bvec3& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3i(binder.GetLocation(), value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::bvec4& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4i(binder.GetLocation(), value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, int value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1i(binder.GetLocation(), value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::ivec2& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2i(binder.GetLocation(), value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::ivec3& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3i(binder.GetLocation(), value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::ivec4& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4i(binder.GetLocation(), value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, unsigned int value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1ui(binder.GetLocation(), value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::uvec2& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2ui(binder.GetLocation(), value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::uvec3& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3ui(binder.GetLocation(), value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::uvec4& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4ui(binder.GetLocation(), value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, float value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1f(binder.GetLocation(), value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::vec2& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2f(binder.GetLocation(), value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::vec3& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3f(binder.GetLocation(), value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::vec4& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4f(binder.GetLocation(), value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::mat2x2& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniformMatrix2fv(binder.GetLocation(), 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::mat3x3& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniformMatrix3fv(binder.GetLocation(), 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(const char* name, const glm::mat4x4& value) const
    {
        const UniformBinder binder{ m_program, name };

        if (binder.HasValidLocation())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniformMatrix4fv(binder.GetLocation(), 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    void ShaderProgram::LoadConfig(const nlohmann::json& config)
    {
        #define case_str(__x) case FNV1a_32(__x)

        for (auto it = config.begin(); it != config.end(); ++it)
        {
            const std::string type = it.value()["type"];
            const nlohmann::json value = it.value()["value"];

            switch (FNV1a_32(type.begin(), type.end()))
            {
                case_str("bool"):
                {
                    SetUniform(it.key().data(), value.get<bool>());
                }
                break;
                case_str("bvec2"):
                {
                    SetUniform(it.key().data(), value.get<glm::bvec2>());
                }
                break;
                case_str("bvec3"):
                {
                    SetUniform(it.key().data(), value.get<glm::bvec3>());
                }
                break;
                case_str("bvec4"):
                {
                    SetUniform(it.key().data(), value.get<glm::bvec4>());
                }
                break;
                case_str("int"):
                {
                    SetUniform(it.key().data(), value.get<int>());
                }
                break;
                case_str("ivec2"):
                {
                    SetUniform(it.key().data(), value.get<glm::ivec2>());
                }
                break;
                case_str("ivec3"):
                {
                    SetUniform(it.key().data(), value.get<glm::ivec3>());
                }
                break;
                case_str("ivec4"):
                {
                    SetUniform(it.key().data(), value.get<glm::ivec4>());
                }
                break;
                case_str("uint"):
                {
                    SetUniform(it.key().data(), value.get<unsigned int>());
                }
                break;
                case_str("uvec2"):
                {
                    SetUniform(it.key().data(), value.get<glm::uvec2>());
                }
                break;
                case_str("uvec3"):
                {
                    SetUniform(it.key().data(), value.get<glm::uvec3>());
                }
                break;
                case_str("uvec4"):
                {
                    SetUniform(it.key().data(), value.get<glm::uvec4>());
                }
                break;
                case_str("float"):
                {
                    SetUniform(it.key().data(), value.get<float>());
                }
                break;
                case_str("vec2"):
                {
                    SetUniform(it.key().data(), value.get<glm::vec2>());
                }
                break;
                case_str("vec3"):
                {
                    SetUniform(it.key().data(), value.get<glm::vec3>());
                }
                break;
                case_str("vec4"):
                {
                    SetUniform(it.key().data(), value.get<glm::vec4>());
                }
                break;
                case_str("mat2x2"):
                {
                    SetUniform(it.key().data(), value.get<glm::mat2x2>());
                }
                break;
                case_str("mat3x3"):
                {
                    SetUniform(it.key().data(), value.get<glm::mat3x3>());
                }
                break;
                case_str("mat4x4"):
                {
                    SetUniform(it.key().data(), value.get<glm::mat4x4>());
                }
                break;
            }
        }

        #undef case_str
    }

    void ShaderProgram::LoadConfig(const char* path)
    {
        nlohmann::json config;

        std::ifstream{ path } >> config;

        LoadConfig(config);
    }

    bool ShaderProgram::IsValid() const
    {
        return m_program != 0;
    }

    GLuint ShaderProgram::GetNativeHandle() const
    {
        return m_program;
    }

    #if defined(RV_DEBUG)

    void ShaderProgram::D_ShowShaderProgramEditor(bool* open)
    {
        if (!m_program) return;

        if (ImGui::Begin(("ShaderProgram editor " + std::to_string(m_program)).data(), open))
        {
            static char path[128] = { "test.json" };
            ImGui::InputText("##slPath", path, sizeof(path));

            ImGui::SameLine();
            if (ImGui::Button("Save"))
            {
                D_SaveConfig(path);
            }

            ImGui::SameLine();
            if (ImGui::Button("Load"))
            {
                LoadConfig(path);
            }

            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

            if (ImGui::BeginChild("##uniformsSelectPane", ImVec2(160, 0), true))
            {
                static int selected = -1;
                int i = 0;

                for (auto it = d_uniforms.begin(); it != d_uniforms.end(); ++it)
                {
                    if (ImGui::Selectable(it->first.data(), selected == i))
                    {
                        d_currentElem = it;
                        selected = i;
                    }

                    ++i;
                }
            }
            ImGui::EndChild();

            ImGui::SameLine();

            if (ImGui::BeginChild("##uniformsEditPane", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())))
            {
                if (d_currentElem != d_uniforms.end())
                {
                    std::visit(Overloaded {
                        [this](bool& value) {
                            ImGui::Text("Checkbox");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::bvec2& value) {
                            ImGui::Text("Checkboxes");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[0]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[1]);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::bvec3& value) {
                            ImGui::Text("Checkboxes");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[0]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[1]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[2]);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::bvec4& value) {
                            ImGui::Text("Checkboxes");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[0]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[1]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[2]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[3]);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](int& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt(RV_IMGUI_ID(), &value);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::ivec2& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt2(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::ivec3& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt3(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::ivec4& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt4(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](unsigned& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalar(RV_IMGUI_ID(), ImGuiDataType_U32, &value);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::uvec2& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalarN(RV_IMGUI_ID(), ImGuiDataType_U32, glm::value_ptr(value), 2);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::uvec3& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalarN(RV_IMGUI_ID(), ImGuiDataType_U32, glm::value_ptr(value), 3);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::uvec4& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalarN(RV_IMGUI_ID(), ImGuiDataType_U32, glm::value_ptr(value), 4);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](float& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat(RV_IMGUI_ID(), &value, 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::vec2& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat2(RV_IMGUI_ID(), glm::value_ptr(value), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::vec3& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value), 0.01f);
                            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
                            ImGui::Text("ColorEdit"); ImGui::Spacing();
                            ImGui::ColorEdit3(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::vec4& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat4(RV_IMGUI_ID(), glm::value_ptr(value), 0.01f);
                            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
                            ImGui::Text("ColorEdit"); ImGui::Spacing();
                            ImGui::ColorEdit4(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::mat2x2& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat2(RV_IMGUI_ID(), glm::value_ptr(value[0]), 0.01f);
                            ImGui::DragFloat2(RV_IMGUI_ID(), glm::value_ptr(value[1]), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::mat3x3& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value[0]), 0.01f);
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value[1]), 0.01f);
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value[2]), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](glm::mat4x4& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat4(RV_IMGUI_ID(), glm::value_ptr(value[0]), 0.01f);
                            ImGui::DragFloat4(RV_IMGUI_ID(), glm::value_ptr(value[1]), 0.01f);
                            ImGui::DragFloat4(RV_IMGUI_ID(), glm::value_ptr(value[2]), 0.01f);
                            ImGui::DragFloat4(RV_IMGUI_ID(), glm::value_ptr(value[3]), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                    }, d_currentElem->second);
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }

    void ShaderProgram::D_SaveConfig(nlohmann::json& config) const
    {
        for (const auto& [ k, v ] : d_uniforms)
        {
            nlohmann::json& j = config[k];

            std::visit([&j, type = d_uniTypeNames[v.index()]](const auto& value) {
                j["value"] = value;
                j["type"] = type;
            }, v);
        }
    }

    void ShaderProgram::D_SaveConfig(const char* path) const
    {
        nlohmann::json config;

        D_SaveConfig(config);

        std::ofstream{ path } << std::setw(4) << config;
    }

    #endif

    void ShaderProgram::M_Destroy()
    {
        if (m_program)
        {
        	glDeleteProgram(m_program);

            #if defined(RV_DEBUG)
            {
                d_uniforms.clear();
            	d_currentElem = d_uniforms.end();
            }
            #endif
        }
    }

    bool ShaderProgram::M_FinishLinking(NativeHandle_t program)
    {
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (success)
        {
            M_Destroy();

            m_program = program;

            #if defined(RV_DEBUG)
            {
                GLint count;
                GLint size;
                GLenum type;
                GLchar name[64];

                glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &count);

                for (GLint i = 0; i < count; ++i)
                {
                    glGetActiveUniform(m_program, i, sizeof(name), nullptr, &size, &type, name);

                    switch (type)
                    {
                        case GL_BOOL:
                        {
                            int value;
                            glGetUniformiv(m_program, i, &value);
                            d_uniforms.emplace(name, static_cast<bool>(value));
                        }
                        break;
                        case GL_BOOL_VEC2:
                        {
                            glm::ivec2 value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, glm::bvec2{ value });
                        }
                        break;
                        case GL_BOOL_VEC3:
                        {
                            glm::ivec3 value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, glm::bvec3{ value });
                        }
                        break;
                        case GL_BOOL_VEC4:
                        {
                            glm::ivec4 value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, glm::bvec4{ value });
                        }
                        break;
                        case GL_INT:
                        {
                            int value;
                            glGetUniformiv(m_program, i, &value);
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_INT_VEC2:
                        {
                            glm::ivec2 value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_INT_VEC3:
                        {
                            glm::ivec3 value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_INT_VEC4:
                        {
                            glm::ivec4 value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_UNSIGNED_INT:
                        {
                            unsigned value;
                            glGetUniformuiv(m_program, i, &value);
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_UNSIGNED_INT_VEC2:
                        {
                            glm::uvec2 value;
                            glGetUniformuiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_UNSIGNED_INT_VEC3:
                        {
                            glm::uvec3 value;
                            glGetUniformuiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_UNSIGNED_INT_VEC4:
                        {
                            glm::uvec4 value;
                            glGetUniformuiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT:
                        {
                            float value;
                            glGetUniformfv(m_program, i, &value);
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT_VEC2:
                        {
                            glm::vec2 value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT_VEC3:
                        {
                            glm::vec3 value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT_VEC4:
                        {
                            glm::vec4 value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT_MAT2:
                        {
                            glm::mat2x2 value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT_MAT3:
                        {
                            glm::mat3x3 value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                        case GL_FLOAT_MAT4:
                        {
                            glm::mat4x4 value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;
                    }
                }
            }
            #endif

            return true;
        }
        else
        {
            #if defined(RV_DEBUG)
            {
                GLchar infoLog[512];
                glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);

                // TODO better log 'infoLog'
                std::fprintf(stderr, "%s", infoLog);
            }
            #endif

            glDeleteProgram(program);

            return false;
        }
    }
}
