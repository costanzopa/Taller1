/*
 * BackgroundImage.cpp
 *
 *  Created on: 7/10/2016
 *      Author: usuario
 */
#include "BackgroundImage.h"

BackgroundImage:: BackgroundImage(SDL_Renderer* renderer,std::string path, float scale){
	texture = new LTexture(renderer,path,scale);
}
void BackgroundImage:: render(){
	this->texture->render();
}

BackgroundImage::~BackgroundImage() {
	delete texture;
}
