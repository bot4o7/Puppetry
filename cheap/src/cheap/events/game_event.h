#pragma once
#include "event.h"
#include "event.h"

namespace cheap {
	class game_event : public event
	{
	public:
		GET_CATEGORY(event::category::game);

		game_event() = default;
		~game_event() override = default;
	};
}
