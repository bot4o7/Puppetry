#pragma once

#ifdef CP_OPENGL_API
#include "glm/glm.hpp"
namespace cheap {
	class base
	{
	public:
		//[[nodiscard]] unsigned int get_id() const { return m_id_; }
		//void                       set_id(const unsigned int id) { m_id_ = id; }

		base() = default;
		virtual ~base() = default;
	protected:
		unsigned int m_id_;
	};

	// Define constants
	constexpr unsigned short MAX_DRAWABLE_ITEMS = 10000;
	constexpr unsigned short MAX_VERTICES = MAX_DRAWABLE_ITEMS * 4; // 1 drawable = 4 vertices
	constexpr unsigned short MAX_INDICES = MAX_DRAWABLE_ITEMS * 6; // 1 drawable = 2 triangles = 2 * 3 vertices
	constexpr unsigned short MAX_TEXT_LENGTH = MAX_DRAWABLE_ITEMS;
	constexpr unsigned char  MAX_TEXTURES = 15; // 1st slot = no texture

	// An array of floats to be sent to the GPU
	struct vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture_coords;
		int texture_slot;
		bool is_text;
	};

	// Contains information about the data in a single vertex attribute
	struct vertex_attribute
	{
		unsigned int count;
		unsigned int type;
		unsigned int normalized;
		unsigned int offset;
	};
}
#endif
