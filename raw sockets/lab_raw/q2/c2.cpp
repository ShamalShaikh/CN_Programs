#include "sham.h"

int main(int argc, char const *argv[])
{
	int rsfd = socket(AF_INET,SOCK_RAW,120);
	perror("socket");
	cout<<"\n";

	sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=INADDR_ANY;
	myaddr.sin_port=12000;

	char p1[100];
	char p2[100];
	cout<<myaddr.sin_addr.s_addr<<"\n";
	int a  = myaddr.sin_addr.s_addr;
	cout<<itoa(a,p1,10)<<"\n";
	cout<<itoa(myaddr.sin_port,p2,10)<<"\n";
	char buffer[100];
	cout<<"sham\n";
	strcpy(buffer,p1);
	cout<<"sham\n";
	strcat(buffer," ");
	strcat(buffer,p2);

	cout<<buffer<<"\n";

	sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;

	int bytes = sendto(rsfd,buffer,sizeof(buffer), 0, (struct sockaddr *) &saddr, sizeof(saddr));
	perror("sendto :");
	cout<<"\n";

	sockaddr_in vaddr;
	int vaddr_len = sizeof(vaddr);
	vaddr.sin_family=AF_INET;
	vaddr.sin_addr.s_addr=INADDR_ANY;
	vaddr.sin_port=htons(9000);	

	char s[strlen(buffer)];
	int buflen=recvfrom(rsfd,s,sizeof(s),0,(sockaddr *)&vaddr,(socklen_t *)&vaddr_len);
	perror("recvfrom :");
	cout<<"\n";	

	char msg[3];
	if(strcmp(s,buffer) == 0){
		strcpy(msg,"OK"); 
	}
	else{
		strcpy(msg,"NO"); 
	}

	sendto(rsfd,msg,sizeof(msg), 0, (struct sockaddr *) &vaddr, sizeof(vaddr));
	perror("sendto :");
	cout<<"\n";

	cout<<"END\n";

	return 0;
}