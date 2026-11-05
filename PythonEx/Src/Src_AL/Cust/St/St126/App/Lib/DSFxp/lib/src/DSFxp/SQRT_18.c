/**
 * @file       $RCSfile: SQRT_18.c $
 * @brief      This file contains function F__I16SQRTU16 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__I16SQRTU16(ar)
 *
 * DESCRIPTION:
 *   Calculates an integer square root from argument 'ar'. The result 'rslt' is
 *   the largest integer whose square is less than or equal 'ar'.
 *
 * PARAMETERS:
 *   type    name    meaning
 *   UInt16  ar      input value
 *
 * RETURNS:
 *   Int16           return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
Int16 F__I16SQRTU16(UInt16 ar)
{
    Int16 result;                           /* result of sqrt */
    
    C__I16SQRTU16(ar, result);
    return result;
}
/* END F__I16SQRTU16() */
