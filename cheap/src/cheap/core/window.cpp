#include "pch.h"
#include "window.h"

#ifdef CP_OPENGL_API


namespace cheap {
	bool window::is_fullscreen() const { return m_is_fullscreen_; }

	int window::get_width() const { return m_width_; }

	int window::get_height() const { return m_height_; }

	std::string window::get_title() const { return m_title_; }

	int window::get_layout_x() const { return m_x_; }

	int window::get_layout_y() const { return m_y_; }

	bool window::is_window_ptr_null() const { return m_raw_window_ == nullptr; }

	void window::resize(const int width, const int height)
	{
		if (is_window_ptr_null()) return;

		m_width_ = width;
	}
	void window::set_fullscreen(bool is_fullscreen)
	{
		if (is_window_ptr_null()) return;

	}
	void window::set_title(std::string title)
	{
		if (is_window_ptr_null()) return;

	}
	void window::set_layout(int x, int y)
	{
		if (is_window_ptr_null()) return;

	}


	window::window(const std::string& title,
		const int width, const int height,
		const int x, const int y,
		const bool is_fullscreen)
		: m_title_(title), m_width_(width), m_height_(height), m_x_(x), m_y_(y), m_is_fullscreen_(is_fullscreen)
	{

	}

	window::~window()
	{
		if (is_window_ptr_null()) { }


	}

}
#endif
