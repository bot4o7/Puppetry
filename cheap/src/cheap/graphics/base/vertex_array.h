#pragma once
#include "base.h"
#include "vertex_layout.h"

namespace cheap {
	class vertex_array final : public base
	{
	public:
		vertex_array()
		{
			// Create a vertex array and assign it an id
			glGenVertexArrays(1, &m_id_);
			glBindVertexArray(m_id_);
		}
		~vertex_array() override
		{
			glDeleteVertexArrays(1, &m_id_);
		}
		// should be called after binding a vertex buffer
		static void add_layout(const vertex_layout* layout)
		{

			// Get all the different attributes included in a single vertex buffer
			const std::vector<vertex_attribute> attributes = layout->get_attributes();

			// Repeat for every vertex attribute (e.g.: position, color, etc.)
			for (int i = 0; i < attributes.size(); ++i) {
				// Enable the specific attribute
				glEnableVertexAttribArray(i);
				// Add a description about the vertex attribute
				glVertexAttribPointer(i,
					attributes[i].count,
					attributes[i].type,
					attributes[i].normalized,
					layout->get_stride(),
					reinterpret_cast<const void*>(attributes[i].offset));
			}
		}

		void bind() const
		{
			glBindVertexArray(m_id_);
		}

		static void unbind()
		{
			glBindVertexArray(0);
		}

	private:
		std::unique_ptr<vertex_layout> m_layout_;
	};
}
