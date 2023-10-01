/*
 * wBuff.h
 *
 *  Created on: Jun 9, 2021
 *      Author: OS1
 */

#ifndef WBUFF_H_
#define WBUFF_H_
#include "thread.h"
#include "PCB.h"
#include<iostream.h>
class PCB;
typedef struct wbuff{
			PCB* data;
			struct wbuff* next;
			int maxTime,tmpTime;

			wbuff(PCB* kon=NULL, unsigned int t=0){
				data=kon;
				next=NULL;
				maxTime=t;
				tmpTime=t;
			}
}wbuff;
class wBuff {
private:
	wbuff *bafer;
	wbuff *kraj;
	wbuff *tempr;
	wbuff *prev;
	wbuff *poc;
public:
	friend class KernelSem;
	wBuff();
	virtual ~wBuff();
	void add(PCB* proc,unsigned int time);
	PCB* find(int id);
	PCB* remove(int id);
	PCB* pop();
	wbuff* & temp();
	void next();
	void reset();
	PCB* remtemp();
	void write();
};

#endif /* WBUFF_H_ */
