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
    
       
    // Creating socket file descriptor 
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"sfd = "<<sfd<<"\n";   
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
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
        if (getsockname(sock, (struct sockaddr *)&address, &len) == -1)
    perror("getsockname");
else
    printf("port number %d\n", ntohs(sin.sin_port));

printf("port number %d\n", ntohs(sin.sin_port));
        // if ((peer = getpeername(nsfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
        // { 
        //     perror("getpeername"); 
        //     exit(EXIT_FAILURE); 
        // }

        // cout<<address.sin_family<<"\n"; 
        // cout<<address.sin_addr.s_addr<<"\n"; 
        // cout<<address.sin_port<<"\n"; 

        int pid;
        if((pid = fork())<0){   
            perror("fork");
            exit(1);
        }else if(pid > 0){
            close(nsfd);
            // wait(NULL);
            continue;
        }else{
            close(sfd);
            serv_func(nsfd,buffer);
            exit(0);
        } 
    }
    return 0; 
} 