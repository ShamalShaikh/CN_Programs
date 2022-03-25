// OSS :
// AF_UNIX
// socket
// bind 
// listen 
// select
// accept
// send_fd

// S1 :
// AF_UNIX
// socket
// bind 
// listen 
// select
// accept
// read_fd
// recv
// send


// C1 : 
// AF_INET
// socket
// bind 
// listen 
// connnect
// send list
// send 
// recv
// send 
// recv

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
char paths[][100] = {"shamsocket","shamsocket2","shamsocket3","shamsocket4"};
int main(int argc, char const *argv[]) 
{ 
    int sfd,opt=1;
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t cli_len;
    int port_no=PORT;

    sem_unlink("/p1\n");
    
    sem_t *s1;

    s1 = sem_open("/p1",O_CREAT,0644,0);

    int client_socket[3] , max_clients = 3 , activity, i , valread , sd;  
    int max_sd;  
    fd_set readfds;  
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  

    if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    perror("\n socket \n");
    else printf("\n socket created successfully\n");

    if( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
    {  
        perror("setsockopt\n");  
        exit(1);  
    }  
    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
        perror("\n bind : \n");
    else 
        printf("\n bind successful \n");

    listen(sfd,10);
//
// for(int i=0;i<4;++i) 
//
    char list[3];
    int num[3],store[3],fds;
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
            int nsfd;
            if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
                perror("\n accept \n");
            else 
                printf("\n accept successful\n\n"); 
                           
            read(nsfd,list,3);

            for(int j=0;j<2;++j){
                char a = list[j];
                num[j] = atoi(&a);
            }

            for(int j=0;j<2;++j){
                // unlink("shamsocket\n");  
                struct sockaddr_un addr;
                int usfd = socket(AF_UNIX, SOCK_STREAM, 0);
                    if (usfd == -1)
                        cout<< "failed to create socket"<<endl;
                addr.sun_family = AF_UNIX;
                strcpy(addr.sun_path, paths[num[j]-1]);  
                cout<<paths[j]<<"\n";
                if (connect(usfd, (struct sockaddr *) &addr, sizeof( sockaddr_un)) == -1)
                cout<< ("failed to connect to socket\n");

                send_fd (usfd, nsfd); 
                bzero(&addr,sizeof(addr));
                // sem_wait(s1);
                cout<<"Notified that returned from server!\n";

                // int cfd = accept(usfd, NULL, NULL);
                // if (cfd == -1)
                //         cout<<"Failed to accept incoming connection"<<endl;
                cout<<"receiving..\n";
                // nsfd = recv_fd (cfd); 

            }             
        } 
    }

    return 0; 
} 

