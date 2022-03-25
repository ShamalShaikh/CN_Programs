#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<pthread.h>

int fd;
int fd1;  
char str1[80], str2[80]; 
void *reads(void * arg){
	fd1 = open("C1_chat",O_RDONLY);
	read(fd1,str2,80);
	printf("%s",str2);
	close(fd1); 
	return NULL;
}

void *writes(void *arg){
	read(0,str1,80);
	strcat(str1,"1");
	fd = open("Friends",O_WRONLY); 
    write(fd, str1, 80); 
    close(fd);
	return NULL;
}
  
int main() 
{ 
    
    
  	mkfifo("Friends", 0666); 
  	mkfifo("C1_chat",0666);
  	
    
    strcpy(str1,"C1_chat");	
    fd = open("Friends",O_WRONLY); 
    write(fd, str1, 80); 
    close(fd); 
  
 	fd1 = open("C1_chat",O_RDONLY);
	read(fd1,str2,80);
	printf("%s",str2);
	close(fd1);
	
//	strcpy(str1,"Hey Guys, What's Up?");
	pthread_t reader,writer;
	while(1){
	pthread_create(&reader,NULL,reads,NULL);
	pthread_create(&writer,NULL,writes,NULL);
	pthread_join(reader,NULL);
	pthread_join(writer,NULL);	
	}
    return 0; 
} 
