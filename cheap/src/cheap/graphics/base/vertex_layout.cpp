#include "pch.h"
#include "vertex_layout.h"

namespace cheap {
	vertex_layout::vertex_layout() : m_stride_(0)
	{

	}
	vertex_layout::~vertex_layout() = default;

	// Add a new attribute to the vertex buffer layout
	void vertex_layout::add_floats(unsigned int count)
	{
		m_attributes_.emplace_back(count, GL_FLOAT, GL_FALSE, m_stride_);
		m_stride_ += count * sizeof(float);
	}

	const std::vector<vertex_attribute>& vertex_layout::get_attributes() const
	{
		return m_attributes_;
	}
	// Get the size (in bytes) of the entire vertex
	unsigned int vertex_layout::get_stride() const
	{
		return m_stride_;
	}
}
