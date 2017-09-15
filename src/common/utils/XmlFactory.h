/*
 * XmlFactory.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef COMMON_UTILS_XMLFACTORY_H_
#define COMMON_UTILS_XMLFACTORY_H_

#include "XmlElement.h"
 #include <iostream>

namespace xml {

class XmlFactory {
public:
	XmlFactory();
	virtual ~XmlFactory();

	virtual XmlElement* create(const std::string& className) = 0;
};

} /* namespace xml */

#endif /* COMMON_UTILS_XMLFACTORY_H_ */
