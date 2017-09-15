/*
 * GameReloader.h
 *
 *  Created on: 01/01/2014
 *      Author: guido
 */

#ifndef GAMERELOADER_H_
#define GAMERELOADER_H_

class GameReloader {
public:
	bool hasToReload;
	GameReloader();
	virtual ~GameReloader();
	void reloadGame(){ hasToReload=true;}
	void gameReloaded(){ hasToReload=false;}
	bool reload(){ return hasToReload;}
};

#endif /* GAMERELOADER_H_ */
