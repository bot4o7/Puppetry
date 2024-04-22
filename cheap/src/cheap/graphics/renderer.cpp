#include "pch.h"
#include "renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "base/base.h"
#include "base/vertex_layout.h"
#include "../core/window.h"
//#include "Graphics.h"
//#include "SpriteGFX.h"
//#include "TextGFX.h"
#include "../utils/Utils.h"
//#include "UI/Button.h"

namespace cheap {
	renderer::renderer()
		: m_vao_(nullptr), m_vbo_(nullptr), m_ibo_(nullptr), m_shader_program_(nullptr),
		m_saved_tex_slots_(), m_render_queue_()
	{
	}

	void renderer::init(const float window_width, const float window_height, const std::string& shader_path)
	{
		setup_buffers();
		setup_shader_program(window_width, window_height, shader_path);
	}

	void renderer::reset_projection_matrix(float x_min, float y_min, float x_max, float y_max)
	{
		// Set the projection matrix in the shader according to the window size
		//TODO
		//m_shader_program_->set_uniform_mat4_projection_array(glm::ortho(x_min, x_max, y_min, y_max, -1000.0f, 1000.0f));
	}

	// Get an already existing drawable and push it to the render queue
	void renderer::submit(std::vector<std::unique_ptr<UIEntity>>& entities)
	{
		//for (const auto& entity : entities) {
		//	if (entity->is_visible()) {
		//		// Don't render empty text
		//		if (dynamic_cast<TextBox*>(entity.get())) {
		//			if (static_cast<TextGFX*>(entity.get()->get_drawable())->GetItemCount() < 1)
		//				continue;
		//		}
		//		// Also render button text if it exists
		//		else if (dynamic_cast<Button*>(entity.get())) {
		//			if (static_cast<Button*>(entity.get())->GetTextDrawable()->GetItemCount() > 0)
		//				m_render_queue_.emplace_back(static_cast<Button*>(entity.get())->GetTextDrawable());
		//		}
		//		m_render_queue_.emplace_back(entity->get_drawable());
		//	}
		//}

		// Sort entities based on their depth by providing a comparison function
		//std::sort(m_render_queue_.begin(), m_render_queue_.end(),
		//	[](const drawable* a, const drawable* b) {
		//		// Sort in descending order
		//		return a->GetTransform()->GetLayer() < b->GetTransform()->GetLayer();
		//	});

		//render();
	}

	// Render all the drawables in the render queue
	void renderer::render()
	{
		do {
			unsigned int drawables_in_buffer, items_in_buffer;
			// Reset the texture slots so that they can be reused by new textures
			m_saved_tex_slots_.fill(-1);
			// Render each drawable in the vertex buffer
			fill_vertex_buffer(drawables_in_buffer, items_in_buffer);
			glDrawElements(
				GL_TRIANGLES, drawable::get_index_count() * items_in_buffer, GL_UNSIGNED_INT, nullptr);

			// Remove from the queue the drawables that were just rendered
			m_render_queue_.erase(m_render_queue_.begin(), m_render_queue_.begin() + drawables_in_buffer);
		} while (!m_render_queue_.empty());
	}

	/********************************** PRIVATE ****************************************/

	// Initialize the vao, vbo, and ibo to be used for rendering
	void renderer::setup_buffers()
	{
		m_vao_ = std::make_unique<vertex_array>();
		// Allocate memory for 1 large vertex and index buffer
		m_vbo_ = std::make_unique<vertex_buffer>(nullptr, MAX_VERTICES * sizeof(vertex));
		m_ibo_ = std::make_unique<index_buffer>();

		// Create a layout for the vertex array according to the attributes in the Vertex struct
		vertex_layout* layout = new vertex_layout();
		layout->add_floats(vertex().position.length()); // vec3(x, y, z) -> 3 floats
		layout->add_floats(vertex().color.length()); // vec4(r, g, b, a) -> 4 floats
		layout->add_floats(vertex().texture_coords.length()); // vec2(x, y) -> 2 floats
		layout->add_floats(1); // texture slot number -> 1 float
		layout->add_floats(1); // to be rendered as text or not -> 1 float
		m_vao_->add_layout(layout);
	}

	// Initialize the shader program and its uniforms to be used for rendering
	void renderer::setup_shader_program(const float window_width, const float window_height, std::string shader_path)
	{
		// Choose the shaders to be used for rendering
		m_shader_program_ = std::make_unique<shader_program>();

		// Set up the texture slots in the fragment shader
		constexpr int slot_count = MAX_TEXTURES + 1; // include the 'no texture' slot
		int tex_slots[slot_count];
		for (int i = 0; i < slot_count; i++) tex_slots[i] = i;
		m_shader_program_->set_uniform_vec1_texture_slot_array(tex_slots);
		reset_projection_matrix(0.0f, 0.0f, window_width, window_height);
	}

	// Save the drawable's texture id in a new texture slot
	void renderer::save_texture_slot(drawable* drawable, unsigned int& slot_index)
	{
		// Get the texture id of the drawable
		const unsigned int tex_id = drawable->get_tex_id();
		// Check if the texture already has a slot id
		// Save the slot for the current texture and increase the slot index
		if (const bool found = cheap::utils::find_in_array(tex_id, m_saved_tex_slots_.data(), m_saved_tex_slots_.size()) != -1; !found) {
			drawable->set_texture_slot(slot_index + 1); // slot 0 = no texture
			m_saved_tex_slots_[slot_index++] = tex_id;
		}
	}

	// Add up to the maximum number of drawables to the buffer
	void renderer::fill_vertex_buffer(unsigned int& drawables_in_buffer, unsigned int& items_in_buffer)
	{
		unsigned int drawable_count = 0; // number of drawables from the render queue
		unsigned int item_count = 0; // 1 drawable may include multiple items (text includes letters)
		unsigned int buffer_index = 0; // first available byte in the vertex buffer
		unsigned int slot_index = 0;
		// Add drawables from the queue to the vertex buffer
		for (const auto& drawable_obj : m_render_queue_) {
			if (item_count + drawable_obj->get_item_count() > MAX_DRAWABLE_ITEMS || slot_index == MAX_TEXTURES)
				break;

			// Check if the drawable is a sprite or text object (instead of a rectangle)
			//TODO
			//if (dynamic_cast<SpriteGFX*>(drawable_obj) || dynamic_cast<TextGFX*>(drawable_obj))
			save_texture_slot(drawable_obj, slot_index);

			// Add the drawable's data to the large index buffer
			glBufferSubData(GL_ARRAY_BUFFER,
				buffer_index,						// starting point in buffer
				drawable_obj->get_buffer_size(),			// size in buffer
				&(drawable_obj->get_vertex_data()[0]));	// data to be rendered
			drawable_count++;
			item_count += drawable_obj->get_item_count();
			buffer_index += drawable_obj->get_buffer_size();
		}
		drawables_in_buffer = drawable_count;
		items_in_buffer = item_count;
	}
}
