#include"Header1.h"
int main(){
	key_t msg_key = ftok("shamal0.txt",65);
	int msqid = msgget(msg_key,0666);
	msgctl(msqid,IPC_RMID,0);
return 0;
}
