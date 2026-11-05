/**
 * @file       $RCSfile: SQRT_01.c $
 * @brief      This file contains function F__U8SQRTU8 for SQRT calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2015/08/05 11:18:44CEST $
 */

#include "dsfxp.h"

/******************************************************************************
 *
 * FUNCTION:
 *   F__U8SQRTU8(ar)
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
 *   UInt8           return value    rslt = sqrt(ar)
 *
 ******************************************************************************/
UInt8 F__U8SQRTU8(UInt8 ar)
{
    UInt8 rslt;                            /* result of sqrt */
    
    C__U8SQRTU8(ar, rslt);
    return rslt;
}
/* END F__U8SQRTU8() */
