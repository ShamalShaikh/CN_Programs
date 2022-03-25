
#include<stdio.h>
#include<stdlib.h>
#include<poll.h>
#include<unistd.h>
#include<string.h>
int main(){
	char buf[100];

	while(1){
	
		read(0,buf,100);
		
		printf("%s",buf);
		break;
	
	}
return 0;
}
