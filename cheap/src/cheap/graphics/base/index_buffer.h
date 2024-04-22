#pragma once
#include "base.h"

namespace cheap {
	class index_buffer final : public base
	{
	public:
		index_buffer();

		~index_buffer() override;

		void bind() const;

		static void unbind();

	private:
		std::unique_ptr <std::array<unsigned int, MAX_INDICES>> m_indices_;

		// Create and populate an array of indices
		void create_max_index_data() const;
	};
}
