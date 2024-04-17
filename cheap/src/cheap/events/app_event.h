#pragma once
#include "event.h"

namespace cheap {
	class AppEvent : Event
	{
	public:
		enum SubType
		{
			AppUpdate,
			AppRender,
			AppWindowResize,
			AppWindowMove,
			AppWindowFullscreenModeUpdate
		};

		EventType GetType() const override
		{
			return EventType::App;
		}

		~AppEvent() override = default;
	protected:
		AppEvent() = default;
	};

	class AppUpdateEvent :AppEvent
	{
	public:
		int GetSubType() const override
		{
			return AppUpdate;
		}
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == AppUpdate;
		}

		AppUpdateEvent() = default;
		~AppUpdateEvent() override = default;
	};

	class AppRenderEvent :AppEvent
	{
	public:
		int GetSubType() const override
		{
			return AppUpdate;
		}
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == AppUpdate;
		}

		AppRenderEvent() = default;
		~AppRenderEvent() override = default;
	};

	class AppWindowResizeEvent :AppEvent
	{
	public:
		int m_width;
		int m_height;

		int GetSubType() const override
		{
			return AppWindowResize;
		}
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == AppWindowResize;
		}

		AppWindowResizeEvent(const int width, const int height) : m_width(width), m_height(height) { }
		~AppWindowResizeEvent() override = default;
	};

	class AppWindowMoveEvent :AppEvent
	{
	public:
		int m_x;
		int m_y;

		int GetSubType() const override
		{
			return AppWindowMove;
		}
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == AppWindowMove;
		}

		AppWindowMoveEvent(const int x, const int y) : m_x(x), m_y(y) { }
		~AppWindowMoveEvent() override = default;
	};

	class AppWindowFullscreenModeUpdateEvent : AppEvent
	{
	public:
		enum class Mode
		{
			Window,
			Broadless,
			Fullscreen
		};
		Mode m_mode;

		int GetSubType() const override
		{
			return AppWindowFullscreenModeUpdate;
		}
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == AppWindowFullscreenModeUpdate;
		}

		AppWindowFullscreenModeUpdateEvent(const Mode mode) : m_mode(mode) { }
		~AppWindowFullscreenModeUpdateEvent() override = default;
	};
}
