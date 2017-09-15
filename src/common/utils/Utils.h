/*
 * Utils.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef COMMON_UTILS_UTILS_H_
#define COMMON_UTILS_UTILS_H_

#include <string>
#include <sstream>
 #include <iostream>

namespace utils {

class Utils {
public:
	Utils();
	virtual ~Utils();

	int toInt(const std::string& number);
	float toFloat(const std::string& number);
};


} /* namespace utils */

#endif /* COMMON_UTILS_UTILS_H_ */
