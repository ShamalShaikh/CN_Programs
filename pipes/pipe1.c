#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<ctype.h>
// 1024 is maximum pipe limit  
int main() 
{ 
  
    int fd[2][2]; 
    char buf[1024];
    char cp[50];     
    // intitializing pipe to fds
  	for(int i=0;i<2;++i){
  		if(pipe(fd[i])==-1)
  			return 1;
  	}
  	 	
  	char ans;
  	printf("\nSEND SOMETHING TO CHILD PROCESS\t");
    scanf("%[^\n]%*c",&ans);
    fflush(stdin);  	

	int pid = fork();
  	if(pid < 0){
  		return 2;
  	}
  	
	while(ans=='y' || ans=='Y'){
  	if(pid>0){

		close(fd[0][0]);
  		close(fd[1][1]);
  		
        printf("\n(Parent)Enter data\t");
        fgets(cp, 50, stdin);
        
        printf("\nData Writtent to Child: %s",cp);
        if(write(fd[0][1],cp,strlen(cp)+1) < 0)
        {
            break;
        }        

        if(read(fd[1][0],buf,sizeof(buf)) < 0)
        {
            break;
        }
        
        printf("\nParent Process Read: %s\n",buf);
        printf("\nSEND SOMETHING TO CHILD PROCESS\t");
        fflush(stdin);
        scanf(" %[^\n]%*c",&ans);
        if(ans=='n')
        {
                kill(pid,SIGKILL);
        }		
  	}
  	else{ 		
  		if(ans=='n')
        {
            kill(pid,SIGKILL);
        }

  		close(fd[0][1]);
  		close(fd[1][0]);
        if(read(fd[0][0],buf,sizeof(buf)) < 0)
        {
            break;
        }
        
        printf("\nChild Process Read: %s\n",buf);
        printf("\n(child)Enter data:\t");
        fflush(stdin);
        
        fgets(cp, 50, stdin);
        
        printf("\nData Written to Parent: %s",cp);
        if(write(fd[1][1],cp,strlen(cp)+1) < 0)
        {
            break;
        }
  	}
  }

close(fd[0][0]);
close(fd[1][1]);
close(fd[0][1]);
close(fd[1][0]);
return 0;  		
} 
