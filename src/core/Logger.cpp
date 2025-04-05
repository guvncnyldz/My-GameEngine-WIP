#include <src/Logger.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Level Logger::currentLogLevel = Logger::Level::Custom;

void Logger::setLevel(Level level)
{
	currentLogLevel = level;
}

void Logger::error(const char* msg, const char* file, int line, const char* function)
{
	if (currentLogLevel > Level::Error)
		return;

	message(msg, file, line, function, Level::Error, 91);
}

void Logger::info(const char* msg, const char* file, int line, const char* function)
{
	if (currentLogLevel > Level::Info)
		return;

	message(msg, file, line, function, Level::Info, 97);
}

void Logger::warning(const char* msg, const char* file, int line, const char* function)
{
	if (currentLogLevel > Level::Warning)
		return;

	message(msg, file, line, function, Level::Warning, 93);
}

void Logger::log(const char* msg, const char* file, int line, const char* function, Color color)
{
	if (currentLogLevel > Level::Custom)
		return;

	message(msg, file, line, function, Level::Custom, (int)color);
}

void Logger::message(const char* msg, const char* file, int line, const char* function, Level level, int color)
{
	std::string colorCode = "\033[" + std::to_string(color) + "m";

	std::string levelStr;

	switch (level) {
	case Level::Error:   levelStr = "[ERROR]"; break;
	case Level::Warning: levelStr = "[WARNING]"; break;
	case Level::Info:    levelStr = "[INFO]"; break;
	case Level::Custom:  levelStr = "[CUSTOM]"; break;
	}

	std::cout << colorCode << levelStr
		<< " " << msg << " at " << function << " in " << file
		<< ":" << line << "\033[0m" << std::endl;
}