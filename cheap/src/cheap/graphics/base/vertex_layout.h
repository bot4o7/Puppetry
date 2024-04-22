#pragma once
#include "base.h"

namespace cheap {
	class vertex_layout final : public base
	{
	public:
		vertex_layout();
		~vertex_layout() override;

		// Add a new attribute to the vertex buffer layout
		void add_floats(unsigned int count);

		[[nodiscard]] const std::vector<vertex_attribute>& get_attributes() const;
		// Get the size (in bytes) of the entire vertex
		[[nodiscard]] unsigned int get_stride() const;

	private:
		std::vector<vertex_attribute> m_attributes_;
		unsigned int m_stride_;
	};
}
