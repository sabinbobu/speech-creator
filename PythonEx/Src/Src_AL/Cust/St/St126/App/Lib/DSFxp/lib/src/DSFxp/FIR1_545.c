/**
 * @file       $RCSfile: FIR1_545.c $
 * @brief      This file contains function F__I16FIR16_SAT_I8I16 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__I16FIR16_SAT_I8I16(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation.
*
* PARAMETERS:
*   type    name       meaning    
*   Int8    Input      current Input 
*   UInt16  NTabs      number of tabs
*   Int8*   DelayLine  pointer to DelayLine vector
*   Int16*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   Int16   accumulation result 
*
******************************************************************************/

Int16 F__I16FIR16_SAT_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff)
{
Int16  Accu;
	
	C__I16FIR16_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
