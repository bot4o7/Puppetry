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
		[[nodiscard]] virtual bool       is_category(const category category_input) const = 0;
		[[nodiscard]] virtual int        get_type() const = 0;
		[[nodiscard]] virtual bool       is_type(const int sub_type) const = 0;

		virtual ~event() = default;
	protected:
		event() : is_handled(false) { }
	};

	#define GET_CATEGORY(my_category) [[nodiscard]] category get_category() const override\
	{\
	return my_category;\
	}\
	bool is_category(const category category_input) const override\
	{\
	return category_input == get_category();\
	}

	#define GET_TYPE_AND_IS_TYPE(my_type) [[nodiscard]] int get_type() const override\
	{\
		return static_cast<int>(my_type);\
	}\
	[[nodiscard]] bool is_type(const int sub_type) const override\
	{\
		return sub_type == get_type();\
	}
}
