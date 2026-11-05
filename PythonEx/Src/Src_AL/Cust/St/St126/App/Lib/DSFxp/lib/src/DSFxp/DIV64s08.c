/**
 * @file       $RCSfile: DIV64s08.c $
 * @brief      This file contains function F__I32DIVI64sU32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.6 $ $Date: 2017/04/24 09:09:48CEST $
 */

#include "dsfxp.h"


/* mixed division of Int64s by UInt32 */
Int32 F__I32DIVI64sU32(const Int64s *u, UInt32 a)
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

    /* do unsigned divide */
    retval = F__U32DIVU64sU32(&U, a);

    /* restore sign */
    return((sign!=0) ? (-((Int32)retval)) : ((Int32)retval));
}
