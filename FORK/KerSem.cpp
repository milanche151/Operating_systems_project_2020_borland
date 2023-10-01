/*
 * KerSem.cpp
 *
 *  Created on: Jun 9, 2021
 *      Author: OS1
 */
//

#include "KerSem.h"
#include "Idle.h"
semLista* KernelSem::lista=0;
semLista* KernelSem::krajs=0;
extern Idle* idlThr;
KernelSem::KernelSem(int init) {

	val=init;
	blockedBuff=new wBuff();
	semLista* pom=new semLista(this);
	if(lista==0){
		lista=pom;
		krajs=lista;
	}else{
		krajs->next=pom;
		krajs=krajs->next;
	}
}

int KernelSem::wait(Time maxTimeToWait){

	--val;
      if(val<0){
    	  PCB::running->setThreadState(BLOCKED);
    	  this->blockedBuff->add(PCB::running,maxTimeToWait);
    	  dispatch();
    	  return PCB::running->n_timeout;
      }
      return 1;

}
void  KernelSem::signal(){

	++val;
	if(val<=0){
		if(this->blockedBuff->bafer!=0){
			PCB* tmp=this->blockedBuff->pop();
			if(tmp!=0){
				tmp->setThreadState(READY);
				tmp->n_timeout=1;
				Scheduler::put(tmp);
			}
		}
	}

}
KernelSem::~KernelSem() {
	delete blockedBuff;
	semLista* s;
	semLista* prev=new semLista(0);
	prev->next=s;
	for( s=lista;!s;prev=prev->next){
		if(s->data==this){
			prev->next=s->next;
			semLista* tmp=s;
			s=s->next;
			delete tmp;
		}
	}
}
int KernelSem::getVal(){
 return val;
}
void KernelSem::add(KernelSem* k){
	semLista *tmp=new semLista(k),*bi;
	if(lista==0){
		lista=tmp;
		krajs=lista;
	}
	else{
		krajs->next=tmp;
		krajs=krajs->next;
	}

}
void KernelSem::ticksem(){
	wBuff* bi;
	wbuff* tmp;
	semLista *l;
	PCB* pom;
	for(l=lista;l!=0;l=l->next){
		bi=l->data->blockedBuff;
		bi->reset();

		while((tmp=bi->temp())!=0){
			if(tmp->tmpTime>0)--tmp->tmpTime;
			//cout<<tmp->data->getID()<<" "<<tmp->tmpTime<<" "<<Thread::getRunningId()<<" "<<idlThr->getId()<<endl;
			if(tmp->maxTime!=0 && tmp->tmpTime==0){
				pom=bi->remtemp();
			if(pom!=0){
				pom->setThreadState(READY);
				pom->n_timeout=0;
				l->data->val++;
				Scheduler::put(pom);
			}
			}
			else{
				bi->next();
			}
		}
	}



}

