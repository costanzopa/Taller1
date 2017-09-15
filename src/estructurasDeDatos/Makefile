Data:  User.o Node.o MessageList.o OutcomingMessages.o  Demand.o DemandHandler.o ClientGameStatus.o CharactersInGame.o AnimationsInGame.o
	 

User.o: User.h
	g++ -c User.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98


Node.o: User.h Node.h
	g++ -c Node.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98


Demand.o: OutcomingMessages.h User.h Demand.h Demand.cpp
	g++ -c Demand.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

DemandHandler.o: Demand.h DemandHandler.h DemandHandler.cpp
	g++ -c DemandHandler.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

CharactersInGame.o: ../server/logicaDelServidor/Character/Character.h CharactersInGame.h CharactersInGame.cpp
	g++ -c CharactersInGame.cpp -std=c++98

AnimationsInGame.o: AnimationsInGame.h AnimationsInGame.cpp
	g++ -c AnimationsInGame.cpp -std=c++98

MessageList.o: Node.h MessageList.h MessageList.cpp
	g++ -c MessageList.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

OutcomingMessages.o: Node.h OutcomingMessages.h OutcomingMessages.cpp
	g++ -c OutcomingMessages.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

ClientGameStatus.o: ../common/game/GameImage.h ../common/game/AnimationImage.h ../common/game/AnimationImage.h ClientGameStatus.h ClientGameStatus.cpp
	g++ -c ClientGameStatus.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98





clean:
	rm -f *.o
