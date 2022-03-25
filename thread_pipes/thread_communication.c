#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<pthread.h>

// 1024 is maximum pipe limit 
  	pthread_t reader;
	pthread_t writer;
void read_thread(int fd){
	pthread_create(&reader,NULL,reads(),NULL);
}

void write_thread(int fd){
	pthread_create(&writer,NULL,writes(),NULL);
}
 
int main() 
{ 

    int fd1[2];  
    int fd2[2];  

  	read_thread(fd1[0]);

  	write_thread(fd1[1]);  	
    char str[100]; 
    int p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 

    scanf("%s", str); 
    p = fork(); 
  
   if (p > 0) 
    { 
        while(1){
        char concat_str[100]; 
  
        close(fd1[0]);  
        
        write(fd1[1], str, strlen(str)+1); 
        close(fd1[1]); 
  
        wait(NULL); 
  
        close(fd2[1]); 
  
        read(fd2[0], concat_str, 100); 
        printf("Concatenated string %s\n", concat_str); 
        close(fd2[0]); 
        }
    } 
  
    // child process 
    else
    { 
        while(1){
        close(fd1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        char concat_str[100]; 
        read(fd1[0], concat_str, 100); 
  
        char ch;
        while(ch!='\0){
        	ch = toupper(ch);
        }
        // Close both reading ends 
        close(fd1[0]); 
        close(fd2[0]); 
  
        // Write concatenated string and close writing end 
        write(fd2[1], concat_str, strlen(concat_str)+1); 
        close(fd2[1]); 
  		}
        exit(0); 
    } 
} 
