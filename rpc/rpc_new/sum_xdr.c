/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "sum.h"

bool_t
xdr_sum_in (XDR *xdrs, sum_in *objp)
{
	register int32_t *buf;

	 if (!xdr_long (xdrs, &objp->arg1))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->arg2))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_sum_out (XDR *xdrs, sum_out *objp)
{
	register int32_t *buf;

	 if (!xdr_long (xdrs, &objp->res1))
		 return FALSE;
	return TRUE;
}
