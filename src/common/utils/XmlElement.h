/*
 * XmlElement.h
 *
 *  Created on: 02/10/2016
 *      Author: pablo
 */

#ifndef COMMON_UTILS_XMLELEMENT_H_
#define COMMON_UTILS_XMLELEMENT_H_

#include <string>
 #include <iostream>

namespace xml {

class XmlElement {
public:
	XmlElement(const std::string& className);
	virtual ~XmlElement();

	virtual void setFieldValue(const std::string& fieldName, const std::string&  fieldValue) = 0;

	virtual const std::string& getClassName() const;

protected:
	std::string className;
};

} /* namespace xml */

#endif /* COMMON_UTILS_XMLELEMENT_H_ */
