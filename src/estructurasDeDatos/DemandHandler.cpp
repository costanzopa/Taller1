#include <queue>
#include "DemandHandler.h"


using namespace std;

DemandHandler::DemandHandler(){
	pthread_mutex_init(&handlerMutex,NULL);
	this->demand_queue = new queue<Demand*>();	
}

void DemandHandler::pushDemand(Demand* new_demand){
	this->lockHandler();
	demand_queue->push(new_demand);
	this->unlockHandler();

}
bool DemandHandler :: isEmpty(){
	return demand_queue->empty();
}
Demand* DemandHandler::pullDemand(){
	Demand* newDemand = demand_queue->front();
	this->lockHandler();
	demand_queue->pop();
	this->unlockHandler();
	return newDemand;

}

DemandHandler::~DemandHandler() {
	while (!demand_queue->empty()) {
		Demand* demand = demand_queue->front();
		demand_queue->pop();
		delete demand;
	}
	delete this->demand_queue;
}