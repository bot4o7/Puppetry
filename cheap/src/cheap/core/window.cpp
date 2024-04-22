#include "pch.h"
#include "window.h"

#include "../events/app_event.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#ifdef CP_OPENGL_API
namespace cheap {

	#define CP_GLFW_WINDOW_POINTER static_cast<GLFWwindow*>(m_raw_window_)
	#define CP_STB_IMAGE_ICON_POINTER static_cast<GLFWimage*>(m_icons_)

	window::window(
		const std::string& title,
		const int                          window_width,
		const int                          window_height,
		const std::function<void(event*)>& event_callback_function,
		const std::function<void()>& update_callback,
		const int                          x,
		const int                          y,
		const bool                         is_fullscreen)
		:
		m_raw_window_(nullptr),
		m_title_(title),
		/*m_background_color_rgba()*/
		m_start_width_(window_width),
		m_start_height_(window_height),
		m_aspect_ration_(16.0f / 9.0f),
		m_x_(x),
		m_y_(y),
		m_window_data_(window_width, window_height, event_callback_function),
		m_is_fullscreen_(is_fullscreen),
		m_icons_(/*new GLFWimage(0, 0, nullptr)*/),
		m_update_callback_(update_callback)
	{
		LOG();
		if (m_init()) {
			PRINTLN("window init successed.");
		} else {
			PRINTLN("window init failed.");
		}
	}
	window::~window()
	{
		LOG();
		if (is_window_ptr_null()) {
			PRINTLN("m_raw_window_pointer is nullptr.");
		} else {
			glfwDestroyWindow(CP_GLFW_WINDOW_POINTER);
			glfwTerminate();
		}
		if (CP_STB_IMAGE_ICON_POINTER != nullptr && CP_STB_IMAGE_ICON_POINTER->pixels)
			stbi_image_free(CP_STB_IMAGE_ICON_POINTER->pixels);
	}


	void window::set_layout(int x, int y) const
	{
		LOG();
		PRINTLN("set_layout() is not implemented yet.");
		if (is_window_ptr_null()) return;


	}

	int window::get_layout_x() const { return m_x_; }

	int window::get_layout_y() const { return m_y_; }

	bool window::is_window_ptr_null() const { return m_raw_window_ == nullptr; }



	float window::get_aspect_ration()const
	{
		return m_aspect_ration_;
	}

	int    window::get_start_width()const
	{
		return m_start_width_;
	}

	int     window::get_start_height()const
	{
		return m_start_height_;
	}

	int window::get_width() const { return m_window_data_.width; }

	int window::get_height() const { return m_window_data_.height; }

	std::string window::get_title() const { return m_title_; }

	bool window::is_fullscreen() const { return m_is_fullscreen_; }

	void window::set_aspect_ration(unsigned int numerator, unsigned int denominator)
	{
		LOG();
		PRINTLN("set_aspect_ration() is not implemented yet.");
	}

	void window::resize(const int width, const int height)
	{
		LOG();
		if (is_window_ptr_null()) return;

		if (width > -1)
			m_window_data_.width = width;

		if (height > -1)
			m_window_data_.height = height;
	}

	void window::set_title(const std::string& title)
	{
		LOG();
		if (is_window_ptr_null()) return;

		m_title_ = title;
		glfwSetWindowTitle(CP_GLFW_WINDOW_POINTER, m_title_.c_str());
	}

	void window::set_fullscreen(const bool is_fullscreen)
	{
		LOG();
		if (is_window_ptr_null()) return;

		if (is_fullscreen) {
			if (m_is_fullscreen_) return;

			// Save current position of the window
			glfwGetWindowPos(CP_GLFW_WINDOW_POINTER, &m_x_, &m_y_);
			GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);
			glfwSetWindowMonitor(CP_GLFW_WINDOW_POINTER, primary_monitor, 0, 0, video_mode->width, video_mode->height, video_mode->refreshRate);
		} else {
			if (!m_is_fullscreen_) return;
			glfwSetWindowMonitor(CP_GLFW_WINDOW_POINTER, nullptr, m_x_, m_y_, m_start_width_, m_start_height_, GLFW_DONT_CARE);
		}

