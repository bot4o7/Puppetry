#pragma once

namespace cheap {
	class entity
	{
	public:

		enum class category
		{
			GRAPHICS
		};

		explicit entity(const unsigned int aId)
			:
			mId(aId)
		{
			LOG();
		}


		virtual ~entity() = default;

		[[nodiscard]] virtual category get_category() const = 0;
		[[nodiscard]] virtual bool     is_category(category aCategory) const = 0;

		unsigned int mId;
	};
}
