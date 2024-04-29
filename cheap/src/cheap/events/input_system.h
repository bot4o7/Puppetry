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

					//LOG_INFO("指针坐标 Cursor Pos Callback: x=" << aPos_x << "  y=" << aPos_y);

					const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

					int width, height;
					glfwGetFramebufferSize(aWindow, &width, &height);
					//LOG_INFO("帧缓冲的宽高 glfwGetFramebufferSize: width=" << width << "  height=" << height);

					// 因为我使用的图像的坐标是以屏幕中点为原点的 右手系 xOy 平面空间 -1~+1，而 opengl 给我的是 以屏幕右上角为原点的 左手系 xOy 像素点 0~width， 0~height
					// 假设是线性变化，设 我想要的百分比坐标是 x, y,   给的aPos_x/width, aPos_y/height 是 X0 Y0，然后设未知数 a b c d
					/**
					 * 则
					 *    ax + b = X0
					 *	  cy + d = Y0
					 *
					 *	  当 X0 = 0%, Y0 = 0%时， x = -1.0, y = 1.0
					 *	  当 X0 = 100%, Y0 = 100%时， x = 1.0, y = -1.0
					 *
					 *	  求解得到 a=2, b=-1, c=-2, d=1
					 */
					 //const double x = aPos_x / width * 2 - 1;
					 //const double y = aPos_y / height * -2 + 1;
					 //LOG_INFO("返回坐标 Cursor Pos Callback Return: x=" << x << "  y=" << y);
					const auto event = new mouse_moved_event(aPos_x / width * 2 - 1, aPos_y / height * -2 + 1);
					data->mEvent_callback(event);
				}
			);
		}
	};
}
