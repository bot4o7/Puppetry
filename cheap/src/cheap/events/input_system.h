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

		[[nodiscard]] bool is_key_being_pressed(
			const int aKey) const
		{
			return GLFW_PRESS == glfwGetKey(mWindow, aKey);
		}

		[[nodiscard]] bool is_mouse_being_pressed(
			const char aButton) const
		{
			return GLFW_PRESS == glfwGetMouseButton(mWindow, aButton);
		}
		[[nodiscard]] std::pair<double, double> get_mouse_position() const
		{
			double x, y;
			glfwGetCursorPos(mWindow, &x, &y);
			int width, height;
			glfwGetFramebufferSize(mWindow, &width, &height);

			return { x / width * 2 - 1, y / height * -2 + 1 };
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

			glfwSetKeyCallback(mWindow, [](GLFWwindow* aWindow, const int aKey, int aScancode, const int aAction, int aMods) {

				const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));


				switch (aAction) {
					case GLFW_PRESS:
						if (glfwGetKey(aWindow, aKey) == GLFW_PRESS)
							data->mEvent_callback(new key_repeat_event(aKey));
						else
							data->mEvent_callback(new key_press_event(aKey));
						break;
					case GLFW_REPEAT:
						LOG_INFO("This is GLFW_REPEAT,  this will be used in TEXT_INPUT in the future.");
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
