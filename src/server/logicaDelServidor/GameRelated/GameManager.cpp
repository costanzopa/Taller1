#include "GameManager.h"

#define PI 3.14159265
#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_TEAMS 2
using namespace std;

GameManager :: GameManager(MessageList* incomingMessages,MessageList* outcomingMessages, float scale){
	latestPosition = 20;
	collisionMap = new CollisionMap(utils::LEVEL_LENGHT+300,20);
	incomingActions = incomingMessages;
	gameManagerID = new User(utils::SERVER_USER_ID,utils::SERVER_USER_ID);
	gameParticipants = new list<Character*>();
	usersPlaying = new list<MainCharacter*>();
	enemysInLevel = new list<EnemyCharacter*>();
	animations = new AnimationsInGame();
	currentLevel = new CharactersInGame();
	gameBackground = new Parallax();
	connectedUsers = new list<User*>();
	string path = utils::BACKGROUND_DIR;
	reloader = new ReloadReady();
	changingLevel = false;
	broadcaster = new Broadcaster(outcomingMessages,gameParticipants,gameBackground,connectedUsers,path,incomingMessages);
	broadcaster->setReloader(reloader);
	this->charsRequests = new CharactersRequest();
	this->animsRequests = new AnimationsRequest();
	this->image_path = "";
	jumping_table = new vector<int>();
	gameStarted = false;
	numberOfPlayers = NUMBER_OF_PLAYERS;
	numberOfTeams = NUMBER_OF_TEAMS;
	teamAssigment = 0;
	this->stage = NULL;
	windowScale = scale;
	characterScale =scale;
	y = this->setY(utils::DEFAULT_LEVEL);
	characterScale = scale;
	srand(time(NULL));
}

GameManager :: GameManager(MessageList* incomingMessages,MessageList* outcomingMessages,config::Stage* stage){
	latestPosition = 20;
	collisionMap = new CollisionMap(utils::LEVEL_LENGHT+300,20);
	incomingActions = incomingMessages;
	gameManagerID = new User(utils::SERVER_USER_ID,utils::SERVER_USER_ID);
	changingLevel = false;
	this->charsRequests = new CharactersRequest();
	this->animsRequests = new AnimationsRequest();
	gameParticipants = new list<Character*>();
	usersPlaying = new list<MainCharacter*>();
	enemysInLevel = new list<EnemyCharacter*>();
	animations = new AnimationsInGame();
	currentLevel = new CharactersInGame();
	gameBackground = new Parallax();
	connectedUsers = new list<User*>();
	this->stage = stage;
	reloader = new ReloadReady();
	vector<config::Background*> background = stage->getBackgrounds();
	string path = background[0]->getPath();
	broadcaster = new Broadcaster(outcomingMessages,gameParticipants,gameBackground,connectedUsers,path,incomingMessages);
	broadcaster->setReloader(reloader);
	this->image_path = "";
	setNumberOfPlayers();
	setNumberOfTeams();
	teamAssigment = 0;
	jumping_table = new vector<int>();
	gameStarted = false;
	characterScale = stage->getWindow()->getCharacterScale();
	windowScale = stage->getWindow()->getWindowScale();
	stringstream levelId(background[0]->getId());
	levelId >> this->level;
	//printf("el level ID es: %d\n",i);
	y = (int)(windowScale*(float)this->setY(level));// - (characterScale-1)*30;
}
void GameManager::nextLevel(){
	changingLevel= true;
}
void GameManager::changeLevel(){
	//cout << "entra a mostrar info" << endl;
	this->showInfo();
	//cout << "Mostro infoooooooooooooooooooooooooooooooooooooooooo" << endl;
	usleep(1000*1000*10); // 10 segundos de info
	this->removeInfo();
	this->broadcaster->reloadGame();
	while(!this->broadcaster->canBeReloaded){
		usleep(1000);
	}
	reloader->startingReload();
	this->gameBackground->resetParallax();
	if(level == 1)
		this->prepareSecondLevel();
	else{
		if(level == 2){
			this->prepareThirdLevel();
		}
		else{
			//TERMINAR JUEGO
		}
	}
	this->animations->resetAnimations();
	//cout<<"Cargado el tercer nivel"<<endl;
	reloader->reloadFinished();
	changingLevel = false;
}
void GameManager::showInfo(){
	this->broadcaster->broadcastLevelInfo(this->usersPlaying);
}
void GameManager::removeInfo(){
	this->broadcaster->broadcastLevelInfoOver();
}

