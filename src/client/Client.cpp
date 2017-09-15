/*
 * Client.cpp
 *
 *  Created on: 01/09/2016
 *      Author: pablo
 */

#include "Client.h"

namespace client {

const string MESSAGE_HEADER = "--------------------------------------------------------------------------------";
const string MESSAGE_SEPARATOR = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


Client::Client() {
	pthread_mutex_init(&mutex_lock,NULL);
	this->host = "localhost";
	this->port = "15558";
	this->communication = NULL;
	this->quit = false;
	string log = "cliente";
	this->logger = new logger::Logger(log);
	logger->setTrimMessage(true);
	this->connected = false; //Master
}

Client::Client(std::string& host, std::string& port) {
	pthread_mutex_init(&mutex_lock,NULL);
	this->host = host;
	this->port = port;
	this->communication = NULL;
	this->quit = false;
	string log = "cliente";
	this->connected = false; //Master

	this->logger = new logger::Logger(log);
	logger->setTrimMessage(true);
}

Client::~Client() {
	delete this->logger;
}

bool Client::connect() {
	try {
		if (this->communication == NULL) {
			this->communication = new net::Communication(this->host,this->port);
			this->logger->info("Usuario conectado al server de forma correcta");
			connected = true; //Master
		} else {
			std::cout<<"El cliente se encuentra conectado a la ip "<<this->host<<" puerto "<<this->port<<std::endl;
			this->logger->info("Usuario ya conectado");
		}
	} catch (exceptions::SocketException& e) {
		std::cout<<"No se a podido conectar con el servidor por favor vuelva a intentarlo."<<std::endl;
		this->logger->error("No se a podido conectar con el servidor.");
			if (this->communication!=NULL) {
				delete communication;
				this->communication = NULL;
			}
		return false;
	}
	return true;

}

string Client::getUser(){
	return this->user;
}
string Client::getScales(){
	this->lock_client();
	this->communication->sendString(utils::GET_SCALES);
	//cout<<"aa"<<endl;
	Node* message = this->communication->receiveNode();
	//cout<<"bb"<<endl;
	this->unlock_client();
	string scales = message->getMessage();
	//cout<<"cc"<<endl;
	delete message;
	//cout<<"terminamos de pedir scales"<<endl;
	return scales;
}
int Client :: validateInputInNumericRange(int from, int to) {
	string input;
	int option;
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> option && option >= from && option <= to)
		   break;
		cout << "Opcion invalida. Intente nuevamente." << endl;
	}
	return option;
}
bool Client::startGame(){
	this->communication->sendString(utils::DUMP_GAME_MESSAGES);
	cout<<"Seleccione un personaje (de 1 a 6)"<<endl;
	std::string characterSelected;
	std::string characterName;
	std::string message;
	std::string server;
	server.append(utils::SERVER_USER_ID);
	int character = this->validateInputInNumericRange(1,7);
	switch(character){
		case 1:
			characterName = utils::CHARACTER_1;
			break;
		case 2:
			characterName = utils::CHARACTER_2;
			break;
		case 3:
			characterName = utils::CHARACTER_3;
			break;
		case 4:
			characterName = utils::CHARACTER_4;
			break;
		case 5:
			characterName = utils::CHARACTER_5;
			break;
		case 6:
			characterName = utils::CHARACTER_6;
			break;
		case 7:
			characterName = utils::CHARACTER_7;

	}
	cout << "You have choosen the " << characterName << " character" << endl;
	message.append(utils::NEW_CHARACTER);
	message.append("|");
	message.append(characterName);
	this->sendMessageToUser(message,server);
	list<Node*>* messages = this->getMessages();
	list<Node*>:: iterator iter;
	iter = messages->begin();
	while(true){
		while(iter != messages->end()){
				if((*iter)->getMessage().compare(utils::HAS_SPACE)==0)
					return true;
				if((*iter)->getMessage().compare(utils::NO_SPACE)==0)
					return false;
				iter++;
		}
		delete messages;
		messages = this->getMessages();
		iter = messages->begin();
	}


}

