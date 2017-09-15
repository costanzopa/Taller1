/*
 * AnimationsRequest.cpp
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#include "AnimationsRequest.h"

AnimationsRequest::AnimationsRequest() {
	this->animsRequests = new list<std::string>();
	this->bonusRequest = new list<std::string>();
}
void AnimationsRequest::addNewRequest(std::string request){
	this->animsRequests->push_back(request);
}
void AnimationsRequest::empty(){
	delete this->animsRequests;
	delete this->bonusRequest;
	this->animsRequests = new list<std::string>();
	this->bonusRequest = new list<std::string>();
}
std::string AnimationsRequest::getBonusID(){
	iter = this->bonusRequest->begin();
	std::string request = *iter;
	this->bonusRequest->erase(iter);
	return request;
}
std::string AnimationsRequest::getRequest(){
	iter = this->animsRequests->begin();
	std::string request = *iter;
	this->animsRequests->erase(iter);
	return request;
}
void AnimationsRequest::bonusActivated(std::string id){
	this->bonusRequest->push_back(id);
}
bool AnimationsRequest::animationsDissapearingEmpty(){
	return this->animsRequests->empty();
}
bool AnimationsRequest::bonusActivatedEmpty(){
	return this->bonusRequest->empty();
}
AnimationsRequest::~AnimationsRequest() {
	// TODO Auto-generated destructor stub
}

