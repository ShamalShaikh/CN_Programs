#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define size 10

int main(int ac, char* av[]){
	if(ac!=2){
		printf("usage - %s [arguments]",av[0]);
		return -1;
	}
//	char *block = attach_memory_block(FILENAME,BLOCK_SIZE);
	key_t key;
	int shmid;
	char *shm;
	
	key = 1234;
	shmid = shmget(key,size, IPC_CREAT|0666);
	if(shmid<0){
		perror("shmget");
		exit(1);
	}
	
	shm = shmat(shmid,NULL,0);
	if(shm == (char*)-1){
		perror("shamt");
		exit(1);
	}
	
	memcpy(shm, 1, 4);
	
	char *x;
	x=
	
	shmdt(shm);
	
	
/*	ftok(filename,0);
	if(key == -1){
		return -1;
	}
	int shared_x = shmget(key,1,0644|IPC_CREAT);

	while(true){
		sem_wait(sem_y);
		
		x=y+1;
		
	}
	detach_memory_block(block);
*/	
return 0;
}
