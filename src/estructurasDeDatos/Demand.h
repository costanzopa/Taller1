#include "User.h"
#include "OutcomingMessages.h"

using namespace std;

class Demand{
	/*La demanda propiamente dicha, que se instancia en el UserConnection
	 * la cual contiene el usuario que las demanda, y la cola de donde seran
	 * sacadas y enviadas al cliente
	 * */


	public:
		User* demandingUser;
		OutcomingMessages* userQueue;

		Demand(User* demandingUser,OutcomingMessages* userQueue);
		~Demand();
		User* getDemander();
		OutcomingMessages* getMessagesQueue();

};
