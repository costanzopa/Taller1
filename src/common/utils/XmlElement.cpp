/*
 * XmlElement.cpp
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#include "XmlElement.h"

namespace xml {

XmlElement::XmlElement(const std::string& className) {
	this->className = className;
}

XmlElement::~XmlElement() {
	// TODO Auto-generated destructor stub
}

const std::string& XmlElement::getClassName() const {
	return (this->className);
}

} /* namespace xml */
