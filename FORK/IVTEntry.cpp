/*
 * IVTEntry.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#include "IVTEntry.h"
IVTEntry* IVTEntry::table[256];
IVTEntry::IVTEntry(IVTNo numEntry,pInterrupt interruptRoutine) {
	numentry=numEntry;
#ifndef BCC_BLOCK_IGNORE
 oldRout = getvect(numEntry);
 setvect(numEntry, interruptRoutine);
#endif
 table[numEntry]=this;

}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	setvect(numentry,oldRout);
	table[numentry]=0;
#endif
}

void IVTEntry::signal(){
	sem->signal();
}
 IVTEntry* IVTEntry::getIVT(IVTNo ivtNo){
	 return table[ivtNo];
 }
 void IVTEntry::callOld(){
	 oldRout();
 }
