#include "ClientGameStatus.h"
#include <string>
#include <vector>
#include "../common/utils/Constants.h"
#include "../common/utils/Tokenizer.h"
#include "../common/game/SingleShotImage.h"
#include "../common/game/RocketLauncherImage.h"
#include "../common/game/FlameShotImage.h"
#include "../common/game/ZombieShotImage.h"
#include "../common/game/CharacterImage.h"
#include "../common/game/BigEyesLaserImage.h"
#include "../common/game/BossImage.h"
#include "../common/game/BigEyesBombImage.h"
#include "../common/game/TankCannonImage.h"
#include "../common/game/RocketAmmoImage.h"
#include "../common/game/FlameAmmoImage.h"
#include "../common/game/SingleShotAmmoImage.h"
#include "../common/game/KillBonusImage.h"
#include "../common/game/HealBonus.h"

#include <iostream>
#include "../common/game/EnemyImage.h"
using namespace std;
ClientGameStatus:: ClientGameStatus(string userName,SDL_Renderer* renderer,float scale){
	this->user = userName;
	characterList = new list<GameImage*>();
	this->renderer = renderer;
	std::string path;
	path.append(utils::BULLETS_DIR);
	//Bullets
	AnimationImage* singleShot = new SingleShotImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::SINGLE_SHOT] = singleShot;
	characterList->push_back(singleShot);
	AnimationImage* rocketShot = new RocketLauncherImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::ROCKET_SHOT] = rocketShot;
	characterList->push_back(rocketShot);
	AnimationImage* flameShot = new FlameShotImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::FLAME_SHOT] = flameShot;
	characterList->push_back(flameShot);
	AnimationImage* zombieShot = new ZombieShotImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::ZOMBIE_SHOT] = zombieShot;
	characterList->push_back(zombieShot);
	AnimationImage* bigEyesShot = new BigEyesLaserImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::BIGEYES_SHOT] = bigEyesShot;
	characterList->push_back(bigEyesShot);
	AnimationImage* bigEyesBomb = new BigEyesBombImage(renderer,scale);
	characterMap[utils::BIGEYES_BOMB] = bigEyesBomb;
	characterList->push_back(bigEyesBomb);
	AnimationImage* tankCannon = new TankCannonImage(renderer,scale);
	characterMap[utils::TANK_CANNON] = tankCannon;
	characterList->push_back(tankCannon);

	//Bonus

	AnimationImage* singleShotAmmo = new SingleShotAmmoImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::SINGLE_AMMO] = singleShotAmmo;
	characterList->push_back(singleShotAmmo);
	AnimationImage* rocketShotAmmo = new RocketAmmoImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::ROCKET_AMMO] = rocketShotAmmo;
	characterList->push_back(rocketShotAmmo);
	AnimationImage* flameShotAmmo = new FlameAmmoImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::FLAME_AMMO] = flameShotAmmo;
	characterList->push_back(flameShotAmmo);
	AnimationImage* kill = new KillBonusImage(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::BONUS_KILL_ALL] = kill;
	characterList->push_back(kill);
	AnimationImage* heal = new HealBonus(renderer,scale);//Hay que corregir esto manana sigo
	characterMap[utils::BONUS_HEAL] = heal;
	characterList->push_back(heal);


}
void ClientGameStatus:: addCharacter(std::string& ID,GameImage* character){
	characterMap[ID] = character;
	characterList->push_back(character);
}
void ClientGameStatus::modifyEnemyPosition(std::string& id,std::string& coordinates,std::string& frameNumber,std::string& connected){
	GameImage* character = characterMap.at(id);
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(coordinates, ':');
	int x,y,frame,legNumber,connection;
	sscanf(tkns[0].c_str(), "%d", &x);
	sscanf(tkns[1].c_str(), "%d", &y);
	sscanf(frameNumber.c_str(), "%d", &frame);
	sscanf(connected.c_str(), "%d", &connection);


	((EnemyImage*)character)->setStatus(frame);
	character->setPosition(x,y);
	delete tkn;
}
void ClientGameStatus:: modifyBossPosition(std::string& ID,std::string& coordinates,std::string& frameNumber,std::string& connected){
	GameImage* character = characterMap.at(ID);
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(coordinates, ':');
	Tokenizer* tkn1 = new Tokenizer();
	vector<string> tkns1 = tkn1->tokenize(frameNumber, ':');
	int x,y,frame,legNumber,connection;
	sscanf(tkns[0].c_str(), "%d", &x);
	sscanf(tkns[1].c_str(), "%d", &y);
	sscanf(tkns1[0].c_str(), "%d", &frame);
	sscanf(tkns1[1].c_str(), "%d", &legNumber);
	((BossImage*)character)->setMainFrame(frame);
	((BossImage*)character)->setExtraFrame(legNumber);
	character->setPosition(x,y);
	delete tkn;
	delete tkn1;
}
void ClientGameStatus::removeCharacter(std::string& ID){
	GameImage* character = characterMap.at(ID);
	((CharacterImage*)character)->dead();
}
void ClientGameStatus::removeBoss(std::string& ID){
	GameImage* character = characterMap.at(ID);
	((BossImage*)character)->dead();
}
void ClientGameStatus::removeEnemy(std::string& ID){
	GameImage* character = characterMap.at(ID);
	((EnemyImage*)character)->dead();
}
void ClientGameStatus::removeAnimation(std::string& animID,std::string& id){
	GameImage* character = characterMap.at(animID);
	((AnimationImage*)character)->removeAnimation(id);
}
void ClientGameStatus::addNewAnimation(std::string& type,std::string& id,std::string& position,std::string& frameNumber){
	GameImage* character = characterMap.at(type);
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(position, ':');
	int x,y,frame;
	sscanf(tkns[0].c_str(), "%d", &x);
	sscanf(tkns[1].c_str(), "%d", &y);
	sscanf(frameNumber.c_str(), "%d", &frame);
	((AnimationImage*)character)->addNewCopy(id,x,y,frame);
	delete tkn;
}
void ClientGameStatus::modifyAnimation(std::string& type,std::string& id,std::string& position,std::string& frameNumber,std::string& connected){
	GameImage* character = characterMap.at(type);
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(position, ':');
	int x,y,frame;
	sscanf(tkns[0].c_str(), "%d", &x);
	sscanf(tkns[1].c_str(), "%d", &y);
	sscanf(frameNumber.c_str(), "%d", &frame);
	((AnimationImage*)character)->setPosition(id,x,y,frame);
	delete tkn;
}
void ClientGameStatus:: modifyCharacterPosition(std::string& ID,std::string& coordinates,std::string& frameNumber,std::string& connected){
	GameImage* character = characterMap.at(ID);
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(coordinates, ':');
	Tokenizer* tkn1 = new Tokenizer();
	vector<string> tkns1 = tkn1->tokenize(frameNumber, ':');
	int x,y,frame,legNumber,connection;
	sscanf(tkns[0].c_str(), "%d", &x);
	sscanf(tkns[1].c_str(), "%d", &y);
	sscanf(tkns1[0].c_str(), "%d", &frame);
	sscanf(tkns1[1].c_str(), "%d", &legNumber);
	sscanf(connected.c_str(), "%d", &connection);
	((CharacterImage*)character)->setStatus(frame,connection);
	((CharacterImage*)character)->setLegStatus(legNumber);
	character->setPosition(x,y);
	delete tkn;
	delete tkn1;
}
void ClientGameStatus:: startupImages(){
	list<GameImage*>:: iterator iter;
	iter = characterList->begin();
	while( iter != characterList->end()){
		printf("We will load one character\n");
		if(!(*iter)->loadImage()){
			(*iter)->loadFromFile(utils::MISSING_CHARACTER);
		}
		iter++;
	}
}
void ClientGameStatus:: renderCharacters(){
	list<GameImage*>:: iterator iter;
	iter = characterList->begin();
	while( iter != characterList->end()){
		(*iter)->render();
		iter++;
	}
	this->characterMap.at(user)->render();

}
ClientGameStatus:: ~ClientGameStatus(){
	list<GameImage*>::iterator it = this->characterList->begin();
		while (it != characterList->end()) {
			delete (*it);
			it++;
		}
	delete characterList;
}
