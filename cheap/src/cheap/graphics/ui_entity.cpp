#include "pch.h"
#include "ui_entity.h"

namespace cheap {
	UIEntity::UIEntity(bool is_enabled)
		: m_is_visible_(true), m_is_enabled_(is_enabled), m_label_("")
	{
	}

	bool UIEntity::is_visible() const { return m_is_visible_; }
	void UIEntity::show() { m_is_visible_ = true; }
	void UIEntity::hide() { m_is_visible_ = false; }

	bool UIEntity::is_enabled() const { return m_is_enabled_; }
	void UIEntity::enable() { m_is_enabled_ = true; }
	void UIEntity::disable() { m_is_enabled_ = false; }

	std::string UIEntity::get_label() const { return m_label_; }
	void UIEntity::set_label(const std::string& label) { m_label_ = label; }

	std::function<void()> UIEntity::get_left_click_function() const { return m_left_click_function_; }
	std::function<void()> UIEntity::get_right_click_function() const { return m_right_click_function_; }
	std::function<void()> UIEntity::get_hover_function() const { return m_hover_function_; }
	void UIEntity::on_left_click(const std::function<void()>& fun) { m_left_click_function_ = fun; }
	void UIEntity::on_right_click(const std::function<void()>& fun) { m_right_click_function_ = fun; }
	void UIEntity::on_hover(const std::function<void()>& fun) { m_hover_function_ = fun; }

	// Set a layout so that the entity's position is relative to it
	void UIEntity::set_parent_layout(transform* layout) const { get_drawable()->set_parent_transform(layout); }

	// Set the x and y coordinates inside the layout
	void UIEntity::set_layout_position(float x, float y) const
	{
		if (get_drawable()->get_parent_transform())
			get_drawable()->set_parent_layout_coords(x, y);
	}

	// Set the entity's alignment relative to the layout
	void UIEntity::set_layout_position(const layout_position horizontal, const layout_position vertical) const
	{
		/*	if (get_drawable()->get_parent_transform())
				get_drawable()->set_parent_layout_pos(horizontal, vertical);
		*/
	}
}
