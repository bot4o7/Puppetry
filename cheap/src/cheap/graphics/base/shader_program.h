#pragma once
#include "base.h"

#ifdef CP_OPENGL_API

namespace cheap {
	// OpenGL texture slots has 16 at least.
	class shader_program final : public base
	{
	public:
		shader_program()
		{
			LOG();
			m_id_ = create_program();
		}

		~shader_program() override
		{
			LOG();
			glDeleteProgram(m_id_);
		}

		void bind() const
		{
			LOG();
			glUseProgram(m_id_);
		}

		static void unbind()
		{
			LOG();
			glUseProgram(0);
		}

		// should I use Reference or Row Pointer or Smart Pointer?
		void set_uniform_vec1_texture_slot_array(const int* texture_slot_array) const
		{
			LOG();
			static const std::string m_uniform_vec1_texture_slot_array_name = "uTexSlots";

			glUniform1iv(get_uniform_texture_slot_array_location(m_uniform_vec1_texture_slot_array_name.c_str()), MAX_TEXTURES, texture_slot_array);
		}

		void set_uniform_mat4_projection_array(glm::mat4* projection_array) const
		{
			LOG();
			static const std::string m_uniform_mat4_projection_array_name = "uProjection";

			glUniformMatrix4fv(get_uniform_projection_array_location(m_uniform_mat4_projection_array_name.c_str()), MAX_TEXTURES, GL_FALSE, &projection_array[0][0][0]);
		}


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

		int get_uniform_projection_array_location(const char* name) const
		{
			LOG();
			static int m_uniform_projection_array_location = -1;

			if (m_uniform_projection_array_location > -1)
				return m_uniform_projection_array_location;

			// Find the uniform location in the shader program
			m_uniform_projection_array_location = glGetUniformLocation(m_id_, name);

			if (m_uniform_projection_array_location == -1)
				PRINTLN("ERROR::SHADER_UNIFORM projection_array not found or not set correctly.");

			return m_uniform_projection_array_location;
		}

		int get_uniform_texture_slot_array_location(const char* name) const
		{
			LOG();
			static int m_uniform_texture_slot_array_location = -1;

			if (m_uniform_texture_slot_array_location > -1)
				return m_uniform_texture_slot_array_location;

			// Find the uniform location in the shader program
			m_uniform_texture_slot_array_location = glGetUniformLocation(m_id_, name);

			if (m_uniform_texture_slot_array_location == -1)
				PRINTLN("ERROR::SHADER_UNIFORM texture_slot_array not found or not set correctly.");

			return m_uniform_texture_slot_array_location;
		}

		static unsigned int create_program()
		{
			LOG();
			static const std::string m_fragment_shader_file = "shaders/fragment";
			static const std::string m_vertex_shader_file = "shaders/vertex";

			// Create an id for the program and the shaders
			const unsigned int program_id = glCreateProgram();
			const unsigned int vertex_shader_id = compile_shader(GL_VERTEX_SHADER, m_vertex_shader_file);
			const unsigned int fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, m_fragment_shader_file);

			// Link the shaders in a single program
			glAttachShader(program_id, vertex_shader_id);
			glAttachShader(program_id, fragment_shader_id);
			glLinkProgram(program_id);

			// Delete shaders since they are no longer needed
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);

			return program_id;
		}

		[[nodiscard]] static unsigned int compile_shader(const unsigned int shader_type, const std::string& shader_path)
		{
			// Create a specific type of shader and assign it an id
			const unsigned int shader_id = glCreateShader(shader_type);

			// Get the contents of the shader file
			//const std::string shader_source = Utils::ReadFile(shader_path);
			const char* shader_source_c = shader_path.c_str();


			// Link the shader with the appropriate source code
			glShaderSource(shader_id, 1, &shader_source_c, nullptr);
			glCompileShader(shader_id);
			check_compile_errors(shader_id, shader_type);

			return shader_id;
		}

		static void check_compile_errors(const unsigned int shader_id, const unsigned int shader_type)
		{
			LOG();
			// Get the shader's compilation status
			int success;
			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

			// If there were compilation errors
			if (success != GL_TRUE) {
				// Get the length of the error message
				int length;
				glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

				// Get the error message
				char* message = new char[length];
				glGetShaderInfoLog(shader_id, length, &length, message);

				// Display the error message for the appropriate shader
				if (shader_type == GL_VERTEX_SHADER)
					PRINTLN("ERROR::SHADER_COMPILATION of type Vertex.");
				else if (shader_type == GL_FRAGMENT_SHADER)
					PRINTLN("ERROR::SHADER_COMPILATION of type Fragment.");
				else
					PRINTLN("ERROR::SHADER_LINKING.");

				// Free memory for the error message
				delete[] message;
			}
		}
	};

}
#endif
