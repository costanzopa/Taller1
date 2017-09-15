/*
 * Sprite.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef COMMON_STAGE_SPRITE_H_
#define COMMON_STAGE_SPRITE_H_

#include "../../../common/utils/XmlElement.h"
#include "../../../common/utils/Utils.h"
#include <exception>
#include <libxml++/exceptions/exception.h>

namespace config {

class Sprite: public xml::XmlElement {
public:
	Sprite(const std::string& className);
	virtual ~Sprite();

	//divs for enemies
	const int getDiv1() const;
	const int getDiv2() const;
	const int getDiv3() const;
	const int getDiv4() const;
	const int getDiv5() const;
	const int getDiv6() const;
	const int getDiv7() const;

	const int getHeigth() const;
	const int getWidth() const;
	const std::string& getPath() const;
	const std::string& getId() const;
	const std::string& getZIndex() const;

	virtual void setFieldValue(const std::string& fieldName, const std::string& fieldValue);

private:
	std::string id;
	std::string path;
	std::string zindex;
	int heigth;
	int width;
	int div1;int div2;int div3;int div4;
	int div5;int div6;int div7;
};

} /* namespace config */

#endif /* COMMON_STAGE_SPRITE_H_ */
