/**
 * @file       $RCSfile: FIR3_222.c $
 * @brief      This file contains function F__U32FIR32_SAT_U32CBU32 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__U32FIR32_SAT_U32CBU32(Input,NTabs,DelayLine,Coeff,Counter)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation and circular buffer.
*
* PARAMETERS:
*   type     name       meaning
*   UInt32   Input      current Input
*   UInt16   NTabs      number of tabs
*   UInt16*  Counter    pointer to the Counter variable (to work in conjunction with circular buffer)
*   UInt32*  DelayLine  pointer to DelayLine vector
*   UInt32*  Coeff      pointer to Coefficients vector
*
* RETURNS:
*   UInt32   accumulation result
*
******************************************************************************/

UInt32 F__U32FIR32_SAT_U32CBU32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt16* Counter)
{
UInt32 Accu;

	C__U32FIR32_SAT_U32CBU32(Input,NTabs,DelayLine,Coeff,(*Counter),Accu);
	return  Accu;
}
