/*
 * Graphics.h
 *
 *  Created on: Sep 25, 2016
 *      Author: rodri
 */

#ifndef SRC_CLIENT_CLIENTGAMELOGIC_GRAPHICS_H_
#define SRC_CLIENT_CLIENTGAMELOGIC_GRAPHICS_H_


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "GameRefresher.h"
#include "EventHandler.h"
#include "GameReloader.h"
#include "../../common/utils/Constants.h"
#include "../../common/utils/Tokenizer.h"

class Graphics {
public:
	Graphics();
	virtual ~Graphics();
	bool startGameWindow();
	void setUpGame(Client*);
	void setScales(std::string);
	void loopGame(Client* client);
	void ReloadGame(){ hasToReload = true;}

private:
	void closeSDL();
	void setWaitingImage();
	float characterScale;
	float backgroundScale;
	//Window to be rendered
	SDL_Window* gWindow;
	bool hasToReload;
	//The window renderer
	GameReloader* reloader;
	SDL_Renderer* gRenderer;
	GameRefresher* gameRefresher;
	ClientGameStatus* gameStatus;
	Background* background;
	Information* information;
	EventHandler* handler;
	BackgroundImage* waiting;

};

#endif /* SRC_CLIENT_CLIENTGAMELOGIC_GRAPHICS_H_ */