bool Client::login(std::string userName, std::string password) {
	bool isValid = false;
	std::string answer;
	this->communication->sendUser(userName,password);
	this->communication->receiveString(answer);
	if (answer.compare(utils::OK_MESSAGE)==0) {
		isValid = true;
		this->user = userName;
		this->logger->info("Usuario [" + userName + "] Acceso OK");
	} else {
		this->logger->warn("Usuario [" + userName + "] Acceso Error: " + answer);
	}
	return isValid;
}

void Client::getAllUsers() {
	std::cout<<"Recibiendo los usuarios: Aguarde "<<std::endl;
	this->communication->sendString(utils::CONNECT_MESSAGE);
	std::string allUsers;
	this->communication->receiveString(allUsers);
	cout<<allUsers<<endl;
	this->setAllUsers(allUsers);
}

void Client::setAllUsers(std::string& allUsers) {
	if (!allUsers.empty()) {
		std::istringstream auxiliar(allUsers);
		std::string user;
		while(getline(auxiliar,user,':')) {
			users.push_back(user);
		}
	} else {
		throw exceptions::SocketException("No se han recibido los usuarios.");
	}
}

std::vector<std::string> Client::retreiveAllUsers() {
	if(this->users.empty()) {
		this->getAllUsers();
	}
	return this->users;
}


void Client::printAllUsers() {
	std::vector<std::string>::iterator it = this->users.begin();
	for(;it!= this->users.end();++it) {
		std::cout<<*it<<std::endl;
	}
}
void Client::disconnect() {
	if (this->communication != NULL) {
		this->communication->sendString(utils::DISCONNECT_MESSAGE);
		delete communication;
		this->communication = NULL;
		this->users.clear();
		this->logger->info("Disconnect OK");
		connected = false; // Master
	} else {
		this->logger->error("El cliente no se encuentra conectado a la ip "+this->host +" puerto " +this->port);
		std::cout<<"El cliente no se encuentra conectado a la ip "<<this->host<<" puerto "<<this->port<<std::endl;
	}
}

const std::string& Client::getAllMessages() {
	return message;
}

void Client::setQuit() {
	this->quit = true;
}

bool Client::getQuit() {
	return (this->quit);
}
bool Client::getGameReady(){
	this->communication->sendString(utils::START_GAME);
	std::string message;
	do{
		this->communication->sendString(utils::CONNECT_MESSAGE);
		usleep(1000);
		this->communication->receiveString(message);
	}while(!(message.compare(utils::GAME_STARTED)==0));
	return true;
}
bool Client::sendMessageToUser(std::string& message, std::string& to) {
	this->lock_client();
	std::string confirmationString;
	if (this->communication != NULL) {
		try {
			this->communication->sendString(utils::SINGLE_MESSAGE);
			this->communication->sendMessage(this->user, to, message);
			this->unlock_client();
			return true;
		} catch (exceptions::SocketException& e) {
			this->logger->error("Error al enviar un mensaje al usuario "+to);
			delete this->communication;
			this->communication = NULL;
			this->unlock_client();
			return false;
		}
	} else {
		std::cout << "El cliente no se encuentra conectado a la ip " << this->host << " puerto " << this->port << std::endl;
		std::cout << "Por favor utilice primero el comando [conectar]" << std::endl;
		this->unlock_client();
		return false;
	}
}

bool Client::sendMessage(std::string& to, std::string mode) {
	std::string confirmationString;
	if (this->communication != NULL) {
		try {
			this->communication->sendString(utils::SINGLE_MESSAGE);
			std::string message;
			getline(cin, message);
			this->communication->sendMessage(this->user,to, message);
			return true;
		} catch (exceptions::SocketException& e) {
			this->logger->error("Error al enviar un mensaje al usuario "+to);
            delete this->communication;
            this->communication = NULL;
            return false;
		}
	} else {
		std::cout<<"El cliente no se encuentra conectado a la ip "<<this->host<<" puerto "<<this->port<<std::endl;
		std::cout<<"Por favor utilice primero el comando [conectar]"<<std::endl;
		return false;
	}
}

bool Client::sendMessage(std::string& to, std::string mode,std::string& message) {
	std::string confirmationString;
	if (this->communication != NULL) {
		try {
			this->communication->sendString(utils::SINGLE_MESSAGE);
			this->communication->sendMessage(this->user,to, message);
			return true;
		} catch (exceptions::SocketException& e) {
			this->logger->error("Error al enviar un mensaje al usuario "+to);
            delete this->communication;
            this->communication = NULL;
            return false;
		}
	} else {
		std::cout<<"El cliente no se encuentra conectado a la ip "<<this->host<<" puerto "<<this->port<<std::endl;
		std::cout<<"Por favor utilice primero el comando [conectar]"<<std::endl;
		return false;
	}
} // MASTER

