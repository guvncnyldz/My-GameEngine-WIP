#include "pch.h"
#include "Logger.h"

Logger::Level Logger::currentLogLevel = Logger::Level::Custom;

void Logger::setLevel(Level level)
{
	currentLogLevel = level;
}

void Logger::error(std::string msg, std::string file, int line, std::string function)
{
	if (currentLogLevel > Level::Error)
		return;

	message(msg, file, line, function, Level::Error, 91);
}

void Logger::info(std::string msg, std::string file, int line, std::string function)
{
	if (currentLogLevel > Level::Info)
		return;

	message(msg, file, line, function, Level::Info, 97);
}

void Logger::warning(std::string msg, std::string file, int line, std::string function)
{
	if (currentLogLevel > Level::Warning)
		return;

	message(msg, file, line, function, Level::Warning, 93);
}

void Logger::custom(std::string msg, std::string file, int line, std::string function, Color color)
{
	if (currentLogLevel > Level::Custom)
		return;

	message(msg, file, line, function, Level::Custom, (int)color);
}

void Logger::message(std::string msg, std::string file, int line, std::string function, Level level, int color)
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