/**
 * @file       $RCSfile: DIV64s09.c $
 * @brief      This file contains function F__I32DIVU64sI32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2017/04/24 09:09:48CEST $
 */

#include "dsfxp.h"


/* mixed division of UInt64s by Int32 */
Int32 F__I32DIVU64sI32(const UInt64s *u, Int32 v)
{
    UInt32 retval;
    UInt64s U;
    Int8 sign;

    U = *u;    /* local copy to preserve u */

    /* check signs of arguments, force positive */
    if(v < 0)
    {
        retval = (UInt32)(-(v));
        sign = 1;
    }
    else
    {
        retval = (UInt32)(v);
        sign = 0;
    }

    /* do unsigned divide */
    retval = F__U32DIVU64sU32(&U, retval);

    /* restore sign */
    return((sign!=0) ? (-((Int32)retval)) : ((Int32)retval));
}
