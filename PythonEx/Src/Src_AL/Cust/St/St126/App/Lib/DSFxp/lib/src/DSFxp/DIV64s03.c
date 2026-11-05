/**
 * @file       $RCSfile: DIV64s03.c $
 * @brief      This file contains function F__I64sDIVI64sU32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2017/04/06 10:04:03CEST $
 */

#include "dsfxp.h"


/* mixed division of Int64s by UInt32 */
Int64s F__I64sDIVI64sU32(const Int64s *u, UInt32 a)
{
    Int64s ds_tmp__;
    UInt64s retval;
    UInt64s U;
    Int8 sign = 0;

    /* local copy to preserve u */
    U.hi = (UInt32)u->hi;
    U.lo = u->lo;

    /* check signs of arguments, force positive */
    if(U.hi > (UInt32)INT32MAX)
    {
        negate(&U);
        sign = 1;
    }

    /* do unsigned divide */
    retval = F__U64sDIVU64sU32(&U, a);

    /* restore sign */
    if(sign!=0)
    {
        negate(&retval);
    }

    ds_tmp__.hi = (Int32)retval.hi;
    ds_tmp__.lo = retval.lo;
    return(ds_tmp__);
}
