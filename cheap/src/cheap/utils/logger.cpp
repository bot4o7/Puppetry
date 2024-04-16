#include "logger.h"

namespace cheap {
	void Logger::Print(const std::string& str)
	{
		std::cout << str;
	}
	void Logger::Println(const std::string& str)
	{
		std::cout << str << '\n';
	}

	std::string& Logger::GetTime()
	{
		return Get().FunctionGetTime();
	}
	Logger& Logger::Get()
	{
		return m_logger;
	}
	std::string& Logger::FunctionGetTime()
	{
		std::chrono::time_point current_time = std::chrono::system_clock::now();

		const int current_ms_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(current_time).time_since_epoch()).count() % 1000;

		std::string current_time_str = std::format("{:%Y-%m-%d %H:%M:%S::}", current_time);
		if (current_ms_time < 100) {
			current_time_str += '0';
			if (current_ms_time < 10)
				current_time_str += '0';
		}
		current_time_str += std::to_string(current_ms_time);
		return current_time_str;
	}

	//std::string& Logger::GetCodeFile()
	//{
	//}
	//std::string& Logger::GetCodeFilePath()
	//{
	//}
	//std::string& Logger::GetCodeFunction()
	//{
	//}
	//std::string& Logger::GetCodeLine()
	//{
	//}
	//std::string& Logger::GetTypeName(){ }
	//std::string& Logger::GetFileName(){ }
	//std::string& Logger::GetFilePath(){ }
	//void Logger::LogTime(){}
	//void Logger::LogCodeFile()
	//{
	//}
	//void Logger::LogCodeFilePath() { }
	//void Logger::LogCodeFunction() { }
	//void Logger::LogCodeLine() { }
	//void Logger::LogTypeName(){ }
	//void Logger::LogFileName(){ }
	//void Logger::LogFilePath(){ }
	//void Logger::LogFF() { }
	//void Logger::LogFFT() { }
	//void Logger::LogFFL() { }

	void Logger::Log()
	{
		Get().FunctionLog();
	}
	void Logger::FunctionLog()
	{
		std::cout << '[' << GetTime() << "] ["
			<< __FILE__ << ':' << __LINE__ << '_' << __func__ << '\n';
	}

	Logger::Logger()
	{

	}
	Logger::~Logger()
	{
	}
	//void Logger::LogFFLT()
	//{
	//	std::cout << '[' << GetTime() << "] ["
	//		<< __FILE__ << ':' << __LINE__ << '_' << __func__ << '\n';
	//}
	//void Logger::LogFL() { }
	//void Logger::LogFLT()
	//{
	//	std::cout << '[' << GetTime() << "] ["
	//		<< __FILE__ << ':' << __LINE__ << '_' << __func__ << '\n';
	//}
}