void GameManager::gameOver(){
	this->broadcaster->broadcastGameOver();
	this->showInfo();
	//usleep(1000*1000*10);
	//this->removeInfo();

}
void GameManager::setPlatformsLevel(){
	if(this->level ==1){
		lvl1Platforms = new list<GroundFloor*>();
		//cout<<"Ahora agrego las plataformas"<<endl;
		GroundFloor* platform = new GroundFloor(494,375,792,5,collisionMap);
		lvl1Platforms->push_back(platform);
		platform = new GroundFloor(1798,375,395,5,collisionMap);
		lvl1Platforms->push_back(platform);
		//cout<<"agregue las plataformas"<<endl;
	}else if(this->level ==2){
		list<GroundFloor*>::iterator iter;
		iter = lvl1Platforms->begin();
		while(iter!=lvl1Platforms->end()){
			this->collisionMap->removeCollisionable((*iter));
			iter++;
		}
		lvl2Platforms = new list<GroundFloor*>();
		GroundFloor* platform = new GroundFloor(470,370,398,5,collisionMap);
		lvl2Platforms->push_back(platform);
		platform = new GroundFloor(1365,370,795,5,collisionMap);
		lvl2Platforms->push_back(platform);
		platform = new GroundFloor(2635,370,413,5,collisionMap);
		lvl2Platforms->push_back(platform);
	}else{
		list<GroundFloor*>::iterator iter;
		iter = lvl2Platforms->begin();
		while(iter!=lvl2Platforms->end()){
			this->collisionMap->removeCollisionable((*iter));
			iter++;
		}
		lvl3Platforms = new list<GroundFloor*>();
		GroundFloor* platform = new GroundFloor(587,385,813,3,collisionMap);
		lvl3Platforms->push_back(platform);
		platform = new GroundFloor(1988,385,800,3,collisionMap);
		lvl3Platforms->push_back(platform);

	}
}
void GameManager::prepareSecondLevel(){
	config::StageFile stageFile(utils::STAGE_FILE_LVL2);
	stage = stageFile.getStage();
	reloadStageForLevels(2);
	this->setPlatformsLevel();
	this->addEnemies();
	RocketAmmo* bonus1 = new RocketAmmo(800,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus1);

	//cout<<"Estan cargados los Renemys"<<endl;
	BonusKillAll* bonus8 = new BonusKillAll(1200,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus8);

	this->addTank();


}
void GameManager::prepareThirdLevel(){
	config::StageFile stageFile(utils::STAGE_FILE_LVL3);
	stage = stageFile.getStage();
	reloadStageForLevels(3);
	//setEnemiesInDivision();
	this->setPlatformsLevel();
	this->addEnemies();

	BonusHeal* bonus5 = new BonusHeal(800,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus5);

	FlameAmmo* bonus6 = new FlameAmmo(1600,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus6);

	this->addEyes();

	//this->addUFO();
}


