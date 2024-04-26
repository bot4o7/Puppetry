#pragma once

#ifdef CP_OPENGL_API
#include "../events/event.h"

namespace cheap {

	class window
	{
		class window_data
		{
		public:
			unsigned int                mWidth;
			unsigned int                mHeight;
			std::function<void(event*)> mEvent_callback;

			window_data(const unsigned int                 aWindow_width, const unsigned int aWindow_height,
				const std::function<void(event*)>& aEvent_callback_function);

			~window_data();
		};

	public:
		window(
			const std::string& aTitle,
			int                                aWindow_width,
			int                                aWindow_height,
			const std::function<void(event*)>& aEvent_callback_function,
			const std::function<void()>& aUpdate_callback,
			int                                aX = 0,
			int                                aY = 0,
			bool                               aIs_fullscreen = false
		);
		~window();

		// if x < 0, will not set layout_x
		// if y < 0, will not set layout_y
		void              set_layout(int aX, int aY) const;
		[[nodiscard]] int get_layout_x() const;
		[[nodiscard]] int get_layout_y() const;

		[[nodiscard]] float       get_aspect_ration() const;
		[[nodiscard]] unsigned int         get_start_width() const;
		[[nodiscard]] unsigned int         get_start_height() const;
		[[nodiscard]] unsigned int         get_width() const;
		[[nodiscard]] unsigned int         get_height() const;
		[[nodiscard]] std::string get_title() const;
		[[nodiscard]] bool        is_fullscreen() const;

		// for example, 16:9 and 4:3, the 16 and 4 are  numerators, the 9 and 3 are denominator
		static void set_aspect_ration(unsigned int aNumerator, unsigned int aDenominator);
		// if width < 0, will not set width 
		// if height < 0, will not set height
		void resize(unsigned int aWidth, unsigned int aHeight);
		void set_title(const std::string& aTitle);
		void set_fullscreen(bool aIs_fullscreen);
		void set_icon(const std::string& aImage_path) const;

		[[nodiscard]] GLFWwindow* get_raw_window() const;
		[[nodiscard]] bool  is_closed() const;
		// save a function that will run before the app exits
		void on_close(std::function<void()> aClose_function);
		// before exiting, run all "close functions"
		void        run_close_functions() const;
		static void set_vsync(bool aTurn_on = true);
		static void clear();
		void        update() const;
		void        close() const;

	private:
		GLFWwindow* mRaw_window_;
		std::string mTitle;
		// background_color_rgba
		int         mStart_width, mStart_height;
		float       mAspect_ration;
		int         mX, mY;
		window_data mWindow_data;
		bool        mIs_fullscreen;
		GLFWimage* mIcons;
		//void* m_icons_[1];
		std::vector<std::function<void()>> mClose_functions_;
		std::function<void()>              mUpdate_callback_;

		bool        init(bool aIs_turn_on_vsync = true);
		static bool init_glfw();
		bool        init_window();
		static bool init_glad();
		void        set_up_window(bool aIs_turn_on_vsync = true);
		void        set_up_callbacks() const;

		[[nodiscard]] bool is_window_ptr_null() const;
	};
}
#endif
