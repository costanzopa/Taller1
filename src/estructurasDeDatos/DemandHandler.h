
#include "Demand.h"
#include <pthread.h>

using namespace std;
/*DemandHandler es una cola en donde los UserConnections ponen sus
 * requests para recibir los mensajes, estos son luegos manejados por
 * clase que se encarga de sacarlos de la cola busca los mensajes y
 * los manda a otra  que los envia por el socket
*/
class DemandHandler{
	queue<Demand*>* demand_queue;
	pthread_mutex_t handlerMutex;

	public:
		DemandHandler();
		virtual ~DemandHandler();
		void pushDemand(Demand*);
		Demand* pullDemand();
		bool isEmpty();
	private:
		void lockHandler(){pthread_mutex_lock(&handlerMutex);}
		void unlockHandler(){pthread_mutex_unlock(&handlerMutex);}

};
