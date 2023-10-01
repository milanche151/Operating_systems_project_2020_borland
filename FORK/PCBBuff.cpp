#include "PCBBuff.h"


PCBBuff::PCBBuff() {
	  p=0;
	  broj=0;

}

PCBBuff::~PCBBuff() {
	pcbBuffer* tmp;
	for(pcbBuffer* pi=p;pi!=0;){
		tmp=pi;
		pi=pi->next;
		delete tmp;
	}
}
void PCBBuff::put(PCB* nod,int ID){

	pcbBuffer* nd=new pcbBuffer(nod,ID);
	if(this->p==0){
		p=nd;
		++broj;
	}else{

		pcbBuffer *tmp;
			tmp=p;
			while(tmp->next!=0){
				tmp=tmp->next;
			}
			tmp->next=nd;
			nd->prev=tmp;
			nd->next=0;
			++broj;

	}
	//cout<<broj<<endl;
}
PCB* PCBBuff::get(int ID){
	pcbBuffer *tmp;
	tmp=this->p;
	for(int i=0;i<broj;i++){
		if(tmp->ID==ID){
			return (PCB*)tmp->data;
		}
		tmp=tmp->next;
	}
	return 0;

}
PCB* PCBBuff::remove(int ID){
	pcbBuffer *tmp;
		tmp=this->p;
		while(tmp!=NULL){
			if(tmp->ID==ID){
				if(tmp->next!=0 && tmp->prev!=0){
					tmp->next->prev=tmp->prev;
					tmp->prev->next=tmp->next;
					--broj;
					break;
				}else if(tmp->next==0 && tmp->prev==0){
					p=0;
					break;
				}else if(tmp->prev==0){
					p=p->next;
					break;
				}else if(tmp->next==0){
					tmp->next=0;
					break;
				}

			}
			tmp=tmp->next;
		}
		return (PCB*)tmp->data;
}
PCB* PCBBuff::pop(){
	pcbBuffer* tmp=p;
	if(p==0) return NULL;
    p=p->next;
    --broj;
    return (PCB*)tmp->data;
}
int PCBBuff::br(){
	return this->broj;
}
void PCBBuff::write(){
pcbBuffer *tmp=p;
for(int i=0;i<broj;i++){
	cout<<tmp->ID<<" ";
	tmp=tmp->next;
}
cout<<endl;
}
