/**
 * @file       $RCSfile: cmp.h $
 * @brief      This file contains macro definitions for 64bit relational operators.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.11 $ $Date: 2016/06/23 17:16:07CEST $
 */

/* Note:
 *   Both operands must have the same signedness.
 *
 *   The macro name represents the implemented operation:
 *     C__<operation><input_width>
 *
 *     input_width: 64
 *     operation  : EQ, NE, GT, LT, GE, LE
 *
 *     The result of the comparison is always 0 or 1.
 *     All macros have no return value.
 *
 *   The parameters are classified with three keywords.
 *    Parameter  Description                    Properties
 *    --------------------------------------------------------------------------
 *    v*_h       upper part of a 64-bit input   rVars,  NoConsts, NoComplexExpr
 *    v*_l       lower part of a 64-bit input   rVars,  NoConsts, NoComplexExpr
 */


#ifndef DSFXP_CMP_H
#define DSFXP_CMP_H


/* create essential bool values */
#define TLTRUE  (1 == 1)
#define TLFALSE (0 == 1)

/******************************************************************************
*
* GENERAL:
*   Generic rules, all operations, Wx == 64
*
******************************************************************************/

/******************************************************************************
*
* MACROS:
*   C__EQ64(v1_h, v1_l, v2_h, v2_l)
*   C__NE64(v1_h, v1_l, v2_h, v2_l)
*   C__GT64(v1_h, v1_l, v2_h, v2_l)
*   C__LT64(v1_h, v1_l, v2_h, v2_l)
*   C__GE64(v1_h, v1_l, v2_h, v2_l)
*   C__LE64(v1_h, v1_l, v2_h, v2_l)
*
* NOTE:
*   The input parameter is not put in parantheses inside the macro body.
*   Thus, the input value must not be an expression.
*
******************************************************************************/

#define C__EQ64(v1_h, v1_l, v2_h, v2_l)\
( (((v1_h) == (v2_h)) && ((v1_l) == (v2_l))) ? TLTRUE : TLFALSE )
/* END C__EQ64() */

#define C__NE64(v1_h, v1_l, v2_h, v2_l)\
( (((v1_h) == (v2_h)) && ((v1_l) == (v2_l))) ? TLFALSE : TLTRUE )
/* END C__NE64() */

#define C__GT64(v1_h, v1_l, v2_h, v2_l)\
( ((v1_h) > (v2_h)) ? TLTRUE : (((v1_h) < (v2_h)) ? TLFALSE : (((v1_l) > (v2_l)) ? TLTRUE : TLFALSE)) )
/* END C__GT64() */

#define C__LT64(v1_h, v1_l, v2_h, v2_l)\
( ((v1_h) < (v2_h)) ? TLTRUE : (((v1_h) > (v2_h)) ? TLFALSE : (((v1_l) < (v2_l)) ? TLTRUE : TLFALSE)) )
/* END C__LT64() */

#define C__GE64(v1_h, v1_l, v2_h, v2_l)\
( ((v1_h) < (v2_h)) ? TLFALSE : (((v1_h) > (v2_h)) ? TLTRUE : (((v1_l) < (v2_l)) ? TLFALSE : TLTRUE)) )
/* END C__GE64() */

#define C__LE64(v1_h, v1_l, v2_h, v2_l)\
( ((v1_h) > (v2_h)) ? TLFALSE : (((v1_h) < (v2_h)) ? TLTRUE : (((v1_l) > (v2_l)) ? TLFALSE : TLTRUE)) )
/* END C__LE64() */



#ifndef TL_NO_FLOATS

Int8 F__EQFLT(Float32 v1, Float32 v2);

#ifndef C__EQFLT
#define C__EQFLT(v1, v2)\
	(F__EQFLT((v1), (v2)) != 0)
#endif/* END C__EQFLT() */

#ifndef C__NEFLT
#define C__NEFLT(v1, v2)\
	(F__EQFLT((v1), (v2)) == 0)
#endif/* END C__NEFLT() */

#endif /* TL_NO_FLOATs */


#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)

Int8 F__EQDBL(Float64 v1, Float64 v2);

#ifndef C__EQDBL
#define C__EQDBL(v1, v2)\
	(F__EQDBL((v1), (v2)) != 0)
#endif/* END C__EQDBL() */

#ifndef C__NEDBL
#define C__NEDBL(v1, v2)\
	(F__EQDBL((v1), (v2)) == 0)
#endif/* END C__NEDBL() */

#endif /* TL_NO_FLOAT64 */


#endif /* #ifndef DSFXP_CMP_H */
