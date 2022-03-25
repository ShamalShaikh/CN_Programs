#include<stdio.h>
#include<stdlib.h>
#include<poll.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main(){
	int fd[3];
	char buf[100];
	int pret;
	struct pollfd pfds[3];
	int timeout;
	FILE *fp;
	fp = (popen("./c1.exe","r"));
//	fd[1] = fileno(popen("./c2.exe","r"));
//	fd[2] = fileno(popen("./c3.exe","r"));
	
	
	pclose(fp);
		
	for(int i=0;i<3;++i){
		pfds[i].fd = fd[i];
		pfds[i].events = POLLIN;
	}
/*	
	while(1){
		
		timeout = 5000;
	
		pret = poll(pfds,3,timeout);
		
		if(pret == 0){
			printf("%d\n",timeout);
		}
		else
		for(int i=0;i<3;++i){
			if(pfds[i].revents & POLLIN){
				read(fd[i],buf,100);
				puts(buf);	
			}
		}
	}
*/
			
return 0;
}
