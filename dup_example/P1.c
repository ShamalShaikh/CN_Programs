#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<string.h>
#define SEM_P1 "/p1"
#define SEM_P2 "/p2"

int main(){
	
	int pid,fd;
	
	fd = open("mytext.txt" , O_RDONLY);
   	if(fd == -1) {
      perror("Error opening file");
      return(-1);
   	}
	
	sem_unlink(SEM_P1);
	sem_unlink(SEM_P2);	
	
	sem_t *s1 = sem_open(SEM_P1,O_CREAT,0600,0);
	if(s1 == SEM_FAILED){
		perror("sem_open/s1");
		exit(EXIT_FAILURE);
	}
	sem_t *s2 = sem_open(SEM_P2,O_CREAT,0600,1);
	if(s2 == SEM_FAILED){
		perror("sem_open/s2");
		exit(EXIT_FAILURE);
	}  
	 
	int t = 4;
	pid=fork();
	
	if(pid>0){
		while(t--){
			sem_wait(s2);
		
      		printf("P1:\n");
      		char c;
			while(read(fd,&c,1)==1){
			if(c=='\n'){
	      		printf("\n");				
				break;   			
			}
			else
				printf("%c",c);     	
   		}
      		
      		sem_post(s1);
      		
   		}
	}		
	else{
		dup2(fd,0);
		printf("%d",fd);
		fflush(stdout);
		char * a[] = {"P2.exe",NULL};
		execv("P2.exe",a);
	}			 	
close(fd);
sem_close(s1);
sem_close(s2);
return 0;
}
