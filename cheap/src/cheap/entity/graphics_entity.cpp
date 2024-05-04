#include "pch.h"
#include "graphics_entity.h"

namespace cheap {
	graphics_entity::graphics_entity(
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
		mAnimation(nullptr)
	{
		LOG();
	}
}
