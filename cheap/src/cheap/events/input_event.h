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
			KEYBOARD,
			MOUSE
		};

		[[nodiscard]] virtual device get_device() const = 0;

		GET_CATEGORY(event::category::INPUT);

		~input_event() override = default;
	protected:
		input_event() = default;
	};

	#define GET_DEVICE(my_device) [[nodiscard]] device get_device() const override { return my_device; }

	// -------------- KeyEvent 键盘事件 -------------------
	class key_event : public input_event
	{
	public:
		int mCode;

		enum type
		{
			PRESSED,
			RELEASED,
			// TODO KeyType is not Implemented NOW
			TYPED
		};

		GET_DEVICE(input_event::device::KEYBOARD);

		~key_event() override = default;
	protected:
		explicit key_event(const int key) : mCode(key) { }
	};

	class key_pressed_event final : public key_event
	{
	public:
		bool mIs_repeat;

		GET_TYPE_AND_IS_TYPE(key_event::type::PRESSED);

		key_pressed_event(const int aKey, const bool aIs_repeat) : key_event(aKey), mIs_repeat(aIs_repeat) { }
		~key_pressed_event() override = default;
	};

	class key_released_event final : public key_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(key_event::type::RELEASED);


		explicit key_released_event(const int aKey) : key_event(aKey) { }
		~key_released_event() override = default;
	};
	// -------------- key_event 键盘事件 -------------------
	// -------------- MouseEvent 鼠标事件 -----------------
	class mouse_event : public input_event
	{
	public:
		int mButton;
		float mX, mY;

		enum type
		{
			// TODO does Mouse Event need to be MButtonE:ME, MPositionE:ME 要不要把按钮事件和位置事件分开
			PRESSED,   // 鼠标按键事件不需要坐标属性？还是需要
			RELEASED, // 如果不需要，那么把MB事件跟Key事件合并可能更简洁。 
			SCROLLED,
			MOVED
		};

		GET_DEVICE(input_event::device::MOUSE);

		~mouse_event() override;

	protected:
		explicit mouse_event(const int aButton) : mButton(aButton), mX(-1.0f), mY(-1.0f) { }

		mouse_event(const float aX, const float aY) : mButton(CP_MOUSE_BUTTON_LAST + 1), mX(aX), mY(aY) { }

		mouse_event(const int aButton, const float aX, const float aY) : mButton(aButton), mX(aX), mY(aY) { }
	};

	class mouse_pressed_event final :public  mouse_event
	{
	public:

		GET_TYPE_AND_IS_TYPE(mouse_event::type::PRESSED);

		mouse_pressed_event() = delete;
		explicit mouse_pressed_event(const int aButton) : mouse_event(aButton) { }
		mouse_pressed_event(const float aX, const float aY) = delete;
		mouse_pressed_event(const int aButton, const float aX, const float aY) : mouse_event(aButton, aX, aY) { }
	};

	class mouse_released_event final :public  mouse_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(mouse_event::type::RELEASED);

		mouse_released_event() = delete;
		explicit mouse_released_event(const int aButton) : mouse_event(aButton) { }
		mouse_released_event(const float aX, const float aY) = delete;
		mouse_released_event(const int aButton, const float aX, const float aY) : mouse_event(aButton, aX, aY) { }

		~mouse_released_event() override = default;
	};

	class mouse_scrolled_event final : public mouse_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(mouse_event::type::SCROLLED);

		mouse_scrolled_event() = delete;
		explicit mouse_scrolled_event(const int aButton) = delete;
		mouse_scrolled_event(const float aX, const float aY) : mouse_event(aX, aY) { }
		mouse_scrolled_event(const int aButton, const float aX, const float aY) = delete;

		~mouse_scrolled_event() override = default;
	};

	class mouse_moved_event : public mouse_event
	{
	public:
		GET_TYPE_AND_IS_TYPE(mouse_event::type::MOVED);

		mouse_moved_event() = delete;
		explicit mouse_moved_event(const int aButton) = delete;
		mouse_moved_event(const float aX, const float aY) : mouse_event(aX, aY) { }
		mouse_moved_event(const int aButton, const float aX, const float aY) = delete;

		~mouse_moved_event() override = default;
	};
	// -------------- MouseEvent 鼠标事件 -----------------
}
