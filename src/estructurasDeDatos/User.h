/*
 * User.h
 *
 *  Created on: 02/09/2016
 *      Author: guido
 */

#ifndef USER_H_
#define USER_H_
#define MAX_LEN 10
#include <string>
using namespace std;
/* La clase User contiene el nombre y la contraseña
 * No estoy del todo seguro porque tiene la contraseña. Pero mejor 
 * que sosobre y no que fafalte 
 * */
class User{
	std::string userName;
	std::string password;
	bool connected;
	public:
		void Disconnected();
		void Connected();
		bool isConnected();
		User(const std::string& user,const std::string& pass);
		bool isEqualTo(User*);
		std::string& getUserName();
		std::string& getPassword();
		int getNameSize();
		~User();

};

#endif /* USER_H_ */
