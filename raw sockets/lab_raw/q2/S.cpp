#include"sham.h"

int main(int argc, char const *argv[])
{
	int rsfd = socket(AF_INET,SOCK_RAW,120);
	perror("socket");
	cout<<"\n";

	sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=INADDR_ANY;
	// myaddr.sin_port=htons(9000);	
while(1){
	sockaddr_in caddr;
	int caddr_len = sizeof(caddr);
	unsigned char buffer[65536];
	int buflen=recvfrom(rsfd,buffer,65536,0,(sockaddr *)&caddr,(socklen_t *)&caddr_len);
	perror("recvfrom : ");
	cout<<"\n";

	unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)(buffer +  sizeof(struct ethhdr));
    // cout<<iph->ihl<<"\n";
    iphdrlen = iph->ihl*4;
    // iphdrlen = 20;
    // cout<<iphdrlen<<"\n";
    // cout<<sizeof(struct ethhdr)<<"\n";
     
    struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen  + sizeof(struct ethhdr));
     
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
     
    printf( "\n\n***********************UDP Packet*************************\n");
     
    // print_ip_header(Buffer,Size);           
     
    printf( "\nUDP Header\n");
    printf( "   |-Source Port      : %d\n" , ntohs(udph->source));
    printf( "   |-Destination Port : %d\n" , ntohs(udph->dest));
    printf( "   |-UDP Length       : %d\n" , ntohs(udph->len));
    printf( "   |-UDP Checksum     : %d\n" , ntohs(udph->check));
     
    printf( "\n");
         
    printf( "Data Payload\n");    
     
    //Move the pointer ahead and reduce the size of string
    PrintData(buffer + 20 , buflen - 20);
     
    printf( "\n###########################################################");

	sockaddr_in vaddr;
	int vaddr_len = sizeof(vaddr);
	vaddr.sin_family=AF_INET;
	vaddr.sin_addr.s_addr=INADDR_ANY;
	vaddr.sin_port=htons(9000);	

    int bytes = sendto(rsfd,buffer,65536, 0, (struct sockaddr *) &vaddr, sizeof(vaddr));


    char msg[3];
    recvfrom(rsfd,msg,3,0,(sockaddr *)&vaddr,(socklen_t *)&vaddr_len);
	perror("recvfrom : ");
	cout<<"\n";

	if(strcmp(msg,"OK")){
		cout<<"VERIFIED\n";
	}
	else{
		cout<<"REJECTED\n";
	}
}
	return 0;
}