/*
 * Stage.cpp
 *
 *  Created on: 01/10/2016
 *      Author: pablo
 */

#include "Stage.h"

namespace config {

Stage::Stage() {
	this->window = NULL;
}

Stage::~Stage() {
	if (window != NULL) {
		delete window;
	}
	std::vector<Sprite*>::iterator itSprites = this->sprites.begin();
	std::vector<Background*>::iterator itBackgrounds = this->backgrounds.begin();

	while(itSprites != this->sprites.end()) {
		delete (*itSprites);
		itSprites++;
	}

	while(itBackgrounds != this->backgrounds.end()) {
		delete (*itBackgrounds);
		itBackgrounds++;
	}
}

void Stage::add(xml::XmlElement* element) {
	if ((element->getClassName()).compare("Sprite") == 0) {
		Sprite* sprite = dynamic_cast< Sprite* > (element);
		this->sprites.push_back(sprite);
	} else if ((element->getClassName()).compare("Background") == 0) {
		Background* background = dynamic_cast< Background* > (element);
		this->backgrounds.push_back(background);
	} else if ((element->getClassName()).compare("Window") == 0) {
		if (this->window == NULL) {
			this->window = dynamic_cast< Window* > (element);
		} else {
			throw xmlpp::exception("Ya existe una ventana.");
		}
	} else {
		throw xmlpp::exception("Elemento del escenario desconocido" + element->getClassName());
	}
}

Window* Stage::getWindow() const {
	return (this->window);
}

std::vector<Sprite*> Stage::getSprites() const {
	return (this->sprites);
}

std::vector<Background*> Stage::getBackgrounds() const {
	return (this->backgrounds);
}

} /* namespace config */