		m_is_fullscreen_ = is_fullscreen;
	}

	void window::set_icon(const std::string& image_path) const
	{
		LOG();
		// Free previously loaded icons
		//if (static_cast<GLFWimage*>(m_icons_[0])->pixels)
		//	stbi_image_free(static_cast<GLFWimage*>(m_icons_[0])->pixels);
		if (CP_STB_IMAGE_ICON_POINTER->pixels)
			stbi_image_free(CP_STB_IMAGE_ICON_POINTER->pixels);

		// Flip the image vertically before loading
		stbi_set_flip_vertically_on_load(0);
		//static_cast<GLFWimage*>(m_icons_[0])->pixels = stbi_load(image_path.c_str(), &static_cast<GLFWimage*>(m_icons_[0])->width, &static_cast<GLFWimage*>(m_icons_[0])->height, 0, 4);
		//glfwSetWindowIcon(CP_GLFW_WINDOW_POINTER, 1, static_cast<GLFWimage*>(m_icons_[0]));
		CP_STB_IMAGE_ICON_POINTER->pixels = stbi_load(image_path.c_str(), &CP_STB_IMAGE_ICON_POINTER->width, &CP_STB_IMAGE_ICON_POINTER->height, 0, 4);
		glfwSetWindowIcon(CP_GLFW_WINDOW_POINTER, 1, CP_STB_IMAGE_ICON_POINTER);
	}

	void* window::get_raw_window() const
	{
		//LOG();
		return m_raw_window_;
	}

	bool window::is_closed() const
	{
		//LOG();
		return glfwWindowShouldClose(CP_GLFW_WINDOW_POINTER) == GL_TRUE;
	}

	void window::on_close(std::function<void()> close_function)
	{
		LOG();
		m_close_functions_.emplace_back(close_function);
	}

	void window::run_close_functions() const
	{
		LOG();
		for (auto& close_function : m_close_functions_)
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
		glfwSwapBuffers(CP_GLFW_WINDOW_POINTER);
	}

	void window::close() const
	{
		LOG();
		glfwSetWindowShouldClose(CP_GLFW_WINDOW_POINTER, GL_TRUE);
	}



	// success if return true
	bool window::m_init(const bool turn_on_vsync)
	{
		LOG();
		if (!m_init_GLFW())
			return false;

		if (!m_init_window())
			return false;

		if (!m_init_GLAD())
			return false;

		set_up_window(turn_on_vsync);

		set_up_callbacks();

		return true;
	}
	bool window::m_init_GLFW()
	{
		LOG();
		if (glfwInit())
			return true;

		PRINTLN("glfwInit() failed.");
		return false;
	}
	bool window::m_init_window()
	{
		LOG();
		m_raw_window_ = glfwCreateWindow(
			m_window_data_.width, m_window_data_.height,
			m_title_.c_str(),
			m_is_fullscreen_ ? glfwGetPrimaryMonitor() : nullptr,
			nullptr);

		if (m_raw_window_ == nullptr) {
			PRINTLN("m_init_window() failed.");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(CP_GLFW_WINDOW_POINTER);
		return true;
	}
	bool window::m_init_GLAD()
	{
		LOG();
		if (gladLoadGL())
			//if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			return true;

		PRINTLN("gladLoadGL() failed.");
		return false;
	}

	void window::set_vsync(const bool turn_on)
	{
		LOG();
		glfwSwapInterval(turn_on ? 1 : 0);
	}

	void window::set_up_window(const bool turn_on_vsync)
	{
		LOG();
		// Set 1 to limit the window's frame rate
		set_vsync(turn_on_vsync);
		// Set the background color
		glClearColor(0.2f, 0.7f, 0.3f, 0.5f);
		// Enable blending and properly rendering transparent pixels
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Associate the window data with the GLFW window
		glfwSetWindowUserPointer(CP_GLFW_WINDOW_POINTER, (void*)&m_window_data_);
		// Save the current position of the window
		glfwGetWindowPos(CP_GLFW_WINDOW_POINTER, &m_x_, &m_y_);
	}

	void window::set_up_callbacks() const
	{
		LOG();
		glfwSetFramebufferSizeCallback(
			CP_GLFW_WINDOW_POINTER, [](GLFWwindow* window, const int width, const int height) {
				LOG();

				const auto data = static_cast<window_data*>(glfwGetWindowUserPointer(window));

				const auto event = new app_window_resize_event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));

				data->event_callback(event);
			});

		glfwSetWindowCloseCallback(
			CP_GLFW_WINDOW_POINTER, [](GLFWwindow* window) {
				LOG();

				const auto data = static_cast<window_data*>(glfwGetWindowUserPointer(window));

				const auto event = new app_window_close_event();

				data->event_callback(event);
			});
	}
};
#endif
