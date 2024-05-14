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
			const bool aIs_shuttle,
			graphics_entity* aGraphics_entity = nullptr)
			:
			animation(
				type::SCALE,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aRelationship,
				aGraphics_entity),
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
			const bool aIs_shuttle,
			graphics_entity* aGraphics_entity = nullptr)
			:
			animation(
				type::SCALE,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship,
				aGraphics_entity
			),
			mScalar{ aX_scale - 1.f,aY_scale - 1.f,aZ_scale - 1.f }
		{
			LOG();
		}

		~scale_animation()
		{
			LOG();
		}

		[[nodiscard]] glm::mat4 get(const double aCurrent_time) const
		{
			const double factor = get_frame(aCurrent_time);
			if (factor > 1.0)
				LOG_INFO("factor 炸了，怎么 > 1 啊？？？");

			return transform::get_scale(
				1.f + mScalar[0] * factor,
				1.f + mScalar[1] * factor,
				1.f + mScalar[2] * factor);
		}


		void on_end_update_graphics_entity_vertices() override
		{
			LOG_INFO("animation end and update vertices");
			mGraphics_entity->mGraphics_rectangle.update_scale(mScalar[0] + 1.f, mScalar[1] + 1.f, mScalar[2] + 1.f);
			mGraphics_entity->mWidth *= (mScalar[0] + 1.f);
			mGraphics_entity->mHeight *= (mScalar[1] + 1.f);
		}

	protected:
		float mScalar[3];
	};

}
