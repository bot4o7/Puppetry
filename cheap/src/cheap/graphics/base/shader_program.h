#pragma once
#include "base.h"

#ifdef CP_OPENGL_API

namespace cheap {
	// OpenGL texture slots has 16 at least.
	class shader_program2 final : public base
	{
	public:
		shader_program();

		~shader_program() override;

		void bind() const;

		static void unbind();

		// should I use Reference or Row Pointer or Smart Pointer?
		void set_uniform_vec1_texture_slot_array(const int* texture_slot_array) const;

		void set_uniform_mat4_projection_array(glm::mat4* projection_array) const;

	private:
		//static const std::string m_vertex_shader_file;
		//static const std::string m_fragment_shader_file;
		//std::unordered_map<std::string, int> m_uniform_locations;

		//int get_uniform_location(const std::string& name)
		//{
		//	LOG();
		//	// Check is the location is already saved
		//	//if (m_uniform_locations.contains(name))
		//		//return m_uniform_locations[name];
		//	if (m_uniform)


		//	// Find the uniform location in the shader program
		//	const int location = glGetUniformLocation(m_id_, name.c_str());
		//	m_uniform_locations[name] = location;

		//	if (location == -1)
		//		PRINTLN("ERROR::SHADER_UNIFORM " + name + " not found or not set correctly.");

		//	return location;
		//}

		int get_uniform_projection_array_location(const char* name) const;

		int get_uniform_texture_slot_array_location(const char* name) const;

		static unsigned int create_program();

		[[nodiscard]] static unsigned int compile_shader(const unsigned int shader_type, const std::string& shader_path);

		static void check_compile_errors(const unsigned int shader_id, const unsigned int shader_type);
	};

}
#endif
