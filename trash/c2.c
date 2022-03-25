
#include<stdio.h>
#include<stdlib.h>
#include<poll.h>
#include<unistd.h>
int main(){
	char buf[4];
	while(1){
	
		read(0,buf,4);
		write(1,buf,4);
	
	}
return 0;
}
