#include "pch.h"
#include "shader_program.h"

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

	shader_program::~shader_program() = default;

	void shader_program::create_program(const char* aVertex_path, const char* aFragment_path) const
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
		glAttachShader(mId, vertex);
		glAttachShader(mId, fragment);
		glLinkProgram(mId);
		check_compile_errors(mId);
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void shader_program::use(const int aTexture_slot) const
	{
		bind();
		set_texture_slot(aTexture_slot);
	}

	void shader_program::bind_projection() const
	{
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_NAME, mProjection);
	}

	void shader_program::set_projection_to_orthogonal(const float aLeft, const float aRight, const float aBottom,
		const float aTop, const float aNear, const float aFar)
	{
		mProjection = transform::get_orthogonal_projection(
			aLeft,
			aRight,
			aBottom,
			aTop,
			aNear,
			aFar
		);
		bind_projection();
	}

	void shader_program::set_projection_to_perspective(const float aFov_degree, const int aAspect_numerator,
		const int aAspect_denominator, const float aNear, const float aFar)
	{
		mProjection = transform::get_perspective_projection(
			aFov_degree,
			aAspect_numerator,
			aAspect_denominator,
			aNear, aFar);
		bind_projection();
	}

	void shader_program::bind_view() const
	{
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_VIEW_NAME, mView);
	}

	void shader_program::set_view(const float aPos_x, const float aPos_y, const float aPos_z, const float aLook_x,
		const float aLook_y, const float aLook_z)
	{
		mView = transform::get_view(
			aPos_x,
			aPos_y,
			aPos_z,
			aLook_x,
			aLook_y,
			aLook_z);
		bind_view();
	}

	void shader_program::set_transform() const
	{
		bind();
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_TRANSLATE_NAME, mTranslate);
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_ROTATE_NAME, mRotate);
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, mScale);
		set_float(FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME, mOpacity);
	}

	void shader_program::use_transform(const int aTexture_slot, const glm::mat4& aTranslate, const glm::mat4& aRotate,
		const glm::mat4& aScale, const float aOpacity)
	{
		bind();
		set_translate(aTranslate);
		set_rotate(aRotate);
		set_scale(aScale);
		set_texture_slot(aTexture_slot);
		set_opacity(aOpacity);
	}

	void shader_program::bind_translate() const
	{
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_TRANSLATE_NAME, mTranslate);
	}

	void shader_program::set_translate(const glm::mat4& aMat)
	{
		mTranslate = aMat;
		bind_translate();
	}

	void shader_program::set_rotate(const glm::mat4& aMat)
	{
		mRotate = aMat;
		bind_rotate();
	}

	void shader_program::bind_rotate() const
	{
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_ROTATE_NAME, mRotate);
	}

	void shader_program::set_scale(const glm::mat4& aMat)
	{
		mScale = aMat;
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, mScale);
	}

	void shader_program::bind_scale() const
	{
		set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, mScale);
	}

	void shader_program::set_texture_slot(const int aTex_slot) const
	{
		set_int(FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME, aTex_slot);
	}

	void shader_program::set_opacity(const float aOpacity)
	{
		mOpacity = aOpacity;
		bind_opacity();
	}

	void shader_program::bind_opacity() const
	{
		set_float(FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME, mOpacity);
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
