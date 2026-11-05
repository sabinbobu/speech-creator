/**
 * @file       $RCSfile: SIN_06.c $
 * @brief      This file contains function F__I32SINI32_6TERMS for calculation of trigonometric functions.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.8 $ $Date: 2017/02/24 11:21:42CET $
 */

#include "dsfxp.h"

/******************************************************************************
* FUNCTION:
*   F__I32SINI32_6TERMS(v)
*
* DESCRIPTION:
*   Calculates 6 terms of sine series.
*   sin(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9! - x^11/11!
*
* PARAMETERS:
*   Int32   v       input value
*
* RETURNS:
*   Int32   retval  return value
*
******************************************************************************/
Int32 F__I32SINI32_6TERMS(Int32 v)
{
    Int32 retval;
    Int32 xr;
    UInt32 x2;
    Int32 AUX_a_Int64_h;
    UInt32 AUX_a_Int64_l;

    F__I64MULI32U32(v, 0x6487ED51UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
    xr = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );
    F__I64MULI32I32(xr, xr, &AUX_a_Int64_h, &AUX_a_Int64_l);
    x2 = (UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );

    F__I64MULU32U32(x2, 0x4A7904A7UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( 0x40000000UL - ((UInt32)(AUX_a_Int64_h) >> 5U) );

    F__I64MULI32U32(retval, x2, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );
    F__I64MULI32U32(retval, 0x71C71C71UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( 0x40000000UL - ((UInt32)(AUX_a_Int64_h) >> 5U) );

    F__I64MULI32U32(retval, x2, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );
    F__I64MULI32U32(retval, 0x61861862UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( 0x40000000UL - ((UInt32)(AUX_a_Int64_h) >> 4U) );

    F__I64MULI32U32(retval, x2, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );
    F__I64MULI32U32(retval, 0x66666666UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( 0x40000000UL - ((UInt32)(AUX_a_Int64_h) >> 3U) );

    F__I64MULI32U32(retval, x2, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );
    F__I64MULI32U32(retval, 0x55555555UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( 0x40000000UL - ((UInt32)(AUX_a_Int64_h) >> 1U) );

    F__I64MULI32I32(xr, retval, &AUX_a_Int64_h, &AUX_a_Int64_l);
    retval = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );

    return retval;
}
/* END F__I32SINI32_6TERMS() */
