#pragma once

#include "animation.h"
#include "../base/transform.h"

namespace cheap {
	class translation_animation : public animation
	{
	public:

		translation_animation(
			const float aX,
			const float aY,
			const float aZ,
			const double aBegin_time,
			const double aDuration,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::TRANSLATION,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aRelationship),
			mOffset{ aX,aY,aZ }
		{
			LOG();
		}
		translation_animation(
			const float aX,
			const float aY,
			const float aZ,
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::TRANSLATION,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship),
			mOffset{ aX,aY,aZ }
		{
			LOG();
		}

		~translation_animation()
		{

		}

		void set(const double aCurrent_time) const
		{
			const double factor = get_frame(aCurrent_time);

			mGraphics_entity->mUniform.mTranslation = transform::get_translate(
				mOffset[0] * factor,
				mOffset[1] * factor,
				mOffset[2] * factor);
		}

		[[nodiscard]] glm::mat4 get(const double aCurrent_time) const
		{
			const double factor = get_frame(aCurrent_time);

			return transform::get_translate(
				mOffset[0] * factor,
				mOffset[1] * factor,
				mOffset[2] * factor);
		}

		void on_end_update_graphics_entity_vertices() override
		{
			//mGraphics_entity->mVertex_layout.update_translation(mOffset[0], mOffset[1], mOffset[2]);
			mGraphics_entity->mVertex_layout.update_translation(mOffset[0], mOffset[1], mOffset[2]);
		}
	protected:
		float mOffset[3];
	};

}
