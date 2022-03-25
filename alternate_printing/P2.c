#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<string.h>
#include<errno.h>
//int errno=0;
int main(){
	
	int fd;

	fd = open("mytext.txt" , O_RDONLY);
	if(fd == -1){
		perror("file error");
		exit(1);
	}
	char str[100];
	int x = dup(0);
	int f = dup2(fd,0);
//	close(STDIN_FILENO);
//	int f = fcntl(fd,F_DUPFD,STDIN_FILENO);
	scanf("%s",&str);
	fflush(stdin);
	(printf("%s",str));
	fflush(stdout);

	dup2(x,fileno(stdin));

	scanf("%s",&str);
	fflush(stdin);
		
close(fd);
return 0;
}
