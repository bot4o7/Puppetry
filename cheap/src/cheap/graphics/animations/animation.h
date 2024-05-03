#pragma once

namespace cheap {
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

		// 根据所给时间进行一次动画
		animation(
			const type  aType,
			const double aBegin_time,
			const double aDuration)
			: mType(aType),
			mCount(1),
			mIs_loop(false),
			mBegin_time(aBegin_time),
			mEnd_time(aBegin_time + aDuration)
		{
			LOG();
		}
		// 根据所给时间进行 count 次动画
		animation(
			const type  aType,
			const double aBegin_time,
			const double aDuration,
			const unsigned int aCount)
			: mType(aType),
			mCount(aCount),
			mIs_loop(false),
			mBegin_time(aBegin_time),
			mEnd_time(aBegin_time + aDuration)
		{
			LOG();
		}
		// 根据所给时间进行 循环动画
		animation(
			const type  aType,
			const double aBegin_time,
			const double aDuration,
			const bool aIs_loop)
			: mType(aType),
			mCount(1),
			mIs_loop(aIs_loop),
			mBegin_time(aBegin_time),
			mEnd_time(aBegin_time + aDuration)
		{
			LOG();
		}
		// 给一个未设置 开始时间、次数的非循环动画， 但是有运行周期
		animation(
			const type  aType,
			const double aDuration)
			: mType(aType),
			mCount(0),
			mIs_loop(false),
			mBegin_time(0.0),
			mEnd_time(aDuration)
		{
			LOG();
		}
		virtual ~animation()
		{
			LOG();
		}

		[[nodiscard]] type get_type()const { return mType; }

		bool is_loop() const { return mIs_loop; }

		// 1. 是否有剩余次数
		// 2. 是否到了开始时间
		// 3. 是否已经到了结束时间
		// 4. 即使到了结束时间，是否仍有剩余次数，或是无限循环
		bool is_to_play(
			const double current_time)
		{
			if (is_finished()) return false;

			if (is_not_begin(current_time)) return false;

			if (is_end(current_time)) return false;

			return true;
		}

		void update_time(
			const double aBegin_time)
		{
			const double duration_time = mEnd_time - mBegin_time;
			mBegin_time = aBegin_time;
			mEnd_time = mBegin_time + duration_time;
		}
		void update_time(
			const double aBegin_time,
			const double aDuration)
		{
			mBegin_time = aBegin_time;
			mEnd_time = mBegin_time + aDuration;
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
			unsigned int       aCount,
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
		}

		// 没有剩余次数 count，就无法进行
		bool is_finished() const { return mCount < 1; }
		// 到了开始时间 begin_time
		bool is_not_begin(const double aCurrent_time) const { return aCurrent_time < mBegin_time; }
		// 到了结束时间 end_time 且无剩余次数、且非循环
		bool is_end(const double aCurrent_time)
		{
			if (aCurrent_time < mEnd_time) return false;

			if (is_loop() || --mCount > 0)
				return update_replay_time_and_return_false();

			return true;
		}
		// 如果有剩余次数/循环、更新时间。然后为 is_end() 函数返回一个 false 
		bool update_replay_time_and_return_false()
		{
			update_time(
				mEnd_time,
				mEnd_time - mBegin_time);

			return false;
		}
	private:
		type mType;

		// if count > 0,  do it, and then count -= 1;
		// if count <= 0, end;
		// if mBegin_time > mEnd_time, loop forever until set it stop
		unsigned int mCount;
		bool mIs_loop;
		// if > current time, delay
		// if <= current time, do it;
		double mBegin_time;
		// if > current time, do it.
		// if <= current time, need to end it OR need to update it.
		double mEnd_time;


	};
}
