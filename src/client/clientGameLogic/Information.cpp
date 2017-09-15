/*
 * Information.cpp
 *
 *  Created on: Nov 15, 2016
 *      Author: rodri
 */

#include "Information.h"

namespace std {

Information::Information(SDL_Renderer* gRenderer) {
	this->renderer = gRenderer;
	this->scale = 1.0;
	this->gTextTexture = NULL;
	this->gPointsTexture = NULL;
	this->gLevelTexture = NULL;
	this->gFont = NULL;
	this->gFontBig = NULL;
	this->resetLevelInfo();
	this->gameOver = false;
}
void Information::resetLevelInfo(){
	this->showingLevelInfo = false;
	for(int i=0;i<4;i++){
		characters[i] = "";
		charColor[i] = {240, 240, 240};
		charPoints[i] = -1;
	}
	charIndex=0;
}
void Information::setScale(float newScale){
	this->scale = newScale;
}
void Information::finishGame(){
	this->gameOver = true;
}
void Information::loadInfo(){
}
void Information::startUpInfo(){
	//Open the font
	gFont = TTF_OpenFont( "fonts/square-deal.ttf", 24 );
	gFontBig = TTF_OpenFont( "fonts/square-deal.ttf", 30 );


	if( gFont == NULL )
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );

	this->text = "Textoooo";
	this->points = "Puntosss";
}
void Information::render(){

	SDL_Color White = {240, 240, 240};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(gFont,this->text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_DestroyTexture(gTextTexture);
	gTextTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 25*this->scale;  //controls the rect's x coordinate
	Message_rect.y = 550*this->scale; // controls the rect's y coordinte
	Message_rect.w = 20*this->text.length()*this->scale; // controls the width of the rect
	Message_rect.h = 53*this->scale; // controls the height of the rect
	SDL_RenderCopy(renderer, gTextTexture, NULL, &Message_rect);


	SDL_Surface* surfacePoints = TTF_RenderText_Solid(gFont,this->points.c_str(), White);
	SDL_DestroyTexture(gPointsTexture);
	gPointsTexture = SDL_CreateTextureFromSurface(renderer, surfacePoints);
	SDL_FreeSurface(surfacePoints);
	int width =  20*this->points.length()*this->scale;

	SDL_Rect Points_rect; //create a rect
	Points_rect.x = this->scale*600;// - (/* 25*this->scale*/ + width );  //controls the rect's x coordinate
	Points_rect.y = 550*this->scale; // controls the rect's y coordinte
	Points_rect.w = width;// controls the width of the rect
	Points_rect.h = 53*this->scale; // controls the height of the rect
	SDL_RenderCopy(renderer, gPointsTexture, NULL, &Points_rect);

	if(showingLevelInfo){
		std::string title = "Nivel completo!";
		if(gameOver)
			title = "Game Over!";//"Juego terminado!";

		SDL_Surface* lvl = TTF_RenderText_Solid(gFontBig,title.c_str(), White);
		if(gLevelTexture)
			SDL_DestroyTexture(gLevelTexture);
		gLevelTexture = SDL_CreateTextureFromSurface(renderer,lvl);
		SDL_FreeSurface(lvl);
		SDL_Rect rect1;
		rect1.x = this->scale*300;// - (/* 25*this->scale*/ + width );  //controls the rect's x coordinate
		rect1.y = (10)*this->scale; // controls the rect's y coordinte
		rect1.w = 200;// controls the width of the rect
		rect1.h = 100*this->scale; // controls the height of the rect

		SDL_RenderCopy(renderer, gLevelTexture, NULL, &rect1);

		for(int i=0;i<charIndex;i++){
			//cout << "El id es: " << this->characters[i] << endl;
			SDL_Surface* levelSurf = TTF_RenderText_Solid(gFontBig,this->characters[i].c_str(), this->charColor[i]);
			if(gLevelTexture)
				SDL_DestroyTexture(gLevelTexture);
			gLevelTexture = SDL_CreateTextureFromSurface(renderer,levelSurf);
			SDL_FreeSurface(levelSurf);

			SDL_Rect rect;
			width =  30*this->characters[i].length()*this->scale;
			rect.x = this->scale*200;// - (/* 25*this->scale*/ + width );  //controls the rect's x coordinate
			rect.y = (100 + 100*i)*this->scale; // controls the rect's y coordinte
			rect.w = width;// controls the width of the rect
			rect.h = 100*this->scale; // controls the height of the rect


			SDL_RenderCopy(renderer, gLevelTexture, NULL, &rect);

			std::stringstream pointsS;
			std::string levelPoints;
			pointsS << this->charPoints[i];
			levelPoints = pointsS.str();
			width =  20*points.length()*this->scale;
			SDL_Surface* levelPointsSurf = TTF_RenderText_Solid(gFontBig,levelPoints.c_str(), this->charColor[i]);
			if(gLevelTexture)
				SDL_DestroyTexture(gLevelTexture);
			gLevelTexture = SDL_CreateTextureFromSurface(renderer,levelPointsSurf);
			SDL_FreeSurface(levelPointsSurf);

			SDL_Rect rectP;
			width =  40*this->characters[i].length()*this->scale;
			rectP.x = this->scale*600 - (/* 25*this->scale +*/ width );  //controls the rect's x coordinate
			rectP.y = (100 + 100*i)*this->scale; // controls the rect's y coordinte
			rectP.w = 200;// controls the width of the rect
			rectP.h = 100*this->scale; // controls the height of the rect


			SDL_RenderCopy(renderer, gLevelTexture, NULL, &rectP);
		}
	}

}
void Information::setOrder(){
	int aux;
	string str;
	SDL_Color col;
	for(int i=0;i<charIndex;i++){
		for(int j=i;j<charIndex;j++){
			if(charPoints[i]<charPoints[j]){
				aux = charPoints[i];
				charPoints[i] = charPoints[j];
				charPoints[j] = aux;

				str = characters[i];
				characters[i] = characters[j];
				characters[j] = str;

				col = charColor[i];
				charColor[i] = charColor[j];
				charColor[j] = col;
			}
		}
	}
}
void Information::endLevelInfo(){
	this->resetLevelInfo();
}
void Information::setText(std::string newText,std::string newPoints){
	this->text = newText;
	this->points = newPoints;
}
void Information::setLevelText(std::string ID,std::string pointsStr,std::string wonStr){
	this->showingLevelInfo = true;
	int points;
	int won;
	sscanf(pointsStr.c_str(), "%d", &points);
	sscanf(wonStr.c_str(), "%d", &won);
	characters[charIndex] = ID;
	charPoints[charIndex] = points;
	if(won){
		charColor[charIndex] = {0, 160 , 0}; // Algun verde
	}
	else{
		charColor[charIndex] = { 160, 0 , 0}; //Algun rojo
	}
	charIndex++;
	this->setOrder();
}


Information::~Information() {
	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;
}

} /* namespace std */
