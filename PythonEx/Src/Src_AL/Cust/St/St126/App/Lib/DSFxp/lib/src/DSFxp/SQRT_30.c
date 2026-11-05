/**
 * @file       $RCSfile: SQRT_30.c $
 * @brief      This file contains function F__U8SQRTI16_SAT for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__U8SQRTI16_SAT(ar)
 *
 * DESCRIPTION:
 *   Calculates an integer square root from argument 'ar'. The result 'rslt' is
 *   the largest integer whose square is less than or equal 'ar'.
 *
 * PARAMETERS:
 *   type    name    meaning
 *   Int16   ar      input value
 *
 * RETURNS:
 *   UInt8           return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
UInt8 F__U8SQRTI16_SAT(Int16 ar)
{
    UInt8 result;                           /* result of sqrt */
    
    C__U8SQRTI16_SAT(ar, result);
    return result;
}
/* END F__U8SQRTI16_SAT() */
