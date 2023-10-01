#include "thread.h"
#include "core.h"
#include "PCBBuff.h"

volatile int lockFlag=1;

void dispatch(){
   core::disp();
}

void Thread::start(){
  lock();
  core::start(this->myPCB);
  unlock();

}

void Thread::waitToComplete(){

	lockFlag=0;
	 if(this->myPCB->thread_state!=TERMINATED){
		PCB::running->thread_state=BLOCKED;
		this->myPCB->blokirane->put(PCB::running,PCB::running->myID);
		lockFlag=1;
		dispatch();

	 }

}
Thread:: ~Thread(){

	waitToComplete();
	delete myPCB;



}
Thread::Thread (StackSize stackSize, Time timeSlice){
    lockFlag=0;
	this->myPCB=new PCB(stackSize,timeSlice,this);
	//if(PCB::proc==NULL)PCB::proc=new PCBBuff();
	PCB::proc->put(myPCB,myPCB->myID);
	lockFlag=1;

}
ID Thread::getRunningId(){
	return PCB::running->myID;
}
Thread* Thread::getThreadById(ID id){
	PCB *tmp=PCB::proc->get(id);
	return tmp->myThread;
}
ID Thread::getId(){
	return myPCB->myID;
}

Thread* Thread::clone() const {
	return myPCB->clone();
}

ID Thread::fork() {
	return PCB::fork();
}

void Thread::exit() {
	PCB::exitThread();
}

void Thread::waitForForkChildren() {
		PCB::wtffc();
}
