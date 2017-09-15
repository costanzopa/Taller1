/*
 * Background.h
 *
 *  Created on: 7/10/2016
 *      Author: usuario
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "GameImage.h"

class BackgroundImage: public GameImage{
public:
	BackgroundImage(SDL_Renderer*,std::string, float scale);
	virtual void render();
	~BackgroundImage();

};





#endif /* BACKGROUND_H_ */
