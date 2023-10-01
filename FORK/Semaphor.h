/*
 * Semaphore.h
 *
 *  Created on: May 19, 2021
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
#include "thread.h"
#include "core.h"
#include "KerSem.h"
class KernelSem;
class Semaphore {
		public:
		Semaphore (int init=1);
		virtual ~Semaphore ();
		virtual int wait (unsigned int maxTimeToWait);
		virtual void signal();
		int val () const; // Returns the current value of the semaphore

		private: KernelSem* myImpl;
};


#endif /* SEMAPHOR_H_ */
