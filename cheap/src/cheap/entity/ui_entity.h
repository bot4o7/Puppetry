#pragma once

#include "graphics_entity.h"

namespace cheap {
	class ui_entity : public graphics_entity
	{
	public:

		ui_entity(
			unsigned int aId,
			float aX,
			float aY,
			float aZ,
			float aWidth,
			float aHeight,
			float aOpacity,
			const std::string& aPic_file_path,
			const bool aIs_RGBA,
			const bool aIs_visible,
			bool aIs_block_mouse,
			bool aIs_receive_mouse,
			bool aIs_receive_keyboard
		)
			:
			graphics_entity(
				aId,
				type::UI,
				aX,
				aY,
				aZ,
				aWidth,
				aHeight,
				aOpacity,
				aPic_file_path,
				aIs_RGBA,
				aIs_visible,
				aIs_block_mouse,
				aIs_receive_mouse,
				aIs_receive_keyboard)
		{

		}

		~ui_entity()
		{

		}


	};
}
