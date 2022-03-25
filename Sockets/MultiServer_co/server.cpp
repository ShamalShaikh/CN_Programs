#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
#include<poll.h>
using namespace std;
#define PORT 8080 
int port[3] = {8080,7070,6060};
void socks(int &sfd){
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }    
    cout<<"sfd = "<<sfd<<"\n";   
}

void sockopt(int &sfd,struct sockaddr_in &address,int &addrlen,int port){
    // int opt = 1; 
    // if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    // { 
    //     perror("setsockopt"); 
    //     exit(EXIT_FAILURE); 
    // } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
}

void binds(int &sfd,struct sockaddr_in &address){
    if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
}

void listens(int &sfd){
    if (listen(sfd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
}
int main(int argc, char const *argv[]) 
{ 
    int sfd[3], nsfd[3], peer,sock; // used only one nsfd, does it work??
    struct sockaddr_in address[3];         // used only one addr
    int addrlen[3];
    for(int i=0;i<3;++i){
        addrlen[i] = sizeof(address[i]); 
    }
    struct sockaddr_in addr;         // used only one addr
    int adlen;
    char buffer[1024] = {0}; 
    char servers[3][10] = {"./s1","./s2","./s3"};
    struct pollfd pfds[4];
    int timeout,pret;
       
    
    for(int i=0;i<3;++i){
        // Creating socket file descriptor 
        socks(sfd[i]);  
        // Forcefully attaching socket to the port 8080 
        sockopt(sfd[i],address[i],addrlen[i],port[i]);  
        // Forcefully attaching socket to the port 8080 
        binds(sfd[i],address[i]);

        listens(sfd[i]);

        pfds[i].fd = sfd[i];
        pfds[i].events = POLLIN | POLLOUT;
    }



    while(1){ 
        timeout = 5000;
        pret = poll(pfds,3,timeout);
        cout<<pret<<"\n";
        if(pret>0){
            for(int i=0;i<3;++i){
                if(pfds[i].revents & POLLIN){
                    cout<<"pfds = "<<pfds[i].fd<<"\n";
                    if ((nsfd[i] = accept(sfd[i], (struct sockaddr *)&addr, (socklen_t*)&adlen))<0) 
                    { 
                        perror("accept"); 
                        exit(EXIT_FAILURE); 
                    } 
                    int pid;
                    if((pid = fork())<0){
                        perror("fork");
                        exit(1);
                    }else if(pid > 0){
                        close(nsfd[i]);
                        continue;
                    }else{
                        close(sfd[0]);
                        close(sfd[1]);
                        close(sfd[2]);
                        int save_w = dup(1);
                        int save_r = dup(0);
                        cout<<"Dupping now doing exec... Bye\n";
                        dup2(nsfd[i],0);
                        dup2(nsfd[i],1);
                        
                        execlp(servers[i],servers[i],NULL);
                    } 
                }
            }
        }
    }
    return 0; 
} 