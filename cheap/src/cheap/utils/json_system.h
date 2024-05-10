#pragma once

#include "nlohmann_json/json.hpp"

namespace cheap::utils {

	template <typename T>
	struct serializer
	{
		//nlohmann::adl_serializer<T> mSerializer;

		//serializer() :mSerializer() { }

		static void to_json(nlohmann::json& j, const T& value)
		{
			nlohmann::adl_serializer<T>::to_json(j, value);
		}

		static void from_json(nlohmann::json& j, const T& value)
		{
			nlohmann::adl_serializer<T>::from_json(j, value);
		}
	};

}
