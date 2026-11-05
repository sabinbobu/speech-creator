/**
 * @file       $RCSfile: SIN_01.c $
 * @brief      This file contains function F__I16SINI16 for calculation of trigonometric functions.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.6 $ $Date: 2017/04/26 09:23:17CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I16SINI16(v)
*
* DESCRIPTION:
*   Calculates sine as series approach.
*   Scaling is less than Int16, 2^-14
*
* PARAMETERS:
*   Int16   v      input value: -pi .. pi
*
* RETURNS:
*   Int16   fcn    return value
*
******************************************************************************/
Int16 F__I16SINI16(Int16 x)
{
    Int16 y;

    if (x == 0)
    {
        y = 0;
    }
    else
    {
        UInt16 i;
        UInt16 y1;
        Int16 n;

        if (x < 0)
        {
            y1 = (UInt16)(-x);
            y = -1;
        }
        else
        {
            y1 = (UInt16)(x);
            y = 1;
        }

        n = (Int16)(UInt16)(y1 - 0x4000U);
        if ( n < 0 )
        {
            n =  -n;
        }

        i = (UInt16)((UInt16)n >> 7U);
        y1 = cosLUT[i];
        y1 -= (UInt16)((((UInt32)((UInt32)y1 - (UInt32)cosLUT[i+1U])) * ((UInt32)n & 0x007FU)) >> 7U);
        y *= (Int16)y1;
    }
    return y;
}
/* END F__I16SINI16() */
