#include "pch.h"
#include "utils.h"

namespace cheap::utils {
	std::string read_file(const std::string& path)
	{
		// Open a file at a specific path
		std::ifstream file(path);
		if (!file)
			LOG_INFO("Utils:ReadFile", "Unable to open file at path: " + path);

		std::string line;
		std::ostringstream stream;
		// Read each line in the file and store them together in a stream
		while (getline(file, line))
			stream << line << "\n";

		return stream.str();
	}

	std::string to_upper(const std::string& str)
	{
		std::string new_str = str;
		std::ranges::transform(new_str, new_str.begin(), ::toupper);
		return new_str;
	}

	std::string to_lower(const std::string& str)
	{
		std::string new_str = str;
		std::ranges::transform(new_str, new_str.begin(), ::tolower);
		return new_str;
	}

	int find_in_array(const int num, const int* arr, const unsigned int count)
	{
		for (int i = 0; i < count; ++i) {
			if (arr[i] == num)
				return i;
		}
		return -1;
	}
}
