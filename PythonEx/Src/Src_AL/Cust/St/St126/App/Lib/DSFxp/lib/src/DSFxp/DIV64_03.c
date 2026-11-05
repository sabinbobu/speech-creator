/**
 * @file       $RCSfile: DIV64_03.c $
 * @brief      This file contains function for 64 bit division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.3 $ $Date: 2017/02/16 14:40:41CET $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I64DIVU64I32(n_h, n_l, d, r_h, r_l)
*
* DESCRIPTION:
*   Divides the 64bit Value n by the 32bit Value d with a 64bit result.
*
* PARAMETERS:
*   type    name    meaning
*  UInt32    n_h    upper 32Bit of the nominator
*  UInt32    n_l    lower 32Bit of the nominator
*   Int32      d    denominator
*   Int32    r_h    upper 32bit of the result
*  UInt32    r_l    lower 32bit of the result
*
* RETURNS:
*
* NOTE:
*  - "division by zero" detection (gives 0x7FFFFFFFFFFFFFFF respectively
*    0xFFFFFFFFFFFFFFFF)
*  - the algorithm supports only calculations with unsigned values. Therefore
*    the sign of the result is determined separately.
*
******************************************************************************/
void F__I64DIVU64I32(UInt32 n_h, UInt32 n_l, Int32 d, Int32 *r_h, UInt32 *r_l)
{
    UInt64s tmp;
    Int64s tmp2;

    tmp.lo = n_l;
    tmp.hi = n_h;
    tmp2 = F__I64sDIVU64sI32(&tmp, d);
    *r_h = tmp2.hi;
    *r_l = tmp2.lo;
}/* END F__I64DIVU64I32() */
