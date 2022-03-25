#include<bits/stdc++.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include<unistd.h> 
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
#include<pthread.h>
using namespace std;
pthread_t t1,t2;
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

void *fun1(void *arg){
	sleep(1);
	signal(SIGINT,fn1);
	pthread_kill(t1,SIGINT);
	sleep(1);
	pthread_kill(t1,SIGINT);
	return NULL;
}

int main(){
	pthread_create(&t1,NULL,fun,NULL);
	sleep(1);
	pthread_create(&t2,NULL,fun1,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);	
	
	return 0;	
}
