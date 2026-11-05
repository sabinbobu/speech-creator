/**
 * @file       $RCSfile: FIR0_656.c $
 * @brief      This file contains function F__I32FIR32_I16I32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*  F__I32FIR32_I16I32(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type    name       meaning    
*   Int16   Input      current Input 
*   UInt16  NTabs      number of tabs
*   Int16*  DelayLine  pointer to DelayLine vector
*   Int32*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Int32   accumulation result 
*
******************************************************************************/

Int32 F__I32FIR32_I16I32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff)
{
Int32  Accu;
	
	C__I32FIR32_I16I32(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
