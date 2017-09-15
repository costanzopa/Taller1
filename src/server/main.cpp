/*
 * server.cpp
 *
 *  Created on: 28/08/2016
 *      Author: pablo
 */

#include "Server.h"
#include "../common/logger/Logger.h"

int main(int argc,char** argv) {	
	int returnValue = 0;
	std::string main= "Main";
	logger::Logger log(main);
	log.info("Iniciando aplicación principal.");
	try {
		std::string port = utils::DEFAULT_PORT;
		std::string userPath = utils::DEFAULT_PATH_USER_FILE;

		for (int i = 1; i < argc; i++) {
			std::string param = argv[i];
			if ((i + 1) < argc) {
				std::string val = argv[i + 1];
				if (param.compare(utils::USR_PARAM) == 0
						&& val.compare(utils::PORT_PARAM) != 0) {
					userPath = val;
				}
				if (param.compare(utils::PORT_PARAM) == 0
						&& val.compare(utils::USR_PARAM) != 0) {
					port = val;
				}
			}
		}
		server::Server server(port,utils::MAX_QUEUE,userPath);
		server.start();
		std::cout<<"Se ha iniciado el servidor."<<std::endl;
		std::cout<<"Ingrese una Q para cerrar el servidor."<<std::endl;
		char input;
		do {
			std::cin >> input;
		} while ((input != 'q') && (input != 'Q'));
			server.stop();
			server.close();
			std::cout<<"Se ha parado el servidor"<<std::endl;
	} catch (const std::exception &e) {
		std::string main= "Main";
		logger::Logger logError(main);
		std::cout<<"Se ha capturado una excepción, se cerrar el servidor."<<std::endl;
		returnValue = -1;
		logError.error("Se ha capturado una excepción, en el servidor se finaliza con codigo de retorno FAIL.");
		return returnValue;
	}
	std::cout<<"Se cierra la aplicación de manera correcta, con codigo de retorno: "<<returnValue<<std::endl;
	log.info("Se cierra la aplicación de manera correcta, con codigo de retorno: SUCCESS");
	return returnValue;
}


