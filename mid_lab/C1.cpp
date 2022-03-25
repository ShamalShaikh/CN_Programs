#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
#include"sham.h"
using namespace std;
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    int sfd;
    struct sockaddr_in serv_addr;
    int port_no=PORT;

    bzero(&serv_addr,sizeof(serv_addr));

    if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
    perror("\n socket");
    else printf("\n socket created successfully\n");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
        perror("\n connect : ");
    else 
        printf("\nconnect succesful");



    return 0; 
} 