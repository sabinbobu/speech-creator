/**
 * @file       $RCSfile: ATAN_01.c $
 * @brief      This file contains function F__I16ATANI16 for atan calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.7 $ $Date: 2016/06/21 15:10:48CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I16ATANI16(v, c)
*
* DESCRIPTION:
*   Calculates atan using asin.
*   Scaling is less than Int16, 2^-14
*
* PARAMETERS:
*   Int16   v      input value
*   Int32   c      second input value
*
* RETURNS:
*   Int16   fcn    return value
*
******************************************************************************/

Int16 F__I16ATANI16(Int16 v, Int32 c)
{
    Int16 x2;

    if (v == 0)
    {
        x2 = 0;
    }
    else
    {
        Int32 x1;

        x1 = (Int32)(v * ((Int32)v)) + c;

        C__I16SQRTI32((Int32)(x1 >> 2U), x2);

        if (x2 == 0)  /* to prevent integer division by zero */
        {
            if (v > 0)
            {
                x2 = (Int16)20860;   /* pi/2 */
            }
            else
            {
                x2 = (Int16)-20861;   /* -pi/2 */
            }
        }
        else
        {
            x1 = (Int16)(((Int32)((Int32)v) << 13U) / x2);
            x2 = F__I16ASINI16((Int16)x1);
        }
    }

    return x2;

} /* END F__I16ATANI16() */
