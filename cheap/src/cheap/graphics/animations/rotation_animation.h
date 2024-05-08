#pragma once

#include "animation.h"
#include "../base/transform.h"

namespace cheap {
	class rotation_animation : public animation
	{
	public:
		rotation_animation(
			const float aAngle_degree,
			const float aAxis_x,
			const float aAxis_y,
			const float aAxis_z,
			const double aBegin_time,
			const double aDuration,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::ROTATION,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aRelationship),
			mAngle_degree(aAngle_degree),
			mAxis{ aAxis_x,aAxis_y,aAxis_z }
		{
			LOG();
		}
		rotation_animation(
			const float aAngle_degree,
			const float aAxis_x,
			const float aAxis_y,
			const float aAxis_z,
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::ROTATION,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship),
			mAngle_degree(aAngle_degree),
			mAxis{ aAxis_x,aAxis_y,aAxis_z }
		{
			LOG();
		}

		// do the angle
		glm::mat4 get(const double aCurrent_time)
		{
			return
				transform::get_rotate(
					get_frame(aCurrent_time) * mAngle_degree,
					mAxis[0],
					mAxis[1],
					mAxis[2]
				);
		}

		~rotation_animation()
		{

		}

		// TODO
		void on_end_update_graphics_entity_vertices() override
		{
			//mGraphics_entity->mGraphics_rectangle
			//mGraphics_entity->mUniform
		}
	private:
		float mAngle_degree;
		float mAxis[3];
	};
}
