
#include<stdio.h>
#include<stdlib.h>
#include<poll.h>
#include<unistd.h>
#include<string.h>
int main(){
	char buf[100];
	printf("sdkjfdjksb");
	fflush(stdout);
	while(1){
	
		read(0,buf,100);
		
		write(1,buf,strlen(buf)+1);
	
	}
return 0;
}
