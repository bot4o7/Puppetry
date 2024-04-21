#pragma once

namespace cheap::utils {
	// Get a file path and return its contents as a string
	std::string read_file(const std::string& path);

	// Convert a given string to uppercase
	std::string to_upper(const std::string& str);
	// Convert a given string to lowercase
	std::string to_lower(const std::string& str);

	// Search for an integer in an array and return its position
	int find_in_array(int num, const int* arr, unsigned int count);
}
