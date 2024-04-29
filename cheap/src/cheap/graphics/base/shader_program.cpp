#include "pch.h"
#include "shader_program.h"

#include <fstream>
#include <sstream>
#include <glm/ext/matrix_transform.hpp>

namespace cheap {

	// orthogonal projection
	shader_program::shader_program(
		const char* aVertex_path,
		const char* aFragment_path,
		const float aAspect)
		:
		mId(glCreateProgram()),
		mOpacity(UNIFORM_OPAQUE),
		mProjection(transform::get_orthogonal_projection(aAspect)),
		mView(transform::get_view()),
		mTranslate(transform::get_identity_matrix()),
		mRotate(transform::get_identity_matrix()),
		mScale(transform::get_identity_matrix())
	{
		create_program(aVertex_path, aFragment_path);
		bind();
		bind_opacity();
		bind_projection();
		bind_view();
		bind_translate();
		bind_rotate();
		bind_scale();
	}



	void shader_program::bind() const
	{
		glUseProgram(mId);
	}

	void shader_program::unbind()
	{
		glUseProgram(0);
	}

	void shader_program::set_bool(const std::string& aName, const bool aValue) const
	{
		glUniform1i(glGetUniformLocation(mId, aName.c_str()), static_cast<int>(aValue));
	}

	void shader_program::set_int(const std::string& aName, const int aValue) const
	{
		glUniform1i(glGetUniformLocation(mId, aName.c_str()), aValue);
	}

	void shader_program::set_float(const std::string& aName, const float aValue) const
	{
		glUniform1f(glGetUniformLocation(mId, aName.c_str()), aValue);
	}

	void shader_program::set_vec2(const std::string& aName, const glm::vec2& aValue) const
	{
		glUniform2fv(glGetUniformLocation(mId, aName.c_str()), 1, &aValue[0]);
	}

	void shader_program::set_vec2(const std::string& aName, const float aX, const float aY) const
	{
		glUniform2f(glGetUniformLocation(mId, aName.c_str()), aX, aY);
	}

	void shader_program::set_vec3(const std::string& aName, const glm::vec3& aValue) const
	{
		glUniform3fv(glGetUniformLocation(mId, aName.c_str()), 1, &aValue[0]);
	}

	void shader_program::set_vec3(const std::string& aName, const float aX, const float aY, const float aZ) const
	{
		glUniform3f(glGetUniformLocation(mId, aName.c_str()), aX, aY, aZ);
	}

	void shader_program::set_vec4(const std::string& aName, const glm::vec4& aValue) const
	{
		glUniform4fv(glGetUniformLocation(mId, aName.c_str()), 1, &aValue[0]);
	}

	void shader_program::set_vec4(const std::string& aName, const float aX, const float aY, const float aZ, const float aW) const
	{
		glUniform4f(glGetUniformLocation(mId, aName.c_str()), aX, aY, aZ, aW);
	}

	void shader_program::set_mat2(const std::string& aName, const glm::mat2& aMat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(mId, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}

	void shader_program::set_mat3(const std::string& aName, const glm::mat3& aMat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(mId, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}

	void shader_program::set_mat4(const std::string& aName, const glm::mat4& aMat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(mId, aName.c_str()), 1, GL_FALSE, &aMat[0][0]);
	}

	void shader_program::check_compile_errors(const GLuint aShader, const unsigned aType)
	{
		GLint success;

		if (aType == 0) {
			glGetProgramiv(aShader, GL_LINK_STATUS, &success);
		} else {
			glGetShaderiv(aShader, GL_COMPILE_STATUS, &success);
		}

		if (success == GL_FALSE) {
			GLchar info_log[1024];
			if (aType == GL_VERTEX_SHADER) {
				glGetShaderInfoLog(aShader, 1024, NULL, info_log);
				LOG_INFO("ERROR::SHADER_COMPILATION_ERROR of type: " << "Vertex Shader" << "\n" << info_log << "\n -- --------------------------------------------------- -- ");
			} else if (aType == GL_FRAGMENT_SHADER) {
				glGetShaderInfoLog(aShader, 1024, NULL, info_log);
				LOG_INFO("ERROR::SHADER_COMPILATION_ERROR of type: " << "Fragment Shader" << "\n" << info_log << "\n -- --------------------------------------------------- -- ");
			}
		}

	}
}
