#include"Header1.h"
#include<iostream>
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
};
using namespace std;
struct msqid_ds qbuf;
int main() {
	key_t msg_key = ftok("shamal1.txt",65);
	int msqid = msgget(msg_key,0666|IPC_CREAT);
	mesg_buffer message_buffer[] = { {1,"NITW"}, {2,"CSE"},{1,"III YEAR"},{2,"CODE"},{3,"CN"}};
	mesg_buffer message = {1,"NITW"}, message1;
	for (int i = 0; i < 5;++i) {
		msgsnd(msqid, &message_buffer[i], sizeof(message_buffer[i]), 0);
	}
	int r;

		msgctl(msqid, IPC_STAT, &qbuf );
	cout<<"\nMessage Queue ID : "<<msqid;
	cout<<"\nMessage Queue NUM : "<<qbuf.msg_qnum;
	cout<<"\nMessage Queue LEN : "<<qbuf.msg_qbytes;
	cout<<"\nMessage Queue LAST PID : "<<qbuf.msg_lspid;
	cout<<"\nMessage Queue LAST RCV : "<<qbuf.msg_lrpid;		
	
	for (int i = 1; i < 4; ++i) {
		while(1){
		if(r = msgrcv(msqid,&message,sizeof(message),i,IPC_NOWAIT) == -1){
			//cout<<r<<" ";
			break;
		}
		cout<<"[" << message.mesg_type<<"] : ";
		cout << message.mesg_text << "\n";
		}
	}
	int errno;
	int d = msgctl(msqid, IPC_STAT, &qbuf );
	if(d == -1){
		cout<<errno;
		cout<<strerror(errno);
		exit(1);
	}
	cout<<"\nMessage Queue ID : "<<msqid;
	cout<<"\nMessage Queue NUM : "<<qbuf.msg_qnum;
	cout<<"\nMessage Queue LEN : "<<qbuf.msg_qbytes;
	cout<<"\nMessage Queue LAST PID : "<<qbuf.msg_lspid;
	cout<<"\nMessage Queue LAST RCV : "<<qbuf.msg_lrpid;			
	msgctl(msqid,IPC_RMID,0);
	return 0;
}
