#include "DemandAttendant.h"
#include "MessageSender.h"
#include "../logicaDelServidor/GameRelated/GameManager.h"
#include "../../common/threads/Thread.h"
#include "../../common/logger/Logger.h"
#include <sstream>
#include <algorithm>
#include <iterator>

#ifndef USERCONNECTION_H_
#define USERCONNECTION_H_

using namespace std;

class UserConnection: public threads::Thread{
	GameManager* game;
	int* fileDescriptor;
	MessageList* messageList;
	MessageList* gameMessageList;
	MessageList* currentList;
	float characterScale;
	float windowScale;
	User* user;
	DemandHandler* demandHandler;
	DemandAttendant* demandAttendant;
	OutcomingMessages* messageOutQueue;
	MessageSender* messageOutAttendant;
	net::Communication* communication;
	logger::Logger* logger;
	vector<string> allUsers;
	pthread_t messageOutThread;
	pthread_t demandAttendantThread;
	

	public:
		UserConnection( MessageList*, User*, net::Communication*, std::vector<string>& allUsers,MessageList*);
		void setGameScales(float,float);
		void addGameManager(GameManager*);
		void createQueue();
		void ReadMessages();
		void WriteMessage();
		std::string getAllUsers();
		virtual void stop();
		virtual ~UserConnection();
	private:
		void dumpPreviousGameMessages();
		void sendDisconnectionMessage();
		virtual void* process();
		void setDemandsAttendant(MessageList*,DemandHandler*);
		void setMessageSender(OutcomingMessages*, net::Communication*);
};
#endif
