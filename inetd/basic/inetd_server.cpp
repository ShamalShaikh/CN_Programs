#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fstream>
#define SA struct sockaddr
#define BUFLEN 256
using namespace std;

	vector<string>tokens;
int main(int  ac,char *av[]){
	int sfd[20],n=0;
	struct sockaddr_in addr[20];
	ifstream fin("config.txt");
	string line;
	// cout<<"start\n";
	while(getline(fin,line)){
		cout<<"line :"<<line<<"\n";
		istringstream iss(line);
    	string token;
    	while(getline(iss, token, '\t'))
        	tokens.push_back(token);
    	// cout<<"hey\n";
    	if(tokens[1+n*4].compare("TCP") == 0){
			sfd[n] = socket(AF_INET,SOCK_STREAM,0);
    	}
		else{
			sfd[n] = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		}
		// Forcefully attaching socket to the port 8080
		int opt =1;
	    if (setsockopt(sfd[n], SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	    {
	        perror("setsockopt");
	        exit(3);
	    }

		addr[n].sin_family = AF_INET;
		addr[n].sin_addr.s_addr = INADDR_ANY;
		cout<<tokens[3+n*4]<<"\n";
		addr[n].sin_port = (stoi(tokens[0+n*4]));

		bind(sfd[n],(SA*)&addr[n],sizeof(addr[n]));
		// cout<<"leg\n";
		if(tokens[1+n*4].compare("TCP") == 0)
			listen(sfd[n],stoi(tokens[2+n*4]));
		
		struct sockaddr_in address;
		socklen_t addrlen;
		int sock = getsockname(sfd[n], (struct sockaddr *)&address, (socklen_t*)&addrlen);
		cout<<"sock val = "<<sock<<"\n";
		cout<<"sock family = "<<address.sin_family<<"\n"; 
	    cout<<"sock address = "<<address.sin_addr.s_addr<<"\n"; 
	    cout<<"sock port = "<<address.sin_port<<"\n";
	    cout<<"==========================\n";
		
		++n;
		// cout<<"bye\n";
	}

	fd_set rset;
	int maxfd=0;
	FD_ZERO(&rset);
	for(int i=0;i<n;++i){
		FD_SET(sfd[i],&rset);
		maxfd = max(maxfd,sfd[i]);
	}
	cout<<"yo!\n";

	timeval tv = { 15 };
	while(1){
		for(int i=0;i<n;++i){
			FD_SET(sfd[i],&rset);
			// maxfd = max(maxfd,sfd[i]);
		}
		int ret = select(maxfd+1,&rset,NULL,NULL,&tv);
		if(ret == 0){
			cout<<"NOT READY!\n";
			break;
		}	
		else{
			for(int i=0;i<n;++i){
				cout<<"parent server for loop time: "<<i<<" pid = "<<getpid()<<"\n";
				if(FD_ISSET(sfd[i],&rset)){
					int nsfd;
					if(tokens[1+i*4].compare("TCP") == 0){
					SA addr2;
					struct sockaddr_in address;
					socklen_t addr2len,addrlen;
						if((nsfd = accept(sfd[i],(SA*)&addr2,&addr2len))<=0){
							perror("\naccept : ");
							cout<<"\n";
							exit(2);
						}
					if(int peer = getpeername(nsfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)<=0){
						perror("\n peer : ");
						cout<<"\n";
					}
				    cout<<"peer family = "<<address.sin_family<<"\n"; 
				    cout<<"peer address = "<<address.sin_addr.s_addr<<"\n"; 
				    cout<<"peer port = "<<address.sin_port<<"\n";  
					int p = fork();
					if(p==0){
						for(int d=0;d<n;++d){
							close(sfd[d]);
						}
						cout<<"ready to rumble!!\n";
						string execsend = tokens[3+i*4];
						char ans[100];
						strcpy(ans,execsend.c_str());
						if(tokens[1+i*4].compare("TCP") == 0){
							// dup2(nsfd,0);
							// dup2(nsfd,1);
						}
						execlp(ans,ans,NULL);
						exit(1);
					}
					else{
						if(tokens[1+i*4].compare("TCP") == 0){
							close(nsfd);
						}
						else{
							close(sfd[i]);
						}
						// wait(NULL);
					}
					}
					else{
						struct sockaddr_in addr2;
						struct sockaddr_in address;
						socklen_t addr2len;
						int recv_len;
						char buf[BUFLEN];
						if ((recv_len = recvfrom(sfd[i], buf, BUFLEN, 0, (struct sockaddr *) &addr2, (socklen_t*)&addr2len)) == -1)
				      	{
				        	perror("recvfrom() : ");
				        	cout<<"\n";
				      	}
				         
				      	//print details of the client/peer and the data received
				      	buf[recv_len]='\0';
				      	printf("Received packet from %s:%d\n", inet_ntoa(addr2.sin_addr), ntohs(addr2.sin_port));
				      	printf("Data: %s\n" , buf);
				      	cin.clear();
				      	//buf[0]='\0';
				         
				      	//now reply the client with the same data
				      	if (sendto(sfd[i], buf, recv_len, 0, (struct sockaddr*) &addr2, addr2len) == -1)
				      	{
				        	perror("sendto() : ");
				        	cout<<"\n";
				      	}	
					}

					FD_CLR(sfd[i],&rset);
				}
			}
		}
	}
	for(int i=0;i<n;++i){
		close(sfd[i]);
	}
	return 0;
}