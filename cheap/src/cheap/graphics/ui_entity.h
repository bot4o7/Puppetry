#pragma once

#include "base/transform.h"
#include "drawable.h"

namespace cheap {
	class UIEntity
	{
	public:
		[[nodiscard]] virtual drawable* get_drawable() const = 0;
		[[nodiscard]] virtual transform* get_transform() const = 0;
		/* Visibility methods set if the entity should be rendered or not */
		[[nodiscard]] bool is_visible() const;
		virtual void show();
		virtual void hide();
		/* These methods set if the user can interact with the entity or not */
		[[nodiscard]] bool is_enabled() const;
		virtual void enable();
		virtual void disable();
		/* Use a label to distinguish UI entities */
		[[nodiscard]] std::string get_label() const;
		void set_label(const std::string& label);
		/* Get/Set functions that run depending on user input */
		[[nodiscard]] std::function<void()> get_left_click_function() const;
		[[nodiscard]] std::function<void()> get_right_click_function() const;
		[[nodiscard]] std::function<void()> get_hover_function() const;
		void                                on_left_click(const std::function<void()>& fun);
		void                                on_right_click(const std::function<void()>& fun);
		void                                on_hover(const std::function<void()>& fun);
		/* Functions for entities that are children of another entity */
		void set_parent_layout(transform* layout) const;
		void set_layout_position(float x, float y) const;
		void set_layout_position(layout_position horizontal, layout_position vertical) const;

	protected:
		explicit UIEntity(bool is_enabled = true);
		bool     m_is_visible_;
		bool     m_is_enabled_;

	private:
		std::function<void()> m_left_click_function_;
		std::function<void()> m_right_click_function_;
		std::function<void()> m_hover_function_;
		std::string m_label_;
	};
}
