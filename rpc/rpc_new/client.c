#include<stdio.h>
#include<rpc/rpc.h>
#include "sum.h"
int main()
{
	CLIENT *c1;
	sum_in in;
	sum_out *outp;
	c1=clnt_create("127.0.0.1",SUM_PROG,SUM_VERS,"tcp");
	printf("Enter two numbers:\n");
	scanf("%ld",&in.arg1);
	scanf("%ld",&in.arg2);
	outp=sumproc_1(&in,c1);
	if(outp!=NULL)
		printf("The sum value is %d\n",outp->res1);
	exit(0);
	return 0;
}
