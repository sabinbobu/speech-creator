/**
 * @file       $RCSfile: TAN_01a.c $
 * @brief      This file contains function for tangens calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.9 $ $Date: 2017/04/24 13:40:41CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I16TANI16_ARB(v, yN, yD)
*
* DESCRIPTION:
*   Calculates tan as sin/cos using table.
*   Scaling of output is arbitrary
*
* PARAMETERS:
*   Int16   v      input value
*   Int16   yN     nominator of output LSB
*   Int16   yD     denominator of output LSB
*
* RETURNS:
*   Int16   y      return value
*
******************************************************************************/
Int16 F__I16TANI16_ARB(Int16 v, Int16 yN, Int16 yD)
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

        if (((UInt32)y_sin) < ((UInt32)((((UInt32)(((UInt32)y_cos) << 15U)) / ((UInt32)yD)) * ((UInt32)yN))))
        {
            x = (UInt16)((UInt32)((((UInt32)y_sin) * ((UInt32)(yD))) / ((UInt32)(yN)) / ((UInt32)y_cos)));
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
} /* END F__I16TANI16_ARB() */
