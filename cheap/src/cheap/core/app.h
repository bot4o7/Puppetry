#pragma once
#include "window.h"
#include "../events/event_system.h"
#include "../events/input_system.h"
#include "../graphics/renderer.h"

#ifdef CP_OPENGL_API
namespace cheap {
	#define DEFAULT_TITLE "cheap game"

	class app
	{
	public:
		explicit app(unsigned int aWidth = 1184, unsigned int aHeight = 666);
		~app();


		void run();

		void clear() const;
		void update() const;
		bool is_running() const;
		void exit();

		// functions of other classes use this function to pass event to app(this class)
		void on_event(event* aNew_event);

		// input* get_input() const;
		window* get_window() const;

	private:
		// use shared pointers for each subsystem so that app can be copied

		std::shared_ptr<window> mWindow;
		std::shared_ptr<renderer> mRenderer;

		std::shared_ptr<input_system> mInput_system;
		std::shared_ptr<event_system> mEvent_system;

	};
}
#endif