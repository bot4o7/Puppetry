#include "pch.h"



namespace cheap {
	void print(const std::string& str)
	{
		std::cout << str;
	}
	void println(const std::string& str)
	{
		std::cout << str << '\n';
	}

	void log(const char* file, const char* func, const long line)
	{
		std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now()
		} << "]  FILE:"
			<< file << " \t" << func << "() \tLINE:" << line << "\n";
	}
}
