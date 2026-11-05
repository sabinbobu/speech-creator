/**
 * @file       $RCSfile: FIR1_100.c $
 * @brief      This file contains function F__U16FIR16_SAT_U8U8 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U16FIR16_SAT_U8U8(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation.
*
* PARAMETERS:
*   type    name       meaning    
*   UInt8   Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt8*  DelayLine  pointer to DelayLine vector
*   UInt8*  Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   UInt16  accumulation result 
*
******************************************************************************/

UInt16 F__U16FIR16_SAT_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff)
{
UInt16  Accu;
	
	C__U16FIR16_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
