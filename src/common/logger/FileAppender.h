/*
 * FileAppender.h
 *
 *  Created on: Sep 2, 2016
 *      Author: mario
 */

#ifndef COMMON_LOGGER_FILEAPPENDER_H_
#define COMMON_LOGGER_FILEAPPENDER_H_
#include <string>

namespace logger {

class FileAppender {
public:
	FileAppender(std::string& file);

	void append(std::string& message);

	virtual ~FileAppender();

private:
	std::string file;
};

} /* namespace logger */

#endif /* COMMON_LOGGER_FILEAPPENDER_H_ */
