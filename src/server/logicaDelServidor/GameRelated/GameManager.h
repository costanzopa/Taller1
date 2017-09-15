/*
 * gameManager.h
 *
 *  Created on: 16/09/2016
 *      Author: guido
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <list>
#include <vector>
#include <unistd.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include "../Character/Character.h"
#include "../Character/MainCharacter.h"
#include "../Character/MeleeEnemy.h"
#include "../Character/UfoEnemy.h"
#include "../Character/RangeEnemy.h"
#include "../Character/TankEnemy.h"
#include "../Character/BigEyes.h"
#include "Parallax.h"
#include "ReloadReady.h"
#include "Broadcaster.h"
#include "CharacterMap.h"
#include "../../../estructurasDeDatos/CharactersInGame.h"
#include "../../../estructurasDeDatos/AnimationsInGame.h"
#include "../../../common/threads/Thread.h"
#include "../../../estructurasDeDatos/MessageList.h"
#include "../../../estructurasDeDatos/User.h"
#include "../../../estructurasDeDatos/Node.h"
#include "../../config/stage/StageFile.h"
#include "../../config/stage/Stage.h"
#include "../../config/stage/Window.h"
#include "GameController.h"
#include "../Collision/CollisionMap.h"
#include "../Character/CharactersRequest.h"
#include "../Animation/AnimationsRequest.h"
#include "../../../common/utils/Constants.h"
#include "../../../common/utils/Tokenizer.h"
#include "../Collision/GroundFloor.h"
#include "../Animation/BonusKillAll.h"
#include "../Animation/BonusHeal.h"
#include "../Animation/SingleShotAmmo.h"
#include "../Animation/FlameAmmo.h"
#include "../Animation/RocketAmmo.h"

#define N_DIVISION 7
 

using namespace std;

class GameManager: public threads:: Thread{
public:
	int latestPosition;
	int level;
	float windowScale;
	float characterScale;
	Broadcaster* broadcaster;
	list<Character*>* gameParticipants;
	list<EnemyCharacter*>* enemysInLevel;
	list<MainCharacter*>* usersPlaying;
	list<GroundFloor*>* lvl1Platforms;
	list<GroundFloor*>* lvl2Platforms;
	list<GroundFloor*>* lvl3Platforms;
	Parallax* gameBackground;
	list<User*>* connectedUsers;
	std::vector<int>* jumping_table;
	MessageList* incomingActions;
	ReloadReady* reloader;
	bool gameStarted;
	bool changingLevel;
	User* gameManagerID;
	std::string image_path;
	config::Stage* stage;
	int numberOfPlayers;
	int numberOfTeams;
	int teamAssigment;
	int y;
	int enemiesInDivision[N_DIVISION];
	CharactersRequest* charsRequests;
	AnimationsRequest* animsRequests;
	GameController* gameController;
	CharactersInGame* currentLevel;


	AnimationsInGame* animations;
	CollisionMap* collisionMap;
//public:
	void nextLevel();
	void gameOver();
	GameManager(MessageList*,MessageList*, float scale);
	GameManager(MessageList*,MessageList*,config::Stage*);
	/*GameManager(MessageList*,MessageList*);
	GameManager(MessageList*,MessageList*,config::Stage*);*/
	~GameManager();
	void includeNewPlayer(std::string&,std::string&);
	bool started();
	virtual void stop();
private:
	void setEnemiesInDivisionMelee();
	void setEnemiesInDivisionRange();
	void addEnemies();
	void addUFO();
	void addTank();
	void addEyes();
	void changeLevel();
	void showInfo();
	void removeInfo();
	void prepareFirstLevel();
	void setPlatformsLevel();
	void prepareSecondLevel();
	void prepareThirdLevel();
	void reloadStageForLevels(int);
	int setY(int);
	void updateConection(std::string userName);
	void setJumpingTable();
	void broadcastGameInit();
	void processMessages(list<Node*>*);
	void processNode(Node*);
	void updateStatus(std::string&,std::string&);
	void updateBackground();
	void processAction(Character*,std::string&);
	void setCharacterSpawnPosition(std::string&);
	void setCharacterPosition(std::string&,int,int);
	void addNewCharacter(std::string&,std::string&);
	bool addNewUser(std::string&);
	std::string& getImage(std::string&,std::string&);
	virtual void* process();
	void setNumberOfPlayers();
	void setNumberOfTeams();
	std::string& findPath(std::string& characterSelected);

};

#endif /* GAMEMANAGER_H_ */
