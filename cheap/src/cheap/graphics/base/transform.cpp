#include "pch.h"

#include "transform.h"
#include "glm/gtc/matrix_transform.hpp"
namespace cheap {
	transform::transform()
		: m_pos_(glm::vec2(1.0f)), m_scale_(glm::vec2(1.0f)), m_dimens_({ 100.0f, 100.0f }),
		m_rotation_(0.0f), m_flip_axis_(flip_axis::flip_none), m_layer_(0.0f), m_is_layout_child_(false)
	{
	}

	/******************** ACCESSOR METHODS ***********************/
	vector2 transform::get_pos() const { return { m_pos_.x, m_pos_.y }; }
	vector2 transform::get_scale() const { return { m_scale_.x, m_scale_.y }; }
	float transform::get_layer() const
	{
		// Layout children should be displayed on top of parents
		if (m_is_layout_child_)
			return m_layer_ + 0.1;
		return m_layer_;
	}
	float transform::get_width() const { return m_dimens_.x; }
	float transform::get_height() const { return m_dimens_.y; }
	float transform::get_rotation() const { return m_rotation_; }
	flip_axis transform::get_flip() const { return m_flip_axis_; }

	vector2 transform::get_transformed_pos(const float x, const float y) const
	{
		// Create a rotation matrix
		// Rotate by the number of degrees set
		glm::mat4 rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
		// Flip according to the flip axis/axes set
		switch (m_flip_axis_) {
			case flip_axis::flip_x:
				rot_mat = glm::rotate(rot_mat, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			case flip_axis::flip_y:
				rot_mat = glm::rotate(rot_mat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			case flip_axis::flip_xy:
				rot_mat = glm::rotate(rot_mat, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				rot_mat = glm::rotate(rot_mat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			default:;
		}
		// Get the new position, rotated around the object's center
		const glm::vec2 end_pos = glm::vec2((2 * m_pos_.x + m_dimens_.x) * m_scale_.x, (2 * m_pos_.y + m_dimens_.y) * m_scale_.y);
		const glm::vec4 rot_pos =
			rot_mat * glm::vec4(glm::vec3(x, y, 0.0f) - glm::vec3(end_pos.x / 2, end_pos.y / 2, 0.0f), 1.0f);
		const glm::vec3 pos = glm::vec3(rot_pos) + glm::vec3(end_pos.x / 2, end_pos.y / 2, 0.0f);
		return { pos.x, pos.y };
	}

	/******************** MUTATOR METHODS ************************/
	void transform::set_pos(const float x, const float y) { m_pos_ = glm::vec2(x, y); }
	void transform::set_scale(const float x, const float y) { m_scale_ = glm::vec2(x, y); }
	void transform::set_layer(const float layer) { m_layer_ = layer; }
	void transform::set_width(const float width) { m_dimens_.x = width; }
	void transform::set_height(const float height) { m_dimens_.y = height; }
	void transform::set_rotation(const float rotation) { m_rotation_ = rotation; }
	void transform::set_flip(const flip_axis flip_axis) { m_flip_axis_ = flip_axis; }
	void transform::set_layout_child(const bool is_layout_child) { m_is_layout_child_ = is_layout_child; }
}
