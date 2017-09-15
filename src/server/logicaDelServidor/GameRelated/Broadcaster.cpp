/*
 * BroadCaster.cpp
 *
 *  Created on: 1/10/2016
 *      Author: usuario
 */
#include "Broadcaster.h"



Broadcaster::Broadcaster(MessageList* outMessages,list<Character*>* characters,Parallax* gameBack,list<User*>* users,string path,MessageList* incoming){
	connectedUsers = users;
	incomingMessages = incoming;
	gameParticipants = characters;
	gameBackground = gameBack;
	newStatus = outMessages;
	reconnectingPlayer = NULL;
	backgroundPath = path;
	mustBeReloaded = false;
	canBeReloaded = false;
}
void Broadcaster::reloadGame(){
	mustBeReloaded = true;
}
void Broadcaster::setLevel(CharactersInGame* level){
	//cout<<"seteamos el current lvl"<<endl;
	currentLevel = level;
	currentLevel->setBackground(this->gameBackground);
}
void Broadcaster::setAnimations(AnimationsInGame* animations){
	this->currentAnimations = animations;
	this->currentAnimations->setBackground(this->gameBackground);
}
void Broadcaster::setReloader(ReloadReady* reloaderr){
	reloader = reloaderr;
}
void Broadcaster:: broadcastNewGameTo(User* user){

	User* user_3 = new User (user->getUserName(),"-");
	User* sender_back = new User (utils::SERVER_USER_ID,"-");
	string msj_background;
	msj_background.append(utils::SET_BACKGROUND_DIR);
	msj_background.append("|");
	msj_background.append(backgroundPath);
	Node* message_3 = new Node(sender_back,user_3,msj_background);
	newStatus->addMesage(message_3);
	currentLevel->initBroadCast();
				while (!currentLevel->finished()){
					User* user_1 = new User (user->getUserName(),"-");
					User* user_2 = new User (user->getUserName(),"-");
					User* sender_image = new User (utils::SERVER_USER_ID,"-");
					User* sender_pos = new User (utils::SERVER_USER_ID,"-");
					//cout<<"a"<<endl;
					newStatus->addMesage(currentLevel->getCharacterSettings(sender_image,user_1));
					//cout<<"b"<<endl;
					newStatus->addMesage(currentLevel->getCharacterStatus(sender_pos,user_2));

				}
				User* userDestination = new User (user->getUserName(),"-");
				User* sender = new User (utils::SERVER_USER_ID,"-");
				std::string message;
				message.append(utils::GAME_READY);
				Node* message_end = new Node(sender,userDestination,message);
				newStatus->addMesage(message_end);
}

void Broadcaster::broadcastGameBegin(){
	list<User*>:: iterator iterUser;
	iterUser = connectedUsers->begin();
	while(iterUser != connectedUsers->end()){
			//cout<<"enviamos todo a todos"<<endl;
			this->broadcastNewGameTo((*iterUser));
			iterUser++;
		}

}

void Broadcaster::reconnectPlayer(User* user){
	reconnectingPlayer = user;
}

