/**
 * @file       $RCSfile: SQRT_08.c $
 * @brief      This file contains function F__U8SQRTI32 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__U8SQRTI32(ar)
 *
 * DESCRIPTION:
 *   Calculates an integer square root from argument 'ar'. The result 'rslt' is
 *   the largest integer whose square is less than or equal 'ar'.
 *
 * PARAMETERS:
 *   type    name    meaning
 *   Int32   ar      input value
 *
 * RETURNS:
 *   UInt8          return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
UInt8 F__U8SQRTI32(Int32 ar)
{
    UInt8 rslt;                            /* result of sqrt */
    
    C__U8SQRTI32(ar, rslt);
    return rslt;
}
/* END F__U8SQRTI32() */
