#pragma once
#include "event.h"

namespace cheap {
	class app_event : public event
	{
	public:
		enum class type
		{
			update,
			render,
			window_resize,
			window_close,
			//window_move,
			window_fullscreen_mode_update
		};

		GET_CATEGORY(event::category::app);

		~app_event() override = default;
	protected:
		app_event() = default;
	};

	class app_update_event : public app_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(app_event::type::update);

		app_update_event() = default;
		~app_update_event() override = default;
	};

	class app_render_event :public app_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(app_event::type::render);

		app_render_event() = default;
		~app_render_event() override = default;
	};

	class app_window_resize_event final :public app_event
	{
	public:
		unsigned int m_width;
		unsigned int m_height;

		GET_TYPE_AND_IS_TYPE(app_event::type::window_resize);

		app_window_resize_event(const unsigned int width, const unsigned int height) : m_width(width), m_height(height) { }
		~app_window_resize_event() override = default;
	};

	//class app_window_move_event final :public app_event
	//{
	//public:
	//	int m_x;
	//	int m_y;

	//	GET_TYPE_AND_IS_TYPE(app_event::type::window_move);

	//	app_window_move_event(const int x, const int y) : m_x(x), m_y(y) { }
	//	~app_window_move_event() override = default;
	//};

	class app_window_close_event final : public app_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(app_event::type::window_close);

		app_window_close_event() = default;
		~app_window_close_event() override = default;
	};

	class app_window_fullscreen_mode_update_event : public app_event
	{
	public:
		enum class fullscreen_mode
		{
			window,
			no_broad,
			fullscreen
		};

		fullscreen_mode m_mode;
		GET_TYPE_AND_IS_TYPE(app_event::type::window_fullscreen_mode_update);

		explicit app_window_fullscreen_mode_update_event(const fullscreen_mode mode) : m_mode(mode) { }
		~app_window_fullscreen_mode_update_event() override = default;
	};
}
