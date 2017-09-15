/*
 * Utils.cpp
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#include "Utils.h"

namespace utils {

Utils::Utils() {
	// TODO Auto-generated constructor stub

}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

int Utils::toInt(const std::string& number) {
	int integer;
	std::stringstream  ssnumber(number);
	if ((ssnumber >> integer).fail()) {
		std::cout<<"Fallo la conversion"<<std::endl;
	 	throw std::exception();
	 }
	return integer;
}

float Utils::toFloat(const std::string& number) {
	float num;
	std::stringstream  ssnumber(number);
	if ((ssnumber >> num).fail()) {
		std::cout<<"Fallo la conversion"<<std::endl;
	 	throw std::exception();
	 }
	return num;
}

} /* namespace utils */
