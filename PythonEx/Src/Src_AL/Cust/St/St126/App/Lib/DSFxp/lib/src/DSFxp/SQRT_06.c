/**
 * @file       $RCSfile: SQRT_06.c $
 * @brief      This file contains function F__U8SQRTI8 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/05 15:13:01CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__U8SQRTI8(ar)
 *
 * DESCRIPTION:
 *   Calculates an integer square root from argument 'ar'. The result 'rslt' is
 *   the largest integer whose square is less than or equal 'ar'.
 *
 * PARAMETERS:
 *   type    name    meaning
 *   Int8    ar      input value
 *
 * RETURNS:
 *   UInt8           return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
UInt8 F__U8SQRTI8(Int8 ar)
{
    UInt8 result;                           /* result of sqrt */
    
    C__U8SQRTI8(ar, result);
    return result;
}
/* END F__U8SQRTI8() */
