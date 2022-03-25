#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<iostream>
using namespace std;
int main()
{
    int fd;
    mkfifo("/tmp/f2", 0666);

    char arr2[10];
    while (1)
    {
        fd = open("/tmp/f2", O_WRONLY);
        //strcpy(arr2, "Shaikh\n");
        //sleep(2);
        cin>>arr2;
        write(fd, arr2, sizeof(arr2));
		memset(arr2,' ',sizeof(arr2));  
		//cout<<arr2<<endl;      
        close(fd);
    }
    return 0;
}
