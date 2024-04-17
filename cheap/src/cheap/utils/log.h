#pragma once

#ifdef BOT4O7_DEBUG

namespace cheap {
	void Print(const std::string& str);
	void Println(const std::string& str);

	void Log(const char* file, const char* func, long line);
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


