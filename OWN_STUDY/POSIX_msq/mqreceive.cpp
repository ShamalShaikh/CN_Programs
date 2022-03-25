#include<bits/stdc++.h>
#include<mqueue.h>

using namespace std;
int main(int ac, char **av){
	int c, flags;
	mqd_t mqd;
	ssize_t n;
	unsigned int prio;
	//void *buff;
	struct mq_attr attr;
		
 	mqd = mq_open(av[1],O_RDWR);
 	mq_getattr(mqd,&attr);
 	
	char *ptr = (char *)malloc(attr.mq_msgsize);
	
	n = mq_receive(mqd,ptr,attr.mq_msgsize,&prio);
	cout<<"read "<<n<<" bytes. Priority = "<<prio;
	//mq_close(mqd);
return 0;
}
