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
    int csfd = 0, valread; 
    struct sockaddr_in serv_addr,;
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 

    if ((csfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    serv_addr.sin_addr.s_addr = INADDR_ANY;    

   
    if (connect(csfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    send(csfd , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    
    sleep(5);

    valread = read( csfd , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 