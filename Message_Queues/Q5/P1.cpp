#include"Header1.h"
#include<iostream>
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
};
using namespace std;
struct msqid_ds mqbuf;
//struct ipc_perm permission;
int errno;
int main() {
	
	key_t msg_key = ftok("afreen.txt",65);
	cout<<msg_key;
	cout<<strerror(errno);
	int msqid = msgget(msg_key,777|IPC_CREAT);
	
	mesg_buffer message_buffer[] = { {2,"NITW"}, {3,"CSE"},{3,"III YEAR"},{2,"CODE"},{3,"CN"}};
	
//	mesg_buffer message = {1,"NITW"}, message1;
	int result;
	cout<<"start";
	for (int i = 0; i < 5;++i) {
		result = msgsnd(msqid, &message_buffer[i], sizeof(message_buffer[i]), 0);
		if(result != 1 ){
			cout<<errno<<strerror(errno)<<"\n";
		}
	}
	cout<<"done";
	int r;
	//struct mesg_buffer msg_first = mqbuf.msg_first;
//	sleep(1);
	msgctl(msqid, IPC_STAT, &mqbuf );
	cout<<"\nMessage Queue ID : "<<msqid;
	cout<<"\nMessage Queue Permissions : ";
	cout<<"\n key : "<<mqbuf.msg_perm.__key; 
	cout<<"\n uid : "<<mqbuf.msg_perm.uid;
	cout<<"\n gid : "<<mqbuf.msg_perm.gid;
	cout<<"\n cuid : "<<mqbuf.msg_perm.cuid;
	cout<<"\n cgid : "<<mqbuf.msg_perm.cgid;
	cout<<"\n Permissions : "<<mqbuf.msg_perm.mode;
	cout<<"\n sequence number : "<<mqbuf.msg_perm.__seq;
	//cout<<"\n first message : "<<msg_first.mesg_type;
	cout<<"\nMessage Queue NUM : "<<mqbuf.msg_qnum;
	cout<<"\nCurrent number of bytes in Queue : "<<mqbuf.__msg_cbytes;
	cout<<"\nMaximum number of bytes allowed in Queue : "<<mqbuf.__msg_cbytes;
	cout<<"\n PID of last msgsnd() : "<<mqbuf.msg_lspid;
	cout<<"\n PID of last msgrcv() : "<<mqbuf.msg_lrpid;		
	cout<<"\nTime of last msgsnd() : "<<mqbuf.msg_stime;
	cout<<"\nTime of last msgrcv() : "<<mqbuf.msg_rtime;		
	cout<<"\nTime of last change : "<<mqbuf.msg_ctime;	
		
		cout<<"\n";	

	cout<<"Let's Check the Queue info now!";
	sleep(10);
	

	msgctl(msqid, IPC_STAT, &mqbuf );
	cout<<"\nMessage Queue ID : "<<msqid;
	cout<<"\nMessage Queue Permissions : ";
	cout<<"\n key : "<<mqbuf.msg_perm.__key; 
	cout<<"\n uid : "<<mqbuf.msg_perm.uid;
	cout<<"\n gid : "<<mqbuf.msg_perm.gid;
	cout<<"\n cuid : "<<mqbuf.msg_perm.cuid;
	cout<<"\n cgid : "<<mqbuf.msg_perm.cgid;
	cout<<"\n Permissions : "<<mqbuf.msg_perm.mode;
	cout<<"\n sequence number : "<<mqbuf.msg_perm.__seq;
	cout<<"\nMessage Queue NUM : "<<mqbuf.msg_qnum;
	cout<<"\nCurrent number of bytes in Queue : "<<mqbuf.__msg_cbytes;
	cout<<"\nMaximum number of bytes allowed in Queue : "<<mqbuf.__msg_cbytes;
	cout<<"\n PID of last msgsnd() : "<<mqbuf.msg_lspid;
	cout<<"\n PID of last msgrcv() : "<<mqbuf.msg_lrpid;		
	cout<<"\nTime of last msgsnd() : "<<mqbuf.msg_stime;
	cout<<"\nTime of last msgrcv() : "<<mqbuf.msg_rtime;		
	cout<<"\nTime of last change : "<<mqbuf.msg_ctime;		
	
	cout<<"\n";
/*	for (int i = 1; i < 4; ++i) {
		while(1){
		if(r = msgrcv(msqid,&message,sizeof(message),i,IPC_NOWAIT) == -1){
			//cout<<r<<" ";
			break;
		}
		cout<<"[" << message.mesg_type<<"] : ";
		cout << message.mesg_text << "\n";
		}
	}
*/	
//	int errno;
/*	int d = msgctl(msqid, IPC_STAT, &qbuf );
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
*/
	msgctl(msqid,IPC_RMID,0);
	
	return 0;
}
