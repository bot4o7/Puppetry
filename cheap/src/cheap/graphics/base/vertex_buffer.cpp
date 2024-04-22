#include "pch.h"
#include "vertex_buffer.h"

namespace cheap {
	vertex_buffer::vertex_buffer(const float* vertices, const unsigned int size)
	{
		// Create a buffer object and assign it an id
		glGenBuffers(1, &m_id_);
		// Set the buffer as the current vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_id_);
		// Add the given vertex data to the VBO
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	}
	vertex_buffer::~vertex_buffer()
	{
		glDeleteBuffers(1, &m_id_);
	}

	void vertex_buffer::bind() const
	{
		// Set the buffer as the current vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_id_
		);
	}

	void vertex_buffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};
