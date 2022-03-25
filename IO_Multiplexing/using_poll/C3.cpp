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
//	sleep(2);
//	strcpy(str,"Hey! My name is Shamal C3 BOT ;D\n");
	while(1){
	cin>>str;
	printf("%s\n",str);
		sleep(2);
	}	
return 0;
}
