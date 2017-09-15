/*
 * Logger.h
 *
 *  Created on: Sep 2, 2016
 *      Author: mario
 */

#ifndef COMMON_LOGGER_LOGGER_H_
#define COMMON_LOGGER_LOGGER_H_

#include <string>
#include "FileAppender.h"

enum LogLevel {DEBUG = 4, INFO = 3, WARN = 2, ERROR = 1, OFF= 0};

namespace logger {

class Logger {

public:
	Logger(std::string& message);
	void error(const std::string& message);
	void debug(const std::string& message);
	void info(const std::string& message);
	void warn(const std::string& message);

	virtual ~Logger();

	const std::string& getIdentifier() const;
	void setIdentifier(const std::string& identifier);

	LogLevel getLevel() const;
	void setLevel(LogLevel level);

	bool isTrimMessage() const;
	void setTrimMessage(bool trimMessage);

private:
	bool trimMessage;
	LogLevel level;
	std::string identifier;
	FileAppender* appender;

	std::string trimLogMessage(const std::string& message);
	void log(std::string& message, LogLevel level, std::string& lvlText);
};

} /* namespace logger */

#endif /* COMMON_LOGGER_LOGGER_H_ */
