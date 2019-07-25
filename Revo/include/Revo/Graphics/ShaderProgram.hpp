#pragma once

// Revo
#include <Revo/Graphics/Shader.hpp>
#include <Revo/Math/Matrix.hpp>
#include <Revo/Math/Vector.hpp>
#include <Revo/Utility/FNV.hpp>

// C++
#include <map>

// nlohmann Json
#include <nlohmann/json_fwd.hpp>

#if defined(RV_DEBUG)
#   include <string>
#   include <variant>
#endif

namespace rv
{
    ///
    class ShaderProgram
    {
    public:

        using NativeHandle_t     = uint32_t;
        using UniformsLocation_t = std::map<Hash32_t, int32_t>;

        ///
        ShaderProgram();

        ///
        ShaderProgram(ShaderProgram const&) = delete;

        ///
        ShaderProgram& operator = (ShaderProgram const&) = delete;

        ///
        ShaderProgram(ShaderProgram&& rhs) noexcept;

        ///
        ShaderProgram& operator = (ShaderProgram&& rhs) noexcept;

        ///
        ~ShaderProgram();

        ///
        bool LinkShaders(std::initializer_list<Shader*> il);

        ///
        void UseProgram() const;

        ///
        bool SetUniform(char const* name, bool value) const;

        ///
        bool SetUniform(char const* name, Vec2b const& value) const;

        ///
        bool SetUniform(char const* name, Vec3b const& value) const;

        ///
        bool SetUniform(char const* name, Vec4b const& value) const;

        ///
        bool SetUniform(char const* name, int32_t value) const;

        ///
        bool SetUniform(char const* name, Vec2i const& value) const;

        ///
        bool SetUniform(char const* name, Vec3i const& value) const;

        ///
        bool SetUniform(char const* name, Vec4i const& value) const;

        ///
        bool SetUniform(char const* name, uint32_t value) const;

        ///
        bool SetUniform(char const* name, Vec2u const& value) const;

        ///
        bool SetUniform(char const* name, Vec3u const& value) const;

        ///
        bool SetUniform(char const* name, Vec4u const& value) const;

        ///
        bool SetUniform(char const* name, float value) const;

        ///
        bool SetUniform(char const* name, Vec2f const& value) const;

        ///
        bool SetUniform(char const* name, Vec3f const& value) const;

        ///
        bool SetUniform(char const* name, Vec4f const& value) const;

        ///
        bool SetUniform(char const* name, Mat2x2f const& value) const;

        ///
        bool SetUniform(char const* name, Mat3x3f const& value) const;

        ///
        bool SetUniform(char const* name, Mat4x4f const& value) const;

        ///
        void LoadConfig(nlohmann::json const& config);

        ///
        void LoadConfig(char const* path);

        ///
        bool IsValid() const;

        ///
        NativeHandle_t GetNativeHandle() const;

        #if defined(RV_DEBUG)

        using UniMap_t = std::map<std::string, std::variant<bool, Vec2b, Vec3b, Vec4b, int32_t, Vec2i, Vec3i, Vec4i, uint32_t, Vec2u, Vec3u, Vec4u, float, Vec2f, Vec3f, Vec4f, Mat2x2f, Mat3x3f, Mat4x4f>>;

        ///
        void D_ShowShaderProgramEditor(bool* open);

        ///
        void D_SaveConfig(nlohmann::json& config) const;

        ///
        void D_SaveConfig(char const* path) const;

        mutable UniMap_t d_uniforms;
        UniMap_t::iterator d_currentElem = d_uniforms.end();

        #endif

    private:

        ///
        void M_Destroy();

        ///
        bool M_FinishLinking(NativeHandle_t program);

        NativeHandle_t m_program;
        UniformsLocation_t m_uniformsLocation;
    };
}
