/*
 * KernelEv.h
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#include "event.h"
#include "PCBBuff.h"
#include"IVTEntry.h"
#ifndef KEREV_H_
#define KEREV_H_

class KernelEv {
public:
	KernelEv(IVTNo ivtno);
	virtual ~KernelEv();

		friend class wBuff;
		void wait();
		void signal();
		static void tickev();
		int getVal();
		static void add(KernelEv* k);
private:
		int flag;
		PCB* owner;
		PCB* blockedBuff;

};

#endif /* KERNELEV_H_ */
