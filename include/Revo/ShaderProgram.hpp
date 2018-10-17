#pragma once

// Revo
#include <Revo/Shader.hpp>

// glm
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

// nlohmann Json
#include <nlohmann/json_fwd.hpp>

#if defined(M2_DEBUG)
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
		ShaderProgram(const ShaderProgram&) = delete;

		///
		ShaderProgram& operator = (const ShaderProgram&) = delete;

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
		bool SetUniform(const char* name, bool value) const;

		///
		bool SetUniform(const char* name, const glm::bvec2& value) const;

		///
		bool SetUniform(const char* name, const glm::bvec3& value) const;

		///
		bool SetUniform(const char* name, const glm::bvec4& value) const;

		///
		bool SetUniform(const char* name, int value) const;

		///
		bool SetUniform(const char* name, const glm::ivec2& value) const;

		///
		bool SetUniform(const char* name, const glm::ivec3& value) const;

		///
		bool SetUniform(const char* name, const glm::ivec4& value) const;

		///
		bool SetUniform(const char* name, unsigned int value) const;

		///
		bool SetUniform(const char* name, const glm::uvec2& value) const;

		///
		bool SetUniform(const char* name, const glm::uvec3& value) const;

		///
		bool SetUniform(const char* name, const glm::uvec4& value) const;

		///
		bool SetUniform(const char* name, float value) const;

		///
		bool SetUniform(const char* name, const glm::vec2& value) const;

		///
		bool SetUniform(const char* name, const glm::vec3& value) const;

		///
		bool SetUniform(const char* name, const glm::vec4& value) const;

		///
		bool SetUniform(const char* name, const glm::mat2x2& value) const;

		///
		bool SetUniform(const char* name, const glm::mat3x3& value) const;

		///
		bool SetUniform(const char* name, const glm::mat4x4& value) const;

		///
		void LoadConfig(const nlohmann::json& config);

		///
		void LoadConfig(const char* path);

		///
		bool IsValid() const;

		///
		NativeHandle_t GetNativeHandle() const;

		#if defined(M2_DEBUG)

		using UniKey_t     = std::string;
		using UniVariant_t = std::variant<bool, glm::bvec2, glm::bvec3, glm::bvec4, int, glm::ivec2, glm::ivec3, glm::ivec4, unsigned, glm::uvec2, glm::uvec3, glm::uvec4, float, glm::vec2, glm::vec3, glm::vec4, glm::mat2x2, glm::mat3x3, glm::mat4x4>;
		using UniMap_t     = std::map<UniKey_t, UniVariant_t>;

		///
		void D_ShowShaderProgramEditor(bool* open);

		///
		void D_SaveConfig(nlohmann::json& config) const;

		///
		void D_SaveConfig(const char* path) const;

		mutable UniMap_t d_uniforms;
		UniMap_t::iterator d_currentElem = d_uniforms.end();
		const char* const d_uniTypeNames[std::variant_size_v<UniVariant_t>] = { "bool", "bvec2", "bvec3", "bvec4", "int", "ivec2", "ivec3", "ivec4", "uint", "uvec2", "uvec3", "uvec4", "float", "vec2", "vec3", "vec4", "mat2x2", "mat3x3", "mat4x4" };

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

		#if defined(M2_DEBUG)
		{
			// TODO better logging
			std::printf("Sent shaders must be valid ones\n");
		}
		#endif

		return false;
	}

}
