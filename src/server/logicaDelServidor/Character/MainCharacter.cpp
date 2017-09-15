/*
 * MainCharacter.cpp
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */

#include "MainCharacter.h"

#define FRAME_SPEED 8

#define MOVING_LEG_OFFSET 1*FRAME_SPEED
#define MOVING_LEG_OFFSET_LENGHT 18*FRAME_SPEED

#define CRAWL_LEG_OFFSET 19*FRAME_SPEED

#define LEFT_LEG_OFFSET 20*FRAME_SPEED


#define IDLE_OFFSET 0
#define IDLE_OFFSET_LENGTH 4*FRAME_SPEED

#define FIRING_OFFSET 4*FRAME_SPEED
#define FIRING_OFFSET_LENGTH 7*FRAME_SPEED

#define UP_OFFSET 15*FRAME_SPEED

#define RELOADING_OFFSET 26*FRAME_SPEED
#define RELOADING_OFFSET_LENGTH 19*FRAME_SPEED

#define CRAWL_OFFSET 53*FRAME_SPEED

#define CHANGING_WEAPON_OFFSET 64*FRAME_SPEED
#define CHANGING_WEAPON_OFFSET_LENGTH 12*FRAME_SPEED

#define SHOTGUN_OFFSET 76*FRAME_SPEED

#define DYING_OFFSET 152*FRAME_SPEED
#define DYING_OFFSET_LENGTH 18*FRAME_SPEED

#define LEFT_OFFSET 170*FRAME_SPEED

#define MIN_POSITION 20

#define CROUCH_WIDTH 23
#define CROUCH_HEIGHT 20
#define CROUCH_X_OFFSET 3
#define CROUCH_Y_OFFSET 19
#define LONG_BODY_WIDTH 12
#define LONG_BODY_HEIGHT 38
#define SHORT_BODY_WIDTH 8
#define SHORT_BODY_HEIGHT 30
using namespace std;



MainCharacter :: MainCharacter
(float scale,string& ID,int vel,std::vector<int>* jump_table,std::string characterSelected,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map){
	this->setCollisionMap(map);
	this->scale = scale;
	longBodyWidth = LONG_BODY_WIDTH*scale;
	longBodyHeight = LONG_BODY_HEIGHT*scale;
	shortBodyWidth = SHORT_BODY_WIDTH*scale;
	shortBodyHeight = SHORT_BODY_HEIGHT*scale;
	crouchBodyWidth = CROUCH_WIDTH*scale;
	crouchBodyHeight = CROUCH_HEIGHT*scale;
	this->setCollisionBox();
	current_y = 0;
	this->secondaryBox = new CollisionBox();
	int newy = current_y - (scale-1)*20;
	this->crouch = new CollisionRectangle(x,newy,crouchBodyWidth,crouchBodyHeight,CROUCH_X_OFFSET*scale,CROUCH_Y_OFFSET*scale);
	this->secondaryBox->addNewHitbox(crouch);
	longBody = new CollisionRectangle(x,newy,longBodyWidth,longBodyHeight,9*scale,1*scale);
	shortBody = new CollisionRectangle(x,newy,shortBodyWidth,shortBodyHeight,3*scale,9*scale);//Xpos Ypos width height Xoffset Yoffset
	this->hitBox->addNewHitbox(longBody);
	this->hitBox->addNewHitbox(shortBody);
	this->setIntroductionMessage(utils::NEW_CHARACTER);
	this->setExistingMessage(utils::EXISTING_CHARACTER);
	this->setAnimationsRequest(animsRequest);
	this->setCharactersRequest(requestHandler);
	this->setActionsList();
	this->alive = true;
	this->dead = false;
	this->onScreen=true;
	this->healthPoints = 100;
	this->points = 0;
	currentDirection = right;
	verticalDirection = horizontal;
	sequence_select = 0;
	sequence_offset = 0;
	weapons = new Weapons();
	jumping_table= jump_table;
	this->setCharacterID(ID);
	velocidad = vel;
	frame_selector = 0;
	frame_offset = 0;
	x=current_y=screenPosition=0;
	jump_stage = 0;
	jumping = false;
	connected = true;
	anchoPantalla = utils::SCREEN_WIDTH;
	characterSelect = characterSelected;
	leftLimit = this->x;
	rightLimit = this->x + 22; //Ancho del personaje, despues modificar
	floorLevel = topLevel = current_y;
	moving = false;
	changingWeapon = false;
}
void MainCharacter::setLevel(int i){
	this->levelId = i;
	this->setTopLevel();
}
void MainCharacter::setEnemies(list<EnemyCharacter*>* e){
	this->enemies = e;
}
EnemyCharacter* MainCharacter::getClosestEnemy(){

	int min = 4000;
	list<EnemyCharacter*> :: iterator iter;
	EnemyCharacter* chosenOne = NULL;
	iter = enemies->begin();
	while(iter != enemies->end()){
		int dist = abs((*iter)->x - this->x);
		if(dist < min){
			chosenOne = (*iter);
			min = dist;
		}
		iter++;
	}
	return (chosenOne);
}
void MainCharacter::setTeam(int t){
	this->team = t;
}
void MainCharacter::setTopLevel(){
	if(levelId == 1){
		topLevel = 375;
		return;
	}
	if(levelId == 2){

	}
	if(levelId == 3){

	}
}
void MainCharacter::addPoints(int x){
	this->points += x;
}
void MainCharacter::healAll(){
	this->healthPoints = 100;
}
void MainCharacter::die(){
	this->dying = true;
	this->alive = false;
	this->selectCurrentSequence();
	this->sequence_offset = 0;
}
bool MainCharacter::collisionWith(Collisionable* collided){
	if(!alive || !connected)
		return false;
	return collided->collisionWith(this);
}
bool MainCharacter::collisionWith(MainCharacter* collided){
	if(!alive || !connected)
			return false;
	return true;
}
bool MainCharacter::collisionWith(EnemyCharacter* collided){
	if(!alive || !connected)
			return false;
	return true;
}
bool MainCharacter::collisionWith(Animation* other){
	if(!alive || !connected)
			return false;
	return other->collisionWith(this);
}

