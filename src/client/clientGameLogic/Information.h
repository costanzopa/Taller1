/*
 * Information.h
 *
 *  Created on: Nov 15, 2016
 *      Author: rodri
 */

#ifndef SRC_CLIENT_CLIENTGAMELOGIC_INFORMATION_H_
#define SRC_CLIENT_CLIENTGAMELOGIC_INFORMATION_H_

#define MAX_PLAYERS 4

#include <string>
#include <iostream>
#include <sstream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../../common/game/LTexture.h"

namespace std {



class Information {
public:
	Information(SDL_Renderer*);
	virtual ~Information();
	void loadInfo();
	void setScale(float);
	void startUpInfo();
	void endLevelInfo();
	void resetLevelInfo();
	void setOrder();
	void finishGame();
	void setText(std::string,std::string);
	void setLevelText(std::string,std::string,std::string);
	void render();

	SDL_Renderer* renderer;
	SDL_Texture* gTextTexture;
	SDL_Texture* gPointsTexture;
	TTF_Font* gFont;
	TTF_Font* gFontBig;
	float scale;
	std::string text;
	std::string points;

	bool gameOver;

	bool showingLevelInfo;
	int charIndex;
	std::string characters[MAX_PLAYERS];
	int charPoints[MAX_PLAYERS];
	SDL_Color charColor[MAX_PLAYERS];
	SDL_Texture* gLevelTexture;
};

} /* namespace std */

#endif /* SRC_CLIENT_CLIENTGAMELOGIC_INFORMATION_H_ */
