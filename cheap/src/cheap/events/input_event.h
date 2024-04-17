#pragma once
#include "event.h"
#include "input/mouse_button.h"
#include "input/key_code.h"

namespace cheap {
	class InputEvent : Event
	{
	public:
		enum class Device
		{
			Keyboard,
			Mouse
		};

		virtual Device GetDevice() const = 0;

		EventType GetType() const override { return EventType::Input; }

		~InputEvent() override = default;
	protected:
		InputEvent() = default;
	};
	// -------------- KeyEvent 键盘事件 -------------------
	class KeyEvent : InputEvent
	{
	public:
		int m_code;

		enum SubType
		{
			Pressed,
			Released,
			// TODO KeyType is not Implemented NOW
			Typed
		};

		Device GetDevice() const override { return Device::Keyboard; }

		~KeyEvent() override = default;
	protected:
		KeyEvent(const int key) : m_code(key) { }
	};

	class KeyPressedEvent : KeyEvent
	{
	public:
		int  GetSubType() const override { return Pressed; }
		bool IsSubType(int sub_type) const override
		{
			return sub_type == Pressed;
		}

		KeyPressedEvent(const int key) : KeyEvent(key) { }
		~KeyPressedEvent() override = default;
	};

	class KeyReleasedEvent : KeyEvent
	{
	public:
		int  GetSubType() const override { return Released; }
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == Released;
		}

		KeyReleasedEvent(const int key) : KeyEvent(key) { }
		~KeyReleasedEvent() override = default;
	};
	// -------------- KeyEvent 键盘事件 -------------------
	// -------------- MouseEvent 鼠标事件 -----------------
	class MouseEvent : InputEvent
	{
	public:
		int m_button;
		float m_x, m_y;

		enum SubType
		{
			// TODO does Mouse Event need to be MButtonE:ME, MPositionE:ME 要不要把按钮事件和位置事件分开
			Pressed,   // 鼠标按键事件不需要坐标属性？还是需要
			Released, // 如果不需要，那么把MB事件跟Key事件合并可能更简洁。 
			Scrolled,
			Moved
		};

		Device GetDevice() const override { return Device::Mouse; }

		~MouseEvent() override = default;

	protected:
		MouseEvent(const int button) : m_button(button), m_x(-1.0f), m_y(-1.0f) { }

		MouseEvent(const float x, const float y) : m_button(CP_MOUSE_BUTTON_LAST + 1), m_x(x), m_y(y) { }

		MouseEvent(const int button, const float x, const float y) : m_button(button), m_x(x), m_y(y) { }
	};

	class MousePressedEvent : MouseEvent
	{
	public:
		int GetSubType() const override { return Pressed; }
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == Pressed;
		}

		MousePressedEvent() = delete;
		MousePressedEvent(const int button) : MouseEvent(button) { }
		MousePressedEvent(const float x, const float y) = delete;
		MousePressedEvent(const int button, const float x, const float y) : MouseEvent(button, x, y) { }
	};

	class MouseReleasedEvent : MouseEvent
	{
	public:
		int GetSubType() const override { return Released; }
		bool IsSubType(int sub_type) const override
		{
			return sub_type == Released;
		}

		MouseReleasedEvent() = delete;
		MouseReleasedEvent(const int button) : MouseEvent(button) { }
		MouseReleasedEvent(const float x, const float y) = delete;
		MouseReleasedEvent(const int button, const float x, const float y) : MouseEvent(button, x, y) { }

		~MouseReleasedEvent() = default;
	};

	class MouseScrolledEvent : MouseEvent
	{
	public:
		int GetSubType() const override { return Scrolled; }
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == Scrolled;
		}

		MouseScrolledEvent() = delete;
		MouseScrolledEvent(const int button) = delete;
		MouseScrolledEvent(const float x, const float y) : MouseEvent(x, y) { }
		MouseScrolledEvent(const int button, const float x, const float y) = delete;

		~MouseScrolledEvent() = default;
	};

	class MouseMovedEvent : MouseEvent
	{
	public:
		int GetSubType() const override { return Moved; }
		bool IsSubType(const int sub_type) const override
		{
			return sub_type == Moved;
		}

		MouseMovedEvent() = delete;
		MouseMovedEvent(const int button) = delete;
		MouseMovedEvent(const float x, const float y) : MouseEvent(x, y) { }
		MouseMovedEvent(const int button, const float x, const float y) = delete;

		~MouseMovedEvent() = default;
	};
	// -------------- MouseEvent 鼠标事件 -----------------
}
