#pragma once

namespace cheap::utils {
	// Get a file path and return its contents as a string
	std::string read_file(const char* aPath);

	// Convert a given string to uppercase
	std::string to_upper(const std::string& aStr);
	// Convert a given string to lowercase
	std::string to_lower(const std::string& aStr);

	// Search for an integer in an array and return its position
	int find_in_array(int aNum, const int* aRr, unsigned int aCount);
}
