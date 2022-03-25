#include<bits/stdc++.h>
 #include <sys/wait.h>
#include <stdint.h>
// #include <stdlib.h>
#include <unistd.h>
// #include <stdio.h>
using namespace std;

int main(int ac,char *av[]){
	int pid,w;
	int wstatus;

	pid = fork();

	if(pid ==0){
       printf("Child PID is %jd\n", (intmax_t) getpid());
       if (ac == 1)
           pause();                    /* Wait for signals */
       _exit(atoi(av[1]));
       	// exit(1);

	}
	else{
		do {
           w = waitpid(pid, &wstatus,WUNTRACED | WCONTINUED);	//
           if (w == -1) {
               perror("waitpid");
               exit(2);
           }

           if (WIFEXITED(wstatus)) {
               printf("exited, status=%d\n", WEXITSTATUS(wstatus));
           } 
           else if (WIFSIGNALED(wstatus)) {
               printf("killed by signal %d\n", WTERMSIG(wstatus));
           } 
           else if (WIFSTOPPED(wstatus)) {
               printf("stopped by signal %d\n", WSTOPSIG(wstatus));
           } 
           else if (WIFCONTINUED(wstatus)) {
               printf("continued\n");
           }
       } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
       exit(0);

	}

	return 0;
}