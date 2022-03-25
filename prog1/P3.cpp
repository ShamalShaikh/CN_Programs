#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
int main(){

int c = fork();
if(c>0){
	wait(NULL);
}
if(c==0){
	cout<<"In process 3";
	cout<<"\nProcess ID = "<<getpid();
	cout<<"\nCalling process 4\n";
	execlp("./P4.exe","./P4.exe",NULL);
}
return 0;
}
