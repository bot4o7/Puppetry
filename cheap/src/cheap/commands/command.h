#pragma once

namespace cheap {
	class command
	{
	public:
		enum class type
		{
			APP,
			RENDER,
			GAME_DATA
		};

		command(type aType) :mType(aType) { }

		virtual ~command() = default;

	protected:
		type mType;
	};
}
