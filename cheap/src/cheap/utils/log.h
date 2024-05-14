#pragma once

#ifdef BOT4O7_DEBUG

#define PRINT(x) std::cout << x
#define PRINTLN(x) std::cout << x << '\n'
#define LOG() std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now()} << "]  FILE:"<< __FILE__ << " \t" << __func__ << "() \tLINE:" << __LINE__ << '\n'
#define LOG_INFO(info) std::cout << '[' << std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now()} << "]  FILE:"<< __FILE__ << " \t" << __func__ << "() \tLINE:" << __LINE__ << "\nLOG::INFO::[" << info << "]\n"

#else
// if not debug mode
#define PRINT(x) 
#define PRINTLN(x) 
#define LOG()
#define LOG_INFO(info)
#endif


