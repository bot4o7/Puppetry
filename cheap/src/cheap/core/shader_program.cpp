#include "pch.h"
#include "shader_program.h"

#include "base.h"

namespace cheap {
	shader_program::shader_program(const std::string& aVertex_shader_path, const std::string& aFragment_shader_path) :
		mId(create_program(aVertex_shader_path, aFragment_shader_path)),
		mUniform_projection_array_location(-1),
		mUniform_texture_slot_array_location(-1),
		mUniform_texture_slot_array_name("uProjectionArray"),
		mUniform_projection_array_name("uTexSlotArray")
	{
		LOG();
	}

	shader_program::~shader_program()
	{
		LOG();
		glDeleteProgram(mId);
	}

	void shader_program::bind() const
	{
		LOG();
		glUseProgram(mId);
	}

	void shader_program::unbind()
	{
		LOG();
		glUseProgram(0);
	}

	void shader_program::set_uniform_texture_slot_array(const int* aTexture_slot_array)
	{
		LOG();
		glUniform1iv(get_uniform_texture_slot_array_location(mUniform_texture_slot_array_name.c_str()), MAX_TEXTURES, aTexture_slot_array);
	}

	void shader_program::set_uniform_projection_array(glm::mat4* aProjection_array)
	{
		LOG();
		glUniformMatrix4fv(get_uniform_projection_array_location(mUniform_projection_array_name.c_str()), MAX_TEXTURES, GL_FALSE, &aProjection_array[0][0][0]);
	}

	int shader_program::get_uniform_projection_array_location(const char* aName)
	{
		LOG();
		if (mUniform_projection_array_location > -1)
			return mUniform_projection_array_location;

		// Find the uniform location in the shader program
		mUniform_projection_array_location = glGetUniformLocation(mId, aName);

		if (mUniform_projection_array_location == -1)
			PRINTLN("ERROR::SHADER_UNIFORM projection_array not found or not set correctly.");

		return mUniform_projection_array_location;
	}

	int shader_program::get_uniform_texture_slot_array_location(const char* aName)
	{
		LOG();
		if (mUniform_texture_slot_array_location > -1)
			return mUniform_texture_slot_array_location;

		// Find the uniform location in the shader program
		mUniform_texture_slot_array_location = glGetUniformLocation(mId, aName);

		if (mUniform_texture_slot_array_location == -1)
			PRINTLN("ERROR::SHADER_UNIFORM texture_slot_array not found or not set correctly.");

		return mUniform_texture_slot_array_location;
	}

	unsigned shader_program::create_program(const std::string& aVertex_path, const std::string& aFragment_path)
	{
		LOG();
		// Create an id for the program and the shaders
		const unsigned int program_id = glCreateProgram();
		const unsigned int vertex_shader_id = compile_shader(GL_VERTEX_SHADER, aVertex_path.c_str());
		const unsigned int fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, aFragment_path.c_str());

		// Link the shaders in a single program
		glAttachShader(program_id, vertex_shader_id);
		glAttachShader(program_id, fragment_shader_id);
		glLinkProgram(program_id);

		// Delete shaders since they are no longer needed
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);

		return program_id;
	}

	unsigned shader_program::compile_shader(const unsigned aShader_type, const char* aShader_path)
	{
		// Create a specific type of shader and assign it an id
		const unsigned int shader_id = glCreateShader(aShader_type);

		// Link the shader with the appropriate source code
		glShaderSource(shader_id, 1, &aShader_path, nullptr);
		glCompileShader(shader_id);
		check_compile_errors(shader_id, aShader_type);

		return shader_id;
	}

	void shader_program::check_compile_errors(const unsigned aShader_id, const unsigned aShader_type)
	{
		LOG();
		// Get the shader's compilation status
		int success;
		glGetShaderiv(aShader_id, GL_COMPILE_STATUS, &success);

		// If there were compilation errors
		if (success != GL_TRUE) {
			// Get the length of the error message
			int length;
			glGetShaderiv(aShader_id, GL_INFO_LOG_LENGTH, &length);

			// Get the error message
			char* message = new char[length];
			glGetShaderInfoLog(aShader_id, length, &length, message);

			// Display the error message for the appropriate shader
			if (aShader_type == GL_VERTEX_SHADER)
				PRINTLN("ERROR::SHADER_COMPILATION of type Vertex.");
			else if (aShader_type == GL_FRAGMENT_SHADER)
				PRINTLN("ERROR::SHADER_COMPILATION of type Fragment.");
			else
				PRINTLN("ERROR::SHADER_LINKING.");

			// Free memory for the error message
			delete[] message;
		}
	}
}
