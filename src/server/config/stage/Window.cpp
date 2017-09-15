/*
 * Window.cpp
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#include "Window.h"

namespace config {

Window::Window(const std::string& className):xml::XmlElement(className) {
	this->heigth = -1;
	this->width = -1;
	this->players = -1;
	this->characterScale = -1;
	this->windowScale = -1;
	this->gameMode = "";
}

Window::~Window() {
}

void Window::setFieldValue(const std::string& fieldName, const std::string& fieldValue) {
	utils::Utils util;
	try {
		if (fieldName.compare("heigth") == 0) {
			this->heigth = util.toInt(fieldValue);
		} else if (fieldName.compare("width") == 0) {
			this->width = util.toInt(fieldValue);
		} else if (fieldName.compare("players") == 0) {
			this->players = util.toInt(fieldValue);
		} else if (fieldName.compare("characterScale") == 0) {
			this->characterScale = util.toFloat(fieldValue);
		} else if (fieldName.compare("windowScale") == 0) {
			this->windowScale = util.toFloat(fieldValue);
		} else if (fieldName.compare("gameMode") == 0) {
			this->gameMode = fieldValue;
		} else {
			throw std::exception();
		}
	} catch (std::exception& e) {
		throw xmlpp::exception("Error en el parseo de los datos Window");
	}

}

const int Window::getHeigth() const {
	return (this->heigth);
}

const int Window::getWidth() const {
	return (this->width);
}

const int Window::getPlayers() const {
	return (this->players);
}

const float Window::getCharacterScale() const {
	return (this->characterScale);
}

const float Window::getWindowScale() const {
	return (this->windowScale);
}
const std::string Window::getGameMode() const {
	return (this->gameMode);
}

} /* namespace config */
