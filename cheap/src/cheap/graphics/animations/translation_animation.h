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

		[[nodiscard]] glm::mat4 get(const double aCurrent_time)
		{
			const double factor = get_frame(aCurrent_time);

			return transform::get_translate(
				mOffset[0] * factor,
				mOffset[1] * factor,
				mOffset[2] * factor);
		}

	private:
		float mOffset[3];
	};

}
