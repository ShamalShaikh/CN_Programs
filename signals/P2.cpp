#include<bits/stdc++.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include<unistd.h> 
#include<semaphore.h>
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/ipc.h>

using namespace std;
int *y,*x;
int X,Y;
void f1(int a)
{
	cout<<"process2    "<<*x<<"  "<<*y<<endl;
	*y=*x+1;
	cout<<"process2     "<<*x<<"  " <<*y<<endl;
	sleep(1);
	
	
	kill(X,SIGUSR2);
	
}



int main()
{

	signal(SIGUSR1,f1);

	mkfifo("fifo1",0666);
	mkfifo("fifo2",0666);

	int fd2=open("fifo2",0666);
	int fd1=open("fifo1",0666);

	key_t ShmKEY,ShmKEY1;
	ShmKEY = ftok(".", 123345);
	ShmKEY1 = ftok(".", 111);
	int seg_id1 = shmget(ShmKEY,4096,IPC_CREAT | 0666);
	int seg_id2 = shmget(ShmKEY1,4096,IPC_CREAT | 0666);
	x=(int *)shmat(seg_id1,NULL,0);
	y=(int *)shmat(seg_id2,NULL,0);

	char s1[30],s2[30];
	Y=getpid();
	sprintf(s2,"%d",Y);
	write(fd1,s2,sizeof(s2));
	read(fd2,s1,sizeof(s1));
	
	X=atoi(s1);
	cout<<"x="<<X<<endl;
	cout<<"y="<<Y<<endl;
	
	while(1);
}
