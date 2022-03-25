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
#include <linux/if_ether.h> 
#define MSG_LEN 10
#if !defined(IPVERSION)
#define IPVERSION 4
#endif 
#include<bits/stdc++.h>
using namespace std;


struct dhcpmessage
{
    uint8_t op;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
    char chaddr[16];
    char sname[64];
    char file[128];
    char magic[4];
    char opt[3];
} __attribute__((__packed__));

unsigned short csum(unsigned short *ptr,int nbytes) 
{
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;
	
	return(answer);
}

uint8_t *
allocate_ustrmem (int len) {

  uint8_t *tmp;

  if (len <= 0) {
    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n", len);
    exit (EXIT_FAILURE);
  }

  tmp = (uint8_t *) malloc (len * sizeof (uint8_t));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (uint8_t));
    return (tmp);
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
    exit (EXIT_FAILURE);
  }
}
  
int main(int argc,char *argv[])
{
	unsigned char *packet;
	struct ethhdr *eth = (struct ethhdr *)packet;
	struct iphdr *iph = (struct iphdr *)(packet  + sizeof(struct ethhdr) );
	// struct udphdr *udp=(struct udphdr*)(packet + sizeof(struct iphdr) + sizeof(struct ethhdr));

	struct in_addr saddr,daddr;
	struct sockaddr_in clin;
	unsigned short sport,dport;
	int sfd,on=1,n;
	char *p="Message";

  	if(argc < 5)  {
  	  fprintf(stderr,"usage: %s source_port source_address dest_port dest_address\n",
		    argv[0]);
  	  exit(1);
  	}

	sport=(unsigned short)atoi(argv[1]);
	saddr.s_addr=inet_addr(argv[2]);

	dport=(unsigned short)atoi(argv[3]);
	daddr.s_addr=inet_addr(argv[4]);

	sfd=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
	setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,(char *)&on,sizeof(on));


	struct dhcpmessage *dhcpmsg;
	cout<<sizeof(dhcpmessage)<<"\n";
	bzero(dhcpmsg,sizeof(dhcpmsg));
	dhcpmsg->op = 1;
	dhcpmsg->htype = 1;
	dhcpmsg->hlen = 6;
	dhcpmsg->hops = 0;
	dhcpmsg->xid = htonl(1000);
	dhcpmsg->secs = htons(0);
	dhcpmsg->flags = htons(0x8000);
	dhcpmsg->chaddr[0] = 0x08;
	dhcpmsg->chaddr[1] = 0x00;
	dhcpmsg->chaddr[2] = 0x27;
	dhcpmsg->chaddr[3] = 0x80;
	dhcpmsg->chaddr[4] = 0xf0;
	dhcpmsg->chaddr[5] = 0xb3;
	dhcpmsg->magic[0]=99;
	dhcpmsg->magic[1]=130;
	dhcpmsg->magic[2]=83;
	dhcpmsg->magic[3]=99;
	dhcpmsg->opt[0]=53;
	dhcpmsg->opt[1]=1;
	dhcpmsg->opt[2]=1;


	memset((char *)iph,'\0',sizeof(struct iphdr));
	iph->ihl=5;
	iph->ttl=60;
	iph->version=IPVERSION;
	iph->tot_len=htons(sizeof(packet));
	iph->id=htons(getpid());
	iph->protocol=IPPROTO_UDP;
	iph->saddr=saddr.s_addr;
	iph->daddr=daddr.s_addr;
	iph->check=0;

	// udp = (struct udphdr *)(packet+sizeof(struct iphdr));
	// memset((packet+sizeof(struct udphdr)+sizeof(struct iphdr)),'0',MSG_LEN);
	// udp->source = htons(sport);
 //  	udp->dest = htons(dport);
 //  	udp->len = htons(sizeof(struct udphdr)+MSG_LEN);
 //  	udp->check = 0;
	// memcpy((packet+sizeof(struct iphdr)+sizeof(struct udphdr)),p,sizeof(p)+1);	

	// bzero(&clin,sizeof(clin));
	memset(&clin,'\0',sizeof(clin));
	clin.sin_family=AF_INET;
	clin.sin_port=htons(dport);
	clin.sin_addr=daddr;
	
if((n=sendto(sfd,&packet,sizeof(packet),0x0,(struct sockaddr*)&clin,sizeof(clin)))!=sizeof(packet))
{
	perror("Error:");
}
return 0;
}
	

	
