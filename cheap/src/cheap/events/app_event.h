#pragma once
#include "event.h"

namespace cheap {
	class app_event : event
	{
	public:
		enum class type
		{
			update,
			render,
			window_resize,
			window_close,
			window_move,
			window_fullscreen_mode_update
		};

		[[nodiscard]] category get_category() const override
		{
			return category::app;
		}

		~app_event() override = default;
	protected:
		app_event() = default;
	};

	class app_update_event :app_event
	{
	public:
		[[nodiscard]] int get_type() const override
		{
			return static_cast<int>(type::update);
		}

		[[nodiscard]] bool is_type(const int sub_type) const override
		{
			return sub_type == static_cast<int>(type::update);
		}

		app_update_event() = default;
		~app_update_event() override = default;
	};

	class app_render_event :app_event
	{
	public:
		[[nodiscard]] int get_type() const override
		{
			return static_cast<int>(type::render);
		}

		[[nodiscard]] bool is_type(const int sub_type) const override
		{
			return sub_type == static_cast<int>(type::render);
		}

		app_render_event() = default;
		~app_render_event() override = default;
	};

	class app_window_resize_event final :app_event
	{
	public:
		int m_width;
		int m_height;

		[[nodiscard]] int get_type() const override
		{
			return static_cast<int>(type::window_resize);
		}

		[[nodiscard]] bool is_type(const int sub_type) const override
		{
			return sub_type == static_cast<int>(type::window_resize);
		}

		app_window_resize_event(const int width, const int height) : m_width(width), m_height(height) { }
		~app_window_resize_event() override = default;
	};

	class app_window_move_event final :app_event
	{
	public:
		int m_x;
		int m_y;

		[[nodiscard]] int get_type() const override
		{
			return static_cast<int>(type::window_move);
		}

		[[nodiscard]] bool is_type(const int sub_type) const override
		{
			return sub_type == static_cast<int>(type::window_move);
		}

		app_window_move_event(const int x, const int y) : m_x(x), m_y(y) { }
		~app_window_move_event() override = default;
	};

	class app_window_close_event final : app_event
	{
	public:
		[[nodiscard]] int get_type() const override
		{
			return static_cast<int>(type::window_close);
		}

		[[nodiscard]] bool is_type(const int sub_type) const override
		{
			return sub_type == static_cast<int>(type::window_close);
		}

		app_window_close_event() = default;
		~app_window_close_event() override = default;
	};

	class app_window_fullscreen_mode_update_event : app_event
	{
	public:
		enum class mode
		{
			window,
			no_broad,
			fullscreen
		};
		mode m_mode;

		[[nodiscard]] int get_type() const override
		{
			return static_cast<int>(type::window_fullscreen_mode_update);
		}

		[[nodiscard]] bool is_type(const int sub_type) const override
		{
			return sub_type == static_cast<int>(type::window_fullscreen_mode_update);
		}

		explicit app_window_fullscreen_mode_update_event(const mode mode) : m_mode(mode) { }
		~app_window_fullscreen_mode_update_event() override = default;
	};
}
