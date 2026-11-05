/**
 * @file       $RCSfile: DIV64s04.c $
 * @brief      This file contains function F__I64sDIVU64sI32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.3 $ $Date: 2017/02/22 11:23:38CET $
 */

#include "dsfxp.h"


/* mixed division of UInt64s by Int32 */
Int64s F__I64sDIVU64sI32(const UInt64s *u, Int32 v)
{
	Int64s ds_tmp__;
	UInt64s retval;
	UInt64s U;
	Int32 a = v;
	Int8 sign = 0;

	U = *u;	/* local copy to preserve u */

	/* check signs of arguments, force positive */
	if(a < 0)
	{
		a = -a;
		sign = 1;
	}

	/* do unsigned divide */
	retval = F__U64sDIVU64sU32(&U, (UInt32)a);

	/* restore sign */
	if(sign!=0)
	{
		negate(&retval);
	}
	
	ds_tmp__.hi = (Int32)retval.hi;
	ds_tmp__.lo = retval.lo;
	return(ds_tmp__);
}
