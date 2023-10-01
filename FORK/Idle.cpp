/*
 * Idle.cpp
 *
 *  Created on: Jun 8, 2021
 *      Author: OS1
 */

#include "Idle.h"
extern int syncPrintf(const char *format, ...);
Idle::Idle(StackSize stackSize, Time timeSlice):Thread(stackSize,timeSlice) {
end=0;
	// TODO Auto-generated constructor stub

}

void Idle::run(){
	//cout<<"usao";
	while(1){
	}

}
Idle::~Idle() {

}

Thread* Idle::clone() const {
	return 0;
}
