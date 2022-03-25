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

int X;

int main() {

	int fd = fileno(popen("pidof ./S", "r"));
	char s[1000];
	read(fd, &s, 1000);
	X = atoi(s);
	int x;
	while (x>0) {
//		sleep(3);
		cin>>x;
		kill(X, SIGUSR1);
	}
	
	return 0;
}
