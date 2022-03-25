#include "sham.h"
int main(int argc, char const *argv[])
{
	int rsfd = socket(AF_INET,SOCK_RAW,120);
	perror("socket");
	cout<<"\n";

	sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=INADDR_ANY;
	myaddr.sin_port=9000;

	sockaddr_in saddr;
	int saddr_len = sizeof(saddr);
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
// while(1){
	char s[100];
	int buflen=recvfrom(rsfd,s,sizeof(s),0,(sockaddr *)&saddr,(socklen_t *)&saddr_len);
	perror("recvfrom :");
	cout<<"\n";	

	sockaddr_in caddr;
	int caddr_len = sizeof(caddr);
	caddr.sin_family=AF_INET;
	char p[1];
	p[0] = s[0];
	caddr.sin_addr.s_addr=atoi(p);
	char arr[10];
	for(int i=2;s[i]!='\0';++i){
		arr[i] = s[i];
	}
	cout<<arr<<"\n";
	int a = atoi(arr);
	cout<<a<<"\n";
	caddr.sin_port=a;	

	int bytes = sendto(rsfd,s,sizeof(s), 0, (struct sockaddr *) &caddr, sizeof(caddr));
	perror("sendto :");
	cout<<"\n";

	char msg[10];
	buflen=recvfrom(rsfd,msg,sizeof(msg),0,(sockaddr *)&caddr,(socklen_t *)&caddr_len);
	perror("recvfrom :");
	cout<<"\n";	

	bytes = sendto(rsfd,msg,sizeof(msg), 0, (struct sockaddr *) &saddr, sizeof(saddr));
	perror("sendto :");
	cout<<"\n";
// }
	return 0;
}