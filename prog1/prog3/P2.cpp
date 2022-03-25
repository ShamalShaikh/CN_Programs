#include <stdio.h>
#include <semaphore.h>
#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>
using namespace std;

int main(){
	
	int pid,c=0,t=5;
	sem_t *sem1 = sem_open("sem_1", O_EXCL,0644,0);
	sem_t *sem2 = sem_open("sem_2", O_EXCL,0644,1);
	if (sem1 == SEM_FAILED) {
     perror("Failed to open semphore");
     exit(-1);
	}
	if (sem2 == SEM_FAILED) {
     perror("Failed to open semphore");
     exit(-1);
	}

	pid=fork();
	if(pid==0){
		while(t--){
		sem_wait(sem2);
		cout<<"Hey! In process 1";
		c++;
		cout<<" -> "<<c<<" time"<<endl;	
		sem_post(sem1);
		sem_wait(sem2);
		cout<<"You Again in  Process 1 ?!";
		c++;
		cout<<" -> "<<c<<" time"<<endl;
		sem_post(sem1);
		}		
	}
	else{
		while(t--){
	    sem_wait(sem1);
	 	cout<<"Hey! In process 2";
	 	c++;
	 	cout<<" -> "<<c<<" time"<<endl;
	 	sem_post(sem2);
	 	sem_wait(sem1);
		cout<<"You Again in  Process 2 ?!";
		c++;
		cout<<" -> "<<c<<" time"<<endl;
		sem_post(sem2);	
		}			 	
		}
return 0;
}
