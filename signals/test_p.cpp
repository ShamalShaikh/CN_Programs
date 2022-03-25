#include<bits/stdc++.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include<unistd.h> 
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
using namespace std;

void fn1(int signum){
	cout<<"I won't stop\n";
	signal(SIGINT,SIG_DFL);
}

int main(){
	signal(SIGINT,fn1);
	while(1){
		cout<<"Press ctrl+c to stop\n";
		sleep(1);
	}
}
