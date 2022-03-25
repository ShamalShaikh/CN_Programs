#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include<bits/stdc++.h>
#include<arpa/inet.h>
#include <sys/types.h> /* basic system data types */
#include <errno.h> /* for the EINTR constant */
#include <sys/wait.h> /* for the waitpid() system call */
#include <sys/un.h> /* for Unix domain sockets */
#define MAXLINE BUFSIZ
#define SA struct sockaddr
#define UNIXSTR_PATH "~/Desktop/CN_Prog/UDS/sham.str"
#define SERV_PORT 5134
#define LISTENQ 20

int main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_in	servaddr;
	int pid = 0, n;
	char buf[1024];
	if (argc != 2)
		printf("usage: tcpcli <IPaddress>");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1619);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (SA *) &servaddr, sizeof(servaddr));


	pid = fork();
	while(1) 
	{
		if(pid==0)
		{
			while((n=read(0,buf,1024))>0) 
			{
				buf[n-1]='\0';
				write(sockfd, buf, n);
			}
		}
		else 
		{
			while((n=read(sockfd, buf, 1024))>0)  
			{
				buf[n]='\0';
				printf("Message: %s\n", buf);
			}
		}
	}		
	exit(0);
}
