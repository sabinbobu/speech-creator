/**
 * @file       $RCSfile: DIV64s01.c $
 * @brief      This file contains function F__U64sDIVU64sU16 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2017/06/07 10:25:45CEST $
 */

#include "dsfxp.h"


/* divide a UInt64s by an UInt16; a != 0 */
UInt64s F__U64sDIVU64sU16(const UInt64s *u, UInt16 a)
{
    UInt64s retval;
    UInt32  r, v;

    r = u->lo;
    v = u->hi;

    /* do division */
    retval.hi = v / a;
    v -= retval.hi * a;

    /* next part of v */
    v = (UInt32)(((UInt32)(v) << 16U) + ((UInt32)(r) >> 16U));

    retval.lo  = v / a;
    v -= retval.lo * a;

    /* next part of v */
    v = (UInt32)(((UInt32)(v) << 16U) + (UInt16)(r));

    retval.lo = (UInt32)(((retval.lo) << 16U) + (UInt16)(v / a));

    return(retval);
}
