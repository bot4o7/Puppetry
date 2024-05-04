#pragma once
#include "../graphics_rectangle.h"
#include "../../entity/graphics_entity.h"

namespace cheap {


	// -------------------- depth bound -----------------
	//orthogonal proj is right-hand-coords system, GL is left hand
	// because layout and translate transforms are related to
	// screen space, instead of the GL "-1.0 ~ 1.0" Standard Space, s
	// so the NEAREST -1.0f is for GL's left-hand-coords system
	#define LAYER_DEPTH_NEAREST (-1.0f)
	// 75% to deep bound
	#define LAYER_DEPTH_UI_INIT (-0.975f)
	// between UI and OBJ
	#define LAYER_DEPTH_UI_AND_OBJ_BOUND (-0.9f)
	// middle
	#define LAYER_DEPTH_OBJ_INIT (0.0f)
	// between OBJ and BG
	#define LAYER_DEPTH_OBJ_AND_BG_BOUND (0.9f)
	// 30% to deep bound
	#define LAYER_DEPTH_BG_INIT (0.97f)
	// see LAYER_DEPTH_NEAREST
	#define LAYER_DEPTH_FARTHEST 1.0f
	// -------------------- depth bound -----------------


	class layer
	{
	public:

		explicit layer(graphics_entity* aGraphics_entity, bool aPlaceholder_to_calculate_height)
			:
			mGraphics_entity(aGraphics_entity),
			mGraphics_rectangle(
				mGraphics_entity->mX,
				mGraphics_entity->mY,
				mGraphics_entity->mZ,
				mGraphics_entity->mWidth,
				true,
				mGraphics_entity->mPic_file_path.c_str(),
				mGraphics_entity->mIs_RGBA)
		{
			LOG();
		}
		explicit layer(bool aPlaceholder_to_calculate_width, graphics_entity* aGraphics_entity)
			:
			mGraphics_entity(aGraphics_entity),
			mGraphics_rectangle(
				mGraphics_entity->mX,
				mGraphics_entity->mY,
				mGraphics_entity->mZ,
				true,
				mGraphics_entity->mHeight,
				mGraphics_entity->mPic_file_path.c_str(),
				mGraphics_entity->mIs_RGBA)
		{
			LOG();
		}

		explicit layer(graphics_entity* aGraphics_entity)
			:
			mGraphics_entity(aGraphics_entity),
			mGraphics_rectangle(
				mGraphics_entity->mX,
				mGraphics_entity->mY,
				mGraphics_entity->mZ,
				mGraphics_entity->mWidth,
				mGraphics_entity->mHeight,
				mGraphics_entity->mPic_file_path.c_str(),
				mGraphics_entity->mIs_RGBA)
		{
			LOG();
		}

		// don't delete mGraphics_entity, because you may need it to create a new layer;
		~layer()
			= default;

		[[nodiscard]] graphics_entity::type get_type() const { return mGraphics_entity->mType; }
		[[nodiscard]] unsigned int get_id() const { return mGraphics_entity->mId; }
		[[nodiscard]] float get_depth() const { return mGraphics_entity->mZ; }
		[[nodiscard]] float get_opacity() const { return mGraphics_entity->mOpacity; }
		[[nodiscard]] bool                      is_show() const { return mGraphics_entity->mIs_show; }
		[[nodiscard]] bool                      is_block_mouse() const { return mGraphics_entity->mIs_block_mouse; }
		[[nodiscard]] bool                      is_receive_mouse() const { return mGraphics_entity->mIs_receive_mouse; }
		[[nodiscard]] bool                      is_receive_keyboard() const { return mGraphics_entity->mIs_receive_keyboard; }
		[[nodiscard]] const graphics_rectangle* get_graphics_rectangle() const { return &mGraphics_rectangle; }

		// TODO
		void update()
		{
			LOG();
			mGraphics_rectangle.update();
		}

		void set_anim(animation* aAnim) const
		{
			delete mGraphics_entity->mAnimation;
			mGraphics_entity->mAnimation = aAnim;
		}

		void stop_anim() const
		{
			mGraphics_entity->mAnimation->end();
		}

		void set_anim_begin(const double aBegin_time) const
		{
			mGraphics_entity->mAnimation->replay(aBegin_time);
		}

		[[nodiscard]] animation* get_anim() const
		{
			return mGraphics_entity->mAnimation;
		}

		void before_draw(const int aTexture_slot) const
		{
			//LOG();
			mGraphics_rectangle.before_draw(aTexture_slot);
		}

	private:
		graphics_entity* mGraphics_entity;
		graphics_rectangle               mGraphics_rectangle;
	};
}

