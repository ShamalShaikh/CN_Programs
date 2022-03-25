#include<stdio.h>
#include<rpc/rpc.h>
#include "sum.h"
sum_out *
sumproc_1_svc(sum_in *inp,struct svc_req *rqstp)
{
	static sum_out out;
	out.res1=inp->arg1+inp->arg2;
	return (&out);
}
