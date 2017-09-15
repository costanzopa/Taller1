/*
 * StageFactory.cpp
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#include "StageFactory.h"

namespace config {

StageFactory::StageFactory() {
	// TODO Auto-generated constructor stub

}

StageFactory::~StageFactory() {
	// TODO Auto-generated destructor stub
}


xml::XmlElement* StageFactory::create(const std::string& className) {
	xml::XmlElement* element = NULL;
	if (className.compare("Sprite") == 0) {
		element = new Sprite(className);
	} else if (className.compare("Background") == 0) {
		element = new Background(className);
	} else if  (className.compare("Window") == 0) {
		element = new Window(className);
	} else {
		throw (xmlpp::exception("Xml mal formado: Elemento inválido " + className));
	}
	return element;
}

} /* namespace config */
