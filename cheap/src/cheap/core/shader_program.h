#pragma once

#include <glm/glm.hpp>

namespace cheap {
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

		// should I use Reference or Row Pointer or Smart Pointer?
		// texture_slot is uniform vec1
		void set_uniform_texture_slot_array(const int* aTexture_slot_array);

		// projection_array is uniform mat4
		void set_uniform_projection_array(glm::mat4* aProjection_array);

	private:
		unsigned int mId;
		int mUniform_projection_array_location;
		int mUniform_texture_slot_array_location;
		std::string mUniform_texture_slot_array_name;
		std::string mUniform_projection_array_name;

		int get_uniform_projection_array_location(const char* aName);

		int get_uniform_texture_slot_array_location(const char* aName);

		static unsigned int create_program(const std::string& aVertex_path, const std::string& aFragment_path);

		[[nodiscard]] static unsigned int compile_shader(const unsigned int aShader_type, const char* aShader_path);

		static void check_compile_errors(const unsigned int aShader_id, const unsigned int aShader_type);;
	};
}
