#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#define PORT 8080 

void * clientThread(void *arg)
{
  printf("In thread\n");
  char message[1000];
  char buffer[1024];
  int csfd;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
 
  csfd = socket(AF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  addr_size = sizeof(serverAddr);
  connect(csfd, (struct sockaddr *) &serverAddr, addr_size);
  strcpy(message,"Hello");

 if( send(csfd , message , strlen(message) , 0) < 0)
  {
          printf("Send failed\n");
  }

  if(recv(csfd, buffer, 1024, 0) < 0)
  {
     printf("Receive failed\n");
  }
 
  printf("Data received: %s\n",buffer);
  close(csfd);
  return NULL;
}
int main(){
  int i = 0;
  pthread_t tid[5];
  while(i< 5)
  {
    if( pthread_create(&tid[i], NULL, clientThread, NULL) != 0 )
           printf("Failed to create thread\n");
    i++;
  }

  sleep(5);
  i = 0;
  while(i< 5)
  {
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i);
  }
  return 0;
}