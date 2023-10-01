/*
 * event.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#include"event.h"
#include"KerEv.h"
Event::Event (IVTNo ivtNo){
	myImpl=new KernelEv(ivtNo);

}
Event::~Event (){
	delete myImpl;
}
void Event::wait (){
	myImpl->wait();
}
void Event::signal(){
	myImpl->signal();
}
