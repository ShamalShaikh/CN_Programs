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
//	sleep(5);
	while(1){
	cin>>str;
	printf("%s\n",str);
	sleep(8);
	}	
return 0;
}
