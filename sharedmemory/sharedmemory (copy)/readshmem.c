#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <semaphore.h>
#include "shared_memory.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
 #include <fcntl.h>
#define BLOCK_SIZE sizeof(int)

int main(int ac, char* av[]){
	if(ac!=1){
		printf("usage - %s //NO arguments",av[0]);
		return -1;
	}

	sem_t *s1 = sem_open(SEM_P1,1);
	if(s1 == SEM_FAILED){
		perror("sem_open/s1");
		exit(EXIT_FAILURE);
	}
	sem_t *s2 = sem_open(SEM_P2,0);
	if(s2 == SEM_FAILED){
		perror("sem_open/s2");
		exit(EXIT_FAILURE);
	}

	
	int t=2;
	int *x = attach_memory_block(FILENAME,BLOCK_SIZE);
		if(x == NULL){
			printf("ERROR : couldn't get block\n");
			return -1;
		}
	int *y = attach_memory_block(FILENAME2,BLOCK_SIZE);
		if(y == NULL){
			printf("ERROR : couldn't get block\n");
			return -1;
		}
		
	while(t--){
		sem_wait(s1);
		
		printf("Reading: \"%d\"\n",*x);
		
		*y = *x+1;
		
		printf("Writing: \"%d\"\n",*y);
		
		sem_post(s2);	
	}
	
	sem_close(s1);
	sem_close(s2);
	detach_memory_block(x);
	detach_memory_block(y);	
	
return 0;
}
