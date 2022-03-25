#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	printf("Hey! My Name is Jesus!! and My ID is %d",getpid());
	fflush(stdout);
	int c = fork();
	if(c>0){
		wait(NULL);
	}
	if(c==0){

		printf("\nLet me introduce you Muhammad\n\n");
		char * argv_list[] = {"p4.exe",NULL};
		execv("p4.exe",argv_list);
	}
return 0;
}
