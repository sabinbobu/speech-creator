/**
 * @file       $RCSfile: neg.h $
 * @brief      This file contains several macro definitions for the negation with 64bit values.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2012, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.7 $ $Date: 2016/06/23 13:54:18CEST $
 */

/* Note:
 * - C-macros are characterized by a leading "C__".
 *   Ansi-C-functions are characterized by a leading "F__".
 * - The macro/function-name represents the implemented operation(s):
 *	(C__|F__) + output_type + OPERATION + input_type [+ input_type] [+ _SAT]
 *
 *   C__I64NEGI64():             negate value 64bit->64bit
 *   C__I64NEGU64():             negate value 64bit->64bit
 *   C__I64NEGI32():             negate value 32bit->64bit
 *   C__I64NEGU32():             negate value 32bit->64bit
 */


#ifndef DSFXP_NEG_H
#define DSFXP_NEG_H


/******************************************************************************
*
* MACRO:
*   C__I64NEGI64(v_h, v_l, r_h, r_l)
*   C__I64NEGU64(v_h, v_l, r_h, r_l)
*
* DESCRIPTION:
*   Negates a 64 bit value to a 64bit value
*
* PARAMETERS:
*   type    name    meaning
*  xInt32   v_h    upper 32bit of the input value
*  UInt32   v_l    lower 32bit of the input value
*
* RETURNS:
*   Int32   r_h    upper 32bit of the result
*  UInt32   r_l    lower 32bit of the result
*
******************************************************************************/
#define C__I64NEGI64(v_h, v_l, r_h, r_l)\
do {\
	(r_l) = -(v_l);	/* complement */\
	(r_h) = ~(v_h);\
	if ((r_l) == 0U) { ++(r_h); }\
} while (0)
/* END C__I64NEGI64() */

#define C__I64NEGU64(v_h, v_l, r_h, r_l)\
do {\
	(r_l) = -(v_l);	/* complement */\
	(r_h) = (Int32)~(v_h);\
	if ((r_l) == 0U) { ++(r_h); }\
} while (0)
/* END C__I64NEGU64() */

/******************************************************************************
*
* MACRO:
*   C__I64NEGI32(v, r_h, r_l)
*   C__I64NEGU32(v, r_h, r_l)
*
* DESCRIPTION:
*   Negates a 32 bit value to a 64bit value
*
* PARAMETERS:
*   type    name    meaning
*  xInt32   v       input value
*
* RETURNS:
*   Int32   r_h    upper 32bit of the result
*  UInt32   r_l    lower 32bit of the result
*
******************************************************************************/
#define C__I64NEGI32(v, r_h, r_l)\
do {\
    (r_l) = (UInt32)(-(v));\
    (r_h) = (((v) > 0) ? -1 : 0);\
} while (0)
/* END C__I64NEGI32() */

#define C__I64NEGU32(v, r_h, r_l)\
do {\
    (r_l) = -(v);\
    (r_h) = (((v) > 0U) ? -1 : 0);\
} while (0)
/* END C__I64NEGU32() */


#endif /* #ifndef DSFXP_NEG_H */
