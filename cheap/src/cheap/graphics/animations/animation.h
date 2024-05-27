#pragma once

#include "../../entity/graphics_entity.h"

namespace cheap {

	#define PI 3.1415926535897931

	class animation
	{
	public:
		enum class type
		{
			// 平移
			TRANSLATION,
			// 旋转
			ROTATION,
			// 缩放
			SCALE,
			// 对称
			REFLECTION,
			// 切变
			SHIFT,
			// 颜色
			COLOR,
			// 不透明度
			OPACITY
		};

		enum class relationship
		{
			// y = ax
			// a * duration = 1
			LINEAR,
			// y = sin(ax)
			// sin(a duration) = 1 = sin(90°) = sin(PI/2)
			// a = 90°/duration = PI / 2*duration
			SIN,
			// y = ax^2
			// a duration^2 = 1
			// a = 1/duration*duration
			SQUARE,
		};


		[[nodiscard]] double get_frame(const double aCurrent_time) const
		{
			return  get_y(aCurrent_time - mBegin_time);
		}
		// 根据所给时间进行一次动画
		animation(
			const type  aType,
			const bool aIs_shuttle,
			const double aBegin_time,
			const double aDuration,
			const relationship aRelationship,
			graphics_entity* aGraphics_entity = nullptr
		)
			:
			mGraphics_entity(aGraphics_entity),
			mType(aType),
			mRelationship(aRelationship),
			mCount(1),
			mIs_loop(false),
			mIs_shuttle(aIs_shuttle),
			mBegin_time(aBegin_time),
			mDuration(aDuration),
			mEnd_time(aBegin_time + aDuration),
			mParam(calculate_param(aRelationship))
		{
			if (mGraphics_entity != nullptr)
				mGraphics_entity->mIs_playing_animation = true;
			else {
				LOG_INFO("is_to_play(): mGraphics_entity is nullptr");
			}
		}

		// 根据所给时间进行 count 次动画
		animation(
			const type  aType,
			const bool aIs_shuttle,
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount,
			const relationship aRelationship,
			graphics_entity* aGraphics_entity = nullptr)
			:
			mGraphics_entity(aGraphics_entity),
			mType(aType),
			mRelationship(aRelationship),
			mCount(aCount),
			mIs_loop(false),
			mIs_shuttle(aIs_shuttle),
			mBegin_time(aBegin_time),
			mDuration(aDuration),
			mEnd_time(aBegin_time + aDuration),
			mParam(calculate_param(aRelationship))
		{
			LOG();
			if (mGraphics_entity != nullptr)
				mGraphics_entity->mIs_playing_animation = true;
			else {
				LOG_INFO("is_to_play(): mGraphics_entity is nullptr");
			}
		}
		// 根据所给时间进行 循环动画
		animation(
			const type  aType,
			const bool aIs_shuttle,
			const double aBegin_time,
			const double aDuration,
			const bool aIs_loop,
			const relationship aRelationship,
			graphics_entity* aGraphics_entity = nullptr)
			:
			mGraphics_entity(aGraphics_entity),
			mType(aType),
			mRelationship(aRelationship),
			mCount(1),
			mIs_loop(aIs_loop),
			mIs_shuttle(aIs_shuttle),
			mBegin_time(aBegin_time),
			mDuration(aDuration),
			mEnd_time(aBegin_time + aDuration),
			mParam(calculate_param(aRelationship))
		{
			LOG();
			if (mGraphics_entity != nullptr)
				mGraphics_entity->mIs_playing_animation = true;
			else {
				LOG_INFO("is_to_play(): mGraphics_entity is nullptr");
			}
		}
		// 给一个未设置 开始时间、次数的非循环动画， 但是有运行周期
		animation(
			const type  aType,
			const bool aIs_shuttle,
			const double aDuration,
			const relationship aRelationship,
			graphics_entity* aGraphics_entity = nullptr)
			:
			mGraphics_entity(aGraphics_entity),
			mType(aType),
			mRelationship(aRelationship),
			mCount(0),
			mIs_loop(false),
			mIs_shuttle(aIs_shuttle),
			mBegin_time(0.0),
			mDuration(aDuration),
			mEnd_time(aDuration),
			mParam(calculate_param(aRelationship))
		{
			LOG();
			if (mGraphics_entity != nullptr)
				mGraphics_entity->mIs_playing_animation = true;
			else {
				LOG_INFO("is_to_play(): mGraphics_entity is nullptr");
			}
		}

		virtual ~animation()
		{
			LOG();
		}

		[[nodiscard]] type get_type()const { return mType; }

		[[nodiscard]] bool is_loop() const { return mIs_loop; }

		// 1. 是否有剩余次数
		// 2. 是否到了开始时间
		// 3. 是否已经到了结束时间
		// 4. 即使到了结束时间，是否仍有剩余次数，或是无限循环
		bool is_to_play(
			const double current_time)
		{
			if (is_finished()) return false;
			//LOG_INFO("is not finished");

			if (is_not_begin(current_time)) return false;
			//LOG_INFO("is begin");

			if (is_end(current_time)) return false;
			//LOG_INFO("is not end");

			return true;
		}

		void update_time(
			const double aBegin_time)
		{
			mBegin_time = aBegin_time;
			mEnd_time = mBegin_time + mDuration;
		}
		void update_time(
			const double aBegin_time,
			const double aDuration)
		{
			mBegin_time = aBegin_time;
			mEnd_time = mBegin_time + aDuration;
		}

