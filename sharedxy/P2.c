#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define size 10

int main(int ac, char* av[]){
	if(ac!=1){
		printf("usage - %s //NO arguments",av[0]);
		return -1;
	}
	
	key_t key1;
	int shmid1;
	char *shm1;
	
	key1 = 1234;
	shmid1 = shmget(key1,size, IPC_CREAT|0666);
	if(shmid1<0){
		perror("shmget");
		exit(1);
	}
	
	shm1 = shmat(shmid1,NULL,0);
	if(shm1 == (char*)-1){
		perror("shamt");
		exit(1);
	}
	
	memcpy(shm1, 1, 4);
	
	shmdt(shm1);
return 0;
}

/*sem_t *sem_s1 = sem_open(s1,IPC_CREAT,0666,0);
	if(sem_s1 == SEM_FAILED){
		perror("sem_open/s1");
		exit(EXIT_FAILURE);
	}
	sem_t *sem_s2 = sem_open(s2,IPC_CREAT,0666,1);
	if(sem_s2 == SEM_FAILED){
		perror("sem_open/s2");
		exit(EXIT_FAILURE);
	}
*/	
