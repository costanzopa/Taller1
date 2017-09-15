/*
 * RocketShot.h
 *
 *  Created on: Nov 12, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_ROCKETSHOT_H_
#define SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_ROCKETSHOT_H_

 #include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>

#include "../Animation/Animation.h"
#include "../GameRelated/Parallax.h"
#include "../GameRelated/CharacterMap.h"
#include "../../../common/utils/Constants.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/MainCharacter.h"


class MainCharacter;
class EnemyCharacter;

namespace std {

class RocketShot: public Animation {
	enum HorizontalDirection { right , left};
public:
	RocketShot(int,int,int,int,CollisionMap*,AnimationsRequest*,string);
	virtual ~RocketShot();
		bool inAction;
		bool firstFrame;
		int inclination;
		int speed;
		int anchoPantalla;
		int x;
		int y;
		int screenPosition;
		int directionOffset;
		int loopingFrames;
		int dissapearingFrames;
		std::string type;
		std::string ID;
		CollisionRectangle* shot;
		int sequenceSelector;
		virtual bool collisionWith(Collisionable*);
		virtual bool collisionWith(MainCharacter*);
		virtual bool collisionWith(EnemyCharacter*);
		virtual bool collisionWith(Animation*);
		HorizontalDirection x_dir;
		virtual void collisioned(Collisionable*);
		virtual int getDisplacement();
		virtual int getLeftLimit();
		virtual int getRightLimit();
		virtual std::string getType();
		void nextPosition();
		void nextYPosition();
		virtual bool isConnected();
		virtual std::string getFrame();
		virtual int getXPos(std::Parallax*);
		virtual int getYPos();
		void setDirection(int);
		int getId();

	private:
		static int newId;
		const int id;
};

} /* namespace std */

#endif /* SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_ROCKETSHOT_H_ */
