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
cout<<"In process 2";
cout<<"\nProcess ID = "<<getpid();
cout<<"\nCalling process 3\n";
execlp("./P3.exe","./P3.exe",NULL);
}
return 0;
}