int MainCharacter::getRightLimit(){
	return this->x + 30;
}
int MainCharacter::getLeftLimit(){
	return this->x;
}
void MainCharacter:: Disconnected(){
	connected = false;
}
void MainCharacter:: Connected(){
	connected = true;
}
bool MainCharacter :: isConnected(){
	return connected;
}
int MainCharacter::getScreenPosition(){
	return screenPosition;
}
int MainCharacter::getDisplacement(){
	return this->displacement;
}
bool MainCharacter:: hasID(std::string& ID){
	if (this->getCharacterID().compare(ID)==0)
		return true;
	return false;
}
void MainCharacter::shoot(){
	if(!(verticalDirection == horizontal || verticalDirection == down || this->weapons->currentWeapon == 0))
		return;
	if(!weapons->hasAmmo())
		return;
	if(!reloading && !changingWeapon){
		if(!firing){
			firing = true;
			this->selectCurrentSequence();
		}
		sequence_offset = 0;
		VerticalDirection dir = this->verticalDirection;
		if(dir == down)
			dir = horizontal;
		reloading = weapons->shoot();
		int shoot_x = this->getXShot();
		int shoot_y = this->getYShot();
		if(this->weapons->currentWeapon == 0)
			playerActions->push_back(new SingleShot(shoot_x,shoot_y,this->screenPosition,currentDirection,dir,this->collisionMap,this->animsRequestHandler,this->characterID));
		if(this->weapons->currentWeapon == 1)
			playerActions->push_back(new RocketShot(shoot_x,shoot_y,this->screenPosition,currentDirection,this->collisionMap,this->animsRequestHandler,this->characterID));
		if(this->weapons->currentWeapon == 2)
			playerActions->push_back(new FlameShot(shoot_x,shoot_y,this->screenPosition,currentDirection,this->collisionMap,this->animsRequestHandler,this->characterID));
		if(this->weapons->currentWeapon == 3){
			this->getClosestEnemy();
			playerActions->push_back(new EnemyChaser(shoot_x,shoot_y,this->screenPosition,this->getClosestEnemy(),this->collisionMap,this->animsRequestHandler,this->characterID));
		}

		this->requestHandler->addNewRequest(this->characterID);
		if(dir == diagonal)
			this->verticalDirection = up;
	}
}
int MainCharacter::getXShot(){
	//Handgun
	if(this->weapons->currentWeapon==0){
		if(currentDirection == right){
			if(verticalDirection != up)
				return  this->x + 42;
			else
				return this->x + 27;
			}
		else{
			if(verticalDirection != up)
				return  this->x - 12;
			else
				return this->x + 27;
		}
	}
	//Shotgun
	else{
		if(currentDirection==right)
			return this->x + 42;
		else
			return this->x + -10;
	}
}
int MainCharacter::getYShot(){
	//Handgun
	if(this->weapons->currentWeapon==0){
		if(verticalDirection == horizontal)
			return  this->current_y + 13;
		if(verticalDirection == down)
			return  this->current_y + 29;
		if(verticalDirection == up)
			return this->current_y;
	}
	//Shotgun
	if(verticalDirection == horizontal)
		return this->current_y + 18;
	if(verticalDirection == down)
		return this->current_y + 27;
	return this->current_y;
}
void MainCharacter:: setCharacterPosition(int x,int y){
	//cout<<"Entro aca"<<endl;
	this->x = x;
	this->current_y = current_y;
	leftLimit = this->x;
	rightLimit = this->x + 22; //Ancho del personaje, despues modificar
	current_y = y;
	int newy = current_y - (scale-1)*20;
	this->hitBox->moveCollisionBox(this->x,newy);
	this->floorLevel = y;
}
void MainCharacter:: setCharacterScreenPosition(int mapPosition){
	int medioAncho = anchoPantalla/2;
	//if(mapPosition>medioAncho)
		this->screenPosition = this->x - mapPosition + medioAncho;
	//else
		//this->screenPosition = this->x;
}
void MainCharacter:: processAction(std::string& action){
	if(!alive)
		return;

	if(action.compare(utils::KEY_PRESS_DOWN)==0){
		this->crawl();
		return;
	}
	if(action.compare(utils::KEY_RELEASE_DOWN)==0){
		this->standUp();
		return;
	}
	if(action.compare(utils::KEY_PRESS_UP)==0){
		this->lookUp();
		return;
	}
	if(action.compare(utils::KEY_RELEASE_UP)==0){
		this->lookRightFromUp();
		return;
	}
	if(action.compare(utils::KEY_PRESS_LEFT)==0){
		this->moveLeft();
		return;
	}
	if(action.compare(utils::KEY_PRESS_RIGHT)==0){
		this->moveRight();
		return;
	}
	if(action.compare(utils::KEY_RELEASE_LEFT)==0){
		this->halt();
		return;
	}
	if(action.compare(utils::KEY_RELEASE_RIGHT)==0){
		this->halt();
		return;
	}
	if(action.compare(utils::KEY_PRESS_SHOOT)==0){
		this->shoot();
		return;
	}
	if(action.compare(utils::KEY_PRESS_JUMP)==0){
		if(verticalDirection != down){
			if(!jumping){
				jumping = true;
				jump_stage = 0;
			}
		}
		return;
	}
	if(action.compare(utils::KEY_CYCLE_PREVIOUS)==0){
		this->cyclePreviousWeapon();
	}
	if(action.compare(utils::KEY_CYCLE_NEXT)==0){
		this->cycleNextWeapon();
	}
}

