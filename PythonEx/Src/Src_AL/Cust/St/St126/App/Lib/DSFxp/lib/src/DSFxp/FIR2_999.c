/**
 * @file       $RCSfile: FIR2_999.c $
 * @brief      This file contains function F__F64FIR64_F64CBF64 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.6 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*  F__F64FIR64_F64CBF64(Input,NTabs,DelayLine,Coeff,Counter)
*
* DESCRIPTION:
*   FIR - Filter calculation with circular buffer.
*
* PARAMETERS:
*   type     name       meaning    
*   Float64  Input      current Input 
*   UInt16   NTabs      number of tabs
*   UInt16*  Counter    pointer to the Counter variable (to work in conjunction with circular buffer)
*   Float64* DelayLine  pointer to DelayLine vector
*   Float64* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Float64  accumulation result 
*	
******************************************************************************/

#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)

Float64 F__F64FIR64_F64CBF64(Float64 Input,UInt16 NTabs,Float64* DelayLine,const Float64* Coeff,UInt16* Counter)
{
Float64  Accu;
	
	C__F64FIR64_F64CBF64(Input,NTabs,DelayLine,Coeff,(*Counter),Accu);
	return  Accu;
}
#endif /* TL_NO_FLOATS */
