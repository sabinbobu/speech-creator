/**
 * @file       $RCSfile: TAN_01.c $
 * @brief      This file contains function for tangens calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.8 $ $Date: 2017/04/24 13:39:58CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I16TANI16(v, ysh)
*
* DESCRIPTION:
*   Calculates tan as sin/cos using table.
*   Output scaling is 2^-ysh
*
* PARAMETERS:
*   Int16   v      input value
*   Int8    ysh    exponent of output LSB negate
*
* RETURNS:
*   Int16   y      return value
*
******************************************************************************/
Int16 F__I16TANI16(Int16 v, Int8 ysh)
{
    Int16 y;

    if (v == INT16MIN)
    {
        y = INT16MIN;
    }
    else
    {
        UInt16 y_cos;
        UInt16 y_sin;
        UInt16 i;
        UInt16 x;

        if ( v < 0 )
        {
            x = (UInt16)(-v);
            y = -1;
        }
        else
        {
            x = (UInt16)(v);
            y = 1;
        }

        /* calculate table index and value of cosine */
        i = (UInt16)(x >> 8U);
        y_cos = cosLUT[i];
        y_cos -= (UInt16)((((UInt32)((UInt32)y_cos - (UInt32)cosLUT[i+1U])) * ((UInt32)x & 0xFFU)) >> 8U);

        /* calculate table index and value of sine */
        i = (128U - i);
        y_sin = cosLUT[i];
        y_sin += (UInt16)(((UInt32)((UInt32)cosLUT[i-1U] - (UInt32)y_sin) * ((UInt32)x & 0xFFU)) >> 8U);

        if ((UInt32)y_sin < (UInt32)((UInt32)y_cos << (UInt8)(Int8)(15 - ysh)))
        {
            x = (UInt16)((UInt32)((UInt32)y_sin << (UInt8)ysh) / y_cos);
			y *= (Int16)x;
        }
        else
        {
            if (y == 1)
            {
                y = INT16MAX;
            }
            else
            {
                y = INT16MIN;
            }
        }
    }
    return y;
} /* END F__I16TANI16() */
