/**
 * @file       $RCSfile: DIV64_06.c $
 * @brief      This file contains function for 64 bit division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2012, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.3 $ $Date: 2017/02/16 14:41:33CET $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I32DIVI64U32(n_h, n_l, d)
*
* DESCRIPTION:
*   Divides the 64bit Value n by the 32bit Value d with a 32bit result.
*
* PARAMETERS:
*   type    name    meaning
*   Int32    n_h    upper 32Bit of the nominator
*   UInt32   n_l    lower 32Bit of the nominator
*   UInt32     d    denominator
*
* RETURNS:
*   Int32      result
*
* NOTE:
*  - "division by zero" detection (gives 0x7FFFFFFF respectively 0xFFFFFFFF)
*  - the algorithm supports only calculations with unsigned values. Therefore
*    the sign of the result is determined separately.
*
******************************************************************************/
Int32 F__I32DIVI64U32(Int32 n_h, UInt32 n_l, UInt32 d)
{
	Int64s tmp;

	tmp.lo = n_l;
	tmp.hi = n_h;
	return( F__I32DIVI64sU32(&tmp, d) );
}/* END F__I32DIVI64U32() */
