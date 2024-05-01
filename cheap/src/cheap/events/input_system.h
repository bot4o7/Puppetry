#pragma once

#include "../core/window.h"
#include "input_event.h"
#include "input/key_code.h"
#include "input/mouse_button.h"

namespace cheap {

	class input_system
	{
	public:

		// normal cursor
		explicit input_system(GLFWwindow* aWindow)
			:
			mWindow(aWindow)
		{
			LOG();
			set_up_callbacks();
		}

		~input_system()
		{
			LOG();
		}

	private:
		GLFWwindow* mWindow;

		void set_up_callbacks() const
		{
			glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			LOG();
			// Mouse Cursor Pos Callback
			glfwSetCursorPosCallback(
				mWindow, [](GLFWwindow* aWindow, const double aPos_x, const double aPos_y) {

					const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

					int width, height;
					glfwGetFramebufferSize(aWindow, &width, &height);

					const auto event = new mouse_move_event(aPos_x / width * 2 - 1, aPos_y / height * -2 + 1);
					data->mEvent_callback(event);
				}
			);

			// key callback
			// The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE. Events with GLFW_PRESS and GLFW_RELEASE actions are emitted for every key press. Most keys will also emit events with GLFW_REPEAT actions while a key is held down.
			// Key events with GLFW_REPEAT actions are intended for text input. They are emitted at the rate set in the user's keyboard settings. At most one key is repeated even if several keys are held down. GLFW_REPEAT actions should not be relied on to know which keys are being held down or to drive animation. Instead you should either save the state of relevant keys based on GLFW_PRESS and GLFW_RELEASE actions, or call glfwGetKey, which provides basic cached key state.
			//具有 GLFW_REPEAT 操作的按键事件用于文本输入。它们以用户键盘设置中设置的速率发出。即使同时按住多个键，也最多重复一个键。 GLFW_REPEAT 不应依赖操作来了解哪些键被按下或驱动动画。相反，您应该根据 GLFW_PRESS 和 GLFW_RELEASE 操作保存相关键的状态，或者调用 glfwGetKey，它提供基本的缓存键状态。
			//
			// glfwGetKey : The returned state is one of GLFW_PRESS or GLFW_RELEASE.
			// 返回的状态是 GLFW_PRESS 或 GLFW_RELEASE 之一。
			glfwSetKeyCallback(mWindow, [](GLFWwindow* aWindow, const int aKey, int aScancode, const int aAction, int aMods) {

				const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

				// glfwGetKey 要么返回 PRESS 要么返回 RELEASE
				// 官方说应该用这个来判断按键是 按住，还是按下
				// 那么我猜，当是按住的时候，glfwGetKey返回 PRESS，
				// 反之返回 RELEASE
				//
				// 而 aAction 也是
				switch (aAction) {
					case GLFW_PRESS:
						if (glfwGetKey(aWindow, aKey) == GLFW_PRESS)
							data->mEvent_callback(new key_repeat_event(aKey));
						else
							data->mEvent_callback(new key_press_event(aKey));
						break;
					case GLFW_REPEAT:
						LOG_INFO("This is GLFW_REPEAT");
						break;
					case GLFW_RELEASE:
						data->mEvent_callback(
							new key_release_event(aKey)
						);
						break;
					default:
						LOG_INFO("GLFW key callback pass a UNKNOW key event action");
				}
				}
			);

			glfwSetCursorEnterCallback(mWindow, [](GLFWwindow* aWindow, const int aIs_entered) {
				const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

				if (aIs_entered)
					data->mEvent_callback(new mouse_enter_event());
				else
					data->mEvent_callback(new mouse_leave_event());
				});

			glfwSetScrollCallback(mWindow,
				[](GLFWwindow* aWindow,
					const double aX_offset,
					const double aY_offset) {
						const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));
						data->mEvent_callback(
							new mouse_scroll_event(aX_offset, aY_offset));
				});

			glfwSetMouseButtonCallback(mWindow,
				[](GLFWwindow* aWindow,
					const int   aButton,
					const int   aAction, int aMods) {

						const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

						if (aAction == GLFW_PRESS) {
							if (glfwGetMouseButton(aWindow, aButton))
								data->mEvent_callback(new mouse_repeat_event(aButton));
							else
								data->mEvent_callback(new mouse_press_event(aButton));
						} else
							data->mEvent_callback(new mouse_release_event(aButton));
				});

		}


	};
}
