#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <semaphore.h>
#include <sys/stat.h>
 #include <fcntl.h>
#include "shared_memory.h"

#define BLOCK_SIZE sizeof(int)

int main(int ac, char* av[]){
	if(ac!=2){
		printf("usage - %s [arguments]",av[0]);
		return -1;
	}
	
	//setup semaphore
	sem_unlink(SEM_P1);
	sem_unlink(SEM_P2);	
	
	sem_t *s1 = sem_open(SEM_P1,O_CREAT,0600,1);
	if(s1 == SEM_FAILED){
		perror("sem_open/s1");
		exit(EXIT_FAILURE);
	}
	sem_t *s2 = sem_open(SEM_P2,O_CREAT,0600,0);
	if(s2 == SEM_FAILED){
		perror("sem_open/s2");
		exit(EXIT_FAILURE);
	}
	
	int *x = attach_memory_block(FILENAME,BLOCK_SIZE);
	if(x == NULL){
		printf("ERROR : couldn't get block\n");
		return -1;
	}
	int a = atoi(av[1]);
	printf("Writing: \"%d\"\n",a);
	memcpy(x,&a,BLOCK_SIZE);
	fflush(stdout);
	int t=2;
	int *y= attach_memory_block(FILENAME2,BLOCK_SIZE);
	if(y == NULL){
		printf("ERROR : couldn't get block\n");
		return -1;
	}
	
	while(t--){
	sem_wait(s2);
		
	printf("Reading: \"%d\"\n",*y);

	*x = *y+1;
	
	printf("Writing: \"%d\"\n",*x);
	
	sem_post(s1);
	}
	
	sem_close(s1);
	sem_close(s2);	
	detach_memory_block(x);
	detach_memory_block(y);	
	
return 0;
}