void GameManager::prepareFirstLevel(){


	gameController = new GameController(currentLevel,charsRequests,animations,animsRequests);
	gameController->setGameManager(this);
	this->setPlatformsLevel();
	this->addEnemies();

	this->addUFO();

	//this->addEyes();

	//this->addTank();

	BonusKillAll* bonus = new BonusKillAll(1200,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus);

	BonusHeal* bonus2 = new BonusHeal(800,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus2);

	SingleShotAmmo* bonus3 = new SingleShotAmmo(500,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus3);

	FlameAmmo* bonus4 = new FlameAmmo(1600,this->y,1000,this->collisionMap,this->animsRequests);
	this->animations->addNewAnimation(bonus4);

	gameController->setCharactersList(this->usersPlaying);
	gameController->setEnemiesList(this->enemysInLevel);
	broadcaster->setLevel(currentLevel);
	broadcaster->setAnimations(animations);
}
void GameManager::addEnemies(){
	setEnemiesInDivisionMelee();
	int i=0;
	int divLen = utils::LEVEL_LENGHT/N_DIVISION;
	for(int div=0;div<N_DIVISION;div++){
	//	cout<<"Enemies in division"<<enemiesInDivision[div]<<endl;
		for(int j=0;j< enemiesInDivision[div];i++,j++){
			std::string enemyId = "Menemy";
			int pos = div*divLen + ( std::rand() % (divLen + 1 ) );
			std::string id;
			stringstream out3;
			out3<<i;
			id = out3.str();
			enemyId.append(id);
			MeleeEnemy* melee = new MeleeEnemy(characterScale,enemyId,(int)1,10,this->usersPlaying,charsRequests,animsRequests,collisionMap);
			melee->setCharacterPosition(pos,this->y);
			melee->setCharacterImage(utils::ENEMY_1_DIR);
			melee->setCharacterScreenPosition(pos);
			enemysInLevel->push_back(melee);
			currentLevel->addNewPlayer(melee);
		}
	}
	setEnemiesInDivisionRange();
	i=0;
	for(int div=0;div<N_DIVISION;div++){
		for(int j=0;j< enemiesInDivision[div];j++,i++){
			std::string enemyId = "Renemy";
			int pos = div*divLen + ( std::rand() % (divLen + 1 ) );
			std::string id;
			stringstream out3;
			out3<<i;
			id = out3.str();
			enemyId.append(id);
			RangeEnemy* range = new RangeEnemy(characterScale,enemyId,(int)1,300,10,this->usersPlaying,charsRequests,animsRequests,collisionMap);
			range->setCharacterPosition(pos,this->y);
			range->setCharacterImage(utils::ENEMY_2_DIR);
			range->setCharacterScreenPosition(pos);
			enemysInLevel->push_back(range);
			currentLevel->addNewPlayer(range);
		}
	}
}
void GameManager::addUFO(){
	int spwnNumber =5;
	list<EnemyCharacter*>* ufospwn = new list<EnemyCharacter*>();
	cout<<"Voy con los del ufo"<<endl;
	for(int i = 0;i< spwnNumber; i++){
		std::string enemyId = "MenemyUFO";
		std::string id;
		stringstream out3;
		out3<<i;
		id = out3.str();
		enemyId.append(id);
		MeleeEnemy* melee = new MeleeEnemy(characterScale,enemyId,(int)1,10,this->usersPlaying,charsRequests,animsRequests,collisionMap);
		melee->setCharacterPosition(3500,this->y);
		melee->setCharacterImage(utils::ENEMY_1_DIR);
		melee->setCharacterScreenPosition(5000);
		ufospwn->push_back(melee);
		enemysInLevel->push_back(melee);
		currentLevel->addNewPlayer(melee);
	}
	cout<<"Voy con el ufo"<<endl;
	std::string ufoID = "UFO";
	int ufoPos = 2000;
	UfoEnemy* ufo = new UfoEnemy(characterScale,ufospwn,ufoID,(int)1,0,this->usersPlaying,charsRequests,animsRequests,collisionMap);
	ufo->setCharacterPosition(3000,this->y-75);
	ufo->setCharacterImage(utils::ENEMY_UFO);
	ufo->setCharacterScreenPosition(ufoPos);
	currentLevel->addNewPlayer(ufo);
	enemysInLevel->push_back(ufo);
}
void GameManager::addTank(){
	std::string tankId = "Tank";
	int tankPos = 600;
	TankEnemy* tank = new TankEnemy(characterScale,tankId,(int)1,10,usersPlaying,charsRequests,animsRequests,collisionMap);
	//cout<<"Creo el tank"<<endl;
	tank->setCharacterPosition(3000,(this->y - 40));//17)/*- (characterScale-1)*40*/); //20 esta bien
	tank->setCharacterImage(utils::ENEMY_TANK);
	tank->setCharacterScreenPosition(tankPos);
	currentLevel->addNewPlayer(tank);
	enemysInLevel->push_back(tank);
}
void GameManager::addEyes(){
	std::string bigEyesId = "BigEyes";
	int bPos = 3000;
	BigEyes* bigEyes = new BigEyes(characterScale,bigEyesId,(int)1,10,bPos,this->usersPlaying,charsRequests,animsRequests,collisionMap);
	//cout<<"Creo el big Eye"<<endl;
	bigEyes->setCharacterPosition(bPos,(this->y - 175)/*- (characterScale-1)*40*/);
	bigEyes->setCharacterImage(utils::ENEMY_EYES);
	bigEyes->setCharacterScreenPosition(bPos);
	currentLevel->addNewPlayer(bigEyes);
	enemysInLevel->push_back(bigEyes);

}

