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

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	printf ("Sending PID: %ld, UID: %ld\n",
			(long)siginfo->si_pid, (long)siginfo->si_uid);

}

void fn(int signum){

	cout<<"I won't Stop !! \n";
	
}

int main()
{
	
	int a,b,c;
	a = fork();
	
	if(a==0){	// Child process P2
	//	setpgid(getppid(),getpid());
		printf("P2 groupid : %d\n",getpgid(getpid()));
		struct sigaction act;
		memset(&act, '\0', sizeof(act));
		act.sa_sigaction = &hdl;
		act.sa_flags = SA_SIGINFO;
		if(sigaction(SIGUSR1,&act,NULL)<0){
			perror("sigaction");
			return 1;
		}
		while(1)
		{
			sleep(3);
			printf("P2 Pid : %d\n",getpid());
		}
		return 0;
	}
	
	b = fork();
	
	if(b==0){	// Child process P3
	//	setpgid(getppid(),getpid());
		printf("P3 groupid : %d\n",getpgid(getpid()));
		struct sigaction act;
		memset(&act, '\0', sizeof(act));
		act.sa_sigaction = &hdl;
		act.sa_flags = SA_SIGINFO;
		if(sigaction(SIGUSR1,&act,NULL)<0){
			perror("sigaction");
			return 1;
		}
		while(1)
		{
			sleep(3);
			printf("P3 Pid : %d\n",getpid());
		}
		return 0;
	}
	
	c = fork();
	
	if(c==0){	// Child process P4
	//	setpgid(getppid(),getpid());
		printf("P4 groupid : %d\n",getpgid(getpid()));
		struct sigaction act;
		memset(&act, '\0', sizeof(act));
		act.sa_sigaction = &hdl;
		act.sa_flags = SA_SIGINFO;
		if(sigaction(SIGUSR1,&act,NULL)<0){
			perror("sigaction");
			return 1;
		}
		while(1)
		{
			sleep(3);
			printf("P4 Pid : %d\n",getpid());
		}
		return 0;
	}
	
	sleep(10);
	printf("Parent group id : %d\n",getpgid(getpid()));
	signal(SIGUSR1,fn);
	killpg(getpgid(getpid()),SIGUSR1);
	killpg(getpgid(getpid()),SIGTERM);
	return 0;

}
