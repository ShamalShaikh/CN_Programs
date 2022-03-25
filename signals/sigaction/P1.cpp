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



int main()
{

	int fd = fileno(popen("pidof ./P2","r"));
	char s[1000];
	read(fd,&s,1000);
	X = atoi(s);
	printf("%d %d\n",X,getpid());

	kill(X,SIGUSR1);

	close(fd);
//		while(1);
	sleep(10);
	kill(X,SIGTERM);
	return 0;

}
