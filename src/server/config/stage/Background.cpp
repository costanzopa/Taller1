/*
 * Background.cpp
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#include "Background.h"

namespace config {

Background::Background(const std::string& className):xml::XmlElement(className) {
	this->id = "";
	this->path = "";
	this->zindex = "";
}

Background::~Background() {
	// TODO Auto-generated destructor stub
}

void Background::setFieldValue(const std::string& fieldName, const std::string& fieldValue) {
	if (fieldName.compare("path") == 0) {
		this->path = fieldValue;
	} else if (fieldName.compare("id") == 0) {
		this->id = fieldValue;
	} else if  (fieldName.compare("zindex") == 0) {
		this->zindex = fieldValue;
	} else {
		throw xmlpp::exception("No existe campo "+ fieldName + " en clase Background.");
	}
}


const std::string& Background::getPath() const {
	return (this->path);
}

const std::string& Background::getId() const {
	return (this->id);
}

const std::string& Background::getZIndex() const {
	return (this->zindex);
}
} /* namespace config */
