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

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	printf ("Sending PID: %ld, UID: %ld\n",
			(long)siginfo->si_pid, (long)siginfo->si_uid);
}

void f2(int b)
{
	cout<<"process1\n\n";
	
}


int main()
{
	struct sigaction act;
	memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &hdl;
	act.sa_flags = SA_SIGINFO;
	signal(SIGTERM, f2);
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
