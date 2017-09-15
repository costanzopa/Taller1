/*
 * Background.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef COMMON_STAGE_BACKGROUND_H_
#define COMMON_STAGE_BACKGROUND_H_

#include "../../../common/utils/XmlElement.h"
#include <exception>
#include <libxml++/exceptions/exception.h>

namespace config {

class Background: public xml::XmlElement {
public:
	Background(const std::string& className);
	virtual ~Background();

	const std::string& getPath() const;
	const std::string& getId() const;
	const std::string& getZIndex() const;

	virtual void setFieldValue(const std::string& fieldName, const std::string& fieldValue);
private:
	std::string id;
	std::string path;
	std::string zindex;
};

} /* namespace config */

#endif /* COMMON_STAGE_BACKGROUND_H_ */
