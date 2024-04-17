#pragma once
#include "event.h"

namespace cheap {
	class game_event : event
	{
	public:

		game_event() = default;
		~game_event() override = default;
	};
}
