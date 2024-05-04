#pragma once

#include "animation.h"

namespace cheap {
	class opacity_animation : public animation
	{
	public:
		opacity_animation(
			const float aOpacity,
			const double aBegin_time,
			const double aDuration,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::OPACITY,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aRelationship),
			mOpacity(aOpacity)
		{
			LOG();
		}
		opacity_animation(
			const float aOpacity,
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount,
			const relationship aRelationship,
			const bool aIs_shuttle)
			:
			animation(
				type::OPACITY,
				aIs_shuttle,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship),
			mOpacity(aOpacity)
		{
			LOG();
		}

		~opacity_animation()
		{

		}

		[[nodiscard]] float get(const double aCurrent_time) const
		{
			return mOpacity * static_cast<float>(get_frame(aCurrent_time));
		}

	private:
		float mOpacity;
	};
}