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
	sem_t *sem14,*sem34;

	int pid;

	sem14 = sem_open("/p14",0);
	sem34 = sem_open("/p34",0);

	int msqid;
	key_t msg_key = ftok("hi.txt",65);
	msqid = msgget(msg_key,0666|IPC_CREAT);
	cout<<"Wait for P1 to complete"<<endl;
	sem_wait(sem14);
	
	msgrcv(msqid,&msg,sizeof(msg),0,0);
	pid = msg.mtype;

	msg2.mtype = getpid();
	cout<<msg2.mtype<<" "<<getpid();
	//strcpy(msg.mdata,"Salam");
	sleep(3);
	msgsnd(msqid,&msg2,sizeof(msg2),0);
	
	sem_post(sem34);
	
	cout<<"PID[1] : "<<pid;
	cout<<"PID[4] : "<<getpid();
	cout<<"\nSending Message To P1 :\n";
	msg.mtype = pid;
	strcpy(msg.mdata,"Hey Nice to Meet You!");
	msgsnd(msqid,&msg,sizeof(msg),0);

	msgrcv(msqid,&msg,sizeof(msg),getpid(),0);
	cout<<msg.mdata;


	return 0;
}