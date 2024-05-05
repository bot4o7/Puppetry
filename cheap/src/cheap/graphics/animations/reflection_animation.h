#pragma once

#include "scale_animation.h"

namespace cheap {
	// 对称动画可以用scale来实现：把 xyz变为负数就能做到翻转
		// 暂时还不想做“沿任意轴翻转”
		// 现在这个 对称动画 就是一个 缩放动画 scale_animation 的包装而已
	// 额，如果理解了 缩放动画 可以实现对称，那就没必要用这个
	#define NO_REFLECTION (-1.f)


	class reflection_animation : public scale_animation
	{
	public:


		// 额，如果理解了 缩放动画 可以实现对称，那就没必要用这个
		reflection_animation(
			const double aBegin_time,
			const double aDuration,
			const relationship aRelationship,
			const bool aIs_shuttle,
			const float aX_scale = NO_REFLECTION,
			const float aY_scale = NO_REFLECTION,
			const float aZ_scale = NO_REFLECTION)
			:
			scale_animation(
				-aX_scale,
				-aY_scale,
				-aZ_scale,
				aBegin_time,
				aDuration,
				aRelationship,
				aIs_shuttle
			)
		{
			LOG();
		}
		// 额，如果理解了 缩放动画 可以实现对称，那就没必要用这个
		reflection_animation(
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount,
			const relationship aRelationship,
			const bool aIs_shuttle,
			const float aX_scale = NO_REFLECTION,
			const float aY_scale = NO_REFLECTION,
			const float aZ_scale = NO_REFLECTION)
			:
			scale_animation(
				-aX_scale,
				-aY_scale,
				-aZ_scale,
				aBegin_time,
				aDuration,
				aCount,
				aRelationship,
				aIs_shuttle
			)
		{
			LOG();
		}
		~reflection_animation()
		{

		}
	};
}
