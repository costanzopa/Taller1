server:  
	cd config; make config;
	cd ..;
	cd logicaDelServidor; make logicaDelServidor;
	make DemandAttendant.o MessageSender.o UserConnection.o; mv DemandAttendant.o MessageSender.o UserConnection.o conexion;
	make Server.o main.o;
	g++ -O2 -g3 -o  server  ./../common/utils/*.o ./../common/network/*.o  ./../estructurasDeDatos/*.o  ./../common/logger/*.o  ./../common/threads/*.o  ../common/game/*.o  ./conexion/*.o  ./../common/*.o logicaDelServidor/Animation/*.o  logicaDelServidor/Character/*.o logicaDelServidor/Collision/*.o logicaDelServidor/GameRelated/*.o config/stage/*.o Server.o main.o -lpthread -pthread -lSDL2 -lSDL2_image -lSDL2_ttf `pkg-config --libs libxml++-2.6`

main.o: Server.h main.cpp 
	g++ -c main.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`

Server.o: config/stage/Stage.h  config/stage/StageFile.h  ../common/network/Communication.h ../common/utils/Constants.h ../common/threads/Thread.h ../common/UserIdProvider.h conexion/UserConnection.h Server.cpp 
	g++ -c Server.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`


DemandAttendant.o: ../estructurasDeDatos/MessageList.h ../estructurasDeDatos/DemandHandler.h ../common/threads/Thread.h conexion/DemandAttendant.h conexion/DemandAttendant.cpp
	g++ -c conexion/DemandAttendant.cpp -std=c++98

MessageSender.o: ../estructurasDeDatos/OutcomingMessages.h ../common/threads/Thread.h ../common/utils/Constants.h ../common/network/Communication.h conexion/MessageSender.h conexion/MessageSender.cpp
	g++ -c conexion/MessageSender.cpp -std=c++98

UserConnection.o: ../common/threads/Thread.h conexion/MessageSender.h conexion/DemandAttendant.h conexion/UserConnection.h conexion/UserConnection.cpp
	 g++ -c conexion/UserConnection.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`

clean:
	rm -f server *.o
	rm -f conexion/*.o
	cd logicaDelServidor; make clean;

