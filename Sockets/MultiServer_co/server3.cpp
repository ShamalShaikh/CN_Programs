#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
using namespace std;

void read_func(int nsfd,char buffer[]){
    int valread = read( nsfd , buffer, 1024); 
    printf("%s\n",buffer ); 
}

void write_func(int nsfd,char hello[]){


    send(nsfd , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
}
 
void serv_func(int nsfd,char buffer[]){
    read_func(nsfd,buffer);

    char hello[] = "Hello from server";
    write_func(nsfd,hello);
}

#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int sfd, nsfd, peer,sock; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    cout<<"In server 3\n";
    dup2(1,nsfd);
    dup2(0,nsfd);
    cout<<"nsfd = "<<sfd<<"\n";   

    serv_func(nsfd,buffer);
    return 0; 
} 