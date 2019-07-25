#include <Revo/Graphics/ShaderProgram.hpp>

// Revo
#include <Revo/ImGui/ImGuiContext.hpp>
#include <Revo/Utility/FNV.hpp>
#include <Revo/Utility/glmSerializers.hpp>
#include <Revo/Utility/Overloaded.hpp>

// C++
#include <fstream>
#include <iomanip>

// glm
#include <glm/gtc/type_ptr.hpp>

namespace rv
{
    ShaderProgram::ShaderProgram()
        : m_program { 0 }
        , m_uniformsLocation {}
    {

    }

    ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept
        : m_program { rhs.m_program }
        , m_uniformsLocation { std::move(rhs.m_uniformsLocation) }
    {
        rhs.m_program = 0;
    }

    ShaderProgram& ShaderProgram::operator = (ShaderProgram&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_program = rhs.m_program;
            m_uniformsLocation = std::move(rhs.m_uniformsLocation);

            rhs.m_program = 0;
        }

        return *this;
    }

    ShaderProgram::~ShaderProgram()
    {
        M_Destroy();
    }

    bool ShaderProgram::LinkShaders(std::initializer_list<Shader*> il)
    {
        if (std::all_of(il.begin(), il.end(), [](auto const ptr) { return ptr->IsValid(); }))
        {
            NativeHandle_t program = glCreateProgram();

            for (auto const ptr : il)
            {
                glAttachShader(program, ptr->GetNativeHandle());
            }

            glLinkProgram(program);

            for (auto const ptr : il)
            {
                glDetachShader(program, ptr->GetNativeHandle());
            }

            return M_FinishLinking(program);
        }

        #if defined(RV_DEBUG)
        {
            // TODO better logging
            std::fprintf(stderr, "Sent shaders must be valid ones\n");
        }
        #endif

        return false;
    }

    void ShaderProgram::UseProgram() const
    {
        glUseProgram(m_program);
    }

    bool ShaderProgram::SetUniform(char const* name, bool value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1i(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2b const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2i(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3b const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3i(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4b const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4i(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, int32_t value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1i(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2i const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2i(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3i const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3i(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4i const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4i(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, uint32_t value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1ui(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2u const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2ui(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3u const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3ui(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4u const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4ui(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, float value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform1f(it->second, value);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec2f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform2f(it->second, value.x, value.y);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec3f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform3f(it->second, value.x, value.y, value.z);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Vec4f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniform4f(it->second, value.x, value.y, value.z, value.w);

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Mat2x2f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniformMatrix2fv(it->second, 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Mat3x3f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    bool ShaderProgram::SetUniform(char const* name, Mat4x4f const& value) const
    {
        auto const it = m_uniformsLocation.find(FNV1a_32(name));

        if (it != m_uniformsLocation.end())
        {
            #if defined(RV_DEBUG)
            {
                d_uniforms[name] = value;
            }
            #endif

            glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(value));

            return true;
        }

        return false;
    }

    void ShaderProgram::LoadConfig(nlohmann::json const& config)
    {
        #define case_str(__x) case FNV1a_32(__x)

        for (auto it = config.begin(); it != config.end(); ++it)
        {
            std::string const type = it.value()["type"];
            nlohmann::json const value = it.value()["value"];

            switch (FNV1a_32(type.begin(), type.end()))
            {
                case_str("bool"):
                {
                    SetUniform(it.key().data(), value.get<bool>());
                }
                break;

                case_str("bvec2"):
                {
                    SetUniform(it.key().data(), value.get<Vec2b>());
                }
                break;

                case_str("bvec3"):
                {
                    SetUniform(it.key().data(), value.get<Vec3b>());
                }
                break;

                case_str("bvec4"):
                {
                    SetUniform(it.key().data(), value.get<Vec4b>());
                }
                break;

                case_str("int"):
                {
                    SetUniform(it.key().data(), value.get<int32_t>());
                }
                break;

                case_str("ivec2"):
                {
                    SetUniform(it.key().data(), value.get<Vec2i>());
                }
                break;

                case_str("ivec3"):
                {
                    SetUniform(it.key().data(), value.get<Vec3i>());
                }
                break;

                case_str("ivec4"):
                {
                    SetUniform(it.key().data(), value.get<Vec4i>());
                }
                break;

                case_str("uint"):
                {
                    SetUniform(it.key().data(), value.get<uint32_t>());
                }
                break;

                case_str("uvec2"):
                {
                    SetUniform(it.key().data(), value.get<Vec2u>());
                }
                break;

                case_str("uvec3"):
                {
                    SetUniform(it.key().data(), value.get<Vec3u>());
                }
                break;

                case_str("uvec4"):
                {
                    SetUniform(it.key().data(), value.get<Vec4u>());
                }
                break;

                case_str("float"):
                {
                    SetUniform(it.key().data(), value.get<float>());
                }
                break;

                case_str("vec2"):
                {
                    SetUniform(it.key().data(), value.get<Vec2f>());
                }
                break;

                case_str("vec3"):
                {
                    SetUniform(it.key().data(), value.get<Vec3f>());
                }
                break;

                case_str("vec4"):
                {
                    SetUniform(it.key().data(), value.get<Vec4f>());
                }
                break;

                case_str("mat2x2"):
                {
                    SetUniform(it.key().data(), value.get<Mat2x2f>());
                }
                break;

                case_str("mat3x3"):
                {
                    SetUniform(it.key().data(), value.get<Mat3x3f>());
                }
                break;

                case_str("mat4x4"):
                {
                    SetUniform(it.key().data(), value.get<Mat4x4f>());
                }
                break;
            }
        }

        #undef case_str
    }

    void ShaderProgram::LoadConfig(char const* path)
    {
        nlohmann::json config;

        std::ifstream{ path } >> config;

        LoadConfig(config);
    }

    bool ShaderProgram::IsValid() const
    {
        return m_program;
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

            if (ImGui::BeginChild("##uniformsSelectPane", ImVec2{ 160, 0 }, true))
            {
                static int32_t selected = -1;
                int32_t i = 0;

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

            if (ImGui::BeginChild("##uniformsEditPane", ImVec2{ 0, -ImGui::GetFrameHeightWithSpacing() }))
            {
                if (d_currentElem != d_uniforms.end())
                {
                    std::visit(Overloaded {
                        [this](bool& value) {
                            ImGui::Text("Checkbox");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec2b& value) {
                            ImGui::Text("Checkboxes");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[0]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[1]);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec3b& value) {
                            ImGui::Text("Checkboxes");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[0]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[1]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[2]);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec4b& value) {
                            ImGui::Text("Checkboxes");
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[0]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[1]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[2]); ImGui::SameLine();
                            ImGui::Checkbox(RV_IMGUI_ID(), &value[3]);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](int32_t& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt(RV_IMGUI_ID(), &value);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec2i& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt2(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec3i& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt3(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec4i& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputInt4(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](uint32_t& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalar(RV_IMGUI_ID(), ImGuiDataType_U32, &value);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec2u& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalarN(RV_IMGUI_ID(), ImGuiDataType_U32, glm::value_ptr(value), 2);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec3u& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalarN(RV_IMGUI_ID(), ImGuiDataType_U32, glm::value_ptr(value), 3);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec4u& value) {
                            ImGui::Text("Input"); ImGui::Spacing();
                            ImGui::InputScalarN(RV_IMGUI_ID(), ImGuiDataType_U32, glm::value_ptr(value), 4);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](float& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat(RV_IMGUI_ID(), &value, 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec2f& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat2(RV_IMGUI_ID(), glm::value_ptr(value), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec3f& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value), 0.01f);
                            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
                            ImGui::Text("ColorEdit"); ImGui::Spacing();
                            ImGui::ColorEdit3(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Vec4f& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat4(RV_IMGUI_ID(), glm::value_ptr(value), 0.01f);
                            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
                            ImGui::Text("ColorEdit"); ImGui::Spacing();
                            ImGui::ColorEdit4(RV_IMGUI_ID(), glm::value_ptr(value));
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Mat2x2f& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat2(RV_IMGUI_ID(), glm::value_ptr(value[0]), 0.01f);
                            ImGui::DragFloat2(RV_IMGUI_ID(), glm::value_ptr(value[1]), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Mat3x3f& value) {
                            ImGui::Text("DragInput"); ImGui::Spacing();
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value[0]), 0.01f);
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value[1]), 0.01f);
                            ImGui::DragFloat3(RV_IMGUI_ID(), glm::value_ptr(value[2]), 0.01f);
                            SetUniform(d_currentElem->first.data(), value);
                        },
                        [this](Mat4x4f& value) {
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
        static char const* uniTypeNames[] = {
            "bool", "bvec2", "bvec3", "bvec4",
            "int", "ivec2", "ivec3", "ivec4",
            "uint", "uvec2", "uvec3", "uvec4",
            "float", "vec2", "vec3", "vec4",
            "mat2x2", "mat3x3", "mat4x4"
        };

        for (auto const& [ k, v ] : d_uniforms)
        {
            nlohmann::json& j = config[k];

            std::visit([&j, type = uniTypeNames[v.index()]](auto const& value) {
                j["value"] = value;
                j["type"] = type;
            }, v);
        }
    }

    void ShaderProgram::D_SaveConfig(char const* path) const
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
        int32_t success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (success)
        {
            M_Destroy();

            m_program = program;

            #if defined(RV_DEBUG)
            {
                int32_t count;
                int32_t size;
                GLenum type;
                char name[64];

                glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &count);

                for (int32_t i = 0; i < count; ++i)
                {
                    glGetActiveUniform(m_program, i, sizeof(name), nullptr, &size, &type, name);

                    m_uniformsLocation.emplace(FNV1a_32(name), i);

                    switch (type)
                    {
                        case GL_BOOL:
                        {
                            int32_t value;
                            glGetUniformiv(m_program, i, &value);
                            d_uniforms.emplace(name, static_cast<bool>(value));
                        }
                        break;

                        case GL_BOOL_VEC2:
                        {
                            Vec2i value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, Vec2b{ value });
                        }
                        break;

                        case GL_BOOL_VEC3:
                        {
                            Vec3i value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, Vec3b{ value });
                        }
                        break;

                        case GL_BOOL_VEC4:
                        {
                            Vec4i value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, Vec4b{ value });
                        }
                        break;

                        case GL_INT:
                        {
                            int32_t value;
                            glGetUniformiv(m_program, i, &value);
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_INT_VEC2:
                        {
                            Vec2i value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_INT_VEC3:
                        {
                            Vec3i value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_INT_VEC4:
                        {
                            Vec4i value;
                            glGetUniformiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_UNSIGNED_INT:
                        {
                            uint32_t value;
                            glGetUniformuiv(m_program, i, &value);
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_UNSIGNED_INT_VEC2:
                        {
                            Vec2u value;
                            glGetUniformuiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_UNSIGNED_INT_VEC3:
                        {
                            Vec3u value;
                            glGetUniformuiv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_UNSIGNED_INT_VEC4:
                        {
                            Vec4u value;
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
                            Vec2f value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_FLOAT_VEC3:
                        {
                            Vec3f value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_FLOAT_VEC4:
                        {
                            Vec4f value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_FLOAT_MAT2:
                        {
                            Mat2x2f value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_FLOAT_MAT3:
                        {
                            Mat3x3f value;
                            glGetUniformfv(m_program, i, glm::value_ptr(value));
                            d_uniforms.emplace(name, value);
                        }
                        break;

                        case GL_FLOAT_MAT4:
                        {
                            Mat4x4f value;
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
                char infoLog[512];
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
