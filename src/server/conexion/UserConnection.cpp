#include <iostream>
#include <unistd.h>
#include "UserConnection.h"
#include "../../common/utils/Constants.h"
#define BUFFSIZE 1024;
#define CMD_DISCONNECT "logOff"
#define CMD_RECIEVE "recieve"
#define CMD_WRITE "write"

using namespace std;

UserConnection::UserConnection(MessageList* list, User* connectedUser, net::Communication* communication, vector<string>& allUsers,MessageList* gameList){
	// Esta clase sirve para recibir los mensajes del usuario y poder crear los threads que operen sobre la lista de mensajes
	messageList = list;
	this->user = connectedUser;
	this->communication = communication;
	this->gameMessageList = gameList;
	this->currentList = messageList;
	messageOutQueue = new OutcomingMessages();
	demandHandler = new DemandHandler();
	this->setMessageSender(messageOutQueue,communication);
	this->setDemandsAttendant(list,demandHandler);
	string log = "Server";
	this->logger = new logger::Logger(log);
	this->allUsers = allUsers;
}
void UserConnection::addGameManager(GameManager* gameManager){
	game= gameManager;

}

void UserConnection :: setMessageSender(OutcomingMessages* outcomingMessages, net::Communication* communication){
	this->messageOutAttendant = new MessageSender();
	this->messageOutAttendant->setMessageQueue(outcomingMessages);
	this->messageOutAttendant->setCommunication(communication);
	this->messageOutAttendant->start();
}
void UserConnection:: setDemandsAttendant(MessageList* list,DemandHandler* demandsHandler){
	this->demandAttendant = new DemandAttendant();
	this->demandAttendant->setMessagesList(list);
	this->demandAttendant->setDemandHandler(demandsHandler);
	this->demandAttendant->start();
}
void UserConnection::dumpPreviousGameMessages(){
	gameMessageList->erraseMessagesFor(user);

}
void UserConnection::setGameScales(float window,float character){
	windowScale= window;
	characterScale = character;
}
void* UserConnection:: process(){
	try {
    	while(this->isRunning()){

    		std::string command;
    		this->communication->receiveString(command);
    		if (command.compare(utils::CONNECTED_MESSAGE)==0){
    			this->communication->sendString(utils::OK_MESSAGE);
    			continue;
    		} //MASTER
    		if (command.compare(utils::CONNECT_MESSAGE)==0) {
    			std::string allUsersString = this->getAllUsers();
    			this->communication->sendString(allUsersString);
    			continue;
    		}
    		if(command.compare(utils::SINGLE_MESSAGE) == 0){
    			this->WriteMessage();
    			continue;
    		}
    		if(command.compare(utils::RECIEVE_MESSAGES) == 0){
    			this->ReadMessages();
    			continue;
    		}
    		if(command.compare(utils::DUMP_GAME_MESSAGES)==0){
    			this->dumpPreviousGameMessages();
    		}
    		if(command.compare(utils::DISCONNECT_MESSAGE) == 0){
    			logger->info("Se desconecto " + this->user->getUserName());
    			this->stop();
    			continue;
    		} 
    		if(command.compare(utils::GET_SCALES) == 0){
    			windowScale = this->game->windowScale;
    			characterScale = this->game->characterScale;
    			User* sender = new User(utils::SERVER_USER_ID,utils::SERVER_USER_ID);
    		    User* recv = new User(utils::SERVER_USER_ID,utils::SERVER_USER_ID);
    		    std::string message;
    		    std::ostringstream ostr;
    		    std::ostringstream ostr2;
    		    ostr << windowScale;
    		    std::string s = ostr.str();
    		    message.append(s);
				message.append("|");
				ostr2 << characterScale;
				s = ostr2.str();
				message.append(s);
				cout<<message<<endl;
				Node* scales = new Node(sender,recv,message);
				this->communication->sendNode(scales);
				continue;
    		}
    		if(command.compare(utils::START_GAME)==0){
    			cout<< user->getUserName()<< "	pidio jugar"<<endl;
    			while(!game->started()){
    				std::string check_connection;
    				this->communication->receiveString(check_connection);
    				usleep(1000);
    				this->communication->sendString(utils::OK_MESSAGE);

    			}
    			std::string check_connection;
    			this->communication->receiveString(check_connection);
    			usleep(1000);
    			this->communication->sendString(utils::GAME_STARTED);

    			demandAttendant->setMessagesList(gameMessageList);
    		}
    		if(command.compare(utils::QUIT_GAME)==0){
    			this->sendDisconnectionMessage();
    			demandAttendant->setMessagesList(messageList);
    		}
    	}

   		demandAttendant->stop();
   		demandAttendant->close();
   		messageOutAttendant->stop();
    	messageOutAttendant->close();

	}catch(const exceptions::SocketException &e) {
		cout<<"Explota aca"<<endl;
		demandAttendant->stop();
   		demandAttendant->close();
   		messageOutAttendant->stop();
    	messageOutAttendant->close();
    	this->sendDisconnectionMessage();
    	this->stop();
		std::cout<<"Se ha caido la conexion "<< this->user->getUserName()<<std::endl;
		logger->error("Se ha caido la conexion del usuario: " + this->user->getUserName());
		return (void*)NULL;
	} catch(exceptions::ThreadException &tException) {
		cout<<"Explota aca threadd"<<endl;
		this->sendDisconnectionMessage();
		this->stop();
		demandAttendant->stop();
   		demandAttendant->close();
   		messageOutAttendant->stop();
    	messageOutAttendant->close();
	    std::cout<<"Problema en un tread "<<std::endl;
		logger->error("Error en un thread: " + this->user->getUserName());
		return (void*)NULL;
	}
    return (void*)NULL;
}
void UserConnection::sendDisconnectionMessage(){
	User* server = new User(utils::SERVER_USER_ID,"-");
	User* userSender = new User(this->user->getUserName(),"-");
	std::string msg;
	msg.append(utils::DISCONNECTED);
	msg.append("|");
	msg.append("Desconectado");
	Node* message = new Node(userSender,server,msg);
	messageList->addMesage(message);
}

void UserConnection:: stop(){
	//this->communication->interrupt();
	Thread::stop();
}
void UserConnection::ReadMessages(){
	Demand* new_demand = new Demand(this->user,this->messageOutQueue);
	this->demandHandler->pushDemand(new_demand);
}
void UserConnection::WriteMessage(){
	Node* message = this->communication->receiveMessage();
	messageList->addMesage(message);
	logger->debug(this->user->getUserName() + " escribio: " + message->getMessage() + " Para: " + message->getTo()->getUserName());

}


std::string UserConnection::getAllUsers() {
	std::ostringstream ss;
	if(!this->allUsers.empty()) {
		std::copy(allUsers.begin(),allUsers.end()-1,
			std::ostream_iterator<string>(ss,":"));
			ss<<allUsers.back();
		}
	return ss.str();
}


UserConnection::~UserConnection() {
	delete user;
	delete  demandAttendant;
	delete messageOutAttendant;
}
