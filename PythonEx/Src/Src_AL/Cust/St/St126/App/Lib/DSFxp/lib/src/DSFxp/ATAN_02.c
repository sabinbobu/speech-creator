/**
 * @file       $RCSfile: ATAN_02.c $
 * @brief      This file contains function F__I16ATAN2I16 for atan2 calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.3 $ $Date: 2016/06/21 15:29:49CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I16ATAN2I16(v, c, y)
*
* DESCRIPTION:
*   Calculates atan2 using asin.
*   Scaling is less than Int16, 2^-13
*
* PARAMETERS:
*   Int16   v      = x / y; input value of atan
*   Int32   c      second input value
*   Int16   y      denominator of v = x/y
*
* RETURNS:
*   Int16   fcn    return value
*
******************************************************************************/
Int16 F__I16ATAN2I16(Int16 v, Int32 c, Int16 y)
{
    Int16 v1;

       v1 = (Int16)(F__I16ATANI16(v, c) >> 1U);

       if (y < 0)
       {
           if (v >= 0)
           {
		       v1 -= 0x6488; /* -pi */
           }
           else
           {
		       v1 += 0x6488; /* +pi */
           }
           v1 = (Int16)-v1;
       }
       return v1;
} /* END F__I16ATAN2I16() */
