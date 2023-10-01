/*
 * core.h
 *
 *  Created on: May 13, 2021
 *      Author: OS1
 */

#ifndef CORE_H_
#define CORE_H_

#include "thread.h"
#include "pcb.h"
#include "KerSem.h"
#include "Semaphor.h"
class PCB;
class core{
public:
		friend class Semaphore;
		friend class PCB;
		friend class Thread;
	    friend void interrupt timer();
		static void inic();
		static void restore();
		static void start(PCB* kontekst);
		static int userMain(int argc,char* argv[]);
		static void disp();
		static Semaphore* s;

};


#endif /* CORE_H_ */
