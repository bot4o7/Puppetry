#pragma once
#include "entity.h"

namespace cheap {
	class graphics_entity : public  cheap::entity
	{
	public:
		enum class type
		{
			UI,
			OBJ,
			BG
		};

		type mType;
		float mX;
		float mY;
		float mZ;
		float mWidth;
		float mHeight;
		std::string mPic_file_path;
		bool mIs_RGBA;
		bool mIs_show;
		bool mIs_block_mouse;
		bool mIs_receive_mouse;
		bool mIs_receive_keyboard;

		// data
		// on_event_list
		// animation

		// if aWidth < 0, use aHeight to calculate Width,
		// if height < 0, use width to calculate h
		// if both < 0, set both = 1.0
		// else use both
		graphics_entity(
			unsigned int       aId,
			type               aType,
			float              aX,
			float              aY,
			float              aZ,
			float              aWidth,
			float              aHeight,
			const std::string& aPic_file_path,
			bool               aIs_RGBA,
			bool               aIs_show,
			bool               aIs_block_mouse,
			bool               aIs_receive_mouse,
			bool               aIs_receive_keyboard);


		~graphics_entity() override = default;

		[[nodiscard]] category get_category() const override
		{
			LOG();
			return category::GRAPHICS;
		}

		[[nodiscard]] bool is_category(const category aCategory) const override
		{
			LOG();
			return aCategory == category::GRAPHICS;
		}
	};
}
