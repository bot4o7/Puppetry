#pragma once
#include "event.h"

namespace cheap {
	class game_event : public event
	{
	public:
		GET_CATEGORY(event::category::GAME);

		game_event() = default;
		~game_event() override = default;
	};
}
