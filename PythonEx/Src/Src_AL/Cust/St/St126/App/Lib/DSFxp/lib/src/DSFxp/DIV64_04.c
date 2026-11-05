/**
 * @file       $RCSfile: DIV64_04.c $
 * @brief      This file contains function for 64 bit division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2012, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.2 $ $Date: 2013/02/14 08:19:58CET $
 */
 
#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__U64DIVU64U32(n_h, n_l, d, r_h, r_l)
*
* DESCRIPTION:
*   Divides the 64bit Value n by the 32bit Value d with a 64bit result. 
*
* PARAMETERS:
*   type    name    meaning    
*  UInt32    n_h    upper 32Bit of the nominator
*  UInt32    n_l    lower 32Bit of the nominator
*  UInt32      d    denominator 
*  UInt32    r_h    upper 32bit of the result
*  UInt32    r_l    lower 32bit of the result
*
* RETURNS:
*
* NOTE:
*  - "division by zero" detection (gives 0x7FFFFFFFFFFFFFFF respectively 
*    0xFFFFFFFFFFFFFFFF)
*  - the algorithm supports only calculations with unsigned values. Therefore
*    the sign of the result is determined separately.
*
******************************************************************************/
void F__U64DIVU64U32(UInt32 n_h, UInt32 n_l, UInt32 d, UInt32 *r_h, UInt32 *r_l)
{														                        
	UInt64s tmp;										                        
	tmp.lo = n_l;										                        
	tmp.hi = n_h;										                        
	tmp = F__U64sDIVU64sU32(&tmp, d);					                        
	*r_h = tmp.hi;										                        
	*r_l = tmp.lo;										                        
}/* END F__U64DIVU64U32() */