void GameManager::reloadStageForLevels(int level){
	vector<config::Background*> background = stage->getBackgrounds();
	this->broadcaster->backgroundPath = background[0]->getPath();
	int i;
	stringstream levelId(background[0]->getId());
	levelId >> i;
	//printf("el level ID es: %d\n",i);
	y = (int)(windowScale*(float)this->setY(i));
	this->level = i;

	latestPosition = 20;
	list<MainCharacter*>:: iterator iter;
	iter =	usersPlaying->begin();
	while((iter)!=usersPlaying->end()){
		(*iter)->setCharacterImage(this->findPath((*iter)->characterSelect));
		(*iter)->setCharacterPosition(latestPosition,this->y);
		latestPosition +=60;
		iter++;
	}
}
void GameManager::setEnemiesInDivisionMelee(){
	std::vector<config::Sprite*> enemies = stage->getSprites();
	//Melee
	enemiesInDivision[0] = enemies.at(7)->getDiv1();
	enemiesInDivision[1] = enemies.at(7)->getDiv2();
	enemiesInDivision[2] = enemies.at(7)->getDiv3();
	enemiesInDivision[3] = enemies.at(7)->getDiv4();
	enemiesInDivision[4] = enemies.at(7)->getDiv5();
	enemiesInDivision[5] = enemies.at(7)->getDiv6();
	enemiesInDivision[6] = enemies.at(7)->getDiv7();
	//cout <<"Enemies in div:  "<< enemiesInDivision[5] << endl;
}
void GameManager::setEnemiesInDivisionRange(){
	std::vector<config::Sprite*> enemies = stage->getSprites();
	//Range
	enemiesInDivision[0] = enemies.at(8)->getDiv1();
	enemiesInDivision[1] = enemies.at(8)->getDiv2();
	enemiesInDivision[2] = enemies.at(8)->getDiv3();
	enemiesInDivision[3] = enemies.at(8)->getDiv4();
	enemiesInDivision[4] = enemies.at(8)->getDiv5();
	enemiesInDivision[5] = enemies.at(8)->getDiv6();
	enemiesInDivision[6] = enemies.at(8)->getDiv7();
}

void GameManager::broadcastGameInit(){
	list<MainCharacter*>:: iterator iter;
	iter = usersPlaying->begin();
	while (iter != usersPlaying->end()){
		currentLevel->addNewPlayer(*iter);
		iter++;
	}
	this->prepareFirstLevel();
	//cout<<"Game is ready	"<<gameParticipants->size()<<endl;
	gameStarted = true;
	usleep(1000);
	broadcaster->start();
	gameController->start();
}


/*
 *
 *
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 * 											COSAS DEL LA SEGUNDA ENTREGA MAS ABAJO
 *
 *
 *
 *
 *
 * */
bool GameManager:: addNewUser(std::string& userName){
	if(gameStarted){
		bool found = false;
		list<MainCharacter*>:: iterator iter;
		iter = usersPlaying->begin();
		while(iter != usersPlaying->end()){
			if((*iter)->hasID(userName)){
				found = true;
				break;
			}
			iter++;
		}
		if(found)
			(*iter)->Connected();
		list<User*>:: iterator iter_user;
		iter_user = connectedUsers->begin();
		while((iter_user)!= connectedUsers->end()){
			if((*iter_user)->getUserName().compare(userName)==0){
				broadcaster->reconnectPlayer(*iter_user);
				return true;
			}
			iter_user++;
		}
		return false;
	}
	User* newUser = new User(userName,"-");
	//cout<<"We pushed new user	"<< userName<<endl;
	connectedUsers->push_back(newUser);
	return false;
}


int GameManager::setY(int level){
	if(level==1 || level==2)
		return 430;
	/*if(level==2)
		return 470;
	//if (level==3)*/
	return 455;
}

void GameManager :: addNewCharacter(std::string& userName,std::string& characterSelected){

	int velocidad = (int)3*characterScale;
	MainCharacter* newCharacter = new MainCharacter(characterScale,userName,velocidad,jumping_table,characterSelected,charsRequests,animsRequests,collisionMap);
	std::string imagePath = this->getImage(userName,characterSelected);
	newCharacter->setCharacterImage(imagePath);
	newCharacter->setEnemies(enemysInLevel);
	newCharacter->setCharacterPosition(latestPosition,this->y /*- (characterScale-1)*40*/);
	newCharacter->setCharacterScreenPosition(latestPosition);
	newCharacter->setLevel(this->level);
	int settingTeam = (this->teamAssigment*this->numberOfTeams)/this->numberOfPlayers;
	newCharacter->setTeam(settingTeam);
	//cout << "We set team: " << settingTeam << endl;
	teamAssigment++;
	//cout<<"Muere aca"<<endl;
	gameParticipants->push_back(newCharacter);
	usersPlaying->push_back(newCharacter);
	//cout << "va a agregar" << endl;
	CharacterMap::addCharacter(userName,newCharacter);
	//cout << "agrego" << endl;
	latestPosition +=60;
}

