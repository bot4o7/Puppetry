#include "pch.h"
#include "application.h"

#ifdef CP_OPENGL_API
namespace cheap {
	application::application()
		= default;

	application::~application()
	{
	}

	bool application::is_running()
	{
	}

	void application::update()
	{
	}

	void application::exit()
	{
	}

	void application::clear_event()
	{
	}

	void application::event_call_back(event* event)
	{
	}

	void application::run()
	{

		while (true);
	}
}
#endif
