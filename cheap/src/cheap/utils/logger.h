#pragma once

#ifdef BOT4O7_DEBUG

// if defined BOT4O7_DEBUG, class Logger could be used.
// TODO
#include <string> // 这个，后面可能会重复 include, 要注意一下
#include <iostream>
#include <chrono>
#include <format>

namespace cheap {
	// 单例 single instance
	class Logger
	{
	public:
		// char* 效率更高， more efficient, //TODO
		//void Print(const char* str);

		static Logger& Get();
		static void Print(const std::string& str);
		static void Println(const std::string& str);

		static std::string& GetTime();
		//std::string& GetCodeFile();
		//std::string& GetCodeFilePath();
		//std::string& GetCodeFunction();
		//std::string& GetCodeLine();
		//std::string& GetTypeName();
		//std::string& GetFileName();
		//std::string& GetFilePath();
		//void LogTime();
		//void LogCodeFile();
		//void LogCodeFilePath();
		//void LogCodeFunction();
		//void LogCodeLine();
		//void LogTypeName();
		//void LogFileName();
		//void LogFilePath();
		//void LogFF();
		//void LogFFT();
		//void LogFFL();
		//void LogFFLT();
		//void LogFL();
		//void LogFLT();

		static void Log();

		~Logger();
	private:
		static Logger m_logger;

		// 删除拷贝构造、拷贝赋值
		// delete copy ctor, copy assignment
		static void FunctionLog();
		static std::string& FunctionGetTime();

		Logger(const Logger& logger) = delete;
		Logger& operator=(const Logger& logger) = delete;

		// ctor
		Logger();


	};

	Logger Logger::m_logger;
}



#define PRINT(x) cheap::Logger::Print(x)
#define PRINTLN(x) cheap::Logger::Println(x)
#define GET_TIME() cheap::Logger::GetTime()
#define LOG() cheap::Logger::Log()

#else

// if not debug mode

#define PRINT(x) 
#define PRINTLN(x) 
#define GET_TIME() 
#define LOG() 

#endif


