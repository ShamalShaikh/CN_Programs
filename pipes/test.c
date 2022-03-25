#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
  
    int fd1[2];  
    
    char str[100],output_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    scanf("%s", str);
    
   	write(fd1[1], str, strlen(str)+1); 
    close(fd1[1]); 
    read(fd1[0], output_str, strlen(str)+1);
    
    printf("%s",output_str);
} 
