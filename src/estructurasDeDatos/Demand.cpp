#include "Demand.h"

using namespace std;

 Demand::Demand(User* demander,OutcomingMessages* queue){
	demandingUser = demander;
	userQueue = queue;

}

Demand::~Demand(){
	delete demandingUser;
	delete userQueue;
}

User* Demand :: getDemander(){
		return demandingUser;
}

OutcomingMessages* Demand :: getMessagesQueue(){
		return userQueue;
}
