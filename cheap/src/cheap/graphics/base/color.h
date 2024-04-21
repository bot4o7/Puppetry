#pragma once
#include <glm/glm.hpp>

namespace cheap {
	#define COLOR_RGBA_MAX 255
	class color
	{
	public:
		color(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a = COLOR_RGBA_MAX)
			: m_r_(r > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : r), m_g_(g > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : g), m_b_(b > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : b), m_a_(a > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : a)
		{
			LOG();
		}

		~color() = default;

		[[nodiscard]] glm::uvec4 get_RGBA() const
		{
			LOG();
			return { m_r_, m_g_, m_b_, m_a_ };
		}
		[[nodiscard]] glm::vec4  get_RGBA_float() const
		{
			LOG();
			return { m_r_ / 255.0f, m_g_ / 255.0f, m_b_ / 255.0f, m_a_ / 255.0f };
		}

	private:
		unsigned int m_r_, m_g_, m_b_, m_a_;
	};
}
