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
#include<sys/wait.h>
using namespace std;

int main()
{
	
	int a,b,c;
	a = fork();
	
	if(a==0){
		printf("%d %d\n",getpid(),getpgid(0));
		return 1;
	}
	
	b = fork();
	
	if(b==0){
		printf("%d %d\n",getpid(),getpgid(0));
		return 2;
	}
	
	c = fork();
	
	if(c==0){
		printf("%d %d\n",getpid(),getpgid(0));
		return 3;
	}
	
	return 0;

}
