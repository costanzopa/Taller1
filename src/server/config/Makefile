config: 
		make StageFile.o StageFactory.o; mv StageFile.o StageFactory.o stage;
	    make Background.o Sprite.o Stage.o Window.o; mv Background.o Sprite.o Stage.o Window.o stage;



StageFactory.o: ../../common/utils/XmlFactory.h stage/Background.h stage/Sprite.h stage/Window.h stage/StageFactory.h stage/StageFactory.cpp
	g++ -c stage/StageFactory.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`

StageFile.o: ../../common/utils/XmlFile.h stage/Stage.h ../../common/logger/Logger.h  stage/StageFile.h stage/StageFile.cpp
	 g++ -c stage/StageFile.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`


Stage.o:  stage/Window.h stage/Background.h stage/Sprite.h ../../common/utils/XmlElement.h stage/Stage.h stage/Stage.cpp
	g++ -c stage/Stage.cpp -O2 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config --cflags libxml++-2.6`

Window.o: ../../common/utils/XmlElement.h ../../common/utils/Utils.h stage/Window.h stage/Window.cpp
	g++ -c stage/Window.cpp -O2 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config --cflags libxml++-2.6`

Background.o: ../../common/utils/XmlElement.h ../../common/utils/Utils.h  stage/Background.h stage/Background.cpp
	g++ -c stage/Background.cpp -O2 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config --cflags libxml++-2.6`

Sprite.o: ../../common/utils/XmlElement.h ../../common/utils/Utils.h  stage/Sprite.h stage/Sprite.cpp
	g++ -c stage/Sprite.cpp -O2 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config --cflags libxml++-2.6`


clean:
	rm -f stage/*.o