void Broadcaster:: broadcastNewStatus(){
	//Recorremos la lista de personajes y emitimos sus posiciones para todos los jugadores conectados [en teoria]
	currentLevel->initBroadCast();
	while (!currentLevel->finished()){
		list<User*>:: iterator iterUser;
		iterUser = connectedUsers->begin();

		std::string msj = currentLevel->getCharacterStatus();
		if(msj.compare(utils::NO_NEW_ACTION)==0)
			continue;
		while(iterUser != connectedUsers->end()){
			if((*iterUser)->isConnected()){
			User* sender = new User(utils::SERVER_USER_ID,"-");
			User* user = new User((*iterUser)->getUserName(),"-");
			Node* message = new Node(sender,user,msj);
			newStatus->addMesage(message);
			}
			iterUser++;
		}

	}
	currentAnimations->initBroadCast();
		while (!currentAnimations->finished()){
			list<User*>:: iterator iterUser;
			iterUser = connectedUsers->begin();
			std::string msj = currentAnimations->getAnimationsMessages();
			while(iterUser != connectedUsers->end()){
				if((*iterUser)->isConnected()){
				User* sender = new User(utils::SERVER_USER_ID,"-");
				User* user = new User((*iterUser)->getUserName(),"-");
				Node* message = new Node(sender,user,msj);
				newStatus->addMesage(message);
				}
				iterUser++;
			}

		}
}
void Broadcaster:: broadcastNewBackgroundStatus(){
	//Recorremos la lista de personajes y emitimos sus posiciones para todos los jugadores conectados [en teoria]

	list<User*>:: iterator iterUser;
	iterUser = connectedUsers->begin();
	std::string msj;
	msj.append(utils::NEW_BACKGROUND_POSITION);
	msj.append("|");
	std::string x;
	std::stringstream out;
	out << gameBackground->getPosition();
	x = out.str();
	msj.append(x);
	while(iterUser != connectedUsers->end()){
		if((*iterUser)->isConnected()){
		User* sender = new User (utils::SERVER_USER_ID,"-");
		User* user = new User((*iterUser)->getUserName(),"-");



		Node* message = new Node(sender,user,msj);
		newStatus->addMesage(message);
		}
		iterUser++;
	}
}/*
void Broadcaster:: broadcastLevelInfo(list <MainCharacter*>* users){
	//Recorremos la lista de personajes y emitimos sus posiciones para todos los jugadores conectados [en teoria]
	currentLevel->initBroadCast();
	while (!currentLevel->finished()){
		list<User*>:: iterator iterUser;
		iterUser = connectedUsers->begin();

		std::string msj = currentLevel->getCharacterLevelInfo();
		if(msj.compare("")==0)
			continue;
		while(iterUser != connectedUsers->end()){
			if((*iterUser)->isConnected()){
			User* sender = new User(utils::SERVER_USER_ID,"-");
			User* user = new User((*iterUser)->getUserName(),"-");
			Node* message = new Node(sender,user,msj);
			newStatus->addMesage(message);
			}
			iterUser++;
		}

	}
}*/
void Broadcaster:: broadcastLevelInfo(list <MainCharacter*>* characters){
	//Recorremos la lista de personajes y emitimos sus posiciones para todos los jugadores conectados [en teoria]
	list<MainCharacter*>:: iterator iter;
	iter = characters->begin();
	while (iter!=characters->end()){
		list<User*>:: iterator iterUser;
		iterUser = connectedUsers->begin();

		std::string msj;// = (*iter)->getCharacterLevelInfo();

		msj.append(utils::LEVEL_INFO);
		msj.append("|");
		msj.append((*iter)->getCharacterID());
		msj.append("|");
		std::string x;
		std::stringstream out;
		bool gano = CharacterMap::teamWon((*iter)->getCharacterID());
		out << CharacterMap::getPoints((*iter)->getCharacterID()) << "|" << gano;
		x = out.str();
		msj.append(x);


		while(iterUser != connectedUsers->end()){
			if((*iterUser)->isConnected()){
			User* sender = new User(utils::SERVER_USER_ID,"-");
			User* user = new User((*iterUser)->getUserName(),"-");
			Node* message = new Node(sender,user,msj);
			newStatus->addMesage(message);
			}
			iterUser++;
		}
		iter++;
	}
}
void Broadcaster:: broadcastLevelInfoOver(){
	list<User*>:: iterator iterUser;
	iterUser = connectedUsers->begin();
	std::string msj = utils::END_LEVEL_INFO;
	msj.append("|");
	msj.append(utils::END_LEVEL_INFO);
	while(iterUser != connectedUsers->end()){
		if((*iterUser)->isConnected()){
		User* sender = new User(utils::SERVER_USER_ID,"-");
		User* user = new User((*iterUser)->getUserName(),"-");
		Node* message = new Node(sender,user,msj);
		newStatus->addMesage(message);
		}
		iterUser++;
	}
}
void Broadcaster:: broadcastGameOver(){
	list<User*>:: iterator iterUser;
	iterUser = connectedUsers->begin();
	std::string msj = utils::GAME_OVER;
	msj.append("|");
	msj.append(utils::GAME_OVER);
	while(iterUser != connectedUsers->end()){
		if((*iterUser)->isConnected()){
		User* sender = new User(utils::SERVER_USER_ID,"-");
		User* user = new User((*iterUser)->getUserName(),"-");
		Node* message = new Node(sender,user,msj);
		newStatus->addMesage(message);
		}
		iterUser++;
	}
}
void Broadcaster:: broadcastNewInfo(){
	//Recorremos la lista de personajes y emitimos sus posiciones para todos los jugadores conectados [en teoria]
	currentLevel->initBroadCast();
	while (!currentLevel->finished()){
		list<User*>:: iterator iterUser;
		iterUser = connectedUsers->begin();

		std::string msj = currentLevel->getCharacterInfo();
		size_t n = std::count(msj.begin(), msj.end(), '|');
		if(n<3)
			continue;
		//cout << "msj: " << msj << endl;
		while(iterUser != connectedUsers->end()){
			if((*iterUser)->isConnected()){
			User* sender = new User(utils::SERVER_USER_ID,"-");
			User* user = new User((*iterUser)->getUserName(),"-");
			Node* message = new Node(sender,user,msj);
			newStatus->addMesage(message);
			}
			iterUser++;
		}

	}
}

