/*
 * RangeEnemyImage.h
 *
 *  Created on: Nov 2, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_RANGEENEMYIMAGE_H_
#define SRC_COMMON_GAME_RANGEENEMYIMAGE_H_

#include <iostream>
#include "EnemyImage.h"

#define RENEMY_FRAMES 58
namespace std {

class RangeEnemyImage: public EnemyImage{
public:
	SDL_Rect gSpriteClips[ RENEMY_FRAMES ];
	RangeEnemyImage(SDL_Renderer*,std::string, float scale);
	virtual void setFrameProperties(int);
	void changeImageState();
	void setSprites();
	virtual void setPosition(int,int);
	virtual void render();
	virtual ~RangeEnemyImage();
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_RANGEENEMYIMAGE_H_ */
