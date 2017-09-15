/*
 * Exception.h
 *
 *  Created on: 27/08/2016
 *      Author: pablo
 */

#ifndef SRC_COMMON_UTILS_EXCEPTION_H_
#define SRC_COMMON_UTILS_EXCEPTION_H_

#include <exception>
#include <string>

namespace exceptions {

class Exception: public std::exception {
public:
	Exception();
	Exception(const std::string& reason);
	virtual ~Exception() throw();
	virtual const char* what() const throw();
	virtual const std::string className() const;

private:
	//Metodos Privados
	const std::string& getReason() const;

	//Miembros privados
	std::string reason;
};

class SocketException: public Exception {
public:
	SocketException();
	SocketException(const std::string& reason);
	virtual ~SocketException() throw();
	virtual const std::string className() const;
};

class ThreadException: public Exception {
public:
	ThreadException();
	ThreadException(const std::string& reason);
	virtual ~ThreadException() throw();
	virtual const std::string className() const;
};

} /* namespace exceptions */

#endif /* SRC_COMMON_UTILS_EXCEPTION_H_ */
