/*
 * AnimationsRequest.h
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#ifndef ANIMATIONSREQUEST_H_
#define ANIMATIONSREQUEST_H_
#include <list>
#include <string>
#include <iostream>
using namespace std;
class AnimationsRequest {
public:
	AnimationsRequest();
	std::list<std::string>* animsRequests;
	std::list<std::string>::iterator iter;
	std::list<std::string>* bonusRequest;
	void addNewRequest(std::string);
	void bonusActivated(std::string);
	void empty();
	std::string getRequest();
	std::string getBonusID();
	bool bonusActivatedEmpty();
	bool animationsDissapearingEmpty();
	virtual ~AnimationsRequest();
};

#endif /* ANIMATIONSREQUEST_H_ */
