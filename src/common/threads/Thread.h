/*
 * Thread.h
 *
 *  Created on: 06/09/2016
 *      Author: Pablo
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <iostream>
#include "../utils/Exception.h"
#include "../logger/Logger.h"
#include <pthread.h>

namespace threads {

class Thread {
public:
	Thread();
	virtual ~Thread();
	bool isRunning();
	virtual void start();
	virtual void stop();
	const bool& getRunning() const;
	void close();

private:
	//Metodos Privados
	virtual void* process()=0;
	static void *execute(void *pThread);
	void setRunning(const bool running);
	//Miembros de clase
	bool running;
	pthread_t thread;
	logger::Logger* logger;
	bool hasStarted;
	bool hasStopped;

	Thread(const Thread &thread);
	Thread& operator=(const Thread &thread);
};

} /* namespace threads */
#endif /* THREAD_H_ */
