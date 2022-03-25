#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>  
#include<poll.h>
#include<sys/wait.h>
int main() 
{ 
	int fd[3];
	char str[BUFSIZ];
	int pret;
	struct pollfd pfds[3];
	int timeout;

	 fd[0] = fileno(popen("./C1.exe","r"));
//		sleep(10);
//	 wait(NULL);
	 fd[1] = fileno(popen("./C2.exe","r"));
//	 wait(NULL);	
//		sleep(10); 
	 fd[2] = fileno(popen("./C3.exe","r"));	
//	 wait(NULL);
//		sleep(10);

	for(int i=0;i<3;++i){
	pfds[i].fd = fd[i];
	pfds[i].events = POLLIN;
	}
	int afds = 3;
	while(afds>0){
		
		timeout = 5000;
		
		pret = poll(pfds,3,timeout);
		
		if(pret == 0){
			printf("%d\n",timeout);
		}
		else{
			for(int i=0;i<3;++i){
				if(pfds[i].revents & POLLIN){
					//printf("aaaaaaaaa");
					printf("BOT %d:",i+1);
					read(fd[i],str,BUFSIZ);
					puts(str);
					afds--;	
				}
			}
		}
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
return 0;
}
