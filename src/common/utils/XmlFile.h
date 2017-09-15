/*
 * XmlFile.h
 *
 *  Created on: 01/10/2016
 *      Author: pablo
 */

#ifndef COMMON_UTILS_XMLFILE_H_
#define COMMON_UTILS_XMLFILE_H_

#include <libxml++/libxml++.h>
#include <string>
#include "XmlFactory.h"
#include <iostream>

namespace xml {

class XmlFile: public xmlpp::DomParser  {
public:
	XmlFile(XmlFactory* const factory,const std::string& filePath);
	virtual ~XmlFile();

	void setFilename(const std::string& filename);
	const std::string& getFilePath() const;

	void setFactory(XmlFactory* const factory);
	const XmlFactory* getFactory() const;

	virtual void add(XmlElement* const element) = 0;

protected:
	//Metodos privados
	virtual void complete(const xmlpp::Node* node);
	virtual void complete();

private:
	std::string filepath;
	XmlFactory* factory;
};


} /* namespace xml */

#endif /* COMMON_UTILS_XMLFILE_H_ */
