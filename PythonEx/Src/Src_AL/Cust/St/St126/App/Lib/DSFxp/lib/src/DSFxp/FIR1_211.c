/**
 * @file       $RCSfile: FIR1_211.c $
 * @brief      This file contains function F__U32FIR32_SAT_U16U16 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U32FIR32_SAT_U16U16(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation.
*
* PARAMETERS:
*   type    name       meaning    
*   UInt16  Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt16* DelayLine  pointer to DelayLine vector
*   UInt16* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   UInt32  accumulation result 
*
******************************************************************************/

UInt32 F__U32FIR32_SAT_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff)
{
UInt32  Accu;

	C__U32FIR32_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
