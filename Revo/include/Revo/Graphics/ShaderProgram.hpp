#pragma once

// Revo
#include <Revo/Graphics/Shader.hpp>
#include <Revo/Utility/Matrix.hpp>
#include <Revo/Utility/Vector.hpp>

// nlohmann Json
#include <nlohmann/json_fwd.hpp>

#if defined(RV_DEBUG)
#   include <map>
#   include <string>
#   include <variant>
#endif

namespace rv
{
	///
	class ShaderProgram
	{
	public:

		using NativeHandle_t = GLuint;

		///
		ShaderProgram() = default;

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
		template <typename... Ts>
		bool LinkShaders(Ts&&... shaders);

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
		bool SetUniform(char const* name, int value) const;

		///
		bool SetUniform(char const* name, Vec2i const& value) const;

		///
		bool SetUniform(char const* name, Vec3i const& value) const;

		///
		bool SetUniform(char const* name, Vec4i const& value) const;

		///
		bool SetUniform(char const* name, unsigned int value) const;

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

		using UniKey_t     = std::string;
		using UniVariant_t = std::variant<bool, Vec2b, Vec3b, Vec4b, int, Vec2i, Vec3i, Vec4i, unsigned, Vec2u, Vec3u, Vec4u, float, Vec2f, Vec3f, Vec4f, Mat2x2f, Mat3x3f, Mat4x4f>;
		using UniMap_t     = std::map<UniKey_t, UniVariant_t>;

		///
		void D_ShowShaderProgramEditor(bool* open);

		///
		void D_SaveConfig(nlohmann::json& config) const;

		///
		void D_SaveConfig(char const* path) const;

		mutable UniMap_t d_uniforms;
		UniMap_t::iterator d_currentElem = d_uniforms.end();
		char const* const d_uniTypeNames[std::variant_size_v<UniVariant_t>] = { "bool", "bvec2", "bvec3", "bvec4", "int", "ivec2", "ivec3", "ivec4", "uint", "uvec2", "uvec3", "uvec4", "float", "vec2", "vec3", "vec4", "mat2x2", "mat3x3", "mat4x4" };

		#endif

	private:

		///
		void M_Destroy();

		///
		bool M_FinishLinking(NativeHandle_t program);

		NativeHandle_t m_program = 0;
	};

	template <typename... Ts>
	bool ShaderProgram::LinkShaders(Ts&&... shaders)
	{
		static_assert((std::is_same_v<Shader, std::remove_cv_t<std::remove_reference_t<Ts>>> && ...), "All Ts must be exactly rv::Shader");

		if ((true && ... && shaders.IsValid()))
		{
			NativeHandle_t program = glCreateProgram();

			(glAttachShader(program, shaders.GetNativeHandle()), ...);

			glLinkProgram(program);

			(glDetachShader(program, shaders.GetNativeHandle()), ...);

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
}
