/*
 * wBuff.cpp
 *
 *  Created on: Jun 9, 2021
 *      Author: OS1
 */

#include "wBuff.h"

wBuff::wBuff() {
	bafer=0;
	poc=new wbuff();
	poc->next=bafer;
	prev=poc;
	tempr=bafer;
	kraj=0;
}

wBuff::~wBuff() {
	wbuff* bi,*tmp;
		for(bi=bafer;bi!=0;){
			tmp=bi;
			bi=bi->next;
			delete tmp;
	}
}

void wBuff::add(PCB* proc,Time time){
	wbuff* tmp=new wbuff(proc,time);
	wbuff* bi;
	if(bafer==0){
		bafer=tmp;
		tempr=tmp;
		kraj=tmp;
	}else{
		kraj->next=tmp;
		kraj=kraj->next;
	}

}


PCB* wBuff::find(int id){
	wbuff* bi;
	for(bi=bafer;bi!=0;bi=bi->next){
		if(bi->data->getID()==id){
			return bi->data;
		}
	}
	return 0;
}

PCB* wBuff::remove(int id){
	wbuff* bi,*tmp,*prev;
	for(bi=bafer,prev->next=bi;bi!=0;bi=bi->next,prev=prev->next){
			if(bi->data->getID()==id){
				tmp=bi;
				prev->next=bi->next;
				break;
			}
	}
		return tmp->data;
}
PCB* wBuff::pop(){
	wbuff *tmp;
	PCB* pom;
	tmp=bafer;
	if(bafer!=0){
		bafer=bafer->next;
		pom=tmp->data;
		delete tmp;
	}
    return pom;
}

wbuff* & wBuff::temp() {
	return tempr;

}

void wBuff::next() {
	if(tempr!=0 && bafer!=0){
		tempr=tempr->next;
		prev=prev->next;
	}

}

void wBuff::reset() {
	tempr=bafer;
	prev=poc;
	prev->next=tempr;
}

PCB* wBuff::remtemp() {
	PCB* pom;
	if(bafer!=0){
		if(tempr==bafer){
			//cout<<"Ovde2"<<endl;
			if(kraj==bafer){
				kraj=0;
			}
			wbuff *tmp1;
			prev->next=tempr->next;
			pom=tempr->data;
			bafer=bafer->next;
			tmp1=tempr;
			tempr=tempr->next;

			delete tmp1;
			return pom;
		}else if(tempr==kraj){
			//cout<<"Ovde3"<<endl;
			wbuff *tmp1;
			prev->next=0;
			pom=tempr->data;
			kraj=prev;
			tmp1=tempr;
			delete tmp1;
			return pom;
		}else{
			//cout<<"Ovde4"<<endl;
			wbuff *tmp1;
			prev->next=tempr->next;
			pom=tempr->data;
			tmp1=tempr;
			tempr=tempr->next;
			delete tmp1;
			return pom;
		}
	}
	return NULL;
}

void wBuff::write() {
	for(wbuff* tmp=bafer;tmp!=NULL;tmp=tmp->next){
		cout<<tmp->data->getID()<<" "<<tmp->tmpTime<<"|";
	}
	cout<<endl;
}
