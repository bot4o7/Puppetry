#pragma once
#include "entity.h"
#include "../graphics/graphics_rectangle.h"

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
		float mOpacity;
		std::string mPic_file_path;
		bool mIs_RGBA;
		bool mIs_show;
		bool mIs_block_mouse;
		bool mIs_receive_mouse;
		bool mIs_receive_keyboard;
		graphics_rectangle mGraphics_rectangle;

		// data
		// on_event_list
		// animation

		// if aWidth < 0, use aHeight to calculate Width,
		// if height < 0, use width to calculate h
		// if both < 0, set both = 1.0
		// else use both
		graphics_entity(
			const unsigned     aId,
			const type         aType,
			const float        aX,
			const float        aY,
			const float        aZ,
			const float        aWidth,
			const float        aHeight,
			const float        aOpacity,
			const std::string& aPic_file_path,
			const bool         aIs_RGBA,
			const bool         aIs_show,
			const bool         aIs_block_mouse,
			const bool         aIs_receive_mouse,
			const bool         aIs_receive_keyboard)
			:
			entity(aId),
			mType(aType),
			mX(aX),
			mY(aY),
			mZ(aZ),
			mWidth(aWidth),
			mHeight(aHeight),
			mOpacity(aOpacity),
			mPic_file_path(aPic_file_path),
			mIs_RGBA(aIs_RGBA),
			mIs_show(aIs_show),
			mIs_block_mouse(aIs_block_mouse),
			mIs_receive_mouse(aIs_receive_mouse),
			mIs_receive_keyboard(aIs_receive_keyboard),
			mGraphics_rectangle(
				mX,
				mY,
				mZ,
				mWidth,
				mHeight,
				mPic_file_path.c_str(),
				mIs_RGBA)
		{
			LOG();
		}
		graphics_entity(
			const unsigned     aId,
			const type         aType,
			const float        aX,
			const float        aY,
			const float        aZ,
			const bool         aPlaceholder_width,
			const float        aHeight,
			const float        aOpacity,
			const std::string& aPic_file_path,
			const bool         aIs_RGBA,
			const bool         aIs_show,
			const bool         aIs_block_mouse,
			const bool         aIs_receive_mouse,
			const bool         aIs_receive_keyboard)
			:
			entity(aId),
			mType(aType),
			mX(aX),
			mY(aY),
			mZ(aZ),
			mWidth(-1.f),
			mHeight(aHeight),
			mOpacity(aOpacity),
			mPic_file_path(aPic_file_path),
			mIs_RGBA(aIs_RGBA),
			mIs_show(aIs_show),
			mIs_block_mouse(aIs_block_mouse),
			mIs_receive_mouse(aIs_receive_mouse),
			mIs_receive_keyboard(aIs_receive_keyboard),
			mGraphics_rectangle(
				mX,
				mY,
				mZ,
				true,
				mHeight,
				mPic_file_path.c_str(),
				mIs_RGBA)
		{
			LOG();
		}
		graphics_entity(
			const unsigned     aId,
			const type         aType,
			const float        aX,
			const float        aY,
			const float        aZ,
			const float        aWidth,
			const bool         aPlaceholder_height,
			const float        aOpacity,
			const std::string& aPic_file_path,
			const bool         aIs_RGBA,
			const bool         aIs_show,
			const bool         aIs_block_mouse,
			const bool         aIs_receive_mouse,
			const bool         aIs_receive_keyboard)
			:
			entity(aId),
			mType(aType),
			mX(aX),
			mY(aY),
			mZ(aZ),
			mWidth(aWidth),
			mHeight(-1.f),
			mOpacity(aOpacity),
			mPic_file_path(aPic_file_path),
			mIs_RGBA(aIs_RGBA),
			mIs_show(aIs_show),
			mIs_block_mouse(aIs_block_mouse),
			mIs_receive_mouse(aIs_receive_mouse),
			mIs_receive_keyboard(aIs_receive_keyboard),
			mGraphics_rectangle(
				mX,
				mY,
				mZ,
				mWidth,
				true,
				mPic_file_path.c_str(),
				mIs_RGBA)
		{
			LOG();
		}

		~graphics_entity() override
		{
		}


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
