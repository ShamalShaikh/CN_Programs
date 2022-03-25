#include"sham.h"

void signal_handler(int signal)
{
        printf("Signal %d caught\n", signal);
}

char client_message[1024];
char buffer[1024] = {0}; 

pthread_mutex_t locks = PTHREAD_MUTEX_INITIALIZER;

void read_func(int nsfd,char buffer[]){
    int valread = read( nsfd , buffer, 1024); 
    printf("%s\n",buffer ); 
}

void write_func(int nsfd,char hello[]){


    send(nsfd , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
}

void serv_func(int nsfd,char buffer[]){
    read_func(nsfd,buffer);

    char hello[] = "Hello from server";
    write_func(nsfd,hello);
}

void * socketThread(void *arg)
{
  int nsfd = *((int *)arg);
  pthread_mutex_lock(&locks);
  serv_func(nsfd,client_message);
  printf("Exit socketThread \n");
  pthread_mutex_unlock(&locks);
  close(nsfd);
  return NULL;
}

int main(int argc, char* argv[]){
	
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	struct sigaction act;
        int ret = 0;

        act.sa_handler =  signal_handler;
        sigaction(SIGCONT, &act, NULL);
        ret = pause();
        if (-1 == ret)
                printf("Process exited\n");


	int sfd,opt=1;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully\n");

	bzero(&serv_addr,sizeof(serv_addr));

	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
		perror("\n bind : ");
	else 
		printf("\n bind successful ");

	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
		perror("\n accept ");
	else 
		printf("\n accept successful");

	char c[2];

	read(nsfd,c,sizeof(c));
	char C = c[0];
	pthread_t tid[5];
    int i = 0;
	switch(C){
		case '3' : {
					int pid;
                    if((pid = fork())<0){
                        perror("fork");
                        exit(1);
                    }else if(pid > 0){
                        close(nsfd);
                        // continue;
                    }else{
                        close(sfd);
                        serv_func(nsfd,buffer);
                    } 
                }
		break;
		case '2' : {
			    	if( pthread_create(&tid[i++], NULL, socketThread, &nsfd) != 0)
           				printf("Failed to create thread\n");
				    cout<<"returned from create\n";   
				    if( i >= 5)
				        {
				          i = 0;
				          while(i < 5)
				          {
				            cout<<"joined : "<<i<<"\n";
				            pthread_join(tid[i++],NULL);
				          }
				          i = 0;
				        } 
		}
		break;
		case '1' :	{
			int fd[3];

			fd_set readset;
			FD_ZERO(&readset);
	
			int max=-1;
	
			for(i=0;i<3;i++)
			{
				FD_SET(fd[i], &readset);
				if(fd[i]>max)
				max=fd[i];		
			}
			struct timeval t;
			t.tv_sec=3;
			t.tv_usec=100;
			int rv = select(max + 1, &readset, NULL, NULL, &t);
			if (rv == -1) 
			{
				perror("select");
			}
			
			else if (rv == 0) 
			{
		    		printf("Timeout occurred!\n");
			} 
			
			else 
			{
				int i;
				// check for events 
				for(i=0;i<3;i++)
		    		if (FD_ISSET(fd[i], &readset)) 
				{
					serv_func(nsfd,buffer);

					FD_CLR(fd[i],&readset);
		    		}
			} 

			close(fd[i]);
				}
		break;
	}

	cout<<"DONE HERE!!\n";

	return 0;
}