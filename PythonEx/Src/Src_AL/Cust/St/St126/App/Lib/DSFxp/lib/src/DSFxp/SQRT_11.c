/**
 * @file       $RCSfile: SQRT_11.c $
 * @brief      This file contains function F__I8SQRTU8 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__I8SQRTU8(ar)
 *
 * DESCRIPTION:
 *   Calculates an integer square root from argument 'ar'. The result 'rslt' is
 *   the largest integer whose square is less than or equal 'ar'.
 *
 * PARAMETERS:
 *   type    name    meaning
 *   UInt8   ar      input value
 *
 * RETURNS:
 *   Int8          return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
Int8 F__I8SQRTU8(UInt8 ar)
{
    Int8 result;                            /* result of sqrt */
    
    C__I8SQRTU8(ar, result);
    return result;
}
/* END F__I8SQRTU8() */
