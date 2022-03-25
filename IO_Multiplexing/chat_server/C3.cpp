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
	fd1 = open("C3_chat",O_RDONLY);
	read(fd1,str2,80);
	printf("%s",str2);
	close(fd1); 
	return NULL;
}

void *writes(void *arg){
	read(0,str1,80);
	strcat(str1,"3");
	fd = open("Friends",O_WRONLY); 
    write(fd, str1, 80); 
    close(fd);
	return NULL;
}  
  
int main() 
{ 
    int fd;  
    
  	mkfifo("Friends", 0666); 
  	mkfifo("C3_chat",0666);
    char str1[80], str2[80]; 
    strcpy(str1,"C3_chat");	
    fd = open("Friends",O_WRONLY); 
    write(fd, str1, 80); 
    close(fd); 
  
 	int fd1 = open("C3_chat",O_RDONLY);
	read(fd1,str2,80);
	printf("%s",str2);
	close(fd1);
	
/*	read(0,str1,80);
	strcat(str1,"3");
	fd = open("Friends",O_WRONLY); 
    write(fd, str1, 80); 
    close(fd);
*/    
	
    pthread_t reader,writer;
	while(1){
	pthread_create(&reader,NULL,reads,NULL);
	pthread_create(&writer,NULL,writes,NULL);
	pthread_join(reader,NULL);
	pthread_join(writer,NULL);	
	}
    return 0; 
} 
