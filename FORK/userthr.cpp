/*
 * userthread.cpp
 *
 *  Created on: Jul 27, 2021
 *      Author: OS1
 */

#include "userthr.h"
extern void userMain(int argc,char *argv[]);
extern PCB* mainPCB;
user_thread::user_thread(int argc,char *argv[]):Thread(){
	this->argc=argc;
	this->argv=argv;
}

user_thread::~user_thread() {

	waitToComplete();
}

void user_thread::run() {
	//cout<<"Usao";
	userMain(argc,argv);
	mainPCB->setThreadState(READY);
	Scheduler::put(mainPCB);

}

Thread* user_thread::clone() const {
	return new user_thread(argc,argv);
}
