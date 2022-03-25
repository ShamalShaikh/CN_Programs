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
	
	if(destroy_memory_block(FILENAME)){
		printf("DEstroyed block %s\n",FILENAME);
	}
	else{
		printf("Could not destroy block %s\n",FILENAME);
	}
	
	return 0;
}
