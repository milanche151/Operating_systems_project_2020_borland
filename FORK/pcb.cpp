#include"pcb.h"
#include<dos.h>
#include"Idle.h"
#include "userthr.h"
PCBBuff* PCB::proc=new PCBBuff();
PCB* mainPCB=new PCB(0);
Idle* idlThr=new Idle(1024,1);
ID creatorID=0;
PCB* PCB::running=mainPCB;
PCB* newStack;
//extern user_thread* ut;
int PCB::nextID=-1;
PCB::PCB(StackSize stackSize,Time timeSlice,Thread* t){

	 	forkChildren=new PCBBuff();
		myID=++nextID;
		parent=0;
        this->myThread=t;
        this->kvant=timeSlice;
    	this->n_timeout=1;
    	this->blokirane=new PCBBuff();
    	stackSize /= sizeof(unsigned);
    	stSize=stackSize;
    	PCB::createThread(this,stackSize,wrapper);

}
PCB::PCB(int timeSlice){
			parent=0;
			forkChildren=new PCBBuff();
			myID=++nextID;
			this->myThread=0;
			this->thread_state=CREATED;
			PCB::proc->put(this,myID);
			if(timeSlice<0){
				this->kvant=-1;
			}else {this->kvant=timeSlice;}
			this->stack=0;

}
void PCB::createThread(PCB* newPCB,StackSize stackSize,volatile void (*body)()){
	newPCB->stack=new unsigned[stackSize];

	#ifndef BCC_BLOCK_IGNORE
	 	 	newPCB->stack[stackSize-1]=0x200;
			newPCB->stack[stackSize-2]=FP_SEG(body);
			newPCB-> stack[stackSize-3]=FP_OFF(body);

			newPCB->sp = FP_OFF(newPCB->stack+stackSize-12);
			newPCB->ss = FP_SEG(newPCB->stack+stackSize-12);
			newPCB->bp = FP_OFF(newPCB->stack+stackSize-12);
	#endif
}
void PCB::exitThread(){



	 	lockFlag=0;
	 	running->thread_state=TERMINATED;
	 	while(running->blokirane->br()){

	 	     PCB* tmp=running->blokirane->pop();

	 	     tmp->thread_state=READY;
	 	     Scheduler::put(tmp);

	 	}
	    lockFlag=1;
	    dispatch();


}
volatile void PCB::wrapper(){
                if(running->thread_state!=TERMINATED){

                	PCB::running->myThread->run();
                	running->thread_state=TERMINATED;
                    lockFlag=0;
                    while(running->blokirane->br()){
                    	PCB* tmp=running->blokirane->pop();
                    	tmp->thread_state=READY;
                    	Scheduler::put(tmp);

                    }

                    lockFlag=1;
                    dispatch();
                }



}
PCB::~PCB(){
	if(stack!=NULL)
	delete[] stack;

	if(proc!=NULL)
	proc->remove(this->myID);
}

Thread* PCB::clone() {
	return 0;
}

void interrupt PCB::copy_stack() {
	unsigned tss,tsp,tbp;
	asm{
		mov tsp,sp
		mov tss,ss
		mov tbp,bp
	}
	for(int i=0;i<running->stSize;i++){
		newStack->stack[i]=running->stack[i];
	}
	newStack->sp=tsp+(unsigned)FP_OFF((unsigned long)(newStack->stack))-(unsigned)FP_OFF((unsigned long)(running->stack));
	newStack->ss=FP_SEG(newStack->stack);
	newStack->bp=tbp+(unsigned)(FP_OFF((unsigned long)newStack->stack)-(unsigned)FP_OFF((unsigned long)running->stack));
	for(unsigned ibp=tbp;ibp!=0;){
		unsigned* pom=(unsigned*)MK_FP(tss,ibp);
		unsigned i=pom-running->stack;
		ibp=running->stack[i];
		newStack->stack[i]=ibp+(FP_OFF(newStack->stack)-FP_OFF(running->stack));
	}
}

void PCB::wtffc() {
	while(running->forkChildren->br()){
	PCB*	tmp=running->forkChildren->pop();
	tmp->myThread->waitToComplete();
	}

}

ID PCB::fork() {
	creatorID=running->myID;
	Thread* t=running->myThread->clone();
	if(t==0)
		return -1;
	newStack=t->myPCB;
	newStack->parent=running;
	PCB::copy_stack();
	running->forkChildren->put(t->myPCB,t->getId());
	t->start();
	if(creatorID!=running->myID){
		return 0;
	}else{
		return running->myID;
	}
}
