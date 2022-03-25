#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<string.h>

int main(){
	
	int pid,fd;

	fd = open("mytext.txt" , O_RDONLY);
	if(fd == -1){
		perror("file error");
		exit(1);
	}
	sem_unlink("/p1");
	sem_unlink("/p2");
	
	sem_t *sem1,*sem2;

	sem1 = sem_open("/p1",O_CREAT,0644,0);
	sem2 = sem_open("/p2",O_CREAT,0644,0);	
		
	pid=fork();
	
	if(pid>0){
		char c;
		printf("parent : ");
		while(read(fd,&c,1)==1){
			if(c=='\n'){
	      		printf("\n");				
	    		sem_post(sem1);  		
    			sem_wait(sem2);
				printf("parent : ");    			
			}
			else
				printf("%c",c);     	
   		}
	}		
	else if(pid == 0){
		char c;
		sem_wait(sem1);
		printf("child  : ");
		while(read(fd,&c,1)==1){
			if(c=='\n'){
	      		printf("\n");				
	    		sem_post(sem2);  		
    			sem_wait(sem1);
				printf("child  : ");    			
			}
			else
				printf("%c",c);
      	 }
      	sem_post(sem2); 
	} 	
close(fd);
sem_close(sem1);
sem_close(sem2);
return 0;
}
