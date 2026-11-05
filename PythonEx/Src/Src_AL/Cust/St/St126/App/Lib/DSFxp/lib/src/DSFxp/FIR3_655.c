/**
 * @file       $RCSfile: FIR3_655.c $
 * @brief      This file contains function F__I32FIR32_SAT_I16CBI16 for FIR filter calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2015/08/03 07:25:05CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* Function:
*   F__I32FIR32_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,Counter)
*
* DESCRIPTION:
*   FIR - Filter calculation with saturation and circular buffer.
*
* PARAMETERS:
*   type     name       meaning
*   Int16    Input      current Input
*   UInt16   NTabs      number of tabs
*   UInt16*  Counter    pointer to the Counter variable (to work in conjunction with circular buffer)
*   Int16*   DelayLine  pointer to DelayLine vector
*   Int16*   Coeff      pointer to Coefficients vector
*
* RETURNS:
*   Int32    accumulation result
*
******************************************************************************/

Int32 F__I32FIR32_SAT_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16* Counter)
{
Int32 Accu;

	C__I32FIR32_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,(*Counter),Accu);
	return  Accu;
}
