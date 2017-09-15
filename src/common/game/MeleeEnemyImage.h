/*
 * MeleeEnemyImage.h
 *
 *  Created on: 5/11/2016
 *      Author: usuario
 */

#ifndef MELEEENEMYIMAGE_H_
#define MELEEENEMYIMAGE_H_
#define MENEMY_FRAMES 45
#include "LTexture.h"
#include <string>
#include "EnemyImage.h"

namespace std {

class MeleeEnemyImage:public EnemyImage{
public:
	SDL_Rect gSpriteClips[ MENEMY_FRAMES ];
	//Initializes variables
	MeleeEnemyImage(SDL_Renderer* renderer,std::string path, float scale);

	//Deallocates memory
	virtual void setPosition(int,int);
	virtual ~MeleeEnemyImage();
	virtual void setFrameProperties(int);
	void changeImageState();
	//Renders texture at given point
	virtual void render();
	void setStatus(int frame,int connection);
private:
	void setSprites();

};

} /* namespace std */


#endif /* MELEEENEMYIMAGE_H_ */
