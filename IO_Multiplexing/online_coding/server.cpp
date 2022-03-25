#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>  
int main() 
{ 
    int fd[2];  
  	mkfifo("save", 0666); 
    char str1[BUFSIZ], str2[BUFSIZ];
    int c = fork();
    if(c==0){
    	execlp("gnome-terminal","gnome-terminal",NULL);
    }
	fd[0] = open("save",O_RDONLY);
	sleep(1);	
	read(fd[0],str1,BUFSIZ);
	printf("%s",str1);
	close(fd[0]);

	FILE *fp = fopen("sys.cpp","w");
	fprintf(fp, "%s", str1);
    fclose(fp);

	sleep(1);
	system("g++ sys.cpp -o sys.exe");
	sleep(1);
	FILE *lfp = popen("./sys.exe i.txt","r");
	int lfd = fileno(lfp);
	sleep(1);
	read(lfd,str2,BUFSIZ);
	close(lfd);
	
	fp = fopen("o.txt","r");
	fgets(str1,BUFSIZ,fp);
    fclose(fp);

    str1[strlen(str1)-1] = '\0';
	printf("%s\n",str1);
	printf("%s\n",str2);	
	if(strcmp(str1,str2) == 0){
		printf("Accepted\n");
	}
	else{
		printf("Not Accepted\n");
	}
    return 0; 
} 
