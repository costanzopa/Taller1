/*
 * client.cpp
 *
 *  Created on: 28/08/2016
 *      Author: pablo
 */

#include "ui/ClientUIController.h"

int main(int argc, char** argv) {
	try {
		ClientUIController* client = NULL;
		std::cout << "Iniciando el programa Cliente." << std::endl;
		std::string host = "localhost";
		std::string port = "15558";

		for(int i = 1; i < argc; i++) {
			std::string param = argv[i];
			if((i+1) < argc) {
				std::string val = argv[i + 1];
				if(param.compare(utils::HOST_PARAM) == 0 && val.compare(utils::PORT_PARAM) != 0){
					host = val;
				}
				if(param.compare(utils::PORT_PARAM) == 0 && val.compare(utils::HOST_PARAM) != 0){
					port = val;
				}
			}
		}

		client = new ClientUIController(host, port);
		client->startUI();
		if (client != NULL) {
			delete client;
		}
	} catch (std::exception& e) {
		std::cout << "Se capturo una excepcion: " << e.what() << std::endl;
	}
	return 0;
}
