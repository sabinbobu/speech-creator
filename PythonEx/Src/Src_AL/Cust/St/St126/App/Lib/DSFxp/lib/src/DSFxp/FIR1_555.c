/**
 * @file       $RCSfile: FIR1_555.c $
 * @brief      This file contains function F__I16FIR16_SAT_I16I16 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__I16FIR16_SAT_I16I16(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation.
*
* PARAMETERS:
*   type    name       meaning    
*   Int16   Input      current Input 
*   UInt16  NTabs      number of tabs
*   Int16*  DelayLine  pointer to DelayLine vector
*   Int16*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Int16   accumulation result 
*
******************************************************************************/

Int16 F__I16FIR16_SAT_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff)
{
Int16  Accu;
	
	C__I16FIR16_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
