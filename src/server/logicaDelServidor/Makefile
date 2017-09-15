logicaDelServidor:
	make Animation.o AnimationsRequest.o SingleShot.o RocketShot.o CannonShot.o FlameShot.o EnemyChaser.o ZombieShot.o EyeLaser.o BigEyeBomb.o Bonus.o BonusAmmo.o SingleShotAmmo.o FlameAmmo.o RocketAmmo.o  BonusHeal.o BonusKillAll.o Weapons.o ; mv Animation.o CannonShot.o AnimationsRequest.o SingleShot.o RocketShot.o FlameShot.o EnemyChaser.o ZombieShot.o EyeLaser.o BigEyeBomb.o Bonus.o BonusAmmo.o SingleShotAmmo.o FlameAmmo.o RocketAmmo.o  BonusKillAll.o BonusHeal.o Weapons.o Animation;
	make Character.o CharactersRequest.o EnemyCharacter.o MainCharacter.o MeleeEnemy.o UfoEnemy.o RangeEnemy.o TankEnemy.o BigEyes.o; mv Character.o  CharactersRequest.o EnemyCharacter.o MainCharacter.o MeleeEnemy.o  UfoEnemy.o  RangeEnemy.o TankEnemy.o BigEyes.o Character;
	make Collisionable.o CollisionBox.o CollisionMap.o CollisionFigure.o CollisionElipse.o CollisionRectangle.o GroundFloor.o; mv Collisionable.o CollisionBox.o CollisionMap.o CollisionFigure.o CollisionElipse.o CollisionRectangle.o GroundFloor.o Collision ;
	make Broadcaster.o GameController.o CharacterMap.o GameManager.o Parallax.o ReloadReady.o ; mv Broadcaster.o GameController.o CharacterMap.o GameManager.o Parallax.o ReloadReady.o GameRelated;


Animation.o: Animation/Animation.h Animation/Animation.cpp
	g++ -c -O2 Animation/Animation.cpp -std=c++98

AnimationsRequest.o: Animation/AnimationsRequest.h Animation/AnimationsRequest.cpp
	g++ -c  -O2 Animation/AnimationsRequest.cpp -std=c++98

Broadcaster.o: GameRelated/ReloadReady.h GameRelated/Broadcaster.h GameRelated/Broadcaster.cpp
	g++ -c  -O2 GameRelated/Broadcaster.cpp -std=c++98

Character.o: GameRelated/GameController.h Character/Character.h Character/Character.cpp
	g++ -c  -O2 Character/Character.cpp -std=c++98

CharactersRequest.o: Character/CharactersRequest.h Character/CharactersRequest.cpp
	g++ -c  -O2 Character/CharactersRequest.cpp -std=c++98

Collisionable.o: Collision/CollisionBox.h Collision/CollisionMap.h Collision/Collisionable.h Collision/Collisionable.cpp
	g++ -c  -O2 Collision/Collisionable.cpp -std=c++98

GroundFloor.o: Collision/CollisionBox.h Collision/CollisionMap.h Collision/GroundFloor.h Collision/GroundFloor.cpp
	g++ -c  -O2 Collision/GroundFloor.cpp -std=c++98

CollisionFigure.o: Collision/CollisionFigure.h Collision/CollisionFigure.cpp
	g++ -c  -O2 Collision/CollisionFigure.cpp -std=c++98

CollisionRectangle.o: Collision/CollisionRectangle.h Collision/CollisionRectangle.cpp
	g++ -c  -O2 Collision/CollisionRectangle.cpp -std=c++98

CollisionElipse.o: Collision/CollisionElipse.h Collision/CollisionElipse.cpp
	g++ -c  -O2 Collision/CollisionElipse.cpp -std=c++98

CollisionBox.o: Collision/CollisionBox.h Collision/CollisionBox.cpp
	g++ -c  -O2 Collision/CollisionBox.cpp -std=c++98

CollisionMap.o: Collision/Collisionable.h Collision/CollisionMap.h Collision/CollisionMap.cpp
	g++ -c  -O2 Collision/CollisionMap.cpp -std=c++98

EnemyCharacter.o: Character/Character.h Character/EnemyCharacter.h Character/EnemyCharacter.cpp
	g++ -c  -O2 Character/EnemyCharacter.cpp -std=c++98

