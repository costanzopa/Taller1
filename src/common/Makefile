common:  
	make XmlFactory.o XmlElement.o XmlFile.o Utils.o; mv XmlFactory.o XmlElement.o XmlFile.o Utils.o utils;
	make utils/Exception.o network/Socket.o  ../estructurasDeDatos/User.o network/Communication.o threads/Thread.o logger/FileAppender.o logger/Logger.o UserIdProvider.o game/LTexture.o game/GameImage.o game/AnimationImage.o game/SingleShotImage.o game/TankCannonImage.o game/SingleShotAmmoImage.o game/HealBonus.o game/KillBonusImage.o game/FlameShotImage.o game/ZombieShotImage.o game/RocketLauncherImage.o game/RocketAmmoImage.o game/FlameAmmoImage.o game/CharacterImage.o game/RangeEnemyImage.o game/MeleeEnemyImage.o  game/UfoEnemyImage.o game/EyesEnemyImage.o  game/EnemyImage.o game/BigEyesLaserImage.o game/BigEyesBombImage.o game/BossImage.o game/TankEnemyImage.o game/BackgroundImage.o utils/Tokenizer.o
		 
	 
Thread.o: utils/Exception.h  threads/Thread.h  threads/Thread.cpp
	g++ -c threads/Thread.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98

Communication.o: utils/Exception.h network/Socket.h ../estructurasDeDatos/User.h
	g++ -c network/Communication.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98


Socket.o: utils/Exception.h network/Socket.h network/Socket.cpp
	g++ -c network/Socket.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

Exception.o: utils/Exception.h utils/Exception.cpp
	g++ -c utils/Exception.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

Tokenizer.o: utils/Tokenizer.h utils/Tokenizer.cpp
	g++ -c utils/Tokenizer.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

FileAppender.o: logger/FileAppender.h logger/FileAppender.cpp
		g++ -c utils/FileAppender.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

LTexture.o: game/LTexture.h game/LTexture.cpp
		g++ -c game/LTexture.cpp -O0 -g3 -lSDL2 -lSDL2_image -lSDL2_ttf -pedantic -Wall -Wextra -Wconversion -std=c++98

GameImage.o: game/GameImage.h game/GameImage.cpp
		g++ -c game/GameImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98


AnimationImage.o: game/AnimationImage.h game/AnimationImage.cpp 
		g++ -c game/AnimationImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

ZombieShotImage.o: game/ZombieShotImage.h game/ZombieShotImage.cpp 
		g++ -c game/ZombieShotImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

SingleShotImage.o: game/SingleShotImage.h game/SingleShotImage.cpp 
		g++ -c game/SingleShotImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

BigEyesBombImage.o: game/BigEyesBombImage.h game/BigEyesBombImage.cpp 
		g++ -c game/BigEyesBombImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

TankCannonImage.o: game/TankCannonImage.h game/TankCannonImage.cpp 
		g++ -c game/TankCannonImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98


SingleShotAmmoImage.o: game/SingleShotAmmoImage.h game/SingleShotAmmoImage.cpp 
		g++ -c game/SingleShotAmmoImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

KillBonusImage.o: game/KillBonusImage.h game/KillBonusImage.cpp 
		g++ -c game/KillBonusImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

HealBonus.o: game/HealBonus.h game/HealBonus.cpp 
		g++ -c game/HealBonus.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

BigEyesLaserImage.o: game/BigEyesLaserImage.h game/BigEyesLaserImage.cpp 
		g++ -c game/BigEyesLaserImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

FlameShotImage.o: game/FlameShotImage.h game/FlameShotImage.cpp 
		g++ -c game/FlameShotImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

FlameAmmoImage.o: game/FlameAmmoImage.h game/FlameAmmoImage.cpp 
		g++ -c game/FlameAmmoImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

RocketLauncherImage.o: game/RocketLauncherImage.h game/RocketLauncherImage.cpp 
		g++ -c game/RocketLauncherImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

RocketAmmoImage.o: game/RocketAmmoImage.h game/RocketAmmoImage.cpp 
		g++ -c game/RocketAmmoImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

EnemyImage.o:  game/GameImage.h game/EnemyImage.h game/EnemyImage.cpp 
		g++ -c game/EnemyImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

BossImage.o:  game/GameImage.h game/BossImage.h game/BossImage.cpp 
		g++ -c game/BossImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

CharacterImage.o: game/CharacterImage.h game/GameImage.h game/CharacterImage.cpp 
		g++ -c game/CharacterImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

RangeEnemyImage.o: game/RangeEnemyImage.h game/GameImage.h game/RangeEnemyImage.cpp 
		g++ -c game/RangeEnemyImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

MeleeEnemyImage.o: game/EnemyImage.h  game/MeleeEnemyImage.h game/MeleeEnemyImage.cpp 
		g++ -c game/MeleeEnemyImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

UfoEnemyImage.o: game/BossImage.h  game/UfoEnemyImage.h game/UfoEnemyImage.cpp 
		g++ -c game/UfoEnemyImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

EyesEnemyImage.o: game/BossImage.h  game/EyesEnemyImage.h game/EyesEnemyImage.cpp 
		g++ -c game/EyesEnemyImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

TankEnemyImage.o: game/BossImage.h  game/TankEnemyImage.h game/TankEnemyImage.cpp 
		g++ -c game/TankEnemyImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98

BackgroundImage.o: game/BackgroundImage.h game/GameImage.h game/BackgroundImage.cpp 
		g++ -c game/BackgroundImage.cpp -O0 -g3 -lSDL2 -lSDL2_image -pedantic -Wall -Wextra -Wconversion -std=c++98



Logger.o: logger/FileAppender.h utils/Tokenizer.h logger/Logger.h logger/Logger.cpp
		g++ -c logger/Logger.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

UserIdProvider.o: logger/Logger.h utils/Tokenizer.h UserIdProvider.h UserIdProvider.cpp
		g++ -c UserIdProvider.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

XmlElement.o: utils/XmlElement.h utils/XmlElement.cpp
	g++ -c utils/XmlElement.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

XmlFactory.o: utils/XmlElement.h utils/XmlFactory.h utils/XmlFactory.cpp
	g++ -c utils/XmlFactory.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98

XmlFile.o:	utils/XmlFactory.h utils/XmlFile.h utils/XmlFile.cpp
	g++ -c utils/XmlFile.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98 `pkg-config --cflags libxml++-2.6`

Utils.o: utils/Utils.h  utils/Utils.cpp
	g++ -c utils/Utils.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion -std=c++98


clean:
	rm -f network/*.o
	rm -f utils/*.o
	rm -f threads/*.o
	rm -f logger/*.o
	rm -f game/*.o
	rm -f *.o
