/*
 * ReloadReady.h
 *
 *  Created on: 02/01/2014
 *      Author: guido
 */

#ifndef RELOADREADY_H_
#define RELOADREADY_H_

class ReloadReady{
public:
	bool finishedRealoading;
	ReloadReady();
	virtual ~ReloadReady();
	void reloadFinished(){ finishedRealoading=true;}
	void startingReload(){ finishedRealoading=false;}
	bool finished(){ return finishedRealoading;}
};


#endif /* RELOADREADY_H_ */
