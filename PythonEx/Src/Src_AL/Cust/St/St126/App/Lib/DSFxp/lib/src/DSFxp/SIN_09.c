/**
 * @file       $RCSfile: SIN_09.c $
 * @brief      This file contains function F__I32SINI32_LE9 for calculation of trigonometric functions.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2016/06/30 09:41:58CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I32SINI32_LE9(v)
*
* DESCRIPTION:
*   Calculates sine using series approach. Last term is x^9/9! 
*
* PARAMETERS:
*   Int32   v      input value
*
* RETURNS:
*   Int32    result of trigonometric progression
*
******************************************************************************/
Int32 F__I32SINI32_LE9(Int32 v)
{
    UInt16 n;
    Int32 r;

	r = v + 0x20000000;
	n = (UInt16)((UInt32)r >> 30U);
	r &= 0x3FFFFFFF;
	r -= 0x20000000;	
	 
	switch(n)
	{
	    case 0U: r = F__I32SINI32_5TERMS(r); break;
        case 1U: r = F__I32COSI32_5TERMS(r); break;
        case 2U: r = -F__I32SINI32_5TERMS(r); break;
        default: /* is equal to case 3, because n assumes only integer values [0 .. 3] */
            r = -F__I32COSI32_5TERMS(r); break;
    }
    return r;
}
/* END F__I32SINI32_LE9() */
