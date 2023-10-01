/*
 * IVTEntry.h
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
typedef unsigned char IVTNo;
#include"KerEv.h"
#include<dos.h>
#define PREPAREENTRY(numEntry, callOld1)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
newEntry##numEntry.signal();\
if (callOld1 == 1)\
newEntry##numEntry.callOld();\
}

typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:
	IVTEntry(IVTNo numEntry,pInterrupt interruptRoutine);
	virtual ~IVTEntry();
	void signal();
	static IVTEntry* getIVT(IVTNo ivtNo);
	void callOld();
	void setSem(const KernelEv*& sem) {
		this->sem = (KernelEv*)sem;
	}

private:
	IVTNo numentry;
	pInterrupt oldRout;
	static IVTEntry *table[256];
	KernelEv* sem;
};

#endif /* IVTENTRY_H_ */
