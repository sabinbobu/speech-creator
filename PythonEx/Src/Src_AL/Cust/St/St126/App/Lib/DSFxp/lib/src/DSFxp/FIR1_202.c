/**
 * @file       $RCSfile: FIR1_202.c $
 * @brief      This file contains function F__U32FIR32_SAT_U8U32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U32FIR32_SAT_U8U32(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation.
*
* PARAMETERS:
*   type    name       meaning    
*   UInt8   Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt8*  DelayLine  pointer to DelayLine vector
*   UInt32* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   UInt32  accumulation result 
*
******************************************************************************/

UInt32 F__U32FIR32_SAT_U8U32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff)
{
UInt32  Accu;

	C__U32FIR32_SAT_U8U32(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
