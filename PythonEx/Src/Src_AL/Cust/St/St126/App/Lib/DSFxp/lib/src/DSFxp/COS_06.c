/**
 * @file       $RCSfile: COS_06.c $
 * @brief      This file contains function for cosine calculation.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.6 $ $Date: 2016/07/14 13:35:49CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   F__I32COSI32_6TERMS(v)
*
* DESCRIPTION:
*   Calculates 6 terms of cosine series. 
*   cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + x^8/8! - x^10/10!
*
* PARAMETERS:
*   Int32   v      input value
*
* RETURNS:
*   Int32   fcn    return value 
*
******************************************************************************/
Int32 F__I32COSI32_6TERMS(Int32 v)
{
    Int32 fcn;
	Int32 xr;
	UInt32 x2;
	Int32 AUX_a_Int64_h;
	UInt32 AUX_a_Int64_l;

	F__I64MULI32U32(v, 0x6487ED51UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
	xr = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );

	F__I64MULI32I32(xr, xr, &AUX_a_Int64_h, &AUX_a_Int64_l);
	x2 = (UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) ); 

    F__I64MULU32U32(x2, 0x5B05B05BUL, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)((UInt32)(AUX_a_Int64_h) >> 5U);
	fcn = (Int32)(0x40000000 - fcn);

	F__I64MULU32I32(x2, fcn, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );

	F__I64MULI32U32(fcn, 0x49249249UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)((UInt32)(AUX_a_Int64_h) >> 4U);
	fcn = (Int32)(0x40000000 - fcn);

	F__I64MULU32I32(x2, fcn, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );
 	 
    F__I64MULI32U32(fcn, 0x44444444UL, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)((UInt32)(AUX_a_Int64_h) >> 3U);
	fcn = (Int32)(0x40000000 - fcn);

	F__I64MULU32I32(x2, fcn, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 2U) + (AUX_a_Int64_l >> 30U) );

	F__I64MULI32U32(fcn, 0x55555555UL, &AUX_a_Int64_h, &AUX_a_Int64_l);	
	fcn = (Int32)(UInt32)((UInt32)(AUX_a_Int64_h) >> 2U);
	fcn = (Int32)(0x40000000 - fcn);

	F__I64MULU32I32(x2, fcn, &AUX_a_Int64_h, &AUX_a_Int64_l);
	fcn = (Int32)(UInt32)( ((UInt32)(AUX_a_Int64_h) << 1U) + (AUX_a_Int64_l >> 31U) );
 	fcn = (Int32)(0x40000000 - fcn);

    return fcn;
}
/* END F__I32COSI32_6TERMS() */
