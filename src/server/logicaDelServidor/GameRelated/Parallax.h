/*
 * Parallax.h
 *
 *  Created on: Oct 2, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_PARALLAX_H_
#define SRC_SERVER_LOGICADELSERVIDOR_PARALLAX_H_

#include <string>
#include <iostream>
#include <sstream>
#include "../../../common/utils/Constants.h"

namespace std {

class Parallax {
public:
	Parallax();
	int getPosition();
	void startMinMax();
	void processPosition(int);
	void resetParallax();
	void endMinMax();
	virtual ~Parallax();

	int position;
	int min;
	int max;
	int anchoPantalla;
};

} /* namespace std */

#endif /* SRC_SERVER_LOGICADELSERVIDOR_PARALLAX_H_ */
