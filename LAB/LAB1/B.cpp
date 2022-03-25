#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>  
#include<iostream>

using namespace std;
int main() 
{ 
	char str[BUFSIZ];
	int fd = fileno(popen("pidof ./A","r"));
	char s[1000];
	read(fd,&s,1000);
	int X = atoi(s);
	
	setpgid(getpid(),X);
	
	printf("%d\n",getpgid(getpid()));
	cin>>str;
	printf("%s\n",str);
return 0;
}
