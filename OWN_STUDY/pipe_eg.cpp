#include"../Message_Queues/Header1.h"

using namespace std;
int main(){
	int fd[2][2];
	pid_t child;
	pipe(fd[0]);
	pipe(fd[1]);
	
	if(child = fork() == 0){
		close(fd[0][1]);
		close(fd[1][0]);
		server(pipe[0][0],pipe[1][1]);
		exit(0);
	}
	close(pipe[0][0]);
	close(pipe[1][0]);
	client(pipe[0][1]);
	waitpid(child,NULL,0);
return 0;
}
