/**
 * @file       $RCSfile: DIV64s10.c $
 * @brief      This file contains function F__I32DIVI64sI32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.8 $ $Date: 2017/04/24 09:09:48CEST $
 */

#include "dsfxp.h"


/* signed division of Int64s by Int32 */
Int32 F__I32DIVI64sI32(const Int64s *u, Int32 v)
{
    UInt32 retval;
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

    if(v < 0)
    {
        retval = (UInt32)(-(v));
        /* invert sign */
        sign = 1 - sign;
    }
    else
    {
        retval = (UInt32)(v);
    }

    /* do unsigned divide */
    retval = F__U32DIVU64sU32(&U, retval);

    /* restore sign */
    return((sign!=0) ? (-((Int32)retval)) : ((Int32)retval));
}
