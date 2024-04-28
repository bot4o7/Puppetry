#include "pch.h"
#include "window.h"

#include "../events/app_event.h"
//#include "../events/input_event.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#ifdef CP_OPENGL_API
namespace cheap {

	window::window_data::window_data(const unsigned                     aWindow_width, const unsigned aWindow_height,
		const std::function<void(event*)>& aEvent_callback_function)
		: mWidth(aWindow_width), mHeight(aWindow_height), mEvent_callback(aEvent_callback_function)
	{
	}

	window::window_data::~window_data()
		= default;

	window::window(
		const std::string& aTitle,
		const int                          aWindow_width,
		const int                          aWindow_height,
		const std::function<void(event*)>& aEvent_callback_function,
		const std::function<void()>& aUpdate_callback,
		const int                          aX,
		const int                          aY,
		const bool                         aIs_fullscreen)
		: mRaw_window(nullptr),
		mTitle(aTitle),
		/*m_background_color_rgba()*/
		mStart_width(aWindow_width),
		mStart_height(aWindow_height),
		mAspect_ratio_numerator(DEFAULT_ASPECT_RATIO_NUMERATOR),
		mAspect_ratio_denominator(DEFAULT_ASPECT_RATIO_DENOMINATOR),
		mX(aX),
		mY(aY),
		mWindow_data(aWindow_width, aWindow_height, aEvent_callback_function),
		mIs_fullscreen(aIs_fullscreen),
		mIcons(/*new GLFWimage(0, 0, nullptr)*/),
		mUpdate_callback(aUpdate_callback)
	{
		LOG();
		if (init())
			PRINTLN("window init successed.");
		else
			PRINTLN("window init failed.");
	}

	window::~window()
	{
		LOG();
		if (is_window_ptr_null())
			PRINTLN("m_raw_window_pointer is nullptr.");
		else {
			glfwDestroyWindow(mRaw_window);
			glfwTerminate();
		}
		if (mIcons != nullptr && mIcons->pixels)
			stbi_image_free(mIcons->pixels);
	}

	void window::set_layout(int aX, int aY) const
	{
		LOG();
		PRINTLN("set_layout() is not implemented yet.");
		if (is_window_ptr_null()) return;
	}

	int window::get_layout_x() const { return mX; }

	int window::get_layout_y() const { return mY; }

	bool window::is_window_ptr_null() const { return mRaw_window == nullptr; }

	float window::get_aspect_ratio() const
	{
		return static_cast<float>(mAspect_ratio_numerator) / mAspect_ratio_denominator;
	}

	int window::get_aspect_ratio_numerator() const { return mAspect_ratio_numerator; }
	int window::get_aspect_ratio_denominator() const { return mAspect_ratio_denominator; }

	unsigned int window::get_start_width() const { return mStart_width; }

	unsigned int window::get_start_height() const { return mStart_height; }

	unsigned int window::get_width() const { return mWindow_data.mWidth; }

	unsigned int window::get_height() const { return mWindow_data.mHeight; }

	std::string window::get_title() const { return mTitle; }

	bool window::is_fullscreen() const { return mIs_fullscreen; }

	void window::set_aspect_ratio(const int aNumerator, const  int aDenominator)
	{
		LOG();
		mAspect_ratio_numerator = aNumerator;
		mAspect_ratio_denominator = aDenominator;
		keep_aspect_ratio();
	}
	void window::keep_aspect_ratio() const
	{
		glfwSetWindowAspectRatio(
			mRaw_window,
			mAspect_ratio_numerator,
			mAspect_ratio_denominator);
	}

	void window::resize(const unsigned int aWidth, const unsigned int aHeight)
	{
		LOG();
		if (is_window_ptr_null()) return;

		if (aWidth > -1)
			mWindow_data.mWidth = aWidth;

		if (aHeight > -1)
			mWindow_data.mHeight = aHeight;
	}

	void window::set_title(const std::string& aTitle)
	{
		LOG();
		if (is_window_ptr_null()) return;

		mTitle = aTitle;
		glfwSetWindowTitle(mRaw_window, mTitle.c_str());
	}

	void window::set_fullscreen(const bool aIs_fullscreen)
	{
		LOG();
		if (is_window_ptr_null()) return;

		if (aIs_fullscreen) {
			if (mIs_fullscreen) return;

			// Save current position of the window
			glfwGetWindowPos(mRaw_window, &mX, &mY);
			GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);
			glfwSetWindowMonitor(mRaw_window, primary_monitor, 0, 0, video_mode->width, video_mode->height,
				video_mode->refreshRate);
		} else {
			if (!mIs_fullscreen) return;
			glfwSetWindowMonitor(mRaw_window, nullptr, mX, mY, mStart_width, mStart_height,
				GLFW_DONT_CARE);
		}

