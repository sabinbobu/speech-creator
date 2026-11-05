/**
 * @file       $RCSfile: FIR2_666.c $
 * @brief      This file contains function F__I32FIR32_I32CBI32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*  F__I32FIR32_I32CBI32(Input,NTabs,DelayLine,Coeff,Counter)
*
* DESCRIPTION:
*   FIR - Filter calculation with circular buffer.
*
* PARAMETERS:
*   type    name       meaning    
*   Int32   Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt16* Counter    pointer to the Counter variable (to work in conjunction with circular buffer)
*   Int32*  DelayLine  pointer to DelayLine vector
*   Int32*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Int32   accumulation result 
*
******************************************************************************/

Int32 F__I32FIR32_I32CBI32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,UInt16* Counter)
{  
Int32  Accu;

	C__I32FIR32_I32CBI32(Input,NTabs,DelayLine,Coeff,(*Counter),Accu);
	return  Accu;
}
