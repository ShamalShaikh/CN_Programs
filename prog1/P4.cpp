#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
int main(){
cout<<"In process 4";
cout<<"\nProcess ID = "<<getpid();
cout<<"\nEnough! Stop Bro!\n";
return 0;
}
