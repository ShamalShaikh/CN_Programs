#include"Header1.h"
#include<iostream>
struct mesg {
	long mtype;
	char mdata[100];
};
using namespace std;

	key_t msg_key = ftok("shamal0.txt",65);
	int msqid = msgget(msg_key,0666|IPC_CREAT);
	
	mesg message, idof_C3,msg;

void *writes(void* arg){
	msg.mtype = 3;
	cin>>msg.mdata;
	msgsnd(msqid,&msg,sizeof(msg),0);
   	return NULL;
}

void *reads(void *arg){
	msgrcv(msqid,&msg,sizeof(msg),3,0);
	return NULL;
}

struct msqid_ds qbuf;
int main() {

	idof_C3.mtype = 3;
	strcpy(idof_C3.mdata,"Assalamualaikum");
	
	msgsnd(msqid,&idof_C3,sizeof(idof_C3),0);
		cout<<"Hello sent\n";
	pthread_t reader,writer;
	while(1){
		pthread_create(&reader,NULL,reads,NULL);
		pthread_create(&writer,NULL,writes,NULL);
		pthread_join(reader,NULL);
		pthread_join(writer,NULL);
	}
/*
	message[0].mtype = pidof_P2;	
	message[1].mtype = pidof_P3;	
	
	msgsnd(msqid,&message[0],sizeof(message[0]),0);
	msgsnd(msqid,&message[0],sizeof(message[0]),0);
*/		
//	msgctl(msqid,IPC_RMID,0);
	return 0;
}
