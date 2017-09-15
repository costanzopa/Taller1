/*
 * StageFile.cpp
 *
 *  Created on: 01/10/2016
 *      Author: pablo
 */

#include "StageFile.h"

namespace config {


StageFile::StageFile(const std::string& fileName): xml::XmlFile(new StageFactory(),fileName) {
	try {
		std::string className = "StageFile";
		logger = new logger::Logger(className);
		logger->info("Se va a iniciar el parseo del archivo: " + fileName);
		this->stage = new Stage();
		this->parse_file(fileName);
		logger->info("Se ha parseado el archivo.");
		this->complete();
		logger->info("Se ha cargado en memoria el Escenario.");
	} catch (xmlpp::exception& e) {
		std::cout<<"No se ha podido completar la carga del archivo "<<fileName<<std::endl;
		logger->error(e.what());
		logger->error("No se ha podido completar la carga del archivo: " + fileName);
		delete stage;
		stage = NULL;
	}
}

StageFile::~StageFile() {
	delete logger;
}

void StageFile::add(xml::XmlElement* const element) {
	this->getStage()->add(element);
}

Stage* StageFile::getStage() const {
	return (this->stage);
}
} /* namespace config */
