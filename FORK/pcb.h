/*
 * pcb.h
 *
 *  Created on: May 13, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "PCBBuff.h"
#include "core.h"
#include<iostream.h>
class Thread;
class PCBBuff;
typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef int ID;
enum state{
	CREATED,READY,BLOCKED,RUNNING,TERMINATED
};
//PCB* oldSt;
class PCB{
public:
	friend class Thread;
	friend class core;
private :

	static int nextID;
	int myID;
	Thread* myThread;
	unsigned int sp,ss,bp;
	int kvant;
    unsigned int* stack;
    unsigned stSize;
    state thread_state;
    PCB* parent;
 public:
    static PCBBuff* proc;
    unsigned int n_timeout;
    PCBBuff* blokirane;
    PCBBuff* forkChildren;
    Thread* clone();
    static PCB* running;
    friend void interrupt timer();
	static void createThread(PCB* newPCB,StackSize stackSize,volatile void (*body)());
	static void exitThread();
	static volatile void wrapper();
	static void interrupt copy_stack();
	static void wtffc();
	static ID fork();
	int getID(){
		return myID;
	}
	PCB(StackSize stackSize,Time timeSlice,Thread* t);
	PCB(int timeSlice);
	~PCB();

	const Thread*& getMyThread() const {
		return (const Thread*&)myThread;
	}

	state getThreadState() const {
		return thread_state;
	}

	void setThreadState(state threadState) {
		thread_state = threadState;
	}
};

#endif /* PCB_H_ */
