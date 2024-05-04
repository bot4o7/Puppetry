#pragma once

#include "animation.h"
#include "../base/transform.h"

namespace cheap {
	class scale_animation : public animation
	{
	public:

		scale_animation(
			const float aX_scale,
			const float aY_scale,
			const float aZ_scale,
			const double aBegin_time,
			const double aDuration,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::SCALE,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aRelationship),
			mScalar{ aX_scale - 1.f,aY_scale - 1.f,aZ_scale - 1.f }
		{
			LOG();
		}
		scale_animation(
			const float aX_scale,
			const float aY_scale,
			const float aZ_scale,
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::SCALE,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship),
			mScalar{ aX_scale - 1.f,aY_scale - 1.f,aZ_scale - 1.f }
		{
			LOG();
		}

		~scale_animation()
		{

		}

		[[nodiscard]] glm::mat4 get(const double aCurrent_time) const
		{
			const double factor = get_frame(aCurrent_time);
			if (factor > 1.)
				LOG_INFO("factor 炸了，操你妈，怎么 > 1 啊？？？");

			return transform::get_scale(
				1.f + mScalar[0] * factor,
				1.f + mScalar[1] * factor,
				1.f + mScalar[2] * factor);
		}

	private:
		float mScalar[3];
	};

}
