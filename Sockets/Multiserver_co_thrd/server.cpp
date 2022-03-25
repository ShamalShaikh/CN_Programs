#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;
#define PORT 8080 

char client_message[2000];
char buffer[1024] = {0}; 

pthread_mutex_t locks = PTHREAD_MUTEX_INITIALIZER;

void * socketThread(void *arg)
{
  int nsfd = *((int *)arg);
  pthread_mutex_lock(&locks);
  recv(nsfd , client_message , 2000 , 0);

  // Send message to the client socket 
  cout<<"Enter SocketThread!\n";
  cout<<client_message<<"\n";
  char *message = (char*)malloc(sizeof(client_message)+20);
  strcpy(message,"HELLO WORLD ! ");
  strcat(message,client_message);
  strcat(message,"\n");
  strcpy(buffer,message);
  free(message);

  sleep(1);

  send(nsfd,buffer,13,0);

  printf("Exit socketThread \n");
  pthread_mutex_unlock(&locks);
  close(nsfd);
  return NULL;
}

int main(int argc, char const *argv[]) 
{ 
    int sfd, nsfd,opt=1;
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
 
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(sfd, 5) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }

    pthread_t tid[5];
    int i = 0;
    while(1){ 

    if ((nsfd = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"accepted\n";
    if( pthread_create(&tid[i++], NULL, socketThread, &nsfd) != 0)
           printf("Failed to create thread\n");
    cout<<"returned from create\n";   
    if( i >= 5)
        {
          i = 0;
          while(i < 5)
          {
            cout<<"joined : "<<i<<"\n";
            pthread_join(tid[i++],NULL);
          }
          i = 0;
        }   
    }
    return 0; 
} 