/*
	Sending own usfd to other process
*/

#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<bits/stdc++.h>

using namespace std;
#define SA struct sockaddr
#define SA_in struct sockaddr_in
#define SA_un struct sockaddr_un

#define PORT 18725


int send_fd(int socket, int fd_to_send)
 {
  struct msghdr socket_message;
  struct iovec io_vector[1];

  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  /* storage space needed for an ancillary element with a paylod of length is CMSG_SPACE(sizeof(length)) */
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];
  int available_ancillary_element_buffer_space;

  /* at least one vector of one byte must be sent */
  message_buffer[0] = 'F';
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;

  /* initialize socket message */
  memset(&socket_message, 0, sizeof(struct msghdr));
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));
  memset(ancillary_element_buffer, 0, available_ancillary_element_buffer_space);
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = available_ancillary_element_buffer_space;

  /* initialize a single ancillary data element for fd passing */
  control_message = CMSG_FIRSTHDR(&socket_message);
  control_message->cmsg_level = SOL_SOCKET;
  control_message->cmsg_type = SCM_RIGHTS;
  control_message->cmsg_len = CMSG_LEN(sizeof(int));
  *((int *) CMSG_DATA(control_message)) = fd_to_send;

  return sendmsg(socket, &socket_message, 0);
 }
 
 
 
 
 
 int recv_fd(int socket)
 {
  int sent_fd, available_ancillary_element_buffer_space;
  struct msghdr socket_message;
  struct iovec io_vector[1];
  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];

  /* start clean */
  memset(&socket_message, 0, sizeof(struct msghdr));
  memset(ancillary_element_buffer, 0, CMSG_SPACE(sizeof(int)));

  /* setup a place to fill in message contents */
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = CMSG_SPACE(sizeof(int));

  if(recvmsg(socket, &socket_message, MSG_CMSG_CLOEXEC) < 0)
   return -1;

  if(message_buffer[0] != 'F')
  {
   /* this did not originate from the above function */
   return -1;
  }

  if((socket_message.msg_flags & MSG_CTRUNC) == MSG_CTRUNC)
  {
   /* we did not provide enough space for the ancillary element array */
   return -1;
  }

  /* iterate ancillary elements */
   for(control_message = CMSG_FIRSTHDR(&socket_message);
       control_message != NULL;
       control_message = CMSG_NXTHDR(&socket_message, control_message))
  {
   if( (control_message->cmsg_level == SOL_SOCKET) &&
       (control_message->cmsg_type == SCM_RIGHTS) )
   {
    sent_fd = *((int *) CMSG_DATA(control_message));
    return sent_fd;
   }
  }

  return -1;
 }


int main(){

  int usfd = socket(AF_UNIX,SOCK_STREAM,0);
  cout<<usfd<<"\n";
  SA_un addr3;
  bzero(&addr3,sizeof(addr3));
  addr3.sun_family = AF_UNIX;
  strcpy(addr3.sun_path, "ShamalShaikh");

  if (bind(usfd, (SA*) &addr3,sizeof(SA_un)) == -1)
    perror("Failed to bind to socket\n");
  if (listen(usfd3, 5) == -1)
    perror("Failed to listen on socket\n");

  int cfd = accept(usfd3, NULL, NULL);
  
  if (cfd == -1)
    perror("Failed to accept incoming connection\n");


  int usfd2 = socket(AF_UNIX,SOCK_STREAM,0);
  cout<<usfd2<<"\n";
  SA_un addr2;
  bzero(&addr2,sizeof(addr2));
  addr2.sun_family = AF_UNIX;
  strcpy(addr2.sun_path, "ShamalShaikh2");

  if (connect(usfd2, (struct sockaddr *) &addr2, sizeof( sockaddr_un)) == -1)
    cout<< ("failed to connect to socket");

  send_fd (usfd2, cfd); 
 //  // sleep(5);
 //  if (bind(usfd2, (SA*) &addr2,sizeof(SA_un)) == -1)
 //    perror("Failed to bind to socket\n");
 //  if (listen(usfd2, 5) == -1)
 //    perror("Failed to listen on socket\n");

 //  cfd = accept(usfd2, NULL, NULL);
 //  if (cfd == -1)
 //    perror("Failed to accept incoming connection\n");
  
 //  fds = recv_fd (cfd);



	// send_fd(usfd2,usfd);

	
	// int nsfd = recv_  fd(usfd);


	cout<<"-------sent---------\n";


	return 0;
}