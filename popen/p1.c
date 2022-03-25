#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
int main(void)
{	
	int fd = popen("p2.exe",0);
	dup2(fd,1);
	printf("Hello! My name is popopop");
	return 0;
}
