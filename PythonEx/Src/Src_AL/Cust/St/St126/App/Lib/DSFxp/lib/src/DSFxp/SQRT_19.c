/**
 * @file       $RCSfile: SQRT_19.c $
 * @brief      This file contains function F__I32SQRTU32 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__I32SQRTU32(ar)
 *
 * DESCRIPTION:
 *   Calculates an integer square root from argument 'ar'. The result 'rslt' is
 *   the largest integer whose square is less than or equal 'ar'.
 *
 * PARAMETERS:
 *   type    name    meaning
 *   UInt32  ar      input value
 *
 * RETURNS:
 *   Int32           return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
Int32 F__I32SQRTU32(UInt32 ar)
{
    Int32 result;                           /* result of sqrt */
    
    C__I32SQRTU32(ar, result);
    return result;
}
/* END F__I32SQRTU32() */
