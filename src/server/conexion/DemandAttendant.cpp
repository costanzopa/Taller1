#include "DemandAttendant.h"

using namespace std;

DemandAttendant :: DemandAttendant (){
	activated = false;
	this->demandHandler = NULL;
}

void DemandAttendant:: setMessagesList(MessageList* list){
	this->messageList = list;
}
void DemandAttendant :: setDemandHandler(DemandHandler* demandHandler){
	this->demandHandler = demandHandler;
}
void* DemandAttendant :: process(){
	while(this->isRunning()){
		if(demandHandler->isEmpty())
			continue;
		Demand* newDemand = demandHandler->pullDemand();
		list<Node*>* outMessagesList = messageList->getMessagesFor(newDemand->demandingUser);
		newDemand->userQueue->pushMessage(outMessagesList);
	}
	return (void*)NULL;
}
DemandAttendant :: ~DemandAttendant(){
	if (demandHandler != NULL) {
		delete demandHandler;
	}
}
void DemandAttendant:: stop(){
	Thread::stop();
}
