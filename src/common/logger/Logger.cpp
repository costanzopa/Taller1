/*
 * Logger.cpp
 *
 *  Created on: Sep 2, 2016
 *      Author: mario
 */

#include "Logger.h"
#include <sstream>
#include <ctime>

namespace logger {

const int MAX_MSG_LENGTH = 128;

Logger::Logger(std::string& id) {
	identifier = id;
	level = DEBUG;
	trimMessage = false;
	std::string defaultFile = "logger.log";
	appender = new FileAppender(defaultFile);
}

void Logger::error(const std::string& message) {
	std::string toLog = message;
	std::string lvl = std::string("Error");
	this->log(toLog, ERROR, lvl);
}

void Logger::debug(const std::string& message) {
	std::string toLog = message;
	std::string lvl = std::string("Debug");
	this->log(toLog, DEBUG, lvl);
}

void Logger::info(const std::string& message) {
	std::string toLog = message;
	std::string lvl = std::string("Info");
	this->log(toLog, INFO, lvl);
}

void Logger::warn(const std::string& message) {
	std::string toLog = message;
	std::string lvl = std::string("Warn");
	this->log(toLog, WARN, lvl);
}

Logger::~Logger() {
	delete appender;
}

LogLevel Logger::getLevel() const {
	return level;
}

void Logger::setLevel(LogLevel level) {
	this->level = level;
}

bool Logger::isTrimMessage() const {
	return trimMessage;
}

void Logger::setTrimMessage(bool trimMessage) {
	this->trimMessage = trimMessage;
}

std::string Logger::trimLogMessage(const std::string& message) {
	if (!trimMessage || message.length() <= MAX_MSG_LENGTH) {
		return message;
	}
	return message.substr(0, (MAX_MSG_LENGTH - 1));
}

void Logger::log(std::string& message, LogLevel callLevel, std::string& lvlText) {
	return;
	//Dejo de loggear, no es como si fuera util o algo
	if(callLevel <= this->level) {
		std::string toLog = message;
		std::string msg = this->trimLogMessage(toLog);

		time_t t = time(0);
		struct tm * current = localtime( & t );

		std::stringstream ss;
		ss << (current->tm_year + 1900) << "-" << (current->tm_mon + 1) << "-" 	<< current->tm_mday
				<< " "
				<< current->tm_hour << ":" << current->tm_min << ":" << current->tm_sec
				<< " | " << this->identifier << ": "
				<< "[" << lvlText<< "] " << msg;

		std::string fullMessage = ss.str();

		this->appender->append(fullMessage);
	}
}

} /* namespace logger */