void* Broadcaster::process(){
	this->broadcastGameBegin();
	while(this->isRunning()){
		usleep(10000);
		broadcastNewStatus();
		broadcastNewBackgroundStatus();
		broadcastNewInfo();
		if(reconnectingPlayer != NULL){
			reconnectingPlayer->Connected();
			broadcastNewGameTo(reconnectingPlayer);
			reconnectingPlayer = NULL;
		}
		if(mustBeReloaded){
			this->broadcastReload();
			mustBeReloaded = false;
		}
	}
	return (void*)NULL;
}

void Broadcaster::broadcastReload() {
	canBeReloaded = true;
	list<User*>:: iterator iterUser;
	list<User*>:: iterator iterUser2;
	list<Node*>:: iterator reloadingIterUser;
	list<User*> reloadingUsers;
	std::string msj;
	iterUser = connectedUsers->begin();
	msj.append(utils::RELOAD_GAME);
	msj.append("|");
	msj.append(utils::RELOAD_GAME);
	while(iterUser != connectedUsers->end()){
		if((*iterUser)->isConnected()){
		User* sender = new User(utils::SERVER_USER_ID,"-");
		User* user = new User((*iterUser)->getUserName(),"-");
		Node* message = new Node(sender,user,msj);
		newStatus->addMesage(message);
		reloadingUsers.push_back((*iterUser));
		}
		iterUser++;
	}
	while(!reloader->finished()){
		usleep(1000);
	}
	reloader->startingReload();
	User* broadcaster = new User(utils::BROADCASTER,"-");
	while(!reloadingUsers.empty()){
		list<Node*>* usersReady = incomingMessages->getMessagesFor(broadcaster);

		reloadingIterUser = usersReady->begin();
		while(reloadingIterUser != usersReady->end()){
			iterUser = reloadingUsers.begin();
			while(iterUser != reloadingUsers.end()){
				if((*iterUser)->isEqualTo((*reloadingIterUser)->getFrom())){
					iterUser2 = iterUser;
					iterUser++;
					reloadingUsers.erase(iterUser2);
					continue;
				}
				iterUser++;
			}
			reloadingIterUser++;
		}
		usleep(1000);
	}
	//cout<<"Terminamos todo"<<endl;
	this->broadcastGameBegin();
	canBeReloaded =false;
}

void Broadcaster::stop(){
	Thread::stop();
}