		void update_time()
		{
			mBegin_time = mEnd_time;
			mEnd_time += mDuration;
		}

		// reset Begin, End
		// set Count = 1
		void replay(
			const double       aBegin_time,
			const double       aDuration = -1)
		{
			if (aDuration < 0)
				update_time(aBegin_time);
			else
				update_time(aBegin_time, aDuration);

			mCount = 1;
		}
		// reset Begin, End, Count
		void replay(
			const unsigned int       aCount,
			const double       aBegin_time,
			const double       aDuration = -1)
		{
			if (aDuration < 0)
				update_time(aBegin_time);
			else
				update_time(aBegin_time, aDuration);

			mCount = aCount;
		}

		// TODO
		// 强制 end，  强制 end 需要让动画直接进行到最后一帧。
		// 我首先取消掉 is_loop，
		// 然后让动画结束时间等于开始时间
		// 再设置 count = 1，
		//
		// 这样下次渲染时，会直接渲染最后一帧，并且渲染结束后count 为 0。
		// TODO 这个重要吗？
		// 但是 这样做， 会损失初始的 duration 信息。

		// 复合动画怎么终止呢？ 
		void end()
		{
			// TODO
			mCount = 1;
			mIs_loop = false;
			mEnd_time = mBegin_time;
			mBegin_time -= mDuration;
		}

		// 没有剩余次数 count，就无法进行
		[[nodiscard]] bool is_finished() const
		{
			return mCount < 1;
		}
		// 到了开始时间 begin_time
		[[nodiscard]] bool is_not_begin(const double aCurrent_time) const { return aCurrent_time < mBegin_time; }
		// 到了结束时间 end_time 且无剩余次数、且非循环
		bool is_end(const double aCurrent_time)
		{
			if (aCurrent_time < mEnd_time) return false;

			//LOG_INFO("mCount = " << mCount);
			if (is_loop() || --mCount > 0)
				return update_replay_time_and_return_false();

			//LOG_INFO("--mCount = " << mCount);


			mGraphics_entity->mIs_playing_animation = false;
			// 这句的意思是，如果是 shuttle 往复动画，动画起点与终点的状态相同，就不需要更改 顶点信息
			if (mIs_shuttle) return true;

			// 如果 gfx entity 不为空，在动画结束时，更新 顶点数据
			if (mGraphics_entity != nullptr)
				on_end_update_graphics_entity_vertices();
			else
				LOG_INFO("mAinimation_end_callback: is nullptr");

			return true;
		}

		// TODO MUST be Implemented
		virtual void on_end_update_graphics_entity_vertices()
		{
			LOG_INFO("do nothing.");
		}

		// 如果有剩余次数/循环、更新时间。然后为 is_end() 函数返回一个 false 
		bool update_replay_time_and_return_false()
		{
			LOG();
			update_time();

			return false;
		}

		void set_graphics_entity(graphics_entity* aGraphics_entity)
		{
			LOG();
			mGraphics_entity = aGraphics_entity;
			if (mGraphics_entity != nullptr)
				mGraphics_entity->mIs_playing_animation = true;
			else {
				LOG_INFO("is_to_play(): mGraphics_entity is nullptr");
			}
		}

		bool is_graphics_entity_is_playing_anim() const
		{
			return mGraphics_entity != nullptr && mGraphics_entity->mIs_playing_animation;
		}

		unsigned int get_graphics_entity_id() const
		{
			return mGraphics_entity->mId;
		}

		//protected:
		graphics_entity* mGraphics_entity;
	private:
		type mType;
		relationship mRelationship;
		// if count > 0,  do it, and then count -= 1;
		// if count <= 0, end;
		// if mBegin_time > mEnd_time, loop forever until set it stop
		unsigned int mCount;
		bool mIs_loop;
		bool mIs_shuttle;
		// if > current time, delay
		// if <= current time, do it;
		double mBegin_time;
		double mDuration;
		// if > current time, do it.
		// if <= current time, need to end it OR need to update it.
		double mEnd_time;
		double mParam;



		[[nodiscard]] double get_y(double aX) const
		{
			if (mIs_shuttle)
				if (aX + aX > mDuration)
					aX = mDuration - aX;

			switch (mRelationship) {
				case relationship::LINEAR:
					return do_linear(aX);
				case relationship::SQUARE:
					return do_square(aX);
				case relationship::SIN:
					return do_sin(aX);
				default:
					LOG_INFO("animation.h : no such relationship");
			}
			return 0;
		}

		// y = ax
		// a = 1 / duration
		[[nodiscard]] double do_linear(
			const double aX) const
		{
			return mParam * aX;
		}
		// y = a x^2
		// a = 1/duration * duration
		[[nodiscard]] double do_square(
			const double aX) const
		{
			return mParam * aX * aX;
		}
		// y = sin(ax)
		// a = PI/2 / duration
		[[nodiscard]] double do_sin(
			const double aX) const
		{
			return sin(mParam * aX);
		}

		[[nodiscard]] double calculate_param(
			const relationship aRelationship) const
		{
			switch (aRelationship) {
				case relationship::LINEAR:
					return (mIs_shuttle ? 2.0 : 1.0) / mDuration;
				case relationship::SIN:
					return  (mIs_shuttle ? 2.0 : 1.0) / mDuration / mDuration;
				case relationship::SQUARE:
					return  (mIs_shuttle ? 1.0 : 0.5) * PI / mDuration;
				default:
					LOG_INFO("no such animation::relationship");
			}
			return 1.0;
		}
	};
}
