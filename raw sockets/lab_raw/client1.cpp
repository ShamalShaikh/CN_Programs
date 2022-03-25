
#define DATA "Shamal"
#include <bits/stdc++.h>
#include"sham.h"
using namespace std;

int main(int argc, char **argv) {
  int sock, bytes, one = 1;
  // struct iphdr *ipHdr;
  char packet[20];

  struct sockaddr_in addr_in,myaddr;

  if((sock = socket(AF_INET, SOCK_RAW, 150)) < 0) {
    perror("Error while creating socket");
    exit(-1);
  }

  addr_in.sin_family = AF_INET;
  addr_in.sin_addr.s_addr = inet_addr("192.168.0.107");
  // addr_in.sin_port = htons(12312);


  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = inet_addr("192.168.0.107");
  // myaddr.sin_port = htons(9000);

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



  struct sockaddr_in saddr;
  int saddr_len = sizeof(saddr);
  char buffer[65536];
  // while(1){
    int buflen=recvfrom(sock,buffer,65536,0,(sockaddr *)&saddr,(socklen_t *)&saddr_len);
    if(buflen<0){
      perror("Error in recvfrom : ");
      return -1;
  }
  cout<<buffer<<endl;
  char * newbuf=(buffer+20);
  cout<<"shamal:  "<<newbuf<<endl;
  unsigned short iphdrlen;
  struct sockaddr_in source,dest;
  struct iphdr *ip = (struct iphdr*)(buffer);
  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = ip->saddr;
  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = ip->daddr;
  
  cout<<"version : "<<(unsigned int)ip->version<<endl;
  cout<<"Internet Header Length in words : "<<(unsigned int)ip->ihl<<endl;
  cout<<"Internet Header Length in Bytes : "<<((unsigned int)(ip->ihl))*4<<endl;
  cout<<"Type Of Service : "<<(unsigned int)ip->tos<<endl;
  cout<<"Total Length in Bytes"<<ntohs(ip->tot_len)<<endl;
  cout<<"Identification : "<<ntohs(ip->id)<<endl;
  cout<<"Time To Live : "<<(unsigned int)ip->ttl<<endl;
  cout<<"Protocol : "<<(unsigned int)ip->protocol<<endl;
  cout<<"Header Checksum : "<<ntohs(ip->check)<<endl;
  cout<<"Source IP : "<<inet_ntoa(source.sin_addr)<<endl;
  cout<<"Destination IP :"<<inet_ntoa(dest.sin_addr)<<endl;

  cout<<endl;

  // print_tcp_packet(buffer,sizeof(buffer)); 
// }

     return 0;
}