#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<iostream>
#include<bits/stdc++.h>
struct mesg {
	long mtype;
	char mdata[100];
};
using namespace std;
struct msqid_ds qbuf;
int main() {
	key_t msg_key = ftok("shamal2.txt",65);
	int msqid = msgget(msg_key,0666|IPC_CREAT);
	
	mesg message, pidof_P3;
	pidof_P3.mtype = getpid();
	msgsnd(msqid,&pidof_P3,sizeof(pidof_P3),0);
	
	msgrcv(msqid,&message,sizeof(message),pidof_P3.mtype,0);
	cout<<message.mdata;
/*
	message[0].mtype = pidof_P2;	
	message[1].mtype = pidof_P3;	
	
	msgsnd(msqid,&message[0],sizeof(message[0]),0);
	msgsnd(msqid,&message[0],sizeof(message[0]),0);
*/		
	msgctl(msqid,IPC_RMID,0);
	return 0;
}
