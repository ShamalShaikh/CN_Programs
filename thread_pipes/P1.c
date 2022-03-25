#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int t=1;
int main(){
	int fd1[2];
	pipe(fd1);
	dup2(0,1);
	//dup2(fd1[0],0);
	int c='s';
//	c = fork();

	dup2(1,STDIN_FILENO);
	scanf("%c",(char*)&c);	
	printf("%c",c);
	

	
/*	if(c>0){
		dup2(0,STDIN_FILENO);
		char str[100];
		scanf("%s",str);
		close(fd1[0]);
		write(fd1[1],str,strlen(str)+1);
		close(fd1[1]);
		
	}
	else{
		char* a[] = {"P2.exe",NULL};
		execv("P2.exe",a);
		
	}
*/	
return 0;
}
