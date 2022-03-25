#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<ctype.h>

int main(){
	int fd[2];
	if(pipe(fd)==-1){
		return 1;
	}
	
	int pid1 = fork();
	if(pid1<0){
		return 2;
	}
	
	if(pid1 == 0){
		//child process(P1)
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char str[100] = "shamal shaikh is the best man";
		write(STDOUT_FILENO,str,100);
	}
	
	int pid2 = fork();
	if(pid2<0){
		return 3;
	}
	
	if(pid2==0){
		//child process(P2)
		dup2(fd[0],STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("p2.exe","p2.exe",NULL);
	}
	
	close(fd[1]);
	close(fd[0]);
	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);
	return 0;
}

