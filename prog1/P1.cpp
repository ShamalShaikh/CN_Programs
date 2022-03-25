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
cout<<"In process 1";
cout<<"\nProcess ID = "<<getpid();
cout<<"\nCalling process 2\n";
execlp("./P2.exe","./P2.exe",NULL);
}
return 0;
}
