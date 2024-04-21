#pragma once
#include "base.h"

namespace cheap {
	class vertex_layout final : public base
	{
	public:
		vertex_layout() : m_stride_(0)
		{

		}
		~vertex_layout() override = default;

		// Add a new attribute to the vertex buffer layout
		void add_floats(unsigned int count)
		{
			m_attributes_.emplace_back(count, GL_FLOAT, GL_FALSE, m_stride_);
			m_stride_ += count * sizeof(float);
		}

		[[nodiscard]] const std::vector<vertex_attribute>& get_attributes() const
		{
			return m_attributes_;
		}
		// Get the size (in bytes) of the entire vertex
		[[nodiscard]] unsigned int get_stride() const
		{
			return m_stride_;
		}

	private:
		std::vector<vertex_attribute> m_attributes_;
		unsigned int m_stride_;
	};
}
