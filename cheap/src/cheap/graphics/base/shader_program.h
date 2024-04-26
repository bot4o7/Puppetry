#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>


namespace cheap {
	// TODO look up your shader files, confirm the names of uniforms
	#define VERTEX_SHADER_GLSL_UNIFORM_TRANSFORM_MATRIX_NAME "uTransform"
	//#define VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_MATRIX_NAME "uScale"
	#define FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME "uTexture"

	class shader_program
	{
	public:
		unsigned int mId;
		// constructor generates the shader on the fly
		// ------------------------------------------------------------------------
		shader_program(const char* aVertex_path, const char* aFragment_path);
		// activate the shader
		// ------------------------------------------------------------------------
		void bind() const;

		static void unbind();

		void set_tex(int tex_slot) const;

		void use(const glm::mat4& aTransform, const int aTexture_slot) const;

		void set_transform(const glm::mat4& aMat) const;
		/*void set_scale(const glm::mat4& mat)
		{
			setMat4(VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_MATRIX_NAME, mat);
		}*/
		// utility uniform functions
		// ------------------------------------------------------------------------
		void setBool(const std::string& name, bool value) const;
		// ------------------------------------------------------------------------
		void setInt(const std::string& name, int value) const;
		// ------------------------------------------------------------------------
		void setFloat(const std::string& name, float value) const;
		// ------------------------------------------------------------------------
		void setVec2(const std::string& name, const glm::vec2& value) const;

		void setVec2(const std::string& name, float x, float y) const;
		// ------------------------------------------------------------------------
		void setVec3(const std::string& name, const glm::vec3& value) const;

		void setVec3(const std::string& name, float x, float y, float z) const;
		// ------------------------------------------------------------------------
		void setVec4(const std::string& name, const glm::vec4& value) const;

		void setVec4(const std::string& name, float x, float y, float z, float w) const;
		// ------------------------------------------------------------------------
		void setMat2(const std::string& name, const glm::mat2& mat) const;
		// ------------------------------------------------------------------------
		void setMat3(const std::string& name, const glm::mat3& mat) const;
		// ------------------------------------------------------------------------
		void setMat4(const std::string& name, const glm::mat4& mat) const;

	private:
		// utility function for checking shader compilation/linking errors.
		// ------------------------------------------------------------------------
		static void check_compile_errors(const GLuint aShader, unsigned int aType = 0);
	};
}
