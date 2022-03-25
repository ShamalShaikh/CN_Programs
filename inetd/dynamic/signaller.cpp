#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
	int fd = fileno(popen("pidof ./a.out","r"));
	char s[100];
	read(fd,&s,100);
	int x = atoi(s);

	int fd2 = fileno(popen("pidof ./c","r"));
	char s1[100];
	read(fd2,&s1,100);
	int y = atoi(s1);
	cout<<x<<"\n";
	cout<<y<<"\n";
	kill(x,SIGUSR1);
	// kill(y,SIGUSR1);
	return 0;
}