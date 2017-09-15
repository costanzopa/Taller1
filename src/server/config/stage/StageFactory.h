/*
 * StageFactory.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef SERVER_CONFIG_STAGEFACTORY_H_
#define SERVER_CONFIG_STAGEFACTORY_H_

#include "../../../common/utils/XmlFactory.h"
#include "Background.h"
#include "Sprite.h"
#include "Window.h"
#include <libxml++/exceptions/exception.h>

namespace config {

class StageFactory: public xml::XmlFactory {
public:
	StageFactory();
	virtual ~StageFactory();

	virtual xml::XmlElement* create(const std::string& className);
};

} /* namespace config */

#endif /* SERVER_CONFIG_STAGEFACTORY_H_ */
