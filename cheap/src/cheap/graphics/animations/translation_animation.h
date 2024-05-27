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
			const bool aIs_shuttle,
			graphics_entity* aGraphics_entity = nullptr
		)
			:
			animation(
				type::TRANSLATION,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aRelationship,
				aGraphics_entity),
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
			const bool aIs_shuttle,
			graphics_entity* aGraphics_entity = nullptr
		)
			:
			animation(
				type::TRANSLATION,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship,
				aGraphics_entity),
			mOffset{ aX,aY,aZ }
		{
			LOG();
		}

		~translation_animation()
		{
			LOG();
		}

		[[nodiscard]] glm::mat4 get(const double aCurrent_time)
		{
			const double factor = get_frame(aCurrent_time);
			//LOG_INFO("平移动画 当前时间 ： " << aCurrent_time << "  变换系数 ： " << factor);

			return transform::get_translate(
				mOffset[0] * factor,
				mOffset[1] * factor,
				mOffset[2] * factor);
		}

		void on_end_update_graphics_entity_vertices() override
		{
			mGraphics_entity->mGraphics_rectangle.update_translation(mOffset[0], mOffset[1], mOffset[2]);
		}
	private:
		float mOffset[3];
	};

}
