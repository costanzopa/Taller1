/*
 * Stage.h
 *
 *  Created on: 01/10/2016
 *      Author: pablo
 */

#ifndef COMMON_STAGE_STAGE_H_
#define COMMON_STAGE_STAGE_H_

#include "../../../common/utils/XmlElement.h"
#include "Window.h"
#include "Sprite.h"
#include "Background.h"
#include <vector>
#include <libxml++/exceptions/exception.h>

namespace config {

class Stage {
public:
	Stage();
	virtual ~Stage();

	virtual void add(xml::XmlElement* element);

	Window* getWindow() const;
	std::vector<Sprite*> getSprites() const;
	std::vector<Background*> getBackgrounds() const;

private:
	std::vector<Sprite*> sprites;
	std::vector<Background*> backgrounds;
	Window* window;
};

} /* namespace config */

#endif /* SERVER_CONFIG_STAGE_H_ */
