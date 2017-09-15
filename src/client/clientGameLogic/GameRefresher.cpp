/*
 * GameRefresher.cpp
 *
 *  Created on: 17/09/2016
 *      Author: guido
 */
#include "GameRefresher.h"
#include "../../common/game/CharacterImage.h"
#include "../../common/game/MeleeEnemyImage.h"
#include "../../common/game/UfoEnemyImage.h"
#include "../../common/game/EyesEnemyImage.h"
#include "../../common/game/RangeEnemyImage.h"
#include "../../common/game/GameImage.h"
#include "../../common/utils/Tokenizer.h"
#include "../../common/utils/Constants.h"

GameRefresher :: GameRefresher(ClientGameStatus* game,Background* background,Information* info, SDL_Renderer* renderer,GameReloader* reloaderr){
	gameStatus = game;
	reloader = reloaderr;
	gameBackground = background;
	gameInfo = info;
	gRenderer = renderer;
	communication = NULL;
	gameReady = false;
	scale = 1.0;
}

void GameRefresher:: updateGameStatus(list<Node*>* updates){
	list<Node*>:: iterator iter;
	Node* prueba = NULL;
	iter = updates->begin();
	while(iter != updates->end()){
		this->processMessage(*iter);
		prueba = (*iter);
		iter++;
		delete prueba;
	}
	delete updates;
	//if(!prueba==NULL)
	//cout << prueba->getMessage() << endl;
}
void GameRefresher:: addNewCharacter(std::string& ID,std::string& path){
	GameImage* newCharacter = new CharacterImage(gRenderer,path,scale);
	gameStatus->addCharacter(ID,newCharacter);
}

//TODO

void GameRefresher:: addNewMeleeEnemy(std::string& ID,std::string& path){
	GameImage* newCharacter = new MeleeEnemyImage(gRenderer,path,scale);
	gameStatus->addCharacter(ID,newCharacter);
}

void GameRefresher:: addNewRangeEnemy(std::string& ID,std::string& path){
	GameImage* newCharacter = new RangeEnemyImage(gRenderer,path,scale);
	gameStatus->addCharacter(ID,newCharacter);
}

void GameRefresher:: addNewUfoEnemy(std::string& ID,std::string& path){
	GameImage* newCharacter = new UfoEnemyImage(gRenderer,path,scale);
	//cout<<ID<<endl;
	gameStatus->addCharacter(ID,newCharacter);
}

void GameRefresher:: addNewTankEnemy(std::string& ID,std::string& path){
	GameImage* newCharacter = new TankEnemyImage(gRenderer,path,scale);
	gameStatus->addCharacter(ID,newCharacter);
}

void GameRefresher:: addNewEyesEnemy(std::string& ID,std::string& path){
	GameImage* newCharacter = new EyesEnemyImage(gRenderer,path,scale);
	gameStatus->addCharacter(ID,newCharacter);
}

