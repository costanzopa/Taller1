#include <iostream>
#include "Node.h"
#include <queue>
#include <list>
#include <pthread.h>
#include "OutcomingMessages.h"

using namespace std;
OutcomingMessages :: OutcomingMessages(){
	pthread_mutex_init(&queue_mutex,NULL);
	messages = new queue<list<Node*>*>();
}

void OutcomingMessages :: pushMessage(list<Node*>* message){
	this->lockQueue();
	messages->push(message);
	this->unlockQueue();
}

list<Node*>* OutcomingMessages :: popMessage(){
	this->lockQueue();
	if(messages->empty()){
		this->unlockQueue();
		return NULL;
	}
	list<Node*>* message = messages->front();
	messages->pop();
	this->unlockQueue();
	return message;
	
}

OutcomingMessages::~OutcomingMessages() {
	while (!messages->empty()) {
		list<Node*>* message = messages->front();
		list<Node*>:: iterator it = message->begin();
		while (it != message->end()) {
			delete (*it);
			it++;
		}
		messages->pop();
		delete message;
	}
	delete messages;
}
