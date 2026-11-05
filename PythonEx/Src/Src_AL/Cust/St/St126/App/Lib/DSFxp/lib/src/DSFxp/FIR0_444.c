/**
 * @file       $RCSfile: FIR0_444.c $
 * @brief      This file contains function F__I8FIR8_I8I8 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__I8FIR8_I8I8(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type    name       meaning    
*   Int8    Input      current Input 
*   UInt16  NTabs      number of tabs
*   Int8*   DelayLine  pointer to DelayLine vector
*   Int16*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Int8   accumulation result 
*
******************************************************************************/

Int8 F__I8FIR8_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff)
{
Int8  Accu;
	
	C__I8FIR8_I8I8(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
