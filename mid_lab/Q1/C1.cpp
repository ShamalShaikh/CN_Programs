
#include"sham.h"

int main(int argc,char * argv[]){
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	cout<<"sham\n";

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
		perror("\n connect : ");
	else 
		printf("\nconnect succesful\n");

	char message[] = "3";
	char message1[] = "Shamal Shaikh\n";

 if( send(sfd , message , strlen(message) , 0) < 0)
  {
          printf("Send failed\n");
  }		

 if( send(sfd , message1 , strlen(message1) , 0) < 0)
  {
          printf("Send failed\n");
  }	
  char buffer[1024] = {0}; 

	if(read(sfd , buffer, 1024) < 0)
  {
     printf("Receive failed\n");
  }	
  else{
  	printf("%s\n",buffer ); 
  }
	return 0;
}