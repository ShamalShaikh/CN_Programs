#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string> 
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#define DATA "Shamal"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  int sock, bytes, one = 1;
  struct iphdr *ipHdr;
  // char * srcIP="127.0.0.1";
  // char * dstIP="192.168.0.106";
  // int dstPort = 8081;
  // int srcPort = 8080;

  char packet[20];

  struct sockaddr_in addr_in,myaddr;

  if((sock = socket(AF_INET, SOCK_RAW, argv[1])) < 0) {
    perror("Error while creating socket");
    exit(-1);
  }

  addr_in.sin_family = AF_INET;
  // addr_in.sin_port = htons(dstPort);
  addr_in.sin_addr.s_addr = inet_addr("192.168.0.103");


  myaddr.sin_family = AF_INET;
  // // myaddr.sin_port = htons(srcPort);
  myaddr.sin_addr.s_addr = INADDR_ANY;

  // int b=bind(sock,(sockaddr *)&myaddr, sizeof(myaddr));
  // perror("bind ");
  // cout<<"\n";
  // if(b<0){
  //   perror("Error in binding");
  //   exit(-1);
  // }

  
    if((bytes = sendto(sock,"hello",5, 0, (struct sockaddr *) &addr_in, sizeof(addr_in))) < 0) {
      perror("Error on sendto():");
    }
    else {
      printf("Success! Sent %d bytes.\n", bytes);
    }

  //     if(argc<2)cout<<"Enter protocol in arguments\n";
  // int rsfd=socket(AF_INET,SOCK_RAW,atoi(argv[1]));
  // if(rsfd==-1)custom_perror("socket")
  //   char buf[BUF_LEN];
  struct sockaddr_in client;
  socklen_t clilen=sizeof(client);
  cout<<"receive"<<endl;
  recvfrom(rsfd,buf,BUF_LEN,0,(sockaddr*)&client,(socklen_t*)clilen);
  perror("recv");
  struct iphdr *ip;
  ip=(struct iphdr*)buf;
  cout<<(buf+(ip->ihl)*4)<<endl;


     return 0;
}