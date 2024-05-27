#pragma once
#include "event.h"
#include "input/mouse_button.h"

namespace cheap {

	class input_event : public event
	{
	public:

		enum class type
		{
			KEYBOARD,
			MOUSE
		};

		explicit input_event(const type aType) : mType(aType)
		{
			LOG();
		}
		~input_event() override = default;

		GET_CATEGORY(event::category::INPUT);

		GET_TYPE_AND_IS_TYPE(type, mType);

	private:
		type mType;
	};


	#define GET_ACTION(action_name, arg) [[nodiscard]] action_name get_action() const\
	{\
		return arg;\
	}\
	[[nodiscard]] bool is_action(action_name aAction) const\
	{\
		return aAction == get_action();\
	}


	// -------------- KeyEvent 键盘事件 -------------------
	class key_event : public input_event
	{
	public:
		int mKey;

		enum action
		{
			PRESS,
			REPEAT,
			RELEASE,
			TEXT_INPUT
		};

		~key_event() override = default;

		GET_ACTION(action, mAction);

	protected:
		explicit key_event(const int aKey, action aAction) : input_event(type::KEYBOARD), mKey(aKey), mAction(aAction)
		{
			LOG();
		}
	private:
		action mAction;
	};

	class key_press_event final : public key_event
	{
	public:
		explicit key_press_event(const int aKey) : key_event(aKey, action::PRESS)
		{
			LOG();
		}
		~key_press_event() override = default;
	};

	class key_repeat_event final : public key_event
	{
	public:
		explicit key_repeat_event(const int aKey) : key_event(aKey, action::REPEAT)
		{
			LOG();
		}
		~key_repeat_event() override = default;
	};

	class key_release_event final : public key_event
	{
	public:
		explicit key_release_event(const int aKey) : key_event(aKey, action::RELEASE)
		{
			LOG();
		}
		~key_release_event() override = default;
	};
	class key_text_input_event final : public key_event
	{
	public:
		explicit key_text_input_event(const int aKey) : key_event(aKey, action::TEXT_INPUT)
		{
			LOG();
		}
		~key_text_input_event() override = default;
	};
	// -------------- key_event 键盘事件 -------------------
	// -------------- MouseEvent 鼠标事件 -----------------
	class mouse_event : public input_event
	{
	public:
		char mButton;

		enum action
		{
			MOVE,
			ENTER,
			LEAVE,
			PRESS,
			REPEAT,
			RELEASE,
			SCROLL
		};

		~mouse_event() override = default;

		GET_ACTION(action, mAction);

	protected:
		mouse_event(char aButton, action aAction) : input_event(type::MOUSE), mButton(aButton), mAction(aAction)
		{
			LOG();
		}
	private:
		action mAction;
	};

	class mouse_move_event : public mouse_event
	{
	public:
		double mX;
		double mY;

		mouse_move_event(const double aX, const double aY) : mouse_event(CP_MOUSE_MOVE, action::MOVE), mX(aX), mY(aY)
		{
			LOG();
		}

		~mouse_move_event() override = default;
	};

	class mouse_enter_event : public mouse_event
	{
	public:
		mouse_enter_event() : mouse_event(CP_MOUSE_ENTER, action::ENTER)
		{
			LOG();
		}
		~mouse_enter_event() override = default;
	};

	class mouse_leave_event : public mouse_event
	{
	public:
		mouse_leave_event() : mouse_event(CP_MOUSE_LEAVE, action::LEAVE)
		{
			LOG();
		}
		~mouse_leave_event() override = default;
	};

	class mouse_press_event final :public  mouse_event
	{
	public:
		explicit mouse_press_event(const char aButton) :mouse_event(aButton, action::PRESS)
		{
			LOG();
		}
		~mouse_press_event() override = default;
	};
	class mouse_repeat_event final :public  mouse_event
	{
	public:
		explicit mouse_repeat_event(const char aButton) :mouse_event(aButton, action::REPEAT)
		{
			LOG();
		}
		~mouse_repeat_event() override = default;
	};
	class mouse_release_event final :public  mouse_event
	{
	public:
		explicit mouse_release_event(const char aButton) :mouse_event(aButton, action::RELEASE)
		{
			LOG();
		}
		~mouse_release_event() override = default;
	};

	class mouse_scroll_event : public mouse_event
	{
	public:
		double mX_offset;
		double mY_offset;

		mouse_scroll_event(const double aX, const double aY) : mouse_event(CP_MOUSE_SCROLL, action::SCROLL), mX_offset(aX), mY_offset(aY)
		{
			LOG();
		}

		~mouse_scroll_event() override = default;
	};
	// -------------- MouseEvent 鼠标事件 -----------------
}
