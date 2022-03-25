#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<fstream>
#include<iostream>
using namespace std;  
int main() 
{ 
	FILE *fp = fopen("code.cpp","r"); 
    mkfifo("save",0666);
	int fd2 = open("save",O_WRONLY);

	char c = fgetc(fp); 
    while (c != EOF) 
    { 
		write(fd2,&c,sizeof(char)); 
        c = fgetc(fp); 
    } 
	
	close(fd2);
	fclose(fp);	
	
return 0;
}
