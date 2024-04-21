#pragma once
#include "base.h"

namespace cheap {
	class index_buffer : public base
	{
	public:
		index_buffer() : m_indices_(new std::array<unsigned int, MAX_VERTICES>)
		{
			// Create a buffer object and assign it an id
			glGenBuffers(1, &m_id_);
			// Set the buffer as the current index buffer object
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_);
			// Create and add the index data to the IBO
			create_max_index_data();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_VERTICES * sizeof(unsigned int), m_indices_.get()->data(), GL_STATIC_DRAW);
		}

		~index_buffer() override
		{
			glDeleteBuffers(1, &m_id_);
		}

		void bind() const
		{
			// Set the buffer as the current index buffer object
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_);
		}

		static void unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	private:
		std::unique_ptr <std::array<unsigned int, MAX_VERTICES>> m_indices_;

		// Create and populate an array of indices
		void create_max_index_data() const
		{
			// Repeat for each rectangle
			for (unsigned int i = 0, offset = 0; i < MAX_VERTICES; i += 6, offset += 4) {
				// Indices for 1st triangle
				m_indices_.get()->at(i + 0) = offset + 0;
				m_indices_.get()->at(i + 1) = offset + 1;
				m_indices_.get()->at(i + 2) = offset + 2;
				// Indices for 2nd triangle
				m_indices_.get()->at(i + 3) = offset + 2;
				m_indices_.get()->at(i + 4) = offset + 3;
				m_indices_.get()->at(i + 5) = offset + 0;
			}
		}
	};
}
