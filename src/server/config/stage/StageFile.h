/*
 * StageFile.h
 *
 *  Created on: 01/10/2016
 *      Author: pablo
 */

#ifndef SERVER_CONFIG_STAGEFILE_H_
#define SERVER_CONFIG_STAGEFILE_H_

#include "../../../common/utils/XmlFile.h"
#include "Stage.h"
#include "../../../common/logger/Logger.h"
#include "StageFactory.h"
#include <iostream>

namespace config {

class StageFile :public xml::XmlFile {
public:
	StageFile(const std::string& fileName);
	virtual ~StageFile();

	virtual Stage* getStage() const;

	virtual void add(xml::XmlElement* const element);

private:
	Stage* stage;
	logger::Logger* logger;
};

} /* namespace config */

#endif /* SERVER_CONFIG_STAGEFILE_H_ */
