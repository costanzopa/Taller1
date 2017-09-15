/*
 * Background.h
 *
 *  Created on: Sep 27, 2016
 *      Author: rodri
 */

#ifndef SRC_CLIENT_CLIENTGAMELOGIC_BACKGROUND_H_
#define SRC_CLIENT_CLIENTGAMELOGIC_BACKGROUND_H_

#include <sstream>
#include "../../common/game/BackgroundImage.h"
#include "../../common/utils/Constants.h"

#define NRO_BACKGROUNDS 7

class Background {
public:
	Background(SDL_Renderer*);
	virtual ~Background();
	void modifyBackgroundPosition(std::string&);
	void render();
	void loadBackgrounds();
	void setDirectory(string&);
	void startupBackgrounds();
	void setScale(float);

private:
	BackgroundImage* background[NRO_BACKGROUNDS];
	//BackgroundImage* background2[NRO_BACKGROUNDS];
	SDL_Renderer* renderer;
	string getPath(int i);
	string getDefaultPath(int i);
	string levelPath;
	float bgScale;
	float relativeWidth;

};

#endif /* SRC_CLIENT_CLIENTGAMELOGIC_BACKGROUND_H_ */