void MainCharacter::selectCurrentSequence(){
	sequence_select = 0;

	if(currentDirection == left)
			sequence_select += LEFT_OFFSET;

	if(!alive){
		sequence_select += DYING_OFFSET;
		return;
	}

	if(this->weapons->currentWeapon != 0)
		sequence_select += SHOTGUN_OFFSET;

	if(firing)
		sequence_select += FIRING_OFFSET;
	else{
		if(reloading){
			sequence_select += RELOADING_OFFSET;
			return;
			}
	}
	if(changingWeapon){
		sequence_select += CHANGING_WEAPON_OFFSET;
		return;
	}

	if(verticalDirection == up || verticalDirection == diagonal)
		sequence_select += UP_OFFSET;

	if(verticalDirection == down)
		sequence_select += CRAWL_OFFSET;
}

void MainCharacter::selectLegFrame(){
	frame_selector = 0;
	if(moving)
		frame_selector += MOVING_LEG_OFFSET;
	if(currentDirection == left)
		frame_selector += LEFT_LEG_OFFSET;
	if(verticalDirection == down || !alive)
		frame_selector += CRAWL_LEG_OFFSET;
}

int MainCharacter::getFrameInt(){
	if(!alive){
		sequence_offset++;
		if(sequence_offset == DYING_OFFSET_LENGTH){
			this->dead=true;
			this->setExistingMessage(utils::DYING_CHARACTER);
		}
		return (sequence_select+sequence_offset)/FRAME_SPEED;
	}
	if(changingWeapon){
		sequence_offset++;
		//cout << "The sequence offset is: " << sequence_offset << endl;
		if(sequence_offset >= CHANGING_WEAPON_OFFSET_LENGTH/2){
			//cout << "entre" << endl;
			this->selectCurrentSequence();
		}
		if(sequence_offset == CHANGING_WEAPON_OFFSET_LENGTH){
			changingWeapon=false;
			this->selectCurrentSequence();
			sequence_offset = 0;
		}
		return (sequence_select+sequence_offset)/FRAME_SPEED;
	}
	if(firing){
		sequence_offset++;
		if(sequence_offset == FIRING_OFFSET_LENGTH){
			firing = false;
			sequence_offset = 0;
			this->selectCurrentSequence();
		}
		return (sequence_select+sequence_offset)/FRAME_SPEED;
	}
	if(reloading){
		if(sequence_offset==0){
			this->selectCurrentSequence();
		}
		sequence_offset++;

		if(sequence_offset == RELOADING_OFFSET_LENGTH ){
			reloading = false;
			sequence_offset = 0;
			this->selectCurrentSequence();
		}
		return (sequence_select+sequence_offset)/FRAME_SPEED;
	}
	if(verticalDirection == diagonal){
		if(sequence_offset > 0){
			verticalDirection = up;
		}
	}
	// IF IDLE
	sequence_offset++;
	if(sequence_offset >= IDLE_OFFSET_LENGTH)
		sequence_offset = 0;
	return (sequence_select+sequence_offset)/FRAME_SPEED;

}
std::string MainCharacter::getFrame(){
	int frame = this->getFrameInt();
	std::string frameString;
	std::stringstream out;
	out << frame;
	frameString = out.str();
	int legs = this->getLegsFrame();
	std::string legsFrame;
	std::stringstream out2;
	out2 << legs;
	legsFrame = out2.str();
	std::string finFrame;
	finFrame.append(frameString);
	finFrame.append(":");
	finFrame.append(legsFrame);
	return finFrame;
}

