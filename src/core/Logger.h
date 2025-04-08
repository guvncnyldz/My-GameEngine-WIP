#ifndef LOGGER_H
#define LOGGER_H

#include "pch.h"

class Logger
{
public:
	enum class Level {
		Custom,
		Info,
		Warning,
		Error,
		None
	};

	enum class Color {
		Black = 30,
		Red = 31,
		Green = 32,
		Yellow = 33,
		Blue = 34,
		Magenta = 35,
		Cyan = 36,
		White = 37,
		BrightBlack = 90,
		//BrightRed = 91,
		BrightGreen = 92,
		//BrightYellow = 93,
		BrightBlue = 94,
		BrightMagenta = 95,
		BrightCyan = 96,
		//BrightWhite = 97
	};

	static void error(const char* msg, const char* file, int line, const char* function);
	static void info(const char* msg, const char* file, int line, const char* function);
	static void warning(const char* msg, const char* file, int line, const char* function);
	static void log(const char* msg, const char* file, int line, const char* function, Color color = Color::White);
	static void setLevel(Level level);

private:
	static Level currentLogLevel;

	static void message(const char* msg, const char* file, int line, const char* function, Level level, int color);

	Logger() = delete;
	~Logger() = delete;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};

#define LOG_ERROR(msg) Logger::error(msg, __FILE__, __LINE__, __FUNCTION__)
#define LOG_INFO(msg) Logger::info(msg, __FILE__, __LINE__, __FUNCTION__)
#define LOG_WARNING(msg) Logger::warning(msg, __FILE__, __LINE__, __FUNCTION__)
#define LOG_CUSTOM(msg, color) Logger::log(msg, __FILE__, __LINE__, __FUNCTION__, color)
#define LOG(msg) Logger::log(msg, __FILE__, __LINE__, __FUNCTION__, Logger::Color::White)
#endif 
