/*
 * Graphics.cpp
 *
 *  Created on: Sep 25, 2016
 *      Author: rodri
 */

#include "Graphics.h"

#define CS 5.0
#define BS 2.0

using namespace std;
using namespace utils;

Graphics::Graphics() {
	gWindow = NULL;
	gRenderer = NULL;
	characterScale = CS;
	backgroundScale = BS;
	reloader = new GameReloader();
}

Graphics::~Graphics() {
}

void Graphics::setUpGame(Client* client){
	//	this->ui->drawCharacterSelection();
		cout<<"We about to start the game"<<endl;
		std::string scaleMessage = client->getScales();
		//cout<<scaleMessage<<endl;
	    this->setScales(scaleMessage);
		this->startGameWindow();
		this->setWaitingImage();
		gameStatus = new ClientGameStatus(client->getUser(),gRenderer,characterScale);
		background = new Background(gRenderer);
		information = new Information(gRenderer);
		background->setScale(backgroundScale);
		information->setScale(backgroundScale);
		gameRefresher = new GameRefresher(gameStatus,background,information,gRenderer,reloader);
		gameRefresher->setScale(characterScale);
		cout<<"Esperamos la respuesta del servidor"<<endl;
		client->getGameReady();
		cout<<"Listo el servidor"<<endl;
		gameRefresher->setClient(client);
		gameRefresher->start();
		while(!gameRefresher->gameReady){
		//cargar imagen
			SDL_RenderPresent(gRenderer);
			usleep(1000000);
		}
		SDL_RenderClear(gRenderer);
		background->startupBackgrounds();
		gameStatus->startupImages();
		information->startUpInfo();
		std::string server;
		server.append(utils::SERVER_USER_ID);
		handler = new EventHandler(client, server);
		handler->setGameReloader(reloader);
		handler->start();

}

void Graphics::setWaitingImage(){
	waiting = new BackgroundImage(gRenderer,utils::WAITING_IMG,backgroundScale);
	waiting->loadImage();
	waiting->setPosition(0,0);
	waiting->render();
	//cout << "ya hice el render" << endl;
	SDL_RenderPresent(gRenderer);
}

bool Graphics::startGameWindow(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Metal Slug", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)(SCREEN_WIDTH*backgroundScale), (int)(backgroundScale*SCREEN_HEIGHT), SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, 0 );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}
	return success;

}

void Graphics::setScales(string scales){

	float cs;// window y despues char
	float ws;

	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(scales, '|');
	sscanf(tkns[0].c_str(), "%f", &ws);
	sscanf(tkns[1].c_str(), "%f", &cs);
	backgroundScale = ws;
	characterScale = cs;
}

void Graphics::loopGame(Client* client){
	bool quit = false;
	this->setUpGame(client);
	//While application is running
	while( !quit )	{
		usleep(9000);
		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		background->render();
		gameStatus->renderCharacters();
		information->render();
		//Update screen
		SDL_RenderPresent( gRenderer );
		quit = !handler->getKeepGoing();
		if(reloader->reload()){
			//cout<<"Empezamos a resetear"<<endl;
			handler->stop();
			handler->close();
			delete handler;
			gameRefresher->stop();
			gameRefresher->close();
			delete gameStatus;
			this->closeSDL();
			std::string destinatary;
			std::string msg = "Reset game";
			//cout<<"Estamos listos para resetear"<<endl;
			destinatary.append(utils::BROADCASTER);
			client->sendMessageToUser(msg,destinatary);
			this->setUpGame(client);
			reloader->gameReloaded();
		}
	}
	client->quitGame();
	gameRefresher->stop();
	gameRefresher->close();
	handler->stop();
	delete gameStatus;
	this->closeSDL();
}

void Graphics::closeSDL(){

	delete waiting;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
