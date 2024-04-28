#pragma once

#include "../core/window.h"
#include "input_event.h"

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
			glfwSetCursorPosCallback(
				mWindow, [](GLFWwindow* aWindow, const double aPos_x, const double aPos_y) {

					// xpos	The new cursor x - coordinate, relative to the left edge of the content area.
					// ypos	The new cursor y - coordinate, relative to the top edge of the content area.

					const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

					//LOG_INFO("指针坐标 Cursor Pos Callback: x=" << aPos_x << "  y=" << aPos_y);

					int width, height;
					glfwGetFramebufferSize(aWindow, &width, &height);
					//LOG_INFO("帧缓冲的宽高 glfwGetFramebufferSize: width=" << width << "  height=" << height);

					// 因为我使用的图像的坐标是
					double x = aPos_x;
					double y = aPos_y;

					const auto event = new mouse_moved_event(x, y);
					data->mEvent_callback(event);
				}
			);
		}
	};
}
