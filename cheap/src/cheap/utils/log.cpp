#include "pch.h"
#include "log.h"


namespace cheap::log {

	void print(const std::string& str)
	{
		std::cout << str;
	}
	void println(const std::string& str)
	{
		std::cout << str << '\n';
	}

	void log()
	{
		std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() } << "]  FILE:" << __FILE__ << " \t" << __func__ << "() \tLINE:" << __LINE__ << "\n"
	}

	void log(const std::string& message)
	{
		std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() } << "]  FILE:" << __FILE__ << " \t" << __func__ << "() \tLINE:" << __LINE__ << "\nLOG::INFO: " << message << '\n';
	}
}
