/*
 * Thread.cpp
 *
 *  Created on: 06/09/2016
 *      Author: Pablo
 */

#include "Thread.h"
#include <iostream>
namespace threads {

void *Thread::execute(void *pThread) {
	return ((Thread *) pThread)->process();
}

Thread::Thread() {
	this->setRunning(false);
	this->hasStopped = false;
	this->hasStarted = false;
	this->thread = 0;
	std::string log = "Threads";
	this->logger = new logger::Logger(log);
}

Thread::~Thread() {
	if (this->hasStarted == true) {
		this->stop();
		if(this->hasStopped == false) {
			::pthread_join(thread, NULL);
		}
	}
	delete this->logger;
}

bool Thread::isRunning() {
	return (this->running);
}

void Thread::start() {
	if ( this->hasStarted == false) {
	    if (::pthread_create(&thread, NULL, &execute, this) != 0) {
			this->logger->error("Error al crear el thread.");
	        throw exceptions::ThreadException("ERROR al crear el thread.");
	    }
	    this->setRunning(true);
	    this->hasStarted = true;
	    } else {
			this->logger->error("Error thread ya iniciado.");
			throw exceptions::ThreadException("ERROR thread ya iniciado.");
	    }
}

void Thread::stop() {
	 this->setRunning(false);
}

void Thread::close() {
	if ((this->hasStarted == true) && (this->hasStopped == false)) {
		  this->stop();
	      if (::pthread_join(thread, NULL) != 0) {
			  this->logger->error("Error join hilo.");
	        throw exceptions::ThreadException("ERROR join hilo");
	      } else {
	      	this->hasStopped = true;
	      }
	 } else {
		  this->logger->error("Error hilo cerrado.");
	      throw exceptions::ThreadException("ERROR hilo cerrado");
	 }
}

void Thread::setRunning(const bool running) {
	this->running = running;
}

const bool& Thread::getRunning() const {
	return this->running;
}

} /* namespace threads */
