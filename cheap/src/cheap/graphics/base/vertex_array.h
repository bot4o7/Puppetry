#pragma once
#include "base.h"
#include "vertex_layout.h"

namespace cheap {
	class vertex_array final : public base
	{
	public:
		vertex_array();
		~vertex_array() override;
		// should be called after binding a vertex buffer
		static void add_layout(const vertex_layout* layout);

		void bind() const;
		static void unbind();
	private:
		std::unique_ptr<vertex_layout> m_layout_;
	};
}
