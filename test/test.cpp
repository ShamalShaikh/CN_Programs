#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
using namespace std;
int main(){
	int i = fork();
	if(i==0){
		cout<<"from child\n";
	}
	else{
		wait(NULL);
		cout<<"from parent\n";
	}
	cout<<"back";
}
