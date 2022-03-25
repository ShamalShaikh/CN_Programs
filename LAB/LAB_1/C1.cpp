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
    mkfifo("/tmp/f1", 0666);
    char arr1[10];
    while (1)
    {
        fd = open("/tmp/f1", O_WRONLY);
        //strcpy(arr1, "Shamal\n");
        cin>>arr1;
        write(fd, arr1, sizeof(arr1));
		memset(arr1,' ',sizeof(arr1));
		//cout<<arr1<<endl;
        //sleep(3);
        close(fd);
    }
    return 0;
}
