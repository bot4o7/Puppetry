#include "pch.h"
#include "color.h"

namespace cheap {
	color::color(const unsigned r, const unsigned g, const unsigned b, const unsigned a) : m_r_(r > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : r), m_g_(g > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : g), m_b_(b > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : b), m_a_(a > COLOR_RGBA_MAX ? COLOR_RGBA_MAX : a)
	{
		LOG();
	}

	color::~color() = default;

	glm::uvec4 color::get_RGBA() const
	{
		LOG();
		return { m_r_, m_g_, m_b_, m_a_ };
	}

	glm::vec4 color::get_RGBA_float() const
	{
		LOG();
		return { m_r_ / 255.0f, m_g_ / 255.0f, m_b_ / 255.0f, m_a_ / 255.0f };
	}
}
