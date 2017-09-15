/*
 * Sprite.cpp
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#include "Sprite.h"

namespace config {

Sprite::Sprite(const std::string& className):xml::XmlElement(className) {
	this->heigth = -1;
	this->width = -1;

	this->div1 = -1;
	this->div2 = -1;
	this->div3 = -1;
	this->div4 = -1;
	this->div5 = -1;
	this->div6 = -1;
	this->div7 = -1;

	this->id = "";
	this->path = "";
	this->zindex = "";
}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

void Sprite::setFieldValue(const std::string& fieldName, const std::string& fieldValue) {
	utils::Utils util;
	try {
		if (fieldName.compare("heigth") == 0) {
			this->heigth = util.toInt(fieldValue);
		} else if (fieldName.compare("width") == 0) {
			this->width = util.toInt(fieldValue);
		} else if (fieldName.compare("path") == 0) {
			this->path = fieldValue;
		} else if (fieldName.compare("id") == 0) {
			this->id = fieldValue;
		} else if (fieldName.compare("zindex") == 0) {
			this->zindex = fieldValue;
		} else if (fieldName.compare("div1") == 0) {
			this->div1 = util.toInt(fieldValue);
		} else if (fieldName.compare("div2") == 0) {
			this->div2 = util.toInt(fieldValue);
		} else if (fieldName.compare("div3") == 0) {
			this->div3 = util.toInt(fieldValue);
		} else if (fieldName.compare("div4") == 0) {
			this->div4 = util.toInt(fieldValue);
		} else if (fieldName.compare("div5") == 0) {
			this->div5 = util.toInt(fieldValue);
		} else if (fieldName.compare("div6") == 0) {
			this->div6 = util.toInt(fieldValue);
		} else if (fieldName.compare("div7") == 0) {
			this->div7 = util.toInt(fieldValue);
		} else {
			throw std::exception();
		}
	} catch (std::exception& e) {
		throw xmlpp::exception("Error en el parseo de los datos Sprite.");
	}

}

const int Sprite::getHeigth() const {
	return (this->heigth);
}
const int Sprite::getWidth() const {
	return (this->width);
}

const std::string& Sprite::getPath() const {
	return (this->path);
}

const std::string& Sprite::getId() const {
	return (this->id);
}

const std::string& Sprite::getZIndex() const {
	return (this->zindex);
}

const int Sprite::getDiv1() const {
	return (this->div1);
}

const int Sprite::getDiv2() const {
	return (this->div2);
}

const int Sprite::getDiv3() const {
	return (this->div3);
}

const int Sprite::getDiv4() const {
	return (this->div4);
}

const int Sprite::getDiv5() const {
	return (this->div5);
}

const int Sprite::getDiv6() const {
	return (this->div6);
}

const int Sprite::getDiv7() const {
	return (this->div7);
}

} /* namespace config */
