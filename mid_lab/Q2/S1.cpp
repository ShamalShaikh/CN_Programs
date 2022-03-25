#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
#include<poll.h>
#include"sham.h"
using namespace std;
#define PORT 8080 

void socks(int &sfd){
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed\n"); 
        exit(EXIT_FAILURE); 
    }    
    cout<<"sfd = "<<sfd<<"\n";   
}

void sockopt(int &sfd,struct sockaddr_in &address,int &addrlen,int port){
    // int opt = 1; 
    // if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    // { 
    //     perror("setsockopt\n"); 
    //     exit(EXIT_FAILURE); 
    // } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
}

void binds(int &sfd,struct sockaddr_in &address){
    if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed\n"); 
        exit(EXIT_FAILURE); 
    } 
}

void listens(int &sfd){
    if (listen(sfd, 3) < 0) 
    { 
        perror("listen\n"); 
        exit(EXIT_FAILURE); 
    }
}

int main(int argc, char const *argv[]) 
{ 
        int sfd, cfd, fds;
        struct sockaddr_un addr;
        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
                cout<<"Failed to create socket"<<endl;

        sem_t *s1;
        s1 = sem_open("/p1",O_CREAT,0644,0); 
        int client_socket[3] , max_clients = 3 , activity, i , valread , sd;  
        int max_sd;  
        fd_set readfds;
        for (i = 0; i < max_clients; i++)  
        {  
            client_socket[i] = 0;  
        }      

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        unlink("shamsocket");
        strncpy(addr.sun_path, "shamsocket", sizeof(addr.sun_path) - 1);
        // cout<<"start binding..\n";
        if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
              cout<<"Failed to bind to socket"<<endl;
          // cout<<"listening...\n";
        if (listen(sfd, 5) == -1)
               cout<<"Failed to listen on socket"<<endl;

    while(1){ 
        FD_ZERO(&readfds);  
        FD_SET(sfd, &readfds);  
        max_sd = sfd;  
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            sd = client_socket[i];  
            if(sd > 0)  
                FD_SET( sd , &readfds);  
            if(sd > max_sd)  
                max_sd = sd;  
        }  
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error\n");  
        }  
        if (FD_ISSET(sfd, &readfds))  
        {  
            cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
                cout<<"Failed to accept incoming connection"<<endl;
            cout<<"receiving..\n";
        fds = recv_fd (cfd); 

        char buf[1024] = {0};

        read(fds,buf,1024);

        cout<<buf<<"\n";

        for(int i=0;buf[i]!='\0';++i){
            buf[i] = toupper(buf[i]);
        }

        send(fds,buf,1024,0);
        close(fds);
        // struct sockaddr_un naddr;
        // int nsfd = socket(AF_UNIX, SOCK_STREAM, 0);
        // if (nsfd == -1)
        //     cout<< "failed to create socket"<<endl;
        // naddr.sun_family = AF_UNIX;
        // unlink("shamsocket");
        // strcpy(naddr.sun_path, "shamsocket");   
        // // sem_post(s1);
        // if (connect(nsfd, (struct sockaddr *) &naddr, sizeof( sockaddr_un)) == -1)
        //     perror("failed to connect to socket");
        // // cout<<"before send...\n";
        // send_fd (nsfd, fds); 


        } 

        
    }

    return 0; 
} 