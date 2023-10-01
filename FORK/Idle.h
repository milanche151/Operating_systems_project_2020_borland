/*
 * Idle.h
 *
 *  Created on: Jun 8, 2021
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"

class Idle: public Thread{
private:
	int end;
public:
	Idle(unsigned long stackSize, unsigned int timeSlice);
	virtual ~Idle();
	void run();
	Thread* clone() const;
};

#endif /* IDLE_H_ */
