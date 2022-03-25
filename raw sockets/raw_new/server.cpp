#include<bits/stdc++.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>


using namespace std;
int main()
{
	int rsfd;
	sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=inet_addr("192.168.0.107");
	cout<<myaddr.sin_addr.s_addr<<"\n";
	//myaddr.sin_port=htons(9000);

	rsfd=socket(AF_INET,SOCK_RAW,146);
	perror("socket");
	cout<<"\n";

	// int b=bind(rfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
	// if(b<0)
	// 	perror("bind");
	// cout<<"\n";

	
	struct sockaddr_in saddr;
	int saddr_len = sizeof (saddr);
	 
	
	char buffer[65536];
	while(1){
		int buflen=recvfrom(rsfd,buffer,65536,0,(sockaddr *)&saddr,(socklen_t *)&saddr_len);
		if(buflen<0){
			perror("Error in recvfrom : ");
			return -1;
	}

	cout<<buffer<<endl;
	char * newbuf=(buffer+20);
	cout<<"shamal:	"<<newbuf<<endl;
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

}


return 0;
}