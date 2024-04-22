#pragma once

#include <glm/glm.hpp>
namespace cheap {
	struct vector2
	{
		float x;
		float y;
	};

	enum class flip_axis { flip_none, flip_x, flip_y, flip_xy };


	class transform
	{
	public:
		transform();

		[[nodiscard]] vector2   get_pos() const;
		[[nodiscard]] vector2   get_scale() const;
		[[nodiscard]] float     get_layer() const;
		[[nodiscard]] float     get_width() const;
		[[nodiscard]] float     get_height() const;
		[[nodiscard]] float     get_rotation() const;
		[[nodiscard]] flip_axis get_flip() const;
		// Change the given position according to the saved rotation/flip axis
		[[nodiscard]] vector2 get_transformed_pos(float x, float y) const;

		void set_pos(float x, float y);
		void set_scale(float x, float y);
		void set_layer(float layer);
		void set_width(float width);
		void set_height(float height);
		void set_rotation(float rotation);
		void set_flip(flip_axis flip_axis);
		void set_layout_child(bool is_layout_child);

	private:
		glm::vec2 m_pos_;
		glm::vec2 m_scale_;
		glm::vec2 m_dimens_;
		float m_rotation_;
		flip_axis m_flip_axis_;
		float m_layer_;
		bool m_is_layout_child_;
	};
}
