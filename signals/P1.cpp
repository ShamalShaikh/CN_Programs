#include<bits/stdc++.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include<unistd.h> 
#include<semaphore.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>

using namespace std;
int *y,*x;
int X,Y;

void f2(int b)
{
	cout<<"process1   "<<*x<<"  "<<*y<<endl;
	*x=*y+1;
	cout<<"process1   "<<*x<<"   "<<*y<<endl;
	sleep(1);
	kill(Y,SIGUSR1);
	
}

int main()
{
	int fd1,fd2;
	
	mkfifo("fifo1",0666);
	mkfifo("fifo2",0666);
	
	fd1=open("fifo1",0666);
	fd2=open("fifo2",0666);
	
	signal(SIGUSR2,f2);
	
	char s1[30],s2[30];
	read(fd1,s1,sizeof(s1));
	
	X=getpid();
	
	sprintf(s2,"%d",X);
	write(fd2,s2,sizeof(s2));
	
	Y=atoi(s1);				// process 2's pid
	cout<<"x="<<X<<endl;
	cout<<"y="<<Y<<endl;
	
	int seg_id1 = shmget(ftok(".", 123345),4096,IPC_CREAT | 0666);
	int seg_id2 = shmget(ftok(".",111),4096,IPC_CREAT | 0666);
	x=(int *)shmat(seg_id1,NULL,0);
	y=(int *)shmat(seg_id2,NULL,0);
	*x=5;
	*y=10;

	sleep(5);
	
	kill(Y,SIGUSR1);
	while(1);


}
