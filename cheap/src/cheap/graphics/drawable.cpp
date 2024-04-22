#include "pch.h"
#include "drawable.h"

namespace cheap {
	/******************** STATIC VARIABLES ***********************/
	const unsigned int drawable::s_index_count = 6;

	/******************** STATIC FUNCTIONS ***********************/
	// Get the number of indices to render 1 rectangle (= 2 triangles)
	unsigned int drawable::get_index_count() { return s_index_count; }

	/******************** DRAWABLE METHODS **********************/
	drawable::drawable()
		: m_transform_(std::make_unique<transform>()), m_parent_transform_(nullptr)
	{
	}

	transform* drawable::get_transform() const { return m_transform_.get(); }
	const transform* drawable::get_parent_transform() const { return m_parent_transform_; }
	void drawable::set_parent_transform(transform* transform) { m_parent_transform_ = transform; }

	void drawable::set_parent_layout_pos(const layout_position horizontal, const layout_position vertical)
	{
		m_transform_->set_layout_child(true);
		m_parent_layout_pos_ = std::make_unique<parent_layout_pos>(parent_layout_pos({ horizontal, vertical }));
	}

	void drawable::set_parent_layout_coords(const float x, const float y)
	{
		m_transform_->set_layout_child(true);
		m_parent_layout_coords_ = std::make_unique<parent_layout_coords>(parent_layout_coords({ x, y }));
	}

	void drawable::update_transform() const
	{
		if (!m_parent_transform_)
			return;

		m_transform_->set_layout_child(true);
		m_transform_->set_layer(m_parent_transform_->get_layer());
		m_transform_->set_scale(m_parent_transform_->get_scale().x, m_parent_transform_->get_scale().y);
		if (m_parent_layout_pos_)
			m_transform_->set_pos(find_horizontal_pos(), find_vertical_pos());
		else if (m_parent_layout_coords_)
			m_transform_->set_pos(m_parent_transform_->get_pos().x + m_parent_layout_coords_->x,
				m_parent_transform_->get_pos().y + m_parent_layout_coords_->y);
	}

	float drawable::find_horizontal_pos() const
	{
		float x;
		// Set position on the x_axis
		if (m_parent_layout_pos_->horizontal == layout_position::left) {
			x = m_parent_transform_->get_pos().x;
		} else if (m_parent_layout_pos_->horizontal == layout_position::right) {
			x = m_parent_transform_->get_pos().x + m_parent_transform_->get_width() - m_transform_->get_width();
		} else // align at center
		{
			const float parent_middle = m_parent_transform_->get_pos().x + (m_parent_transform_->get_width() / 2);
			if (m_parent_layout_pos_->horizontal == layout_position::mid_left)
				x = (parent_middle - m_parent_transform_->get_pos().x) / 2 + m_parent_transform_->get_pos().x;
			else if (m_parent_layout_pos_->horizontal == layout_position::mid_right)
				x = (m_parent_transform_->get_pos().x + m_parent_transform_->get_width() - parent_middle) / 2 + parent_middle;
			else // align at center
				x = parent_middle;
			x -= m_transform_->get_width() / 2;
		}
		return x;
	}

	float drawable::find_vertical_pos() const
	{
		float y;
		// Set position on the y_axis
		if (m_parent_layout_pos_->vertical == layout_position::bottom) {
			y = m_parent_transform_->get_pos().y;
		} else if (m_parent_layout_pos_->vertical == layout_position::top) {
			y = m_parent_transform_->get_pos().y + m_parent_transform_->get_height() - m_transform_->get_height();
		} else // align at center
		{
			const float parent_middle = m_parent_transform_->get_pos().y + (m_parent_transform_->get_height() / 2);
			if (m_parent_layout_pos_->vertical == layout_position::mid_bottom)
				y = (parent_middle - m_parent_transform_->get_pos().y) / 2 + m_parent_transform_->get_pos().y;
			else if (m_parent_layout_pos_->vertical == layout_position::mid_top)
				y = (m_parent_transform_->get_pos().y + m_parent_transform_->get_height() - parent_middle) / 2 + parent_middle;
			else
				y = parent_middle;
			y -= m_transform_->get_height() / 2;
		}
		return y;
	}
}
