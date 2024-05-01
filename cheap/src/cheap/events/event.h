#pragma once

namespace cheap {
	// TODO may need to implement [move ctor] and [move assignment]
	class event
	{
	public:
		enum class category
		{
			APP,
			INPUT,
			GAME
		};
		bool mIs_handled;

		[[nodiscard]] virtual category get_category() const = 0;
		[[nodiscard]] virtual bool       is_category(const category aCategory_input) const = 0;

		virtual ~event() = default;

		event(const event& aExist_event) = delete;
		event& operator=(const event& aExist_event) = delete;
	protected:
		event() : mIs_handled(false) { }
	};

	#define GET_CATEGORY(my_category) [[nodiscard]] category get_category() const override\
	{\
	return my_category;\
	}\
	bool is_category(const category category_input) const override\
	{\
	return category_input == get_category();\
	}

	#define GET_TYPE_AND_IS_TYPE(type_name, arg) [[nodiscard]] type_name get_type() const\
	{\
		return arg;\
	}\
	[[nodiscard]] bool is_type(type_name aType) const\
	{\
		return aType == get_type();\
	}
}
