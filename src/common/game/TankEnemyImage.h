/*
 * MeleeEnemyImage.h
 *
 *  Created on: 13/11/2016
 *      Author: pablo
 */

#ifndef TANKENEMYIMAGE_H_
#define TANKENEMYIMAGE_H_
#define TENEMY_FRAMES 55
#include "LTexture.h"
#include <string>
#include "BossImage.h"

namespace std {

class TankEnemyImage:public BossImage{
public:
	SDL_Rect gSpriteClips[ TENEMY_FRAMES ];
	//Initializes variables
	TankEnemyImage(SDL_Renderer* renderer,std::string path, float scale);

	//Deallocates memory
	virtual ~TankEnemyImage();
	virtual void setMainFrame(int);
	virtual void setExtraFrame(int);
	void changeImageState();
	//Renders texture at given point
	virtual void render();
	void setStatus(int frame,int connection);
private:
	void setSprites();

};

} /* namespace std */


#endif /* TANKENEMYIMAGE_H_ */
