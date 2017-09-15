/*
 * GameImage.h
 *
 *  Created on: 7/10/2016
 *      Author: usuario
 */

#ifndef GAMEIMAGE_H_
#define GAMEIMAGE_H_
#include "LTexture.h"
#include <string>

using namespace std;

class GameImage{
public:
	GameImage();
	virtual ~GameImage();
	LTexture* texture;
	bool loadFromFile( std::string path );
	void free();
	bool loadImage();
	float scale;
	virtual void render() = 0;
	virtual void setPosition(int x,int y);
};




#endif /* GAMEIMAGE_H_ */
