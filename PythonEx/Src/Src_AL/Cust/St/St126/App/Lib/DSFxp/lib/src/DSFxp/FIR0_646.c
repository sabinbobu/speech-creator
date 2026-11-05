/**
 * @file       $RCSfile: FIR0_646.c $
 * @brief      This file contains function F__I32FIR32_I8I32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__I32FIR32_I8I32(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type    name       meaning    
*   Int8    Input      current Input 
*   UInt16  NTabs      number of tabs
*   Int8*   DelayLine  pointer to DelayLine vector
*   Int32*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Int32   accumulation result 
*	
******************************************************************************/

Int32 F__I32FIR32_I8I32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff)
{
Int32  Accu;
	
	C__I32FIR32_I8I32(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
