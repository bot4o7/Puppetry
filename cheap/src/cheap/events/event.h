#pragma once

namespace cheap {
	class event
	{
	public:
		enum class category
		{
			app,
			input,
			game
		};
		bool is_handled;

		[[nodiscard]] virtual category get_category() const = 0;
		[[nodiscard]] virtual int        get_type() const = 0;
		[[nodiscard]] virtual bool       is_type(const int sub_type) const = 0;

		virtual ~event() = default;
	protected:
		event() : is_handled(false) { }
	};
}
