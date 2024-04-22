#pragma once
#include "base.h"

namespace cheap {
	class vertex_buffer final : public base
	{
	public:
		vertex_buffer(const float* vertices, const unsigned int size);
		~vertex_buffer() override;

		void bind() const;
		static void unbind();
	};
}
