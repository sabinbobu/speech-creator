/**
 * @file       $RCSfile: SQRT_10.c $
 * @brief      This file contains function F__U16SQRTI32 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__U16SQRTI32(ar)
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
 *   UInt16          return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
UInt16 F__U16SQRTI32(Int32 ar)
{
    UInt16 rslt;                            /* result of sqrt */
    
    C__U16SQRTI32(ar, rslt);
    return rslt;
}
/* END F__U16SQRTI32() */
