/**
 * @file       $RCSfile: TAN_07a.c $
 * @brief      This file contains function for tangens calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.7 $ $Date: 2017/04/10 10:37:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I32TANI32_LE7_ARB(v, yN, yD)
*
* DESCRIPTION:
*   Calculates tan as sin/cos using series approach.
*   Scaling of output is arbitrary
*
* PARAMETERS:
*   Int32   v      input value
*   Int16   yN     nominator of output LSB
*   Int16   yD     denominator of output LSB
*
* RETURNS:
*   Int32   y      return value 
*
******************************************************************************/
Int32 F__I32TANI32_LE7_ARB(Int32 v, Int32 yN, Int32 yD)
{
    Int32 y;

       
    if (v == INT32MIN)
    {
        y = INT32MIN;
    }
    else
    {
        Int32 y_sin;
        Int32 y_cos;
        Int32   y_sin_h;
        UInt32  y_sin_l;
        Int32   y_cos_h;
        UInt32  y_cos_l;
        if (v < 0)
        {
            y_sin_h = -v;
            y = -1;
        }
        else
        {
            y_sin_h = v;
            y = 1;
        }
        
        y_sin_h = y_sin_h >> 1U;
        y_sin = F__I32SINI32_LE7(y_sin_h);
        y_cos = F__I32SINI32_LE7(y_sin_h + 0x40000000);
        
        C__I64SHLI32C6_LT32(y_cos, 31, 1, y_cos_h, y_cos_l);
        C__I64DIVI64I32(y_cos_h, y_cos_l, yD, y_sin_h, y_sin_l);
        C__I64MULI64I32(y_sin_h, y_sin_l, yN, y_cos_h, y_cos_l);
        C__I64COPYI32(y_sin, y_sin_h, y_sin_l);
        
        if (C__LT64(y_sin_h, y_sin_l, y_cos_h, y_cos_l))
        {
            y *= y_sin;
            C__I64MULI32I32(y,yD,y_sin_h, y_sin_l);
            C__I64DIVI64I32(y_sin_h, y_sin_l, yN, y_cos_h, y_cos_l);
            C__I32DIVI64I32(y_cos_h, y_cos_l, y_cos, y);
        }
        else
        {
            if (y == 1)
            {
                y = INT32MAX;
            }
            else
            {
                y = INT32MIN;
            }
        }
    }
    return y;
} /* END F__I32TANI32_LE7_ARB() */
