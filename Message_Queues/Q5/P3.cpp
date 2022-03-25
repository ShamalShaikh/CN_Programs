#include"Header1.h"
#include<iostream>
struct mesg {
	long mtype;
	char mdata[100];
};
using namespace std;
struct msqid_ds qbuf;
int main() {
	key_t msg_key = ftok("afreen.txt",65);
	int msqid = msgget(msg_key,0666|IPC_CREAT);
	
	mesg message, pidof_P3;
	pidof_P3.mtype = 3;
//	msgsnd(msqid,&pidof_P2,sizeof(pidof_P2),0);
		sleep(2);
	msgrcv(msqid,&message,sizeof(message),pidof_P3.mtype,0);
//	msgrcv(msqid,&message,sizeof(message),pidof_P3.mtype,0);
	cout<<message.mdata;
/*
	message[0].mtype = pidof_P2;	
	message[1].mtype = pidof_P3;	
	
	msgsnd(msqid,&message[0],sizeof(message[0]),0);
	msgsnd(msqid,&message[0],sizeof(message[0]),0);
*/		
//	msgctl(msqid,IPC_RMID,0);
	return 0;
}
