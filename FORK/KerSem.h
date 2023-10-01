/*
 * KerSem.h
 *
 *  Created on: Jun 9, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_
#include "PCB.H"
#include"wBuff.h"
class KernelSem;
typedef struct semLista{
	KernelSem* data;
	struct semLista *next;
	semLista(KernelSem* sem){
		data=sem;
		next=0;
	//	prev=0;
	}

}semLista;
class KernelSem {
public:
	static semLista* lista;
	static semLista* krajs;
	friend class wBuff;
	KernelSem(int init=1);
	virtual ~KernelSem();
	int wait(unsigned int maxTimeToWait);
	void signal();
	static void ticksem();
	int getVal();
	static void add(KernelSem* k);

private:
	wBuff *blockedBuff;
	int val;
};

#endif /* KERSEM_H_ */
