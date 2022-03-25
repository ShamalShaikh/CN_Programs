#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<ctype.h>
#include <poll.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include<iostream>
using namespace std;
// 1024 is maximum pipe limit  
int sigcount;
bool flag = true;
int fd[2][2]; 
char buf[1024];
int pid[2],pp1,pp2;
char str1[25], str2[25],str[25];

void print_G1(){

	sleep(2);
	pid[0] = fork();
	if(pid[0]>0){
  			pid[1] = fork();
  	}
  	
  	if(pid[0]>0 && pid[1] > 0){
	close(fd[0][0]);
	close(fd[1][0]);
	write(fd[0][1],str1,strlen(str1)+1);
	close(fd[0][1]);
	write(fd[1][1],str2,strlen(str2)+1);
	close(fd[1][1]);
	return;
	}
  	
  	if(pid[0] == 0){
  		setpgid(getpid(),getpid());
  		close(fd[0][1]);
  		while(1){
  			sleep(2);
	  		if(read(fd[0][0],str1,100)<0){
	  			sleep(5);
				cout<<"Enter Input : \n";				
				read(0,str,100);
				
			}
			else{
				cout<<str1<<endl;
			}
  		}
		kill(getpid(),SIGTERM);
  	}
  	if(pid[1] == 0 && pid[0] != 0){
  		setpgid(getpid(),pid[0]);
  		close(fd[1][1]);
		while(1){	
			if(read(fd[1][0],str2,100)<0){
				sleep(5);				
				cout<<"Enter Input : \n";
				read(0,str,100);
			}
			else{
				cout<<str2<<endl;
			}
		}	
		kill(getpid(),SIGTERM);
  	}	
}

void print_G2(){
	write(pp1,str1,strlen(str1)+1);
	write(pp2,str2,strlen(str2)+1);	
}

void fn(int sig){
	
	flag = !flag;
	sigcount++;
}

int main() 
{   
    
    char cp[50];

    int pret;
	struct pollfd pfds[3];
	int timeout;

  	for(int i=0;i<2;++i){
  		if(pipe(fd[i])==-1)
  			return 1;
  	}
  	
  	system("g++ A.cpp -o A");
  	system("g++ B.cpp -o B");	
  	
	pp1 = fileno(popen("./A","w"));
	pp2 = fileno(popen("./B","w"));

	signal(SIGUSR1,fn);
	signal(SIGINT,SIG_DFL);
  	
    char myfifo[] = "myfifo"; 
    mkfifo(myfifo, 0666);  
  	char myfifo2[] = "myfifo2"; 
    mkfifo(myfifo2, 0666); 
    
    // Reads from C1 and C2 
    int ffd[2];   
    while(1){
    	ffd[0] = open(myfifo,O_RDONLY); 
		read(ffd[0], str1, 25);
		close(ffd[0]);
		ffd[1] = open(myfifo2,O_RDONLY); 
		read(ffd[1], str2, 25); 
		close(ffd[1]);
		if(flag){
			print_G1();
		}
		else{
			print_G2();
		}
    }
      		
   
//		read(ffd[1], str2, BUFSIZ); 
    
    
/*
	for(int i=0;i<2;++i){
	pfds[i].fd = ffd[i];
	pfds[i].events = POLLIN;
	}
	int afds = 2;
	while(afds>0){
		
		timeout = 5000;
		pret = poll(pfds,2,timeout);
		
		if(pret == 0){
			printf("%d\n",timeout);
		}
		else{
			for(int i=0;i<2;++i){
				if(pfds[i].revents & POLLIN){
					
					printf("BOT %d:",i+1);
					read(ffd[i],str,BUFSIZ);
					puts(str);
//					close(ffd[i]);
					afds--;	
				}
			}
		}
	}
close(ffd[0]);
close(ffd[1]);	
	*/
	
  	cout<<"signal count = "<<sigcount<<endl; 
close(fd[0][0]);
close(fd[1][1]);
close(fd[0][1]);
close(fd[1][0]);
close(pp1);
close(pp2);

return 0;  		
} 
