﻿#pragma once
#include "event.h"

namespace cheap {
	class app_event : public event
	{
	public:
		enum class type
		{
			UPDATE,
			RENDER,
			WINDOW_RESIZE,
			WINDOW_CLOSE,
			WINDOW_FULLSCREEN_MODE_UPDATE
		};

		~app_event() override = default;

		GET_CATEGORY(event::category::APP);
		GET_TYPE_AND_IS_TYPE(type, mType);

	protected:
		explicit app_event(const type aType) :mType(aType)
		{
		}

	private:
		type mType;
	};

	class app_update_event final : public app_event
	{
	public:

		app_update_event() : app_event(type::UPDATE) { }
		~app_update_event() override = default;
	};

	class app_render_event final :public app_event
	{
	public:

		app_render_event() : app_event(type::RENDER) { }
		~app_render_event() override = default;
	};

	class app_window_resize_event final :public app_event
	{
	public:
		unsigned int mWidth;
		unsigned int mHeight;


		app_window_resize_event(const unsigned int aWidth, const unsigned int aHeight) : app_event(type::WINDOW_RESIZE), mWidth(aWidth), mHeight(aHeight) { }
		~app_window_resize_event() override = default;
	};

	class app_window_close_event final : public app_event
	{
	public:

		app_window_close_event() : app_event(type::WINDOW_CLOSE) { }
		~app_window_close_event() override = default;
	};

	class app_window_fullscreen_mode_update_event final : public app_event
	{
	public:
		enum class fullscreen_mode
		{
			WINDOW,
			NO_BROAD,
			FULLSCREEN
		};

		fullscreen_mode mMode;

		explicit app_window_fullscreen_mode_update_event(const fullscreen_mode aMode) :app_event(type::WINDOW_FULLSCREEN_MODE_UPDATE), mMode(aMode) { }
		~app_window_fullscreen_mode_update_event() override = default;
	};
}
