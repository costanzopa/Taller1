/*
 * XmlFile.cpp
 *
 *  Created on: 01/10/2016
 *      Author: pablo
 */

#include "XmlFile.h"

namespace xml {

XmlFile::XmlFile(XmlFactory* const factory, const std::string& filePath) {
	this->factory = factory;
	this->setFilename(filePath);
}

XmlFile::~XmlFile() {
	delete factory;
}

void XmlFile::complete() {
	if(this->get_document()) {
       const xmlpp::Node* pNode = this->get_document()->get_root_node(); //deleted by DomParser.
       complete(pNode);
	}
}

void XmlFile::complete(const xmlpp::Node* node) {
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	std::string nodeName = node->get_name();
	if(const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node)) {
	    const xmlpp::Element::AttributeList& attributes = nodeElement->get_attributes();
	    if (!attributes.empty()) {
	    	XmlElement* element = this->factory->create(nodeName);
	    	for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
	    		const xmlpp::Attribute* attribute = *iter;
	    		std::string elementFieldName;
	    		std::string elementFieldValue;
	    		elementFieldName += attribute->get_name();
	    		elementFieldValue += attribute->get_value();
	    		std::cout<< elementFieldName <<" = "<< elementFieldValue<<std::endl;
	    		element->setFieldValue(elementFieldName, elementFieldValue);
	    	}
	    	 this->add(element);
	    }
	}
	if(!nodeContent) {
	   xmlpp::Node::NodeList list = node->get_children();
	   for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter) {
	     complete(*iter);
	   }
	}
}


void XmlFile::setFilename(const std::string& filename) {
	this->filepath = filename;
}

const std::string& XmlFile::getFilePath() const {
	return (this->filepath);
}

void XmlFile::setFactory(XmlFactory* const factory) {
	this->factory = factory;
}

const XmlFactory* XmlFile::getFactory() const {
	return (this->factory);
}

} /* namespace xml */
