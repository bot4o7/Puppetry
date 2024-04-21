#pragma once
#include "base.h"

namespace cheap {
	class vertex_buffer final : public base
	{
	public:
		vertex_buffer(const float* vertices, const unsigned int size)
		{
			// Create a buffer object and assign it an id
			glGenBuffers(1, &m_id_);
			// Set the buffer as the current vertex buffer object
			glBindBuffer(GL_ARRAY_BUFFER, m_id_);
			// Add the given vertex data to the VBO
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
		}
		~vertex_buffer() override
		{
			glDeleteBuffers(1, &m_id_);
		}

		void bind() const
		{
			// Set the buffer as the current vertex buffer object
			glBindBuffer(GL_ARRAY_BUFFER, m_id_
			);
		}

		static void unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};
}
