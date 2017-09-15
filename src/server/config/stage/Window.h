/*
 * Window.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef COMMON_STAGE_WINDOW_H_
#define COMMON_STAGE_WINDOW_H_

#include "../../../common/utils/XmlElement.h"
#include "../../../common/utils/Utils.h"
#include <exception>
#include <libxml++/exceptions/exception.h>

namespace config {

class Window: public xml::XmlElement {
public:
	Window(const std::string& className);
	virtual ~Window();

	const int getHeigth() const;
	const int getWidth() const;
	const int getPlayers() const;
	const float getCharacterScale() const;
	const float getWindowScale() const;
	const std::string getGameMode() const;

	virtual void setFieldValue(const std::string& fieldName, const std::string& fieldValue);

private:
	int heigth;
	int width;
	int players;
	float characterScale;
	float windowScale;
	std::string gameMode;
};

} /* namespace config */

#endif /* COMMON_STAGE_WINDOW_H_ */
