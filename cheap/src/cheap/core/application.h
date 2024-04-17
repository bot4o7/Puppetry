#pragma once
#include "window.h"
#include "../events/event_system.h"

#ifdef CP_OPENGL_API
namespace cheap {
	class event;

	class application
	{
	public:
		application();
		virtual ~application();

		bool is_running();


		void run();
		void update();
		void exit();

		void clear_event();

		void event_call_back(event* event);

	private:
		window window_;
		event_system event_system_;
	};
}
#endif