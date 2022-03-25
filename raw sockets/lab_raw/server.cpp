#include"sham.h"

	// int optval=1;
	// setsockopt(rsfd, IPPROTO_IP, SO_BROADCAST, &optval, sizeof(int));// IP_HDRINCL
	// cout<<"opt\n";
	int rsfd;

	struct sockaddr_in saddr;

	int saddr_len = sizeof(saddr);

	char buffer[65536];


void receive(){

	int buflen=recvfrom(rsfd,buffer,65536,0,(sockaddr *)&saddr,(socklen_t *)&saddr_len);
	perror("Error in recvfrom : ");

	char IP[16];
	inet_ntop(AF_INET, &saddr.sin_addr, IP, sizeof(IP));
	cout<<IP<<"\n";
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

using namespace std;
int main(int argc,char * argv[])
{
	
	sockaddr_in myaddr;

	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=inet_addr("192.168.0.107");
	myaddr.sin_port=htons(9000);
	
	rsfd=socket(AF_INET,SOCK_RAW,150);
	perror("socket");
	cout<<"\n";

	int b=bind(rsfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
	perror("bind");
	cout<<"\n";

	// int myaddr_len = sizeof (myaddr);

	// unsigned char * packet = (unsigned char *) malloc(65536);
	// memset(packet,0,65536);
	// // while(1){
	// 	int packetlen=recvfrom(rsfd,packet,65536,0,(sockaddr *)&myaddr,(socklen_t *)&myaddr_len);
	// 	if(packetlen<0){
	// 		perror("Error in recvfrom : ");
	// 		return -1;
	// }

	// struct ethhdr *eth;
 //    eth = (struct ethhdr *) packet;

	// print_ethernet_header(packet,packetlen);

	// print_ip_header(packet,packetlen);

	// // if(iph->protocol == 6)
	// print_tcp_packet(packet,packetlen);	

	// // else if(ip->protocol == 14)
	// print_udp_packet(packet,packetlen);

	// unsigned char * data = (packet + sizeof(iphdr) + sizeof(struct ethhdr) + sizeof(struct udphdr));

	// PrintData(data,sizeof(data));


	while(1){
	receive();
	int bytes;
	if((bytes = sendto(rsfd,"type : 1",8, 0, (struct sockaddr *) &saddr, sizeof(saddr))) < 0) {
    	perror("Error on sendto():");
  	}
  	else {
    	printf("Success! Sent %d bytes.\n", bytes);
  	}
  	// receive();
}





	// unsigned int client_len=sizeof(client);
	// cout<<"sending\n";
  	// sendto(rsfd,buff,strlen(buff)+1,0,(struct sockaddr*)&client,sizeof(client));
 //  	// cout<<buff<<" "<<strlen(buff)+1<<"\n";
 //  	perror("send : ");
 //  	cout<<"\n";
  

return 0;
}