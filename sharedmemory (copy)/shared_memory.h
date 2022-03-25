#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include<stdbool.h>

int *attach_memory_block(char* filename, int size);
bool detach_memory_block(int *block);
bool destroy_memory_block(char *filename);

#define BLOCK_SIZE sizeof(int)
#define FILENAME "writeshmem.c"
#define FILENAME2 "readshmem.c"
#define SEM_P1 "/p1"
#define SEM_P2 "/p2"

#endif
