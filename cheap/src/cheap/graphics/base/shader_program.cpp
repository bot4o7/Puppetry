#include "pch.h"
#include "shader_program.h"

#include <fstream>
#include <sstream>
#include <glm/ext/matrix_transform.hpp>

namespace cheap {
	shader_program::shader_program(const char* aVertex_path, const char* aFragment_path)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string   vertex_code;
		std::string   fragment_code;
		std::ifstream v_shader_file;
		std::ifstream f_shader_file;
		// ensure ifstream objects can throw exceptions:
		v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open files
			v_shader_file.open(aVertex_path);
			f_shader_file.open(aFragment_path);
			std::stringstream v_shader_stream, f_shader_stream;
			// read file's buffer contents into streams
			v_shader_stream << v_shader_file.rdbuf();
			f_shader_stream << f_shader_file.rdbuf();
			// close file handlers
			v_shader_file.close();
			f_shader_file.close();
			// convert stream into string
			vertex_code = v_shader_stream.str();
			fragment_code = f_shader_stream.str();
		} catch (std::ifstream::failure& e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		const char* v_shader_code = vertex_code.c_str();
		const char* f_shader_code = fragment_code.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &v_shader_code, nullptr);
		glCompileShader(vertex);
		check_compile_errors(vertex, GL_VERTEX_SHADER);
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &f_shader_code, nullptr);
		glCompileShader(fragment);
		check_compile_errors(fragment, GL_FRAGMENT_SHADER);
		// shader Program
		mId = glCreateProgram();
		glAttachShader(mId, vertex);
		glAttachShader(mId, fragment);
		glLinkProgram(mId);
		check_compile_errors(mId);
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void shader_program::bind() const
	{
		glUseProgram(mId);
	}

	void shader_program::unbind()
	{
		glUseProgram(0);
	}

	void shader_program::set_tex(int tex_slot) const
	{
		setInt(FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME, tex_slot);
	}

	void shader_program::use(const glm::mat4& aTransform, const int aTexture_slot) const
	{
		bind();
		set_transform(aTransform);
		set_tex(aTexture_slot);
	}

	void shader_program::set_transform(const glm::mat4& aMat) const
	{
		setMat4(VERTEX_SHADER_GLSL_UNIFORM_TRANSFORM_MATRIX_NAME, aMat);
	}

	void shader_program::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
	}

	void shader_program::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
	}

	void shader_program::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
	}

	void shader_program::setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(mId, name.c_str()), 1, &value[0]);
	}

	void shader_program::setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(mId, name.c_str()), x, y);
	}

	void shader_program::setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(mId, name.c_str()), 1, &value[0]);
	}

	void shader_program::setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(mId, name.c_str()), x, y, z);
	}

	void shader_program::setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(mId, name.c_str()), 1, &value[0]);
	}

	void shader_program::setVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(mId, name.c_str()), x, y, z, w);
	}

	void shader_program::setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void shader_program::setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void shader_program::setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void shader_program::check_compile_errors(const GLuint aShader, unsigned aType)
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
