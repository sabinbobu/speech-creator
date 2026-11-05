/**
 * @file       $RCSfile: FIR0_999.c $
 * @brief      This file contains function F__F64FIR64_F64F64 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*  F__F64FIR64_F64F64(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type     name       meaning    
*   Float64  Input      current Input 
*   UInt16   NTabs      number of tabs
*   Float64* DelayLine  pointer to DelayLine vector
*   Float64* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Float64  accumulation result 
*
******************************************************************************/

#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)

Float64 F__F64FIR64_F64F64(Float64 Input,UInt16 NTabs,Float64* DelayLine,const Float64* Coeff)
{
Float64  Accu;
	
	C__F64FIR64_F64F64(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
#endif /* TL_NO_FLOATS */
