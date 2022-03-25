#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include<bits/stdc++.h>
using namespace std;
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int csfd = 0, valread,sock; 

    struct sockaddr_in serv_addr,address;
    int addrlen = sizeof(address); 
    
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 

    if ((csfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(csfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    if ((sock = getsockname(csfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("getsockname"); 
        exit(EXIT_FAILURE); 
    }

    cout<<address.sin_family<<"\n"; 
    cout<<address.sin_addr.s_addr<<"\n"; 
    cout<<address.sin_port<<"\n"; 

    sleep(5);

    send(csfd , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    
    valread = read( csfd , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 