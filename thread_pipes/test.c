#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
void* read_thread(void *arg){
	int *fd = (int*)arg;
	close(fd[1]);
	char str[50];
	read(fd[0],str,50);
	printf("%s\n",str);
	fflush(stdout);
	close(fd[0]);
	return NULL;
}
void* write_thread(void *arg){
	int *fd = (int*)arg;
	close(fd[0]);
	char str[50];
	scanf("%s",str);
	write(fd[1],str,50);
	close(fd[1]);
	return NULL;
}
int t=1;
int main(){
	pthread_t t1,t2;
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	
	int c;
	c = fork();
	
	if(c>0){

		while(t--){
		pthread_create(&t1,NULL,write_thread,&fd2);
		pthread_create(&t2,NULL,read_thread,&fd1);
		}
	}
	else{
	char * cmd[] = {"/usr/bin/xterm", "-e", "yourchatprogram", NULL};
	execv(cmd[0], cmd);
		while(t--){
		pthread_create(&t2,NULL,read_thread,&fd2);		
		pthread_create(&t1,NULL,write_thread,&fd1);		
		}
	}
	pthread_join(&t1,NULL);
	pthread_join(&t2,NULL);	
return 0;
}
