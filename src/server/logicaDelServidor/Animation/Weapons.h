/*
 * Weapons.h
 *
 *  Created on: Nov 4, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_WEAPONS_H_
#define SRC_SERVER_LOGICADELSERVIDOR_WEAPONS_H_


#define NUMBER_OF_GUNS 4

class Weapons {
public:
	Weapons();
	virtual ~Weapons();
	void cycleNext();
	void cyclePrevious();
	bool shoot();
	bool hasAmmo();

	int getBulletsLeft();
	int getTotalBullets();

	int magazine[NUMBER_OF_GUNS] = {15,2,10,2};
	int bulletsLeft[NUMBER_OF_GUNS] = {15,2,10,2};
	int totalBullets[NUMBER_OF_GUNS] = {65,9,40,6};
	int currentWeapon;
};

#endif /* SRC_SERVER_LOGICADELSERVIDOR_WEAPONS_H_ */
