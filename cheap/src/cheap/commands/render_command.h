#pragma once

#include "command.h"

namespace cheap {
	class render_command : public command
	{
	public:

		enum class instruction_type
		{
			PLAY_ANIMATION,
			STOP_ANIMATION,

			SWITCH_PAGE,

			ADD_LAYER,
			REMOVE_LAYER,
			UPDATE_LAYER
		};

		explicit render_command(
			const instruction_type aInstruction_type) :command(type::RENDER), mInstruction_type(aInstruction_type)
		{
		}

		~render_command() = default;

	protected:
		instruction_type mInstruction_type;
	};

}
