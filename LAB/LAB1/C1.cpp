#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
    char a[] = "myfifo"; 
    mkfifo(a, 0666); 
  
    char arr1[80], arr2[80]; 
    while (1) 
    { 

        fd = open(a, O_WRONLY); 
      	strcpy(arr2,"Shamal\n");
      	
        write(fd, arr2, strlen(arr2)+1); 
        sleep(3);
        close(fd);
    } 
    return 0; 
} 
