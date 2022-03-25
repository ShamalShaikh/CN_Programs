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
	signal(SIGINT,SIG_DFL);
}

void *fun(void *arg){
	while(1){
		cout<<"Press ctrl+c to stop\n";
		sleep(1);
	}
	return NULL;
}

void fun1(int a){
	sleep(1);
	printf("salam\n");
	signal(SIGINT,fn1);
	pthread_kill(t1,SIGINT);
	sleep(1);
	pthread_kill(t1,SIGINT);

}

int main(){
	// To share the P2 pid we can use shared memory
/*	int seg_id1 = shmget(ftok(".", 123345),4096,IPC_CREAT | 0666);
	x=(int *)shmat(seg_id1,NULL,0);
	*x = getpid();
*/

	// Creating a thread P2=>t1
	pthread_create(&t1,NULL,fun,NULL);
	
	signal(SIGUSR1,fun1);
	
	pthread_join(t1,NULL);
	
	return 0;	
}
