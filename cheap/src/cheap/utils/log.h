#pragma once

#ifdef BOT4O7_DEBUG

// if defined BOT4O7_DEBUG, class Logger could be used.
// TODO
#include <string> // 这个，后面可能会重复 include, 要注意一下
#include <iostream>
#include <chrono>
#include <format>

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
		//std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now()
		//} << "]  FILE:"
		//	<< static_cast<std::string>(file).erase(0, static_cast<std::string>(file).find_last_of("\\/") + 1) << "\t" << func << "()\tLINE:" << line << "\n";
		std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now()
		} << "]  FILE:"
			<< file << " \t" << func << "() \tLINE:" << line << "\n";
	}
}

#define PRINT(x) cheap::Print(x)
#define PRINTLN(x) cheap::Println(x)
#    ifdef BOT4O7_VC
#        define LOG() cheap::Log(__FILE__, __func__, __LINE__)
//#        define LOG() cheap::Log(__FILE__, __FUNCSIG__, __LINE__)
#    else
#        define LOG() cheap::Log(__FILE__, __func__, __LINE__)
#    endif
#else
// if not debug mode
#define PRINT(x) 
#define PRINTLN(x) 
#define LOG() 
#endif


