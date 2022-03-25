#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>  
#include<pthread.h>
    int fd[4];
	char fifos[5][80];
	char str1[80], str2[80];    
void *reads(void *arg){
	fd[0] = open("Friends",O_RDONLY); 
	read(fd[0], str2, 80); 
	close(fd[0]);
	return NULL;
}

void *writes(void* arg){
	printf("abc ");
	int *x = (int*)arg;
	printf("is this here : %d\n",*x);
	fd[*x] = open(fifos[*x],O_WRONLY);
	write(fd[*x],str2,80);	 
   	close(fd[*x]);
   	return NULL;
}

int main() 
{ 
  
  	
  	mkfifo("Friends", 0666); 
    strcpy(fifos[0],"Friends");
 
   int p = fork();
    
    if(p==0){
    	int b = fork();
    	if(b==0){
    		int a = fork();
    		if(a==0){
    			execlp("gnome-terminal","gnome-terminal",NULL);
    		}
    		execlp("gnome-terminal","gnome-terminal",NULL);
    	}
    	execlp("gnome-terminal","gnome-terminal",NULL);
    }
 
	for(int i=1;i<=3;++i){
    fd[0] = open("Friends",O_RDONLY); 
    read(fd[0], str1, 80); 
    close(fd[0]); 

	strcpy(fifos[i],str1);
	mkfifo(str1,0666);
	fd[i] = open(str1,O_WRONLY);
	write(fd[i],"hi\n",10);	 
   	close(fd[i]);
}
	pthread_t reader, c[3];
	while(1){

		pthread_create(&reader,NULL,reads,NULL);	
		pthread_join(reader,NULL); 
		char s = str2[strlen(str2)-1];
		str2[strlen(str2)-1] = '\0';
		printf("\n%c",s);
		printf("%s\n",str2);
		if(str2 == "no"){
			break;
		}
		
		int n = atoi(&s);
		// printf("slksdnc\n");
		for(int x=1;x<=3;++x){
		printf("a");
			if(x!=n){
				pthread_create(&c[x-1],NULL,writes,&x); 							
			}
			pthread_join(c[x-1],NULL);
		}
	}
	
	
    return 0; 
} 