int MainCharacter::getLegsFrame(){
	if(verticalDirection==down){
		this->selectLegFrame();
		return frame_selector/FRAME_SPEED;
	}
	if(!moving){
		this->selectLegFrame();
		return frame_selector/FRAME_SPEED;
	}
	//IF MOVING
	frame_offset++;
	if(frame_offset == MOVING_LEG_OFFSET_LENGHT)
		frame_offset = 0;

	return (frame_selector+frame_offset)/FRAME_SPEED;
}
void MainCharacter::crawl(){
	if(verticalDirection != down){
		CollisionBox* aux = this->hitBox;
		this->hitBox = this->secondaryBox;
		this->secondaryBox = aux;
		this->halt();
		verticalDirection = down;
		this->selectCurrentSequence();
		sequence_offset = -8*FRAME_SPEED;
	}
}

void MainCharacter::standUp(){
	if(verticalDirection == down){
		CollisionBox* aux = this->hitBox;
		this->hitBox = this->secondaryBox;
		this->secondaryBox = aux;
		verticalDirection = horizontal;
		this->selectCurrentSequence();
	}
}

void MainCharacter::lookUp(){
	if(verticalDirection == horizontal){
		verticalDirection = up;
		this->selectCurrentSequence();
		sequence_offset = -4*FRAME_SPEED;
		verticalDirection = diagonal;
	}
}

void MainCharacter::lookRightFromUp(){
	if((verticalDirection == up)||(verticalDirection == diagonal)){
		//cout << "entra a lookRightFromUp" << endl;
		verticalDirection = horizontal;
		this->selectCurrentSequence();
		sequence_offset = 0;
	}
}

