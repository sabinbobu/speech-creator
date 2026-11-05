/**
 * @file       $RCSfile: FIR2_311.c $
 * @brief      This file contains function F__U64FIR64_U16CBU16 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U64FIR64_U16CBU16(Input,NTabs,DelayLine,Coeff,Counter,Result_h,Result_l)
*
* DESCRIPTION:
*   FIR - Filter calculation with circular buffer.
*
* PARAMETERS:
*   type    name       meaning    
*   UInt16  Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt16* DelayLine  pointer to DelayLine vector
*   UInt32* Coeff      pointer to Coefficients vector 
*   UInt16* Counter    pointer to the Counter variable (to work in conjunction with circular buffer)
*
* RETURNS:
*   UInt32* Result_h   pointer to the result variable (High part of 64 bit variable)  
*   UInt32* Result_l   pointer to the result variable (Low part of 64 bit Variable)
*
* NOTE:
*   After return the Result_h/Result_l variables contain the 64bit accumulation result.  
*
******************************************************************************/

void F__U64FIR64_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16* Counter,UInt32 *Result_h,UInt32 *Result_l)
{
UInt32  Accu_h;
UInt32  Accu_l;

	C__U64FIR64_U16CBU16(Input,NTabs,DelayLine,Coeff,(*Counter),Accu_h,Accu_l);
	*Result_h = Accu_h;
	*Result_l = Accu_l;
}
