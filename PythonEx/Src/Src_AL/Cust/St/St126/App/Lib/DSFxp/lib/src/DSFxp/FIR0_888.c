/**
 * @file       $RCSfile: FIR0_888.c $
 * @brief      This file contains function F__F32FIR32_F32F32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*  F__F32FIR32_F32F32(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type     name       meaning    
*   Float32  Input      current Input 
*   UInt16   NTabs      number of tabs
*   Float32* DelayLine  pointer to DelayLine vector
*   Float32* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Float32  accumulation result 
*
******************************************************************************/

#ifndef TL_NO_FLOATS

Float32 F__F32FIR32_F32F32(Float32 Input,UInt16 NTabs,Float32* DelayLine,const Float32* Coeff)
{
Float32   Accu;
	
	C__F32FIR32_F32F32(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
#endif /* TL_NO_FLOATS */
