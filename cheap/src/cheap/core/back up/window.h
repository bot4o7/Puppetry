#pragma once

#ifdef CP_OPENGL_API
#include "../events/event.h"

namespace cheap {
	/**
	 * Implemented with OpenGL API
	 */
	class window
	{
		class window_data
		{
		public:
			unsigned int                width;
			unsigned int                height;
			std::function<void(event*)> event_callback;

			window_data(const unsigned int                 aWindow_width, const unsigned int aWindow_height,
				const std::function<void(event*)>& aEvent_callback_function);

			~window_data();
		};

	public:
		window(
			const std::string& aTitle,
			int                                window_width,
			int                                window_height,
			const std::function<void(event*)>& aEvent_callback_function,
			const std::function<void()>& aUpdate_callback,
			int                                x = 0,
			int                                y = 0,
			bool                               is_fullscreen = false
		);
		~window();

		// if x < 0, will not set layout_x
		// if y < 0, will not set layout_y
		void              set_layout(int x, int y) const;
		[[nodiscard]] int get_layout_x() const;
		[[nodiscard]] int get_layout_y() const;

		[[nodiscard]] float       get_aspect_ration() const;
		[[nodiscard]] int         get_start_width() const;
		[[nodiscard]] int         get_start_height() const;
		[[nodiscard]] int         get_width() const;
		[[nodiscard]] int         get_height() const;
		[[nodiscard]] std::string get_title() const;
		[[nodiscard]] bool        is_fullscreen() const;

		// for example, 16:9 and 4:3, the 16 and 4 are  numerators, the 9 and 3 are denominator
		// numer = numerator
		// denom = denominator
		static void set_aspect_ration(unsigned int aNumerator, unsigned int aDenominator);
		// if width < 0, will not set width 
		// if height < 0, will not set height
		void resize(int width, int height);
		void set_title(const std::string& title);
		void set_fullscreen(bool aIs_fullscreen);
		void set_icon(const std::string& image_path) const;

		[[nodiscard]] void* get_raw_window() const;
		[[nodiscard]] bool  is_closed() const;
		// save a function that will run before the app exits
		void on_close(std::function<void()> close_function);
		// before exiting, run all "close functions"
		void        run_close_functions() const;
		static void set_vsync(bool turn_on = true);
		static void clear();
		void        update() const;
		void        close() const;

	private:
		void* m_raw_window_;
		std::string m_title_;
		// background_color_rgba
		int         m_start_width_, mStart_height_;
		float       m_aspect_ration_;
		int         m_x_, m_y_;
		window_data m_window_data_;
		bool        m_is_fullscreen_;
		void* m_icons_;
		//void* m_icons_[1];
		std::vector<std::function<void()>> m_close_functions_;
		std::function<void()>              m_update_callback_;


		bool        m_init(bool turn_on_vsync = true);
		static bool m_init_GLFW();
		bool        m_init_window();
		static bool m_init_GLAD();
		void        set_up_window(bool turn_on_vsync = true);
		void        set_up_callbacks() const;


		[[nodiscard]] bool is_window_ptr_null() const;
	};
}
#endif
