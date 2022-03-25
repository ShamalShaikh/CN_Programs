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
	sem_t *sem12,*sem23;
	int pid;

	sem12 = sem_open("/p12",0);
	sem23 = sem_open("/p23",0);
	
	int msqid;
	key_t msg_key = ftok("hi.txt",65);
	msqid = msgget(msg_key,0666|IPC_CREAT);
	cout<<"Wait for P3 to complete"<<endl;
	sem_wait(sem23);
	
	msgrcv(msqid,&msg,sizeof(msg),0,0);
	pid = msg.mtype;
	
	msg2.mtype = getpid();
	cout<<msg2.mtype<<" "<<getpid();
	//strcpy(msg.mdata,"Salam");
	sleep(3);
	msgsnd(msqid,&msg2,sizeof(msg2),0);
		
	sem_post(sem12);
	
	cout<<"PID[3] : "<<pid;
	cout<<"PID[2] : "<<getpid();

	cout<<"\nSending Message To P3 :\n";
	msg.mtype = pid;
	strcpy(msg.mdata,"Hey Nice to Meet You!");
	msgsnd(msqid,&msg,sizeof(msg),0);

	msgrcv(msqid,&msg,sizeof(msg),getpid(),0);
	cout<<msg.mdata;
	return 0;
}