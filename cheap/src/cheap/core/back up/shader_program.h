﻿#pragma once

#include <glm/glm.hpp>

namespace cheap {

	// TODO look up your shader files, confirm the names of uniforms
	#define VERTEX_SHADER_GLSL_UNIFORM_TRANSFORM_MATRIX_NAME "transform"
	#define FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME "tex"

	class shader_program
	{
	public:
		// create a shader program (not active, you need to bind() to call glUseProgram())
		shader_program(
			const std::string& aVertex_shader_path,
			const std::string& aFragment_shader_path);

		~shader_program();

		// gllUseProgram(mId)
		void bind() const;
		// glUseProgram(0)
		static void unbind();
		// TODO do NOT use this. Now only draw one pic per frame per shader
		// should I use Reference or Row Pointer or Smart Pointer?
		// texture_slot is uniform vec1
		void set_uniform_texture_slot_array(const int* aTexture_slot_array);
		// TODO do NOT use this. Now only draw one pic per frame per shader
		// projection_array is uniform mat4
		void set_uniform_projection_array(glm::mat4* aProjection_array);

		void use(const glm::mat4& aTransform, const int aTexture_slot) const
		{
			bind();
			set_transform_matrix(aTransform);
			set_texture_slot(aTexture_slot);
		}

		void set_texture_slot(const int aTexture_slot) const;

		void set_transform_matrix(const glm::mat4& aTransform) const;

	private:
		unsigned int mId;
		int mUniform_projection_array_location;
		int mUniform_texture_slot_array_location;
		std::string mUniform_texture_slot_array_name;
		std::string mUniform_projection_array_name;

		// TODO do NOT use this. Now only draw one pic per frame per shader
		int get_uniform_projection_array_location(const char* aName);
		// TODO do NOT use this. Now only draw one pic per frame per shader
		int get_uniform_texture_slot_array_location(const char* aName);

		void set_int(const std::string& aName, const int aValue) const;

		void set_mat4(const std::string& aName, const glm::mat4& aMat) const;

		static unsigned int create_program(const std::string& aVertex_path, const std::string& aFragment_path);

		[[nodiscard]] static unsigned int compile_shader(const unsigned int aShader_type, const char* aShader_path);

		static void check_compile_errors(const unsigned int aShader_id, const unsigned int aShader_type);;
	};
}