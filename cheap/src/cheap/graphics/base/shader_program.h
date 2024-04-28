#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

#include "transform.h"


namespace cheap {
	// TODO look up your shader files, confirm the names of uniforms

	#define VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_NAME "uProjection"
	#define VERTEX_SHADER_GLSL_UNIFORM_VIEW_NAME "uView"
	#define VERTEX_SHADER_GLSL_UNIFORM_TRANSLATE_NAME "uTranslate"
	#define VERTEX_SHADER_GLSL_UNIFORM_LAYOUT_NAME "uLayout"
	#define VERTEX_SHADER_GLSL_UNIFORM_ROTATE_NAME "uRotate"
	#define VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME "uScale"

	#define FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME "uTexture"
	#define FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME "uOpacity"

	// uniform opaque, transparency = 1.0
	#define UNIFORM_OPAQUE 1.0f

	class shader_program
	{
	public:
		unsigned int mId;
		// constructor generates the shader on the fly
		// ----------------------------------
		shader_program(
			const char* aVertex_path,
			const char* aFragment_path,
			const float aHalf_screen_width,
			const float aHalf_screen_height,
			const float aNear,
			const float aFar);
		~shader_program() = default;

		void create_program(const char* aVertex_path, const char* aFragment_path) const
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

		// activate the shader
		// ---------------------------
		void bind() const;

		static void unbind();

		void use(const int aTexture_slot) const
		{
			bind();
			set_texture_slot(aTexture_slot);
		}



		void bind_projection() const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_NAME, mProjection);
		}
		void set_projection_to_orthogonal(
			const float aLeft,
			const float aRight,
			const float aBottom,
			const float aTop,
			const float aNear,
			const float aFar
		)
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
		void set_projection_to_perspective(
			const float aFov_degree,
			const int aAspect_numerator,
			const int aAspect_denominator,
			const float aNear, const float aFar)
		{
			mProjection = transform::get_perspective_projection(
				aFov_degree,
				aAspect_numerator,
				aAspect_denominator,
				aNear, aFar);
			bind_projection();
		}
		void bind_view() const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_VIEW_NAME, mView);
		}
		void set_view(
			const float aPos_x,
			const float aPos_y,
			const float aPos_z,
			const float aLook_x,
			const float aLook_y,
			const float aLook_z)
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

		void set_transform() const
		{
			bind();
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_TRANSLATE_NAME, mTranslate);
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_ROTATE_NAME, mRotate);
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, mScale);
			set_float(FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME, mOpacity);
		}

		void use_transform(const int aTexture_slot, const glm::mat4& aTranslate = ID_MAT, const glm::mat4& aRotate = ID_MAT, const glm::mat4& aScale = ID_MAT, const float aOpacity = UNIFORM_OPAQUE)
		{
			bind();
			set_translate(aTranslate);
			set_rotate(aRotate);
			set_scale(aScale);
			set_texture_slot(aTexture_slot);
			set_opacity(aOpacity);
		}

		void bind_translate() const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_TRANSLATE_NAME, mTranslate);
		}
		void set_translate(const glm::mat4& aMat)
		{
			mTranslate = aMat;
			bind_translate();
		}
		void set_rotate(const glm::mat4& aMat)
		{
			mRotate = aMat;
			bind_rotate();
		}
		void bind_rotate() const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_ROTATE_NAME, mRotate);
		}
		void set_scale(const glm::mat4& aMat)
		{
			mScale = aMat;
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, mScale);
		}
		void bind_scale() const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, mScale);
		}
		void set_texture_slot(const int aTex_slot) const
		{
			set_int(FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME, aTex_slot);
		}
		void set_opacity(const float aOpacity)
		{
			mOpacity = aOpacity;
			bind_opacity();
		}
		void bind_opacity() const
		{
			set_float(FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME, mOpacity);
		}

	private:
		float mOpacity;

		glm::mat4 mProjection;
		glm::mat4 mView;
		glm::mat4 mTranslate;
		glm::mat4 mRotate;
		glm::mat4 mScale;


		// utility function for checking shader compilation/linking errors.
		// -------------
		static void check_compile_errors(const GLuint aShader, unsigned int aType = 0);

		// utility uniform functions
		// --------
		void set_bool(const std::string& aName, bool aValue) const;
		// --------
		void set_int(const std::string& aName, int aValue) const;
		// 
		void set_float(const std::string& aName, float aValue) const;
		// 
		void set_vec2(const std::string& aName, const glm::vec2& aValue) const;

		void set_vec2(const std::string& aName, float aX, float aY) const;
		// -----------
		void set_vec3(const std::string& aName, const glm::vec3& aValue) const;

		void set_vec3(const std::string& aName, float aX, float aY, float aZ) const;
		// ------------
		void set_vec4(const std::string& aName, const glm::vec4& aValue) const;

		void set_vec4(const std::string& aName, float aX, float aY, float aZ, float aW) const;
		// --------------
		void set_mat2(const std::string& aName, const glm::mat2& aMat) const;
		// ---------------
		void set_mat3(const std::string& aName, const glm::mat3& aMat) const;
		// -----------------
		void set_mat4(const std::string& aName, const glm::mat4& aMat) const;
	};
}
