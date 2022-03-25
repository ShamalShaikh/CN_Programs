#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "shared_memory.h"

#define BLOCK_SIZE 4096

int main(int ac, char* av[]){
	if(ac!=1){
		printf("usage - %s //NO arguments",av[0]);
		return -1;
	}
	char *block = attach_memory_block(FILENAME,BLOCK_SIZE);
	if(block == NULL){
		printf("ERROR : couldn't get block\n");
		return -1;
	}
	
	printf("Reading: \"%d\"\n",block);
	printf("Reading: \"%s\"\n",block);
	detach_memory_block(block);
	
return 0;
}
