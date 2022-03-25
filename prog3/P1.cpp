#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main(){
	int x=1,y=1,t=2;
	int c = fork();

	if(c>0){
		while(t--){
//		x--;
		wait(&x);
		cout<<"S1"<<endl;
		cout<<"S2"<<endl;	
//		x++;
		signal(x);
//		while(!y);
		cout<<"S5"<<endl;
		cout<<"S6"<<endl;		
//		x++;
		signal(x);
		}
	}
	if(c==0){
		while(t--){
//		y--;
		wait(&y);
//		while(!x);
		cout<<"S3"<<endl;
		cout<<"S4"<<endl;	
//		x--;y++;
		wait(&x);
		signal(y);
//		while(!x);
		cout<<"S7"<<endl;
		cout<<"S8"<<endl;	
		}
	}
return 0;
}

