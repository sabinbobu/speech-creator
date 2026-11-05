/**
 * @file       $RCSfile: FIR3_746.c $
 * @brief      This file contains function F__I64FIR64_SAT_I8CBI32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__I64FIR64_SAT_I8CBI32(Input,NTabs,DelayLine,Coeff,Counter,Result_h,Result_l)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation and circular buffer.
*
* PARAMETERS:
*   type    name       meaning
*   Int8    Input      current Input
*   UInt16  NTabs      number of tabs
*   Int8*   DelayLine  pointer to DelayLine vector
*   Int32*  Coeff      pointer to Coefficients vector
*   UInt16* Counter    pointer to the Counter variable (to work in conjunction with circular buffer)
*
* RETURNS:
*   Int32*  Result_h   pointer to the result variable  (High part of 64 bit variable)
*   UInt32* Result_l   pointer to the result variable  (Low part of 64 bit Variable)
*
* NOTE:
*   After return the Result_h/Result_l variables contain the 64bit accumulation result.
*
******************************************************************************/

void F__I64FIR64_SAT_I8CBI32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,UInt16* Counter,Int32 *Result_h,UInt32 *Result_l)
{
Int32   Accu_h;
UInt32  Accu_l;

	C__I64FIR64_SAT_I8CBI32(Input,NTabs,DelayLine,Coeff,(*Counter),Accu_h,Accu_l);
	*Result_h = Accu_h;
	*Result_l = Accu_l;
}
