/**
 * @file       $RCSfile: FIR0_312.c $
 * @brief      This file contains function F__U64FIR64_U16U32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U64FIR64_U16U32(Input,NTabs,DelayLine,Coeff,Counter,Result_h,Result_l)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type    name       meaning    
*   UInt16  Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt16* DelayLine  pointer to DelayLine vector
*   UInt32* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   UInt32* Result_h   pointer to the result variable (High part of 64 bit variable)  
*   UInt32* Result_l   pointer to the result variable (Low part of 64 bit Variable)
*
* NOTE:
*   After return the Result_h/Result_l variables contain the 64bit accumulation result.  
*
******************************************************************************/

void F__U64FIR64_U16U32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt32 *Result_h,UInt32 *Result_l)
{
UInt32  Accu_h;
UInt32  Accu_l;
	
	C__U64FIR64_U16U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l);
	*Result_h = Accu_h;
	*Result_l = Accu_l;
}
