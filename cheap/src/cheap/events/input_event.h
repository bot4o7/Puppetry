#pragma once
#include "event.h"
#include "input/mouse_button.h"
#include "input/key_code.h"

namespace cheap {
	class input_event : public event
	{
	public:
		enum class device
		{
			keyboard,
			mouse
		};

		[[nodiscard]] virtual device get_device() const = 0;

		GET_CATEGORY(event::category::input);

		~input_event() override = default;
	protected:
		input_event() = default;
	};

	#define GET_DEVICE(my_device) [[nodiscard]] device get_device() const override { return my_device; }

	// -------------- KeyEvent 键盘事件 -------------------
	class key_event : public input_event
	{
	public:
		int m_code;

		enum type
		{
			pressed,
			released,
			// TODO KeyType is not Implemented NOW
			typed
		};

		GET_DEVICE(input_event::device::keyboard);

		~key_event() override = default;
	protected:
		explicit key_event(const int key) : m_code(key) { }
	};

	class key_pressed_event final : public key_event
	{
	public:
		bool m_is_repeat;

		GET_TYPE_AND_IS_TYPE(key_event::type::pressed);

		key_pressed_event(const int key, const bool is_repeat) : key_event(key), m_is_repeat(is_repeat) { }
		~key_pressed_event() override = default;
	};

	class key_released_event : public key_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(key_event::type::released);


		explicit key_released_event(const int key) : key_event(key) { }
		~key_released_event() override = default;
	};
	// -------------- key_event 键盘事件 -------------------
	// -------------- MouseEvent 鼠标事件 -----------------
	class mouse_event : public input_event
	{
	public:
		int m_button;
		float m_x, m_y;

		enum type
		{
			// TODO does Mouse Event need to be MButtonE:ME, MPositionE:ME 要不要把按钮事件和位置事件分开
			pressed,   // 鼠标按键事件不需要坐标属性？还是需要
			released, // 如果不需要，那么把MB事件跟Key事件合并可能更简洁。 
			scrolled,
			moved
		};

		GET_DEVICE(input_event::device::mouse);

		~mouse_event() override;

	protected:
		explicit mouse_event(const int button) : m_button(button), m_x(-1.0f), m_y(-1.0f) { }

		mouse_event(const float x, const float y) : m_button(CP_MOUSE_BUTTON_LAST + 1), m_x(x), m_y(y) { }

		mouse_event(const int button, const float x, const float y) : m_button(button), m_x(x), m_y(y) { }
	};

	class mouse_pressed_event final :public  mouse_event
	{
	public:

		GET_TYPE_AND_IS_TYPE(mouse_event::type::pressed);

		mouse_pressed_event() = delete;
		explicit mouse_pressed_event(const int button) : mouse_event(button) { }
		mouse_pressed_event(const float x, const float y) = delete;
		mouse_pressed_event(const int button, const float x, const float y) : mouse_event(button, x, y) { }
	};

	class mouse_released_event :public  mouse_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(mouse_event::type::released);

		mouse_released_event() = delete;
		explicit mouse_released_event(const int button) : mouse_event(button) { }
		mouse_released_event(const float x, const float y) = delete;
		mouse_released_event(const int button, const float x, const float y) : mouse_event(button, x, y) { }

		~mouse_released_event() override = default;
	};

	class mouse_scrolled_event : public mouse_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(mouse_event::type::scrolled);

		mouse_scrolled_event() = delete;
		explicit mouse_scrolled_event(const int button) = delete;
		mouse_scrolled_event(const float x, const float y) : mouse_event(x, y) { }
		mouse_scrolled_event(const int button, const float x, const float y) = delete;

		~mouse_scrolled_event() override = default;
	};

	class mouse_moved_event : public mouse_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(mouse_event::type::moved);

		mouse_moved_event() = delete;
		explicit mouse_moved_event(const int button) = delete;
		mouse_moved_event(const float x, const float y) : mouse_event(x, y) { }
		mouse_moved_event(const int button, const float x, const float y) = delete;

		~mouse_moved_event() override = default;
	};
	// -------------- MouseEvent 鼠标事件 -----------------
}