bool GameManager::started(){
	return gameStarted;
}

void GameManager:: processMessages(list<Node*>* message){
	list<Node*>:: iterator iter;
	iter = message->begin();
	while(iter != message->end()){
		this->processNode(*iter);
		iter++;
	}
}

void GameManager:: updateStatus(std::string& userName,std::string& action){
	list<MainCharacter*>:: iterator iter;
	iter = usersPlaying->begin();
	while(!(*iter)->hasID(userName)){
		iter++;
	}
	(*iter)->processAction(action);
}

void GameManager:: updateBackground(){
	list<MainCharacter*>:: iterator iter;
	iter = usersPlaying->begin();
	gameBackground->startMinMax();
	while((iter) != usersPlaying->end()){
		if((*iter)->isConnected() && (*iter)->alive)
			gameBackground->processPosition((*iter)->x);
		iter++;
	}
	gameBackground->endMinMax();
}

void GameManager:: processNode(Node* message){
	std::string command = message->getMessage();
	std::string userOrigin = message->getFrom()->getUserName();
	Tokenizer* tkn = new Tokenizer();
	vector<string> tkns = tkn->tokenize(command, '|');
	if((tkns[1].compare(utils::KEY_RELEASE_RELOAD)==0)) {
	  	this->broadcaster->reloadGame();
	  	reloader->startingReload();
	  	config::StageFile stageFile(utils::STAGE_FILE);
		stage = stageFile.getStage();
		vector<config::Background*> background = stage->getBackgrounds();
		this->broadcaster->backgroundPath = background[0]->getPath();
		this->setNumberOfPlayers();
		characterScale = stage->getWindow()->getCharacterScale();
		windowScale = stage->getWindow()->getWindowScale();
		int i;
		stringstream levelId(background[0]->getId());
		levelId >> i;
		//printf("el level ID es: %d\n",i);
		y = (int)(windowScale*(float)this->setY(i));

		list<MainCharacter*>:: iterator iter;
		iter =	usersPlaying->begin();
		while((iter)!=usersPlaying->end()){
			(*iter)->setCharacterImage(this->findPath((*iter)->characterSelect));
			(*iter)->current_y = this->y;
			iter++;
		}
		reloader->reloadFinished();

	}else {
		if(tkns[0].compare(utils::NEW_CHARACTER)==0){
			this->includeNewPlayer(userOrigin,tkns[1]);
		}
		else if(tkns[0].compare(utils::EXISTING_CHARACTER)==0){
			this->updateStatus(userOrigin,tkns[1]);
		}else{
			this->updateConection(userOrigin);
		}
	}
	delete tkn;
	delete message;
}
void GameManager:: updateConection(std::string userName){
	list<MainCharacter*>:: iterator iter;
	iter = usersPlaying->begin();
	while(!(*iter)->hasID(userName)){
		iter++;
	}
	(*iter)->Disconnected();
	list<User*>:: iterator iter_user;
	iter_user = connectedUsers->begin();
	while((iter_user)!= connectedUsers->end()){
		if((*iter_user)->getUserName().compare(userName)==0){
			(*iter_user)->Disconnected();
			break;
		}
		iter_user++;
	}


}
void GameManager:: setJumpingTable(){
	int scale = 200;
	vector <int> auxTable;
	for(int degree=0;degree<180;degree+=2){
		float normalized_height = sin(degree*PI/180);
		jumping_table->push_back((int)(normalized_height*scale));
	}
	auxTable = *jumping_table;
	for(int i=1;i<90;i++){
		int newHeight = auxTable.at(i) - auxTable.at(i-1);
		jumping_table->at(i) = newHeight;
	}

}

void* GameManager:: process(){
	this->setJumpingTable();
	while(this->isRunning()){
		if(changingLevel)
			this->changeLevel();
		if(!(incomingActions->isEmpty())){
		list<Node*>* actions = incomingActions->getMessagesFor(gameManagerID);
		this->processMessages(actions);
		//delete actions;
		}
		this->updateBackground();
		usleep(4000);
	}
	broadcaster->stop();
	return (void*)NULL;
}
void GameManager:: stop(){
	Thread::stop();
}

