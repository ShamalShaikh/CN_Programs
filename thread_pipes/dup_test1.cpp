#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main(){
	int x = open("myfile.txt",O_WRONLY|O_CREAT,0777);
	dup2(1,0);
	dup2(x,1);

	printf("SHAMAL SHAIKH IS THE BEST");
	//dup2(1,x);
	dup2(0,1);
	printf("AM i in terminal??");
return 0;
}
