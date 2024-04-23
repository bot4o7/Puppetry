#include "pch.h"
#include "shader_test.h"
#include "../utils/utils.h"

namespace cheap {
	shader_test::shader_test(const char* vertex_path, const char* fragment_path)
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
			v_shader_file.open(vertex_path);
			f_shader_file.open(fragment_path);
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
		check_compile_errors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &f_shader_code, NULL);
		glCompileShader(fragment);
		check_compile_errors(fragment, "FRAGMENT");
		// shader Program
		id_ = glCreateProgram();
		glAttachShader(id_, vertex);
		glAttachShader(id_, fragment);
		glLinkProgram(id_);
		check_compile_errors(id_, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void shader_test::use() const
	{
		glUseProgram(id_);
	}

	void shader_test::set_bool(const std::string& name, const bool value) const
	{
		glUniform1i(glGetUniformLocation(id_, name.c_str()), static_cast<int>(value));
	}

	void shader_test::set_int(const std::string& name, const int value) const
	{
		glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
	}

	void shader_test::set_float(const std::string& name, const float value) const
	{
		glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
	}

	void shader_test::set_vec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
	}

	void shader_test::set_vec2(const std::string& name, const float x, const float y) const
	{
		glUniform2f(glGetUniformLocation(id_, name.c_str()), x, y);
	}

	void shader_test::set_vec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
	}

	void shader_test::set_vec3(const std::string& name, const float x, const float y, const float z) const
	{
		glUniform3f(glGetUniformLocation(id_, name.c_str()), x, y, z);
	}

	void shader_test::set_vec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
	}

	void shader_test::set_vec4(const std::string& name, const float x, const float y, const float z, const float w) const
	{
		glUniform4f(glGetUniformLocation(id_, name.c_str()), x, y, z, w);
	}

	void shader_test::set_mat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void shader_test::set_mat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void shader_test::set_mat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void shader_test::check_compile_errors(const GLuint shader, const std::string& type)
	{
		GLint  success;
		GLchar info_log[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		} else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, nullptr, info_log);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}
