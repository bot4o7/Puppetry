#pragma once

namespace cheap {
	class entity
	{
		enum class category
		{
			visible,
			invisible
		};
	public:
		[[nodiscard]] virtual category get_category() const = 0;
		[[nodiscard]] virtual bool     is_category(category category_input) const = 0;
		[[nodiscard]] virtual int        get_type() const = 0;
		[[nodiscard]] virtual bool       is_type(const int sub_type) const = 0;
		// TODO
		// what's the common in Visual Entity (Text box, button)
		// and NOT Visual Entity (game settings, custom things, like the money which player has, in the script)
		// what's their difference?
	};


}
