#include<bits/stdc++.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include<unistd.h> 
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
#include<pthread.h>
#include<sys/shm.h>
#include<sys/ipc.h>
using namespace std;
pthread_t t1,t2;
int *x;
int X;
void fn1(int signum){
	cout<<"I won't stop\n";
	sleep(2);
	kill(X,SIGUSR1);
//	signal(SIGUSR1,SIG_DFL);
}

void *fun(void *arg){

	signal(SIGUSR1,fn1);
	raise(SIGUSR1);	
	return NULL;
}

int main(){
	// Get pid of P2
	int fd = fileno(popen("pidof ./P2","r"));
	char s[1000];
	read(fd,&s,1000);
	X = atoi(s);
	printf("%d %d\n",X,getpid());	
	/* Shared memory for P2 pid
	int seg_id1 = shmget(ftok(".", 123345),4096,IPC_CREAT | 0666);
	x=(int *)shmat(seg_id1,NULL,0);
	printf("%d %d\n",*x,getpid());	
	*/
	pthread_create(&t1,NULL,fun,NULL);
	
	pthread_join(t1,NULL);
	
	return 0;	
}
