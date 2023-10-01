/*
 * userthread.h
 *
 *  Created on: Jul 27, 2021
 *      Author: OS1
 */

#ifndef USERTHR_H_
#define USERTHR_H_

#include "thread.h"

class user_thread: public Thread {
private:
	int argc;
	char **argv;
public:
	user_thread(int argc,char *argv[]);
	virtual ~user_thread();
	void run() ;
	Thread* clone() const;
};

#endif /* USERTHR_H_ */
