#include <iostream>
#include <unistd.h>
#include<sys/wait.h>
using namespace std;
int main(){
  int pi_d ;
  int pid ;
  pi_d = fork();
  if(pi_d == 0){
    cout<<"\npid :"<<getpid()<<"\nppid:"<<getppid()<<"\n";
    execlp("./P2.exe","./P2.exe",NULL);
  }
  if(pi_d > 0){
  	wait(NULL);
    pid = fork();
    if(pid > 0){
    	wait(NULL);
      cout<<"\nParent Process:\npid:"<<getpid()<<"\nppid :"<<getppid()<<"\n";
    }
    else if(pid == 0){
      cout<<"Child Process A:\npid :"<<getpid()<<"\nppid:"<<getppid()<<"\n";
      execlp("./P3.exe","./P3.exe",NULL);
    }
  }
  return 0;
}

