#include "pch.h"
#include "utils.h"

namespace cheap::utils {
	std::string read_file(const char* aPath)
	{
		LOG();
		// Open a file at a specific path
		std::ifstream file(aPath);
		if (!file)
			LOG_INFO("cheap::utils\nUtils unable to open file at path: " << aPath);

		std::string line;
		std::ostringstream stream;
		// Read each line in the file and store them together in a stream
		while (getline(file, line))
			stream << line << "\n";

		return stream.str();
	}

	std::string to_upper(const std::string& aStr)
	{
		std::string new_str = aStr;
		std::ranges::transform(new_str, new_str.begin(), ::toupper);
		return new_str;
	}

	std::string to_lower(const std::string& aStr)
	{
		std::string new_str = aStr;
		std::ranges::transform(new_str, new_str.begin(), ::tolower);
		return new_str;
	}

	int find_in_array(const int aNum, const int* aRr, const unsigned int aCount)
	{
		for (int i = 0; i < aCount; ++i) {
			if (aRr[i] == aNum)
				return i;
		}
		return -1;
	}
}
