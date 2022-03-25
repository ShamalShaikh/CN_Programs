#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<string.h>
#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
struct mesg {
	long mtype;
	char mdata[100];
}msg,msg2;
int main(int argc, char const *argv[])
{
	
	int pid;
	sem_t *sem12,*sem14;

	sem12 = sem_open("/p12",O_CREAT,0644,0);
	sem14 = sem_open("/p14",O_CREAT,0644,0);

	int msqid;
	key_t msg_key = ftok("hi.txt",65);
	msqid = msgget(msg_key,0666|IPC_CREAT);
	
	msg.mtype = getpid();
	//strcpy(msg.mdata,"Salam");
	msgsnd(msqid,&msg,sizeof(msg),0);
	
	sem_post(sem14);
	
	cout<<"Wait for P2 to complete"<<endl;

	sem_wait(sem12);
	
	msgrcv(msqid,&msg2,sizeof(msg2),0,0);
	pid = msg2.mtype;
	
	cout<<"PID[2] : "<<pid;
	cout<<"\tPID[1] : "<<getpid();
	
	cout<<"\nSending Message To P2 :\n";
	msg.mtype = pid;
	strcpy(msg.mdata,"P1 : Hey Nice to Meet You, P2!");
	msgsnd(msqid,&msg,sizeof(msg),0);

	msgrcv(msqid,&msg,sizeof(msg),getpid(),0);
	cout<<msg.mdata;

	msgctl(msqid,IPC_RMID,NULL);
	return 0;
}