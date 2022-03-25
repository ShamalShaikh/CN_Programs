#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#define SA struct sockaddr
#define BUFLEN 256
using namespace std;

int main(int ac,char *av[]){
	int sfd[6],i=0;
	struct sockaddr_in addr[6];
	struct sockaddr_in address;
	socklen_t addrlen;
	ifstream fin("config.txt");
	string line;
	vector<string> tokens;
	while(getline(fin,line)){
		sleep(2);
		istringstream iss(line);
    	string token;
    	while(std::getline(iss, token, '\t'))
        tokens.push_back(token);
    	if(tokens[1+i*4].compare("TCP") == 0){
			sfd[i] = socket(AF_INET,SOCK_STREAM,0);
    	}
		else{
			if((sfd[i] = socket(AF_INET,SOCK_DGRAM,0))<=0){
				perror("socket : ");
				cout<<"\n";
			}
		}
		
		int sock = getsockname(sfd[i], (struct sockaddr *)&address, (socklen_t*)&addrlen);

		cout<<"sock val = "<<sock<<"\n";
		cout<<"sock family = "<<address.sin_family<<"\n"; 
	    cout<<"sock address = "<<address.sin_addr.s_addr<<"\n"; 
	    cout<<"sock port = "<<address.sin_port<<"\n"; 

		cout<<tokens[0+i*4]<<"\n";
		int opt =1;
	    if (setsockopt(sfd[i], SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	    {
	        perror("setsockopt");
	        exit(3);
	    }
		addr[i].sin_family = AF_INET;
		addr[i].sin_addr.s_addr = INADDR_ANY;
		addr[i].sin_port = (stoi(tokens[0+i*4]));

		// if(tokens[1+i*4].compare("TCP") == 0){
		// 	address.sin_family = AF_INET;
		// 	address.sin_addr.s_addr = INADDR_ANY;
		// 	address.sin_port = (stoi(tokens[0+i*4])+10);
		// 	if(bind(sfd[i],(SA*)&address,sizeof(sockaddr_in))<=0){
		// 		perror("\nbind : ");
		// 		cout<<"\n";
		// 	}
		// }

		if(tokens[1+i*4].compare("TCP") == 0){
				if(connect(sfd[i],(SA*)&addr[i],sizeof(addr[i]))<=0){
					perror("\nconnect : ");
					cout<<"\n";
			}
		}
		else{
			cout<<"shamal is here \n";
			char message[BUFLEN];
			char buf[BUFLEN];
			socklen_t addr2len;
			cout<<"Enter the message :\n";
	        cin.getline(message,BUFLEN);
	        //send the message
	        if (sendto(sfd[i], message, strlen(message) , 0 , (SA*)&addr[i],sizeof(addr[i]))==-1)
	        {
	            perror("sendto() : ");
	            cout<<"\n";
	        }
	        //receive a reply and print it
	        //clear the buffer by filling null, it might have previously received data
	        memset(buf,'\0', BUFLEN);
	        //try to receive some data, this is a blocking call
	        if (recvfrom(sfd[i], buf, BUFLEN, 0, (SA*)&addr[i],(socklen_t*) &addr2len) == -1)
	        {
	            perror("recvfrom() : ");
	            cout<<"\n";
	        }

	        puts(buf);
		}
		
		int peer = getpeername(sfd[i], (struct sockaddr *)&address, (socklen_t*)&addrlen);
		cout<<"peer val = "<<peer<<"\n";
		if(peer == -1){
			perror("peer : ");
		}
	    cout<<"peer family = "<<address.sin_family<<"\n"; 
	    cout<<"peer address = "<<address.sin_addr.s_addr<<"\n"; 
	    cout<<"peer port = "<<address.sin_port<<"\n"; 
	    ++i;
	}

	for(int j=0;j<i;++j){
		close(sfd[j]);
	}
	return 0;
}