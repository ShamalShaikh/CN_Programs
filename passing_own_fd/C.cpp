#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<bits/stdc++.h>

using namespace std;
#define SA struct sockaddr
#define SA_in struct sockaddr_in
#define SA_un struct sockaddr_un

#define PORT 18725

int main(int argc, char const *argv[])
{
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);

	SA_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = PORT;

	connect(sfd,(SA*) &addr, sizeof(addr));
	char buf[100];

	recv(sfd,buf,100,0);

	cout<<buf<<"\n";

	cin>>buf;

	send(sfd,buf,100,0);

	cout<<"done======\n";

	return 0;
}