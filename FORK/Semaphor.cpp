/*
 * Semaphore.cpp
 *
 *  Created on: May 19, 2021
 *      Author: OS1
 */

#include "Semaphor.h"

Semaphore::Semaphore(int init) {
	myImpl=new KernelSem(init);

}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::wait (Time maxTimeToWait){
	 myImpl->wait(maxTimeToWait);
	 //return myImpl->getVal();
}
void Semaphore::signal(){
	myImpl->signal();
}
int Semaphore::val() const{
	return myImpl->getVal();
}
