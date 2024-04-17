#pragma once

namespace cheap {

	enum class EventType
	{
		App,
		Input,
		Game
	};

	class Event
	{
	public:
		bool is_handled;

		virtual EventType GetType() const = 0;
		virtual int GetSubType() const = 0;
		virtual bool IsSubType(const int sub_type) const = 0;

		virtual ~Event() = default;
	protected:
		Event() :is_handled(false) { }
	};
}
