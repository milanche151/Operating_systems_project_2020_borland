#include<iostream.h>
#include<dos.h>
#include "core.h"
#include "userthr.h"
#include "idle.h"
#include<stdio.h>
//using namespace std;
extern int userMain(int argc,char *argv[]);
extern PCB* mainPCB;
extern Idle* idlThr;
user_thread* ut;
int main(int argc,char *argv[]){


	core::inic();
	ut=new user_thread(argc,argv);
	//userMain(argc,argv);
	ut->start();
	dispatch();
	delete ut;
	core::restore();
	return 0;


}