void GameRefresher:: processMessage(Node* message){
	std::string command = message->getMessage();
	//cout << command << endl;
	if(command.compare(utils::GAME_READY)==0){
		gameReady = true;
		return;
	}
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(command, '|');
	if(tkns[0].compare(utils::RELOAD_GAME)==0){
		reloader->reloadGame();
		delete tkn;
		this->stop();
		return;
	} else if(tkns[0].compare(utils::NEW_CHARACTER)==0){
		this->addNewCharacter(tkns[1],tkns[2]);
	}else if(tkns[0].compare(utils::EXISTING_CHARACTER)==0){
		this->gameStatus->modifyCharacterPosition(tkns[1],tkns[2],tkns[3],tkns[4]);
	}else if(tkns[0].compare(utils::DYING_CHARACTER)==0){
		this->gameStatus->removeCharacter(tkns[1]);
	}else if(tkns[0].compare(utils::NEW_BOSS)==0){
		char tipo = tkns[1][0];
				printf("%c\n",tipo);
				switch(tipo){
				case 'U':
					this->addNewUfoEnemy(tkns[1],tkns[2]);
					delete tkn;
					return;
				case 'T':
					this->addNewTankEnemy(tkns[1],tkns[2]);
					delete tkn;
					return;
				case 'B':
					this->addNewEyesEnemy(tkns[1],tkns[2]);
				}
	}else if(tkns[0].compare(utils::EXISTING_BOSS)==0){
		//cout<<command<<endl;
		this->gameStatus->modifyBossPosition(tkns[1],tkns[2],tkns[3],tkns[4]);
	}else if(tkns[0].compare(utils::DYING_BOSS)==0){
		this->gameStatus->removeBoss(tkns[1]);
	}else if(tkns[0].compare(utils::NEW_ENEMY)==0){
		//cout<<command<<endl;
		char tipo = tkns[1][0];
		printf("%c\n",tipo);
		switch(tipo){
		case 'M':
			this->addNewMeleeEnemy(tkns[1],tkns[2]);
			delete tkn;
			return;
		case 'R':
			this->addNewRangeEnemy(tkns[1],tkns[2]);
			delete tkn;
			return;
		case 'U':
			this->addNewUfoEnemy(tkns[1],tkns[2]);
			delete tkn;
			return;
		case 'T':
			this->addNewTankEnemy(tkns[1],tkns[2]);
			delete tkn;
			return;
		case 'B':
			this->addNewEyesEnemy(tkns[1],tkns[2]);
		}
	}else if(tkns[0].compare(utils::DYING_ENEMY)==0){
		this->gameStatus->removeEnemy(tkns[1]);
	}else if(tkns[0].compare(utils::EXISTING_ENEMY)==0){
		//cout<<command<<endl;
		this->gameStatus->modifyEnemyPosition(tkns[1],tkns[2],tkns[3],tkns[4]);
	}else if(tkns[0].compare(utils::NEW_ANIMATION)==0){
		this->gameStatus->addNewAnimation(tkns[1],tkns[2],tkns[3],tkns[4]);
	}else if(tkns[0].compare(utils::EXISTING_ANIMATION)==0){
		this->gameStatus->modifyAnimation(tkns[1],tkns[2],tkns[3],tkns[4],tkns[5]);
	}else if(tkns[0].compare(utils::DISSAPEAR_ANIMATION)==0){
		this->gameStatus->removeAnimation(tkns[1],tkns[2]);
	}else{
		if(tkns[0].compare(utils::NEW_BACKGROUND_POSITION)==0){
			this->gameBackground->modifyBackgroundPosition(tkns[1]);
		}
	else{
		if(tkns[0].compare(utils::BACKGROUND_SIZE)==0){
			//this->gameBackground->setSize(tkns[1]);
		}
		if(tkns[0].compare(utils::SET_BACKGROUND_DIR)==0){
			//cout << tkns[1];
			this->gameBackground->setDirectory(tkns[1]);
		}
		if(tkns[0].compare(utils::NEW_INFO)==0){
			//cout << command << endl;
			if(this->communication->getUser().compare(tkns[1])==0)
				this->gameInfo->setText(tkns[2],tkns[3]);
		}
		if(tkns[0].compare(utils::LEVEL_INFO)==0){
			this->gameInfo->setLevelText(tkns[1],tkns[2],tkns[3]);
		}
		if(tkns[0].compare(utils::END_LEVEL_INFO)==0){
			this->gameInfo->endLevelInfo();
		}
		if(tkns[0].compare(utils::GAME_OVER)==0){
			//cout << command << endl;
			this->gameInfo->finishGame();
		}
	}
	}
	delete tkn;
}

bool GameRefresher::isEnemy(std::string& id){
	id.substr(1,6);
	if(id.compare("enemy")==0)
		return true;
	return false;
}

void GameRefresher::setScale(float Nscale){
	scale = Nscale;
}

void GameRefresher:: setClient(Client* client){
	communication = client;
}
void* GameRefresher::process(){
	while(this->isRunning()){
		//delete incomingUpdates
		list<Node*>* incomingUpdates = this->communication->getMessages();
		usleep(10000);
		this->updateGameStatus(incomingUpdates);
	}
	return (void*)NULL;
}

void GameRefresher:: stop(){
	Thread::stop();
}

GameRefresher::~GameRefresher() {
	
}