void MainCharacter:: moveRight(){
	if(verticalDirection != down){
		if(!moving){
			this->longBody->setOffset(9*scale,1*scale);
			this->shortBody->setOffset(3*scale,8*scale);
			currentDirection = right;
			this->selectCurrentSequence();
			moving = true;
			this->selectLegFrame();
			return;
		}
	}

}
void MainCharacter:: moveLeft(){
	if(verticalDirection != down){

		if(!moving){
			this->longBody->setOffset(3*scale,1*scale);
			this->shortBody->setOffset(3*scale+longBodyWidth,8*scale);
			currentDirection = left;
			this->selectCurrentSequence();
			moving = true;
			this->selectLegFrame();
			return;
		}
	}
}
void MainCharacter:: halt(){
	moving = false;
	if(currentDirection == right){
		this->selectLegFrame();
		return;
	}
	else if(currentDirection == left){
		this->selectLegFrame();
		return;
	}
}

void MainCharacter::cyclePreviousWeapon(){
	this->changeToWeapon();
	this->weapons->cyclePrevious();
}
void MainCharacter::cycleNextWeapon(){
	this->changeToWeapon();
	this->weapons->cycleNext();
}
void MainCharacter::changeToWeapon(){
	this->changingWeapon = true;
	this->firing = false;
	this->selectCurrentSequence();
	this->sequence_offset = 0;
}

void MainCharacter::collisioned(Collisionable* a){
 //TODO SOY GUIDO, NO ME ACUERDO QUE HACE ESTA FUNCION, DESPUES ME DARE CUENTA.
}
int MainCharacter:: getXPos(Parallax* map){
	//cout<<"Main		"<<this->x<<endl;
	if(!alive)
		return screenPosition;
	if(!connected){
		if(x < map->position - anchoPantalla/2 + 30){
			x = map->position - anchoPantalla/2 + 30;
			leftLimit = this->x;
			rightLimit = this->x + 60; //Ancho del personaje, despues modificar
		}
		else{
			if(x > map->position + anchoPantalla/2 - 30){
				x = map->position + anchoPantalla/2 - 30;
				leftLimit = this->x;
				rightLimit = this->x + 60; //Ancho del personaje, despues modificar
			}
		}

		this->setCharacterScreenPosition(map->position);
		int newy = current_y - (scale-1)*20;
		this->hitBox->moveCollisionBox(x,newy);
		return screenPosition;
	}
	else{
	if(!moving){
		this->setCharacterScreenPosition(map->position);
		return screenPosition;
	}
	if(currentDirection == right){
		//Hardcodeo el screen width por ahora
		if((x < utils::LEVEL_LENGHT - 50) && (x < (map->min + anchoPantalla - 50))){
			this->displacement = velocidad;
			int newy = current_y - (scale-1)*20;
			this->hitBox->moveCollisionBox(x+velocidad,newy);
			if(this->collisionMap->moveAttemptCollisionable(this)){
				x += velocidad;
				leftLimit = this->x;
				rightLimit = rightLimit + velocidad;
			}
			int newy4 = current_y - (scale-1)*20;
			this->hitBox->moveCollisionBox(x,newy4);

			if(x > map->max)
				map->max = x;
		}
	}
	else{
		//De vuelta hardcodeo, despues esto se traduce a algun limite superior e inferior de la pantalla
		if((x > MIN_POSITION/*x > map->position - anchoPantalla/2 -50*/) && (x > (map->max - anchoPantalla + 50))){
			this->displacement = -velocidad;
			int newy2 = current_y - (scale-1)*20;
			this->hitBox->moveCollisionBox(x-velocidad,newy2);
			if(this->collisionMap->moveAttemptCollisionable(this)){
				x -= velocidad;
				leftLimit = this->x;
				rightLimit = rightLimit - velocidad;
			}
			int newy3 = current_y - (scale-1)*20;
			this->hitBox->moveCollisionBox(x,newy3);
			if(x < map->min)
				map->min = x;
		}
	}
	this->setCharacterScreenPosition(map->position);
	return screenPosition;
	}
}
int MainCharacter::getNextHeight(){
	if(jump_stage == jumping_table->size()){
		if(current_y < floorLevel){
			return jumping_table->at(jump_stage-1);
		}
		jump_stage = 0;
		jumping = false;
		return 0;
	}
	int height = jumping_table->at(jump_stage);
	jump_stage ++;
	return height;

	//Viejo
	/*bool platform = (topLevel-10 < (y - height) ) && ((y - height)< topLevel+10);
	if( platform && (isInPlatform())){
		int mitadTabla = jumping_table->size()/2;
		if(jump_stage >= mitadTabla){
			jumping = false;
			jump_stage = 0;
			this->y = topLevel;
			current_y = this->y;
			return 0;
		}
	}
	jump_stage++;
	return height;
	*/
}
void MainCharacter::stopJump(int salto){
	//cout<<"Paramos el jump"<<endl;
	//cout<<salto<<endl;
	if(jump_stage < jumping_table->size()/2 ){ //Si esta subiendo
		jump_stage = jumping_table->size() - jump_stage;
	}else{
		int posible_salto = salto;
		while(this->collisionMap->moveAttemptCollisionable(this)){
			this->current_y++;
			int newy = current_y - (scale-1)*20;
			this->hitBox->moveCollisionBox(this->x,newy);
		}
		jumping = false;
	}
}
bool MainCharacter::isInPlatform(){
	if(levelId == 1){
		if((482 < x) && (x < 1274))
			return true;
		if((1775 < x) && (x < 2170))
			return true;
		return false;
		}
	if(levelId == 2){
		if((482 < x) && (x < 872))
				return true;
		if((1355 < x) && (x < 2160))
				return true;
		if((2615 < x) && (x < 3041))
				return true;
		return false;
	}
	if(levelId == 3){
		if((587 < x) && (x < 1400))
			return true;
		if((1988 < x) && (x < 2792))
			return true;
		return false;
	}
	return false;
	//Si ya se que este ultimo if esta de mas
}
void MainCharacter::falling(){
	//cout<<"We are falling"<<endl;
	jumping = true;
	jump_stage = jumping_table->size()/2;
}

