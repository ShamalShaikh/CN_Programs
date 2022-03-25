#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
int main(void)
{	
	printf("sdjvndkjvn");
	fflush(stdout);
	char str[100];
	read(STDIN_FILENO,str,100);
	puts(str);
	return 0;
}
