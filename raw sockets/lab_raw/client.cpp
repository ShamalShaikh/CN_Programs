#include<iostream>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<netinet/tcp.h>
#include<stdio.h>
// #include<linux/ip.h>
#include <stdlib.h>
#include <errno.h>
#define __USE_BSD
#define __FAVOR_BSD
using namespace std;

unsigned short csum (unsigned short *buf, int nwords)
{
  unsigned long sum;
  for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}


int main()
{
	int one=1;
	cout<<"spoofing ip address using raw sockets\n";
	struct iphdr *ipHdr;
	
	int fd=socket(AF_INET,SOCK_RAW,146);
	perror("socket : ");
	cout<<fd<<"\n";
	
	sockaddr_in sin,din;
	
	sin.sin_family=AF_INET;
	sin.sin_port=9000;
	sin.sin_addr.s_addr=inet_addr("127.0.0.1");
	// sin.sin_addr.s_addr=INADDR_ANY;
	
	if(bind(fd,(sockaddr*)&sin,sizeof(sin))<0)
	perror("Bind failed\n");

	if(setsockopt(fd, IPPROTO_IP, IP_HDRINCL, (char *)&one, sizeof(one)) < 0) {
	    perror("Error while setting socket options");
	    exit(-1);
 	}

 	char packet[500];
 	ipHdr=(struct iphdr *)packet;

	ipHdr->ihl = 5;
	ipHdr->version = 4; 
	ipHdr->tos = 0;
	ipHdr->tot_len = sizeof(struct iphdr);
	ipHdr->id = htons(54321); 
	ipHdr->frag_off = 0x00; 
	ipHdr->ttl = 0xFF;
	ipHdr->protocol = 146; 
	ipHdr->check = 0; 
	ipHdr->saddr = inet_addr("99.99.99.99");
	ipHdr->daddr = inet_addr("127.0.0.1");

    char * buf=(char *)ipHdr;
    strcat(buf,"hello");

	din.sin_family=AF_INET;
	// din.sin_port=9001;
	din.sin_addr.s_addr=inet_addr("127.0.0.1");//"172.30.34.229");//inet_addr("172.30.104.219");
	
		
		//if(sendto(fd,s.c_str(),s.length(),0,(sockaddr*)&din,sizeof(din))<0)
		if(sendto(fd,buf,29,0,(sockaddr*)&din,sizeof(din))<0)
		cout<<"Sent failed\n";
		else
		cout<<"Sent succeeded\n";
	//}
	
}