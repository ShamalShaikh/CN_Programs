#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	printf("Hey! My Name is Adam!! and My ID is %d",getpid());
	fflush(stdout);
	int c = fork();
	if(c>0){
		wait(NULL);
	}
	if(c==0){
		printf("\nLet Me Introduce you to Abraham\n\n");
		char * argv_list[] = {"p2.exe",NULL};
		execv("p2.exe",argv_list);
	}
return 0;
}