int MainCharacter:: getYPos(){
	//cout<<"Main		"<<this->current_y<<endl;
	if(!alive)
			return current_y;
	if(jumping){
		int siguiente_salto = this->getNextHeight();
		int newy = current_y - (scale-1)*20;
		this->hitBox->moveCollisionBox(x,newy - siguiente_salto);
		if(this->collisionMap->moveAttemptCollisionable(this)){
			current_y = current_y - siguiente_salto;
			if (current_y > floorLevel){
				//cout<<"Estoy acaaa"<<endl;
				current_y = floorLevel;
				jumping = false;
				jump_stage = 0;
			}
			return current_y;
		}
		else{
			this->stopJump(siguiente_salto);
		}
	}else if(current_y != floorLevel){
		int mitad = jumping_table->size()/2 + 1;
		int newy = current_y - (scale-1)*20;
		this->hitBox->moveCollisionBox(x,newy + 1);
		if(this->collisionMap->moveAttemptCollisionable(this)){
			this->falling();
		}
		else{
			int newy = current_y - (scale-1)*20;
			this->hitBox->moveCollisionBox(x,newy);
		}
	}
	return current_y;
	/*
	if(y == topLevel){
		if (!isInPlatform()){
			y = floorLevel;
			jumping = true;
			jump_stage = jumping_table->size()/2;
			int a  = floorLevel - topLevel;
			for(;jumping_table->at(jump_stage) > a;jump_stage++);
			this->hitBox->moveCollisionBox(0,current_y - jumping_table->at(jump_stage));
			if(this->collisionMap->moveAttemptCollisionable(this)){
				current_y = y - jumping_table->at(jump_stage);
				return current_y;
			}
		}
	}*/

	//current_y =y;
	return current_y;
}
std::string MainCharacter::getInfo(){
	std::stringstream out;
	out << this->weapons->getBulletsLeft();
	std::stringstream out2;
	out2 << this->weapons->getTotalBullets();
	std::string info;
	info.append(out.str());
	info.append(" 1 ");
	info.append(out2.str());

	//Puntaje
	info.append("|");
	/*std:: stringstream puntos;
	puntos << this->points;
	info.append(puntos.str());*/
	return info;
}

MainCharacter::~MainCharacter() {
	delete weapons;
	// TODO Auto-generated destructor stub
}

