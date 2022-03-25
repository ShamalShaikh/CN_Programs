#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
    char b[] = "myfifo2"; 
    mkfifo(b, 0666); 
  
    char arr1[80], arr2[80]; 
    while (1) 
    { 

        fd = open(b, O_WRONLY); 
      	strcpy(arr2,"Shaikh\n");
      	sleep(2);
        write(fd, arr2, strlen(arr2)+1); 
        close(fd);
    } 
    return 0; 
} 
