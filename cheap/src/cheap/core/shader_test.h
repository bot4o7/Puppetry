#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace cheap {
	class shader_test
	{
	public:
		unsigned int id_;
		// constructor generates the shader on the fly
		// ------------------------------------------------------------------------
		shader_test(const char* vertex_path, const char* fragment_path);
		// activate the shader
		// ------------------------------------------------------------------------
		void use() const;
		// utility uniform functions
		// ------------------------------------------------------------------------
		void set_bool(const std::string& name, const bool value) const;
		// ------------------------------------------------------------------------
		void set_int(const std::string& name, const int value) const;
		// ------------------------------------------------------------------------
		void set_float(const std::string& name, const float value) const;
		// ------------------------------------------------------------------------
		void set_vec2(const std::string& name, const glm::vec2& value) const;

		void set_vec2(const std::string& name, const float x, const float y) const;
		// ------------------------------------------------------------------------
		void set_vec3(const std::string& name, const glm::vec3& value) const;

		void set_vec3(const std::string& name, const float x, const float y, const float z) const;
		// ------------------------------------------------------------------------
		void set_vec4(const std::string& name, const glm::vec4& value) const;

		void set_vec4(const std::string& name, const float x, const float y, const float z, const float w) const;
		// ------------------------------------------------------------------------
		void set_mat2(const std::string& name, const glm::mat2& mat) const;
		// ------------------------------------------------------------------------
		void set_mat3(const std::string& name, const glm::mat3& mat) const;
		// ------------------------------------------------------------------------
		void set_mat4(const std::string& name, const glm::mat4& mat) const;

	private:
		// utility function for checking shader compilation/linking errors.
		// ------------------------------------------------------------------------
		static void check_compile_errors(const GLuint shader, const std::string& type);
	};
}
