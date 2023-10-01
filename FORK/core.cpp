#include "core.h"
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include"Idle.h"
unsigned oldTimerOFF, oldTimerSEG;
unsigned tsp;
unsigned tss;
unsigned tbp;
volatile int brojac = 20;
volatile int zahtevana_promena_konteksta = 0;

Semaphore* core::s=new Semaphore();
extern Idle* idlThr;
/*void tick(){

}*/
extern void tick();
void core::disp(){
	    lock();
	    zahtevana_promena_konteksta = 1;
	    timer();
	    unlock();

}
void core::start(PCB* kontekst){
	lock();
	kontekst->thread_state=READY;
	Scheduler::put(kontekst);
	unlock();

}
extern PCB* mainPCB;
void interrupt timer(){
	if(!zahtevana_promena_konteksta){
		tick();
		KernelSem::ticksem();
		//lockFlag=1;
	}
	    PCB* pom;
		if (!zahtevana_promena_konteksta && (brojac>0) && PCB::running->kvant>0) brojac--;

		if ((brojac == 0 && PCB::running->kvant!=0) || zahtevana_promena_konteksta) {
			//cout<<Thread::getRunningId()<<endl;
		if(lockFlag){

			if(brojac==0)zahtevana_promena_konteksta=0;
			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp= tbp;
		//	cout<<PCB::running->getID()<<"->";
			if((PCB::running->thread_state!=BLOCKED && PCB::running->thread_state!=TERMINATED )&& PCB::running->myID!=idlThr->getId()){
				PCB::running->setThreadState(READY);
				Scheduler::put((PCB *) PCB::running);
			}
			pom=Scheduler::get();
			if(pom==0){
				pom=PCB::proc->get(idlThr->getId());

				if(pom!=0){
					PCB::running=pom;
				}
			}else{
			PCB::running=pom;
			brojac=PCB::running->kvant;

			}
			PCB::running->thread_state=RUNNING;
			//cout<<PCB::running->getID()<<endl;
			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			asm {
				mov sp, tsp   // restore sp
				mov ss, tss    // restore ss
				mov bp,tbp  // restore bp
			}

		 }else{
			 zahtevana_promena_konteksta=1;
		 }
	}

		// poziv stare prekidne rutine koja se
	     // nalazila na 08h, a sad je na 60h
	     // poziva se samo kada nije zahtevana promena
	     // konteksta – tako se da se stara
	     // rutina poziva samo kada je stvarno doslo do prekida
		//cout<<"Ovde\n";
	if(!zahtevana_promena_konteksta) {
		asm int 60h;

	}
	zahtevana_promena_konteksta = 0;



}
/*void interrupt tmr(){
	core::timer();
}*/
void core::inic(){
	asm{
			cli
			push es
			push ax

			mov ax,0   //  ; inicijalizuje rutinu za tajmer
			mov es,ax

			mov ax, word ptr es:0022h //; pamti staru rutinu
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			mov word ptr es:0022h, seg timer	 //postavlja
			mov word ptr es:0020h, offset timer //novu rutinu


			mov ax, oldTimerSEG	 //	postavlja staru rutinu
			mov word ptr es:0182h, ax //; na int 60h
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}

}
void core::restore(){
	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax


			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}
}

