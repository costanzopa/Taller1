/*
 * Communication.cpp
 *
 *  Created on: 28/08/2016
 *      Author: pablo
 */

#include "Communication.h"

namespace net {

Communication::Communication() {
  socket = new Socket();
  pendingMessage = "";
  std::string name = "Communication";
  logger = new logger::Logger(name);
  this->active = true;
}
Communication::Communication(const std::string &port, const int queue) {
  socket = new Socket(port, queue);
  std::string name = "Communication";
  logger = new logger::Logger(name);
  this->active = true;
}

Communication::Communication(const std::string& host, const std::string& port) {
  socket = new Socket(host, port);
  std::string name = "Communication";
  logger = new logger::Logger(name);
  this->active = true;
}

Communication::~Communication() {
  delete socket;
  delete logger;
}

void Communication::accept(Communication* communication) {
  this->socket->accept(communication->socket);
}

void Communication::interrupt() {
  socket->interrupt();
  this->active = false;
}


void Communication::sendString(const std::string &data) const {
    const uint32_t length = data.length();
    const char *buffer = data.c_str();
    uint32_t longmessage = htonl(length);
    size_t pending = sizeof longmessage;
    size_t send = 0;
    int error;
    int time = 0;
    while (pending > 0 && time < utils::TIME_OUT) {
      error = socket->send((char *) &longmessage + send, pending);
      if ( error==0 ) {
        throw exceptions::SocketException("ERROR han cerrado el socket al enviar.");
      } else {
        send += error;
       pending -= error;
     }
     time++;
    }
    if (time == utils::TIME_OUT)
      throw exceptions::SocketException("ERROR de TIME_OUT al enviar datos.");

    pending = length;
    send = 0;
    time = 0;

    while (pending > 0 && time < utils::TIME_OUT) {
      error = socket->send((char *) buffer + send, pending);
      if ( error==0 ) {
        throw exceptions::SocketException("ERROR han cerrado el socket al enviar.");
      } else {
        send += error;
       pending -= error;
     }
     time++;
    }

    if (time == utils::TIME_OUT)
      throw exceptions::SocketException("ERROR de TIME_OUT al enviar datos.");
  }

void Communication::receiveString(std::string& message) const {

    uint32_t longmessage;
    size_t pending = sizeof longmessage;
    size_t received = 0;
    int error;
    int time = 0;
    while (pending > 0 && time < utils::TIME_OUT) {
      error = socket->receive((char *) &longmessage + received, pending);
      if (error == 0) {
        throw exceptions::SocketException(
  	          "ERROR han cerrado el socket al recibir.");
      } else {
        received += error;
        pending -= error;
      }
      time++;
    }
    if (time == utils::TIME_OUT)
      throw exceptions::SocketException("ERROR de TIME_OUT al recibir datos.");

    size_t mensajeLargoHost = ntohl(longmessage);
    char *buffer = new char[mensajeLargoHost + 1];
    memset(buffer, 0, mensajeLargoHost + 1);
    pending = mensajeLargoHost;
    received = 0;
    time = 0;
    while (pending > 0 && time < utils::TIME_OUT) {
      error = socket->receive(buffer + received, pending);
      if (error == 0) {
        delete[] buffer;
        throw exceptions::SocketException(
  	          "ERROR han cerrado el socket al recibir.");
      } else {
        received += error;
        pending -= error;
      }
    }
    message = buffer;
    delete[] buffer;

    if (time == utils::TIME_OUT)
      throw exceptions::SocketException("ERROR de TIME_OUT al recibir datos.");
  }

void Communication::sendUser(User* user) {
	std::string& username = user->getUserName();
	std::string& password = user->getPassword();
	this->sendUser(username, password);
}

void Communication::sendUser(std::string& username, std::string& password) {
	std::stringstream message;	
	message<<username;
	message<<":";
	message<<password;
	//message<<"\n";	
	this->sendString(message.str());
}

User* Communication::receiveUser() {
	std::string message;	
	this->receiveString(message);
	std::string username = message.substr(0,message.find(':'));
	std::string password = message.substr(message.find(':')+1);
	User* newUser = new User(username,password);
	return newUser;
}

void Communication::sendMessage(std::string& from,std::string& to, std::string& message) {
	this->sendString(from);	
	this->sendString(to);
	this->sendString(message);
}

Node* Communication::receiveMessage() {
	std::string from;
	std::string to;
	std::string message;
	this->receiveString(from);
	this->receiveString(to);
	this->receiveString(message);
	User* fromNode = new User(from,from);
	User* toNode = new User(to,to);
	Node* nodeReturn = new Node(fromNode,toNode,message);
	return nodeReturn;
}


void Communication::sendNode(Node* node) {
	std::string message = node->getMessage();
	User* from = node->getFrom();
	User*  to = node->getTo();
	this->sendString(message);
	this->sendUser(from);
	this->sendUser(to);
}

Node* Communication::receiveNode() {
	std::string message;
	this->receiveString(message);
	User* from = this->receiveUser();
	User* to = this->receiveUser();
	Node* node = new Node(from, to, message);
	return node;
}

void Communication::setInActive() {
  this->active = false;
}

bool& Communication::getActive() {
    return active;
}

} /* namespace net */
