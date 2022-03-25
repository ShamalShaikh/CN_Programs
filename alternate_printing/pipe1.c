#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<ctype.h>
// 1024 is maximum pipe limit  
int main() 
{ 
  
    int fd1[2];  
    int fd2[2];  
  
    char str[100]; 
    int p; 
  
    if (pipe(fd1)==-1) 
    { 
        perror("Pipe fd1 Failed" ); 
        exit(1); 
    } 
    if (pipe(fd2)==-1) 
    { 
        perror("Pipe fd2 Failed" ); 
        exit(1); 
    } 


    
    p = fork(); 
  
   if (p > 0) 
    { 
        while(1){
        scanf("%s", str); 
  
        close(fd1[0]);  
        
        write(fd1[1], str, strlen(str)+1); 
        close(fd1[1]); 
  
        wait(NULL); 
  
        close(fd2[1]); 
  		char str2[100];
        read(fd2[0], str2, 100); 
        printf("Received string %s\n", str2); 
        close(fd2[0]); 
        }
    } 
  
    // child process 
    else
    { 
        while(1){
        close(fd1[1]); 
  		char str2[100];
        read(fd1[0], str2, 100); 
  
        for(int i=0;str2[i]!='\0';++i){
        	str2[i] = toupper(str2[i]);
        }
        // Close both reading ends 
        close(fd1[0]); 
        close(fd2[0]); 
  
        // Write concatenated string and close writing end 
        write(fd2[1], str2, strlen(str2)+1); 
        close(fd2[1]); 
  		}
        exit(0); 
    } 
} 