void GameManager::setNumberOfPlayers() {
	if (this->stage != NULL) {
		config::Window* window = stage->getWindow();
		this->numberOfPlayers = window->getPlayers();
	} else {
		this->numberOfPlayers = NUMBER_OF_PLAYERS;
	}
}
void GameManager::setNumberOfTeams() {
	string gameMode;
	if (this->stage != NULL) {
		config::Window* window = stage->getWindow();
		gameMode = window->getGameMode();
		//cout << "El modo de juego sera: " << gameMode << endl;
		if(gameMode.compare("solo") == 0){
			this->numberOfTeams = this->numberOfPlayers;
			return;
		}
		if(gameMode.compare("co-op") == 0){
			this->numberOfTeams = 1;
			return;
		}
		if(gameMode.compare("versus") == 0){
			if(this->numberOfPlayers == 2)
				this->numberOfTeams = 2;
			else{
				if(this->numberOfPlayers == 4){
					this->numberOfTeams = 2;
				}
				else{
					//cout << "Se ha elegido una configuracion de modo de juego invalida." << endl;
					//cout << "Se cargara el modo solo." << endl;
					this->numberOfTeams = this->numberOfPlayers;
				}
			}
		}
	} else {
		this->numberOfTeams = NUMBER_OF_TEAMS;
	}
}

std::string& GameManager::findPath(std::string& characterSelected) {
	this->image_path = utils::CHARACTER_1_DIR;

	std::vector<config::Sprite*> sprites = stage->getSprites();
    
    std::vector<config::Sprite*>::iterator itSprites = sprites.begin();

    while(itSprites != sprites.end()) {
		std::string id = (*itSprites)->getId();
		//std::cout<<"El Id es "<<id<<std::endl;
		if (id.compare(characterSelected) == 0) {
			image_path = (*itSprites)->getPath();
			//std::cout<< "Son iguales "<<std::endl;
			//break;
		}
		itSprites++;
	}
	//std::cout<<"El path a devolver es "<<image_path<<std::endl;
	return image_path;
}
void GameManager:: includeNewPlayer(std::string& userName,std::string& characterSelected){
	//cout<<"We add a new player"<<endl;
	bool wasAlreadyInGame = this->addNewUser(userName);
	if(wasAlreadyInGame){
		User* destination = new User(userName,"-");
		User* origin = new User(utils::SERVER_USER_ID,"-");
		std::string msg;
		msg.append(utils::HAS_SPACE);
		Node* mensaje = new Node(origin,destination,msg);
		incomingActions->addMesage(mensaje);
		return;
	}
	else{
		if(gameStarted){
			User* destination = new User(userName,"-");
			User* origin = new User(utils::SERVER_USER_ID,"-");
			std::string msg;
			msg.append(utils::NO_SPACE);
			Node* mensaje = new Node(origin,destination,msg);
			incomingActions->addMesage(mensaje);
			return;
		}
		User* destination = new User(userName,"-");
		User* origin = new User(utils::SERVER_USER_ID,"-");
		std::string msg;
		msg.append(utils::HAS_SPACE);
		Node* mensaje = new Node(origin,destination,msg);
		incomingActions->addMesage(mensaje);

	}
	this->addNewCharacter(userName,characterSelected);
	if(connectedUsers->size()==numberOfPlayers)
		this->broadcastGameInit();
}
std::string& GameManager:: getImage(std::string& character,std::string& characterSelected){
	if (this->stage != NULL) {
		findPath(characterSelected);
	} else {
		if (characterSelected.compare(utils::CHARACTER_1) == 0) {
			image_path = utils::CHARACTER_1_DIR;
			return image_path;
		}
		if (characterSelected.compare(utils::CHARACTER_2) == 0) {
			image_path = utils::CHARACTER_2_DIR;
			return image_path;
		}
		if (characterSelected.compare(utils::CHARACTER_3) == 0) {
			image_path = utils::CHARACTER_3_DIR;
			return image_path;
		}
		if (characterSelected.compare(utils::CHARACTER_4) == 0) {
			image_path = utils::CHARACTER_4_DIR;
			return image_path;
		}
		if (characterSelected.compare(utils::CHARACTER_5) == 0) {
			image_path = utils::CHARACTER_5_DIR;
			return image_path;
		}
		if (characterSelected.compare(utils::CHARACTER_6) == 0) {
			image_path = utils::CHARACTER_6_DIR;
			return image_path;
		}
		if (characterSelected.compare(utils::CHARACTER_7) == 0) {
			image_path = utils::CHARACTER_7_DIR;
			return image_path;
		}
	}
	return image_path;
}

GameManager::~GameManager() {
	if (stage!=NULL) {
		delete stage;
	}
}
