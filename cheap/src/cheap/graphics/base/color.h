#pragma once
#include <glm/glm.hpp>

namespace cheap {
	#define COLOR_RGBA_MAX 255
	class color
	{
	public:
		color(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a = COLOR_RGBA_MAX);

		~color();

		[[nodiscard]] glm::uvec4 get_RGBA() const;

		[[nodiscard]] glm::vec4  get_RGBA_float() const;

	private:
		unsigned int m_r_, m_g_, m_b_, m_a_;
	};
}
