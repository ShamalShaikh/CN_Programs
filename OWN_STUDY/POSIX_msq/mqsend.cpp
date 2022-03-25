#include<bits/stdc++.h>
#include<mqueue.h>
#include<unistd.h>
#include<stdint.h>
using namespace std;
int main(int ac, char** av){
	mqd_t mqd;
	char *ptr;
	size_t len;
	uint8_t prio;
 	/*while((c = getopt(argc,argv,"em:z:"))!=-1){
 		switch(c){
 			case 'e' : flags |=O_EXCL;
 			break;
 			case 'm' : attr.mq_maxmsg = atol(optarg);
 			break;
 			case 'z' : attr.mq_mgsize = atol(optarg);
 			break;
 		}
 	}
 	*/
 	
 	len = atoi(av[1]);
 	prio = atoi(av[2]);
 	
	mqd = mq_open("/shamal",O_WRONLY);
	ptr = (char *)calloc(len,sizeof(char));
	mq_send(mqd,ptr,len,prio);
	
return 0;
}
