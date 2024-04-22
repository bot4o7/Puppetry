#pragma once

//#include "base/base.h"
#include "base/vertex_array.h"
#include "base/vertex_buffer.h"
#include "base/index_buffer.h"
#include "base/shader_program.h"
#include "drawable.h"
#include "ui_entity.h"

namespace cheap {
	class renderer
	{
	public:
		renderer();

		void init(float window_width, float window_height, const std::string& shader_path);
		// Adjust the projection matrix in the shader when the window is resized
		static void reset_projection_matrix(float x_min, float y_min, float x_max, float y_max);
		// Submit the entities that should be considered for rendering in this frame
		static void submit(std::vector<std::unique_ptr<UIEntity>>& entities);

	private:
		// Variables
		std::unique_ptr<vertex_array> m_vao_;
		std::unique_ptr<vertex_buffer> m_vbo_;
		std::unique_ptr<index_buffer> m_ibo_;
		std::unique_ptr<shader_program> m_shader_program_;
		std::array<int, MAX_TEXTURES> m_saved_tex_slots_;
		std::vector<drawable*> m_render_queue_;

		// Private Methods
		void setup_buffers();
		void setup_shader_program(float window_width, float window_height, std::string shader_path);
		void save_texture_slot(drawable* sprite, unsigned int& slot_index);
		void fill_vertex_buffer(unsigned int& drawables_in_buffer, unsigned int& items_in_buffer);
		void render();
	};
}
