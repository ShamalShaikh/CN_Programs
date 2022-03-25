#include<bits/stdc++.h>
#include<mqueue.h>
#include<unistd.h>
using namespace std;
int main(){
	int c,flags;
 	mqd_t mqd;
 	flags = O_RDWR|O_CREAT;
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
 	 mqd = mq_open("/shamal",flags,0666,NULL);
	
	mq_close(mqd);
return 0;
}
