#pragma once

#ifdef CP_OPENGL_API
#include "../events/event.h"
namespace cheap {
	/**
	 * Implemented with OpenGL API
	 */
	class window
	{
	public:
		[[nodiscard]] bool        is_fullscreen() const;
		[[nodiscard]] int         get_width() const;
		[[nodiscard]] int         get_height() const;
		[[nodiscard]] std::string get_title() const;
		[[nodiscard]] int         get_layout_x() const;
		[[nodiscard]] int         get_layout_y() const;
		[[nodiscard]] bool        is_window_ptr_null() const;


		void resize(const int width, const int height);
		void set_fullscreen(bool is_fullscreen);
		void set_title(std::string title);
		void set_layout(int x, int y);


		window(const std::string& title, int width, int height, int x, int y, bool is_fullscreen);
		~window();

	private:
		void* m_raw_window_;
		std::string m_title_;
		int m_width_, m_height_;
		int m_x_, m_y_;
		bool m_is_fullscreen_;
	};
}
#endif