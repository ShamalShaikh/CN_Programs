#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in_systm.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include<string.h>
#include <unistd.h>
#define MSG_LEN 10
#if !defined(IPVERSION)
#define IPVERSION 4
#endif 
#include<bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[])
{
	unsigned char packet[
	sizeof(struct iphdr)+
	sizeof(struct udphdr)+MSG_LEN];
	unsigned char *k;
	struct in_addr saddr,daddr;
	struct sockaddr_in clin;
	struct udphdr *udp;
	struct iphdr *iphdr;
	unsigned short sport,dport;
	int sfd,on=1,n;
	char p[]="Message";
	
  	// if(argc < 5)  {
  	//   fprintf(stderr,"usage: %s source_port source_address dest_port dest_address\n",
		 //    argv[0]);
  	//   exit(1);
  	// }



	
	sport=(unsigned short)atoi("68");
	saddr.s_addr=inet_addr("0.0.0.0");

	dport=(unsigned short)atoi("67");
	daddr.s_addr=inet_addr("198.168.0.255");

	sfd=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
	setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,(char *)&on,sizeof(on));
	// char interface[40];
	// strcpy (interface, "eth0");
	// setsockopt(sfd, SOL_SOCKET, SO_BINDTODEVICE, interface, sizeof(interface));

	
	iphdr=(struct iphdr *)packet;
	memset((char *)iphdr,'\0',sizeof(struct iphdr));
	iphdr->ihl=5;
	iphdr->ttl=60;
	iphdr->version=IPVERSION;
	iphdr->tot_len=htons(sizeof(packet));
	iphdr->id=htons(getpid());
	iphdr->protocol=IPPROTO_UDP;
	iphdr->saddr=saddr.s_addr;
	iphdr->daddr=daddr.s_addr;
	iphdr->check=0;

	udp = (struct udphdr *)(packet+sizeof(struct iphdr));
	memset((packet+sizeof(struct udphdr)+sizeof(struct iphdr)),'0',MSG_LEN);
	udp->source = htons(sport);
  	udp->dest = htons(dport);
  	udp->len = htons(sizeof(struct udphdr)+MSG_LEN);
  	udp->check = 0;
	memcpy((packet+sizeof(struct iphdr)+sizeof(struct udphdr)),p,sizeof(p)+1);	

	//bzero(&clin,sizeof(clin));
	memset(&clin,'\0',sizeof(clin));
	clin.sin_family=AF_INET;
	clin.sin_port=htons(dport);
	clin.sin_addr=daddr;


  // 	memset (&device, 0, sizeof (device));
 	// if ((device.sll_ifindex = if_nametoindex (interface)) == 0) {
  //  		 perror ("if_nametoindex() failed to obtain interface index ");
  //   	exit (EXIT_FAILURE);
  // 	}
  	
  // 	printf ("Index for interface %s is %i\n", interface, device.sll_ifindex);
	
if((n=sendto(sfd,&packet,sizeof(packet),0x0,(struct sockaddr*)&clin,sizeof(clin)))!=sizeof(packet))
{
	perror("Error:");	
}
socklen_t clin_len;

(n=recvfrom(sfd,&packet,sizeof(packet),0x0,(struct sockaddr*)&clin,(socklen_t*)&clin_len));
perror("recvfrom:");	

return 0;
}
	

	
