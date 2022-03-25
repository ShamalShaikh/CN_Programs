#include"Header1.h"
#include<iostream>
using namespace std;
int main(){
	key_t msg_key = ftok("sham.txt",65);
	int msqid = msgget(msg_key,0666|IPC_CREAT);
	
	msgctl(msqid,IPC_RMID,0);
	return 0;
}
