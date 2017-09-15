#include "MessageSender.h"
#include "../../common/utils/Constants.h"
#include <iostream>

#define MAX_LEN_MSG 300
MessageSender :: MessageSender(){
	std::string message = utils::END_OF_MESSAGES;
	User* end_user = new User(utils::END_OF_MESSAGES,utils::END_OF_MESSAGES);
	User* end_user2 = new User(utils::END_OF_MESSAGES,utils::END_OF_MESSAGES);
	end_of_stream_node = new Node(end_user,end_user2,message);
	this->communication = NULL;
	this->messages_for_user = NULL;
}

void MessageSender :: setMessageQueue(OutcomingMessages* queue){
	messages_for_user = queue;
}
void MessageSender :: setCommunication(net::Communication* com){
	communication = com;
}
void* MessageSender :: process(){
	try{
	while(this->isRunning()){
		if(messages_for_user->isEmpty())
			continue;
		while(!messages_for_user->isEmpty()){
			list<Node*>* messages = messages_for_user->popMessage();
			for(list<Node*>::iterator itr = messages->begin();itr != messages->end();itr++){
						communication->sendNode(*itr);
						//messages->erase(itr);
						delete *itr;
			}
			delete messages;
		}
		communication->sendNode(end_of_stream_node);
	}
	}catch(const exceptions::SocketException &e){
		cout<<"Catcheamos en message sender"<<endl;
		return (void*)NULL;
	}
	return (void*)NULL;
}
 MessageSender::~MessageSender(){
 	if(communication != NULL) {
 		delete communication;
 	}
 	if (messages_for_user != NULL) {
 		delete messages_for_user;
 	}
	delete end_of_stream_node;
 }
void MessageSender:: stop(){
	Thread::stop();
}
