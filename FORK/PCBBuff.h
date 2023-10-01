#ifndef PCBBUFF_H_
#define PCBBUFF_H_
#include "PCB.H"
#include<iostream.h>

class PCB;
typedef struct pcbBuffer{
   void* data;
   int ID;
   struct pcbBuffer *next;
   struct pcbBuffer *prev;
   pcbBuffer(PCB* nod,int ID){
	   this->data=nod;
	   this->ID=ID;
	   this->next=NULL;
	   this->prev=NULL;
   }
}pcbBuffer;
class PCBBuff{
	private: unsigned int broj;
public:
	pcbBuffer* p;
	PCBBuff();
	int br();
	virtual ~PCBBuff();
	void put(PCB* nod,int ID);
	PCB* get(int ID);
	PCB* remove(int ID);
	PCB* pop();
	void write();
};

#endif /* PCBBUFF_H_ */
