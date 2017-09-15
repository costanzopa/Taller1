/*
 * GameImage.cpp
 *
 *  Created on: 7/10/2016
 *      Author: usuario
 */
#include "CharacterImage.h"


GameImage::GameImage(){

}
GameImage:: ~GameImage(){

}

bool GameImage:: loadFromFile( std::string path ){
	return this->texture->loadFromFile(path);
}

bool GameImage::loadImage(){
	return this->texture->loadImage();
}
void GameImage::setPosition(int x,int y){
	this->texture->setPosition(x,y);
}

//Deallocates texture
void GameImage:: free(){
	this->texture->free();
}
