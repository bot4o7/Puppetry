#include "pch.h"

namespace cheap {
	void Print(const std::string& str)
	{
		std::cout << str;
	}
	void Println(const std::string& str)
	{
		std::cout << str << '\n';
	}

	void Log(const char* file, const char* func, long line)
	{
		std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now()
		} << "]  FILE:"
			<< file << " \t" << func << "() \tLINE:" << line << "\n";
	}
}
