/**
 * @file       $RCSfile: DIV64s02.c $
 * @brief      This file contains function F__U32DIVU64sU16 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2017/06/07 10:25:45CEST $
 */

#include "dsfxp.h"


/* divide a UInt64s by an UInt16; a != 0 */
UInt32 F__U32DIVU64sU16(const UInt64s *u, UInt16 a)
{
    UInt32 retval;
    UInt32 r, v;

    r = u->lo;
    v = u->hi;

    /* do division */
    retval = v / a;
    v -= retval * a;

    /* next part of v */
    v = (UInt32)(((UInt32)(v) << 16U) + ((UInt32)(r) >> 16U));

    retval = v / a;
    v -= retval * a;

    /* next part of v */
    v = (UInt32)(((UInt32)(v) << 16U) + (UInt16)(r));

    retval = (UInt32)(((retval) << 16U) + (UInt16)(v / a));

    return(retval);
}
