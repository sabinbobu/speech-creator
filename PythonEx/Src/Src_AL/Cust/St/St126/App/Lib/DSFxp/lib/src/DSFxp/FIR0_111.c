/**
 * @file       $RCSfile: FIR0_111.c $
 * @brief      This file contains function F__U16FIR16_U16U16 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U16FIR16_U16U16(Input,NTabs,DelayLine,Coeff)
*
* DESCRIPTION:
*   FIR - Filter calculation.
*
* PARAMETERS:
*   type    name       meaning    
*   UInt16  Input      current Input 
*   UInt16  NTabs      number of tabs
*   UInt16* DelayLine  pointer to DelayLine vector
*   UInt16* Coeff      pointer to Coefficients vector 
*
* RETURNS:
*   UInt16  accumulation result 
*
******************************************************************************/

UInt16 F__U16FIR16_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff)
{
UInt16  Accu;
	
	C__U16FIR16_U16U16(Input,NTabs,DelayLine,Coeff,Accu);
	return  Accu;
}