		mIs_fullscreen = aIs_fullscreen;
	}

	void window::set_icon(const std::string& aImage_path) const
	{
		LOG();
		// Free previously loaded icons
		if (mIcons->pixels)
			stbi_image_free(mIcons->pixels);

		// Flip the image vertically before loading
		stbi_set_flip_vertically_on_load(0);
		mIcons->pixels = stbi_load(aImage_path.c_str(), &mIcons->width,
			&mIcons->height, nullptr, 4);
		glfwSetWindowIcon(mRaw_window, 1, mIcons);
	}

	GLFWwindow* window::get_raw_window() const
	{
		//LOG();
		return mRaw_window;
	}

	bool window::is_closed() const
	{
		//LOG();
		return glfwWindowShouldClose(mRaw_window) == GL_TRUE;
	}

	void window::on_close(std::function<void()> aClose_function)
	{
		LOG();
		mClose_functions.emplace_back(aClose_function);
	}

	void window::run_close_functions() const
	{
		LOG();
		for (auto& close_function : mClose_functions)
			close_function();
	}

	void window::clear()
	{
		LOG();
		// Clear the background with a given color as well as the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Process new events
		glfwPollEvents();
	}

	void window::update() const
	{
		LOG();
		// Swap front and back window buffers
		glfwSwapBuffers(mRaw_window);
	}

	void window::close() const
	{
		LOG();
		glfwSetWindowShouldClose(mRaw_window, GL_TRUE);
	}

	// success if return true
	bool window::init(const bool aIs_turn_on_vsync)
	{
		LOG();
		if (!init_glfw())
			return false;

		if (!init_window())
			return false;

		if (!init_glad())
			return false;

		set_up_window(aIs_turn_on_vsync);

		set_up_callbacks();

		return true;
	}

	bool window::init_glfw()
	{
		LOG();
		if (glfwInit())
			return true;

		PRINTLN("glfwInit() failed.");
		return false;
	}

	bool window::init_window()
	{
		LOG();
		mRaw_window = glfwCreateWindow(
			mWindow_data.mWidth, mWindow_data.mHeight,
			mTitle.c_str(),
			mIs_fullscreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr);

		if (mRaw_window == nullptr) {
			PRINTLN("m_init_window() failed.");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(mRaw_window);
		return true;
	}

	bool window::init_glad()
	{
		LOG();
		if (gladLoadGL())
			return true;

		PRINTLN("gladLoadGL() failed.");
		return false;
	}

	void window::set_vsync(const bool aTurn_on)
	{
		LOG();
		glfwSwapInterval(aTurn_on ? 1 : 0);
	}

	void window::set_up_window(const bool aIs_turn_on_vsync)
	{
		LOG();
		// Set 1 to limit the window's frame rate
		set_vsync(aIs_turn_on_vsync);
		// Set the background color
		glClearColor(0.2f, 0.7f, 0.3f, 0.5f);
		// Enable blending and properly rendering transparent pixels
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Associate the window data with the GLFW window
		glfwSetWindowUserPointer(mRaw_window, &mWindow_data);
		// Save the current position of the window
		glfwGetWindowPos(mRaw_window, &mX, &mY);
	}

	void window::set_up_callbacks() const
	{
		LOG();
		glfwSetFramebufferSizeCallback(
			mRaw_window,
			[](GLFWwindow* aWindow, const int aWidth, const int aHeight) {
				LOG();

				const auto data = static_cast<window_data*>(
					glfwGetWindowUserPointer(aWindow));

				const auto event = new
					app_window_resize_event(static_cast<unsigned int>(aWidth),
						static_cast<unsigned int>(aHeight));
				// make sure the viewport matches the new window dimensions; note that width and 
				// height will be significantly larger than specified on retina displays.
				glViewport(0, 0, aWidth, aHeight);
				data->mEvent_callback(event);
			});

		glfwSetWindowCloseCallback(
			mRaw_window, [](GLFWwindow* aWindow) {
				LOG();

				const auto data = static_cast<window_data*>(glfwGetWindowUserPointer(aWindow));

				const auto event = new app_window_close_event();

				data->mEvent_callback(event);
			});
		//	glfwSetCursorPosCallback(
		//		mRaw_window_, [](GLFWwindow* aWindow, const double aPos_x, const double aPos_y) {

		//			// xpos	The new cursor x - coordinate, relative to the left edge of the content area.
		//			// ypos	The new cursor y - coordinate, relative to the top edge of the content area.

		//			const auto data = static_cast<window::window_data*>(glfwGetWindowUserPointer(aWindow));

		//			LOG_INFO("Cursor Pos Callback: x=" << aPos_x << "  y=" << aPos_y);

		//			int width, height;
		//			glfwGetFramebufferSize(aWindow, &width, &height);
		//			LOG_INFO("glfwGetFramebufferSize: width=" << width << "  height=" << height);

		//			const float offset_x = (width - data->mWidth) / 2;
		//			const float offset_y = (height - data->mHeight) / 2;
		//			LOG_INFO("offset_x=" << offset_x << "  offset_y=" << offset_y);

		//			const auto event = new mouse_moved_event((double)(aPos_x - offset_x), (double)(data->mHeight - aPos_y + offset_y));
		//			LOG_INFO("aPos_x - offset_x=" << aPos_x - offset_x << "  data->mHeight - aPos_y + offset_y=" << data->mHeight - aPos_y + offset_y);
		//			data->mEvent_callback(event);
		//		}
		//	);
	}
};
#endif