void Client::cycle() {

}
void Client::printMessages() {
	if (this->communication != NULL) {
		this->communication->sendString(utils::RECIEVE_MESSAGES);
		Node* message = this->communication->receiveNode();
		if (message != NULL && !message->getMessage().empty()) {
			while ((message->getMessage()).compare(utils::END_OF_MESSAGES)) {
				cout << MESSAGE_HEADER << endl;
				cout << "From: ";
				cout << message->getFrom()->getUserName() << endl;
				cout << "To: ";
				cout << message->getTo()->getUserName() << endl;
				cout << MESSAGE_HEADER << endl;
				cout << message->getMessage() << endl;
				cout << MESSAGE_SEPARATOR << endl;
				logger->info(
						message->getFrom()->getUserName() + " escribio a: "
								+ message->getTo()->getUserName() + ":\n"
								+ message->getMessage());
				delete message;
				message = this->communication->receiveNode();
			}
		} else {
			cout << "Usted no tiene mensajes" << endl;
		}

	} else {
		std::cout << "El cliente no se encuentra conectado a la ip "
				<< this->host << " puerto " << this->port << std::endl;
		std::cout << "Por favor utilice primero el comando [conectar]"
				<< std::endl;
	}
}
void Client::printHelp() {
	std::cout<<"Se dispone de los siguientes comandos:" << endl;
	std::cout<< "conectar\ndesconectar\nsalir\nrecibir\nlorem ipsum\n" <<endl;
}

list<Node*>* Client:: getMessages(){
	list<Node*>* incomingMessages = new list<Node*>();
	if (this->communication != NULL) {
			this->lock_client();
			this->communication->sendString(utils::RECIEVE_MESSAGES);
			Node* message = this->communication->receiveNode();
			this->unlock_client();
			if (message != NULL && !message->getMessage().empty()) {
				while ((message->getMessage()).compare(utils::END_OF_MESSAGES)) {
					incomingMessages->push_back(message);
					logger->info(
							message->getFrom()->getUserName() + " escribio a: "
									+ message->getTo()->getUserName() + ":\n"
									+ message->getMessage());
					this->lock_client();
					message = this->communication->receiveNode();
					this->unlock_client();
				}
			} else {
				cout << "Usted no tiene mensajes" << endl;
			}

		} else {
			std::cout << "El cliente no se encuentra conectado a la ip "
					<< this->host << " puerto " << this->port << std::endl;
			std::cout << "Por favor utilice primero el comando [conectar]"
					<< std::endl;
		}

	return incomingMessages;
}
/*
void Client::process() {
	std::string input;
	std::getline(std::cin,input);
	std::transform(input.begin(),input.end(),input.begin(),::tolower);
	if (input.compare("conectar") == 0) {
		this->connect();
	} else if (input.compare("desconectar") == 0) {
		this->disconnect();
	} else if (input.compare("salir") == 0) {
		this->setQuit();
	} else if (input.compare("enviar") == 0) {
		this->sendMessage();
	} else if (input.compare("recibir")==0) {
		this->printMessages();
	} else if (input.compare("lorem ipsum")==0) {
		this->cycle();
	} else if (input.compare("ayuda")==0) {
		this->printHelp();
	} else {
		std::cout<<"Ha ingresado un comando inválido."<<std::endl;
		std::cout<<"Ejecute el comando [ayuda].";
	}
}*/

bool& Client::isConnected() {
	return (connected);
}

void Client::setDisconnect() {
	this->connected = false;
}
void Client::quitGame(){
	this->communication->sendString(utils::QUIT_GAME);
}
void Client::checkConnection() {
	if (this->isConnected() == true) {
		if (this->communication !=NULL) {
			std::string messageOk;
			this->communication->sendString(utils::CONNECTED_MESSAGE);
			this->communication->receiveString(messageOk);
			usleep(1000);
		} else {
			throw exceptions::SocketException("El cliente No se encuentra conectado.");
		}
	}
}
} /* namespace client */
