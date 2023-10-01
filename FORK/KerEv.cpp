/*
 * KernelEv.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#include "KerEv.h"

KernelEv::KernelEv(IVTNo ivtNo){
  flag=0;
  owner=PCB::running;
  blockedBuff=0;
  IVTEntry* tmp=IVTEntry::getIVT(ivtNo);
  tmp->setSem((const KernelEv* &)this);
}

KernelEv::~KernelEv() {
	delete blockedBuff;
	//delete owner;
}
void KernelEv::wait(){
	if(owner->getID()==PCB::running->getID()){
		if(flag==1){
			flag=0;
		}else if(flag==0){
			 owner->setThreadState(BLOCKED);
			 this->blockedBuff=owner;
			 dispatch();
		}
	}
}
void KernelEv::signal(){

	if(blockedBuff==0){
		flag=1;
	}else{
		//cout<<"Usao signal "<<blockedBuff->getID()<<" "<<owner->getID()<<endl;
		blockedBuff->setThreadState(READY);
		Scheduler::put(blockedBuff);
		blockedBuff=0;
	}

}