GameController.o: GameRelated/GameController.h GameRelated/GameController.cpp
	g++ -c  -O2 GameRelated/GameController.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`

UfoEnemy.o: GameRelated/GameManager.h Character/EnemyCharacter.h Character/UfoEnemy.h Character/UfoEnemy.cpp
	g++ -c  -O2 Character/UfoEnemy.cpp -std=c++98

TankEnemy.o: GameRelated/GameManager.h Character/EnemyCharacter.h Character/TankEnemy.h Character/TankEnemy.cpp
	g++ -c  -O2 Character/TankEnemy.cpp -std=c++98

BigEyes.o: GameRelated/GameManager.h Character/EnemyCharacter.h Character/BigEyes.h Character/BigEyes.cpp
	g++ -c  -O2 Character/BigEyes.cpp -std=c++98

CharacterMap.o: GameRelated/CharacterMap.h GameRelated/CharacterMap.cpp
	g++ -c  -O2 GameRelated/CharacterMap.cpp -std=c++98

GameManager.o: Character/CharactersRequest.h  ../config/stage/Stage.h  GameRelated/ReloadReady.h ../config/stage/Window.h  GameRelated/GameManager.h GameRelated/GameManager.cpp
	g++ -c  -O2 GameRelated/GameManager.cpp -std=c++98 `pkg-config --cflags libxml++-2.6`

MainCharacter.o: Character/Character.h Character/MainCharacter.h Character/MainCharacter.cpp
	g++ -c  -O2 Character/MainCharacter.cpp -std=c++98

MeleeEnemy.o: Character/EnemyCharacter.h Character/MeleeEnemy.h Character/MeleeEnemy.cpp
	g++ -c  -O2 Character/MeleeEnemy.cpp -std=c++98

Parallax.o: GameRelated/Parallax.h GameRelated/Parallax.cpp
	g++ -c  -O2 GameRelated/Parallax.cpp -std=c++98

RangeEnemy.o: Character/EnemyCharacter.h Character/RangeEnemy.h Character/RangeEnemy.cpp
	g++ -c  -O2 Character/RangeEnemy.cpp -std=c++98

ReloadReady.o: GameRelated/ReloadReady.h GameRelated/ReloadReady.cpp
	g++ -c  -O2 GameRelated/ReloadReady.cpp -std=c++98

CannonShot.o: Animation/Animation.h GameRelated/Parallax.h Animation/CannonShot.h Animation/CannonShot.cpp 
	g++ -c  -O2 Animation/CannonShot.cpp -std=c++98

EyeLaser.o: Animation/Animation.h GameRelated/Parallax.h Animation/EyeLaser.h Animation/EyeLaser.cpp 
	g++ -c  -O2 Animation/EyeLaser.cpp -std=c++98

BigEyeBomb.o: Animation/Animation.h GameRelated/Parallax.h Animation/BigEyeBomb.h Animation/BigEyeBomb.cpp 
	g++ -c  -O2 Animation/BigEyeBomb.cpp -std=c++98

SingleShot.o: Animation/Animation.h GameRelated/Parallax.h Animation/SingleShot.h Animation/SingleShot.cpp 
	g++ -c  -O2 Animation/SingleShot.cpp -std=c++98

RocketShot.o: Animation/Animation.h GameRelated/Parallax.h Animation/RocketShot.h Animation/RocketShot.cpp 
	g++ -c  -O2 Animation/RocketShot.cpp -std=c++98

FlameShot.o: Animation/Animation.h GameRelated/Parallax.h Animation/FlameShot.h Animation/FlameShot.cpp 
	g++ -c  -O2 Animation/FlameShot.cpp -std=c++98

EnemyChaser.o: Animation/Animation.h GameRelated/Parallax.h Animation/EnemyChaser.h Animation/EnemyChaser.cpp 
	g++ -c  -O2 Animation/EnemyChaser.cpp -std=c++98

ZombieShot.o: Animation/Animation.h GameRelated/Parallax.h Animation/ZombieShot.h Animation/ZombieShot.cpp 
	g++ -c  -O2 Animation/ZombieShot.cpp -std=c++98

Bonus.o: Animation/Bonus.h GameRelated/Parallax.h Animation/Bonus.h Animation/Bonus.cpp 
	g++ -c  -O2 Animation/Bonus.cpp -std=c++98

BonusAmmo.o: Animation/Bonus.h GameRelated/Parallax.h Animation/BonusAmmo.h Animation/BonusAmmo.cpp 
	g++ -c  -O2 Animation/BonusAmmo.cpp -std=c++98

SingleShotAmmo.o: Animation/BonusAmmo.h GameRelated/Parallax.h Animation/SingleShotAmmo.h Animation/SingleShotAmmo.cpp 
	g++ -c  -O2 Animation/SingleShotAmmo.cpp -std=c++98

FlameAmmo.o: Animation/BonusAmmo.h GameRelated/Parallax.h Animation/FlameAmmo.h Animation/FlameAmmo.cpp 
	g++ -c  -O2 Animation/FlameAmmo.cpp -std=c++98

RocketAmmo.o: Animation/BonusAmmo.h GameRelated/Parallax.h Animation/RocketAmmo.h Animation/RocketAmmo.cpp 
	g++ -c  -O2 Animation/RocketAmmo.cpp -std=c++98

BonusKillAll.o: Animation/BonusKillAll.h GameRelated/Parallax.h Animation/BonusKillAll.h Animation/BonusKillAll.cpp 
	g++ -c  -O2 Animation/BonusKillAll.cpp -std=c++98

BonusHeal.o: Animation/BonusHeal.h Animation/BonusHeal.cpp 
	g++ -c  -O2 Animation/BonusHeal.cpp -std=c++98


Weapons.o: Animation/Weapons.h Animation/Weapons.cpp
	g++ -c  -O2 Animation/Weapons.cpp -std=c++98

clean:
	rm -f *.o
	rm -f Animation/*.o
	rm -f Character/*.o
	rm -f Collision/*.o
	rm -f GameRelated/*.o
