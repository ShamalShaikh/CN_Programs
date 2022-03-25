#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
using namespace std;

#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int sfd, nsfd, valread, peer,sock; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(sfd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }

    while(1){ 
    if ((nsfd = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    if ((peer = getpeername(nsfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("getpeername"); 
        exit(EXIT_FAILURE); 
    }

    cout<<address.sin_family<<"\n"; 
    cout<<address.sin_addr.s_addr<<"\n"; 
    cout<<address.sin_port<<"\n"; 

    if ((sock = getsockname(nsfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("getpeername"); 
        exit(EXIT_FAILURE); 
    }

    cout<<address.sin_family<<"\n"; 
    cout<<address.sin_addr.s_addr<<"\n"; 
    cout<<address.sin_port<<"\n"; 

    sleep(5);

    valread = read( nsfd , buffer, 1024); 
    printf("%s\n",buffer ); 

    send(nsfd , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 

    }
    return 0; 
} 