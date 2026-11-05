/**
 * @file       $RCSfile: shl.h $
 * @brief      This file contains macro definitions and function declarations for the operation Shift Left.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.11 $ $Date: 2016/11/28 14:51:47CET $
 */

/* Note:
 *   Macros whose names contain 'SAT' are with automatic saturation.
 *   The saturation limits are defined by the type of the returned variable.
 *
 *   The macro name represents the implemented operation:
 *     C__<output_type><operation><input_type>{C|U}6[{LT|EQ|GT}32][_SAT{b|l|u}]
 *
 *     output_type, input_type: U8, U16, U32, U64, I8, I16, I32, I64
 *     operation              : SHL
 *
 *
 *   The result:
 *    If a macro's parameter list contains the parameters r_h and r_l or hi and lo
 *    these variables contain the calculation result and the macro has no return
 *    value. Those macros must not be used inside expressions!
 *    All other macros have a return value.
 *
 *
 *   The parameters are classified with three keywords.
 *
 *    Parameter  Description                    Properties
 *    --------------------------------------------------------------------------
 *    v          input for a ...
 *                ... fixed type operation      rVars,  NoConsts, ComplexExpr
 *                ... saturated operation       rVars,  NoConsts, NoComplexExpr
 *    v_h        upper part of a 64-bit input   rVars,  NoConsts, NoComplexExpr
 *    v_l        lower part of a 64-bit input   rVars,  NoConsts, NoComplexExpr
 *    sh         variable shift factor          rVars,  NoConsts, NoComplexExpr
 *    csh        const shift factor             NoVars, Consts,   NoComplexExpr
 *    csh32      abs(32 - csh)                  NoVars, Consts,   NoComplexExpr
 *    r_h        upper part of a 64-bit output  wVars,  NoConsts, NoComplexExpr
 *    r_l        lower part of a 64-bit output  wVars,  NoConsts, NoComplexExpr
 *    hi          upper part of a combined
 *                64-bit input/output           rwVars, NoConsts, NoComplexExpr
 *    lo          lower part of a combined
 *                64-bit input/output           rwVars, NoConsts, NoComplexExpr
 *    maxIn      const upper input limit        rVars,  Consts,   NoComplexExpr
 *    minIn      const lower input limit        rVars,  Consts,   NoComplexExpr
 *    maxIn_h    upper part of the const
 *                upper input limit             rVars,  Consts,   NoComplexExpr
 *    maxIn_l    lower part of the const
 *                upper input limit             rVars,  Consts,   NoComplexExpr
 *    minIn_h    upper part of the const
 *                lower input limit             rVars,  Consts,   NoComplexExpr
 *    minIn_l    lower part of the const
 *                lower input limit             rVars,  Consts,   NoComplexExpr
 */


#ifndef DSFXP_SHL_H
#define DSFXP_SHL_H


/******************************************************************************
* GENERAL:
*   Generic rules, no saturation
*   (SH < Wo), (Wo == 64) && (Wx <= 32)
******************************************************************************/

/******************************************************************************
* MACROS:
*   C__I64SHLI32C6_LT32(v, csh, csh32, r_h, r_l)
*   C__I64SHLI32C6_EQ32(v, r_h, r_l)
*   C__I64SHLI32C6_GT32(v, csh32, r_h, r_l)
*
*   C__I64SHLI16C6_LT32(v, csh, csh32, r_h, r_l)
*   C__I64SHLI16C6_EQ32(v, r_h, r_l)
*   C__I64SHLI16C6_GT32(v, csh32, r_h, r_l)
*
*   C__I64SHLI8C6_LT32(v, csh, csh32, r_h, r_l)
*   C__I64SHLI8C6_EQ32(v, r_h, r_l)
*   C__I64SHLI8C6_GT32(v, csh32, r_h, r_l)
*
* NOTE:
*   The input value is used more than once inside the macro body.
*   Thus, for performance reasons, the input value should be no expression.
*   These macros do not have a return value.
******************************************************************************/

#define C__I64SHLI32C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)((v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__I64SHLI32C6_EQ32(v, r_h, r_l)\
    (r_h) = (v);\
    (r_l) = 0U

#define C__I64SHLI32C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (Int32)((v) << (csh32));\
    (r_l) = 0U

#define C__I64SHLI16C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)((Int32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__I64SHLI16C6_EQ32(v, r_h, r_l)\
    (r_h) = (Int32)(v);\
    (r_l) = 0U

#define C__I64SHLI16C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (Int32)((Int32)(v) << (csh32));\
    (r_l) = 0U

#define C__I64SHLI8C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)((Int32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__I64SHLI8C6_EQ32(v, r_h, r_l)\
    (r_h) = (Int32)(v);\
    (r_l) = 0U

#define C__I64SHLI8C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (Int32)((Int32)(v) << (csh32));\
    (r_l) = 0U


/******************************************************************************
* MACROS:
*   C__U64SHLU32C6_LT32(v, csh, csh32, r_h, r_l)
*   C__U64SHLU32C6_EQ32(v, r_h, r_l)
*   C__U64SHLU32C6_GT32(v, csh32, r_h, r_l)
*
*   C__U64SHLU16C6_LT32(v, csh, csh32, r_h, r_l)
*   C__U64SHLU16C6_EQ32(v, r_h, r_l)
*   C__U64SHLU16C6_GT32(v, csh32, r_h, r_l)
*
*   C__U64SHLU8C6_LT32(v, csh, csh32, r_h, r_l)
*   C__U64SHLU8C6_EQ32(v, r_h, r_l)
*   C__U64SHLU8C6_GT32(v, csh32, r_h, r_l)
*
* NOTE:
*   The input value is used more than once inside the macro body.
*   Thus, for performance reasons, the input value should be no expression.
*   These macros do not have a return value.
******************************************************************************/

#define C__U64SHLU32C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((v) >> (csh32));\
    (r_l) = (UInt32)((v) << (csh))

#define C__U64SHLU32C6_EQ32(v, r_h, r_l)\
    (r_h) = (v);\
    (r_l) = 0U

#define C__U64SHLU32C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (UInt32)((v) << (csh32));\
    (r_l) = 0U

#define C__U64SHLU16C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__U64SHLU16C6_EQ32(v, r_h, r_l)\
    (r_h) = (UInt32)(v);\
    (r_l) = 0U

#define C__U64SHLU16C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) << (csh32));\
    (r_l) = 0U

#define C__U64SHLU8C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__U64SHLU8C6_EQ32(v, r_h, r_l)\
    (r_h) = (UInt32)(v);\
    (r_l) = 0U

#define C__U64SHLU8C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) << (csh32));\
    (r_l) = 0U


/******************************************************************************
* MACROS:
*   C__I64SHLU32C6_LT32(v, csh, csh32, r_h, r_l)
*   C__I64SHLU32C6_EQ32(v, r_h, r_l)
*   C__I64SHLU32C6_GT32(v, csh32, r_h, r_l)
*
*   C__I64SHLU16C6_LT32(v, csh, csh32, r_h, r_l)
*   C__I64SHLU16C6_EQ32(v, r_h, r_l)
*   C__I64SHLU16C6_GT32(v, csh32, r_h, r_l)
*
*   C__I64SHLU8C6_LT32(v, csh, csh32, r_h, r_l)
*   C__I64SHLU8C6_EQ32(v, r_h, r_l)
*   C__I64SHLU8C6_GT32(v, csh32, r_h, r_l)
*
* NOTE:
*   The input value is used more than once inside the macro body.
*   Thus, for performance reasons, the input value should be no expression.
*   These macros do not have a return value.
******************************************************************************/

#define C__I64SHLU32C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)((v) >> (csh32));\
    (r_l) = (UInt32)((v) << (csh))

#define C__I64SHLU32C6_EQ32(v, r_h, r_l)\
    (r_h) = (Int32)(v);\
    (r_l) = 0U

#define C__I64SHLU32C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (Int32)((v) << (csh32));\
    (r_l) = 0U

#define C__I64SHLU16C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__I64SHLU16C6_EQ32(v, r_h, r_l)\
    (r_h) = (Int32)(v);\
    (r_l) = 0U

#define C__I64SHLU16C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (Int32)((UInt32)(v) << (csh32));\
    (r_l) = 0U

#define C__I64SHLU8C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__I64SHLU8C6_EQ32(v, r_h, r_l)\
    (r_h) = (Int32)(v);\
    (r_l) = 0U

#define C__I64SHLU8C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (Int32)((UInt32)(v) << (csh32));\
    (r_l) = 0U


/******************************************************************************
* MACROS:
*   C__U64SHLI32C6_LT32(v, csh, csh32, r_h, r_l)
*   C__U64SHLI32C6_EQ32(v, r_h, r_l)
*   C__U64SHLI32C6_GT32(v, csh32, r_h, r_l)
*
*   C__U64SHLI16C6_LT32(v, csh, csh32, r_h, r_l)
*   C__U64SHLI16C6_EQ32(v, r_h, r_l)
*   C__U64SHLI16C6_GT32(v, csh32, r_h, r_l)
*
*   C__U64SHLI8C6_LT32(v, csh, csh32, r_h, r_l)
*   C__U64SHLI8C6_EQ32(v, r_h, r_l)
*   C__U64SHLI8C6_GT32(v, csh32, r_h, r_l)
*
* NOTE:
*   The input value is used more than once inside the macro body.
*   Thus, for performance reasons, the input value should be no expression.
*   These macros do not have a return value.
******************************************************************************/

#define C__U64SHLI32C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__U64SHLI32C6_EQ32(v, r_h, r_l)\
    (r_h) = (UInt32)(v);\
    (r_l) = 0U

#define C__U64SHLI32C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) << (csh32));\
    (r_l) = 0U

#define C__U64SHLI16C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__U64SHLI16C6_EQ32(v, r_h, r_l)\
    (r_h) = (UInt32)(v);\
    (r_l) = 0U

#define C__U64SHLI16C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) << (csh32));\
    (r_l) = 0U

#define C__U64SHLI8C6_LT32(v, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) >> (csh32));\
    (r_l) = (UInt32)((UInt32)(v) << (csh))

#define C__U64SHLI8C6_EQ32(v, r_h, r_l)\
    (r_h) = (UInt32)(v);\
    (r_l) = 0U

#define C__U64SHLI8C6_GT32(v, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v) << (csh32));\
    (r_l) = 0U


/******************************************************************************
* GENERAL:
*   Generic rules, no saturation
*   (SH < Wo), (Wo == 64) && (Wx == 64)
******************************************************************************/

/******************************************************************************
* MACROS:
*   C__I64SHLI64C6_LT32(hi, lo, csh, csh32)
*   C__I64SHLI64C6_EQ32(hi, lo)
*   C__I64SHLI64C6_GT32(hi, lo, csh32)
*
* NOTE:
*   The input values are modified.
*   Use these macros only with temporary variables.
*   These macros do not have a return value.
******************************************************************************/

#define C__I64SHLI64C6_LT32(hi, lo, csh, csh32)\
    (hi) = (Int32)(/* CTO */ (UInt32)((hi) << (csh)) + (UInt32)((lo) >> (csh32)) );\
    (lo) = (UInt32)((lo) << (csh))

#define C__I64SHLI64C6_EQ32(hi, lo)\
    (hi) = (Int32)(lo);\
    (lo) = 0U

#define C__I64SHLI64C6_GT32(hi, lo, csh32)\
    (hi) = (Int32)((lo) << (csh32));\
    (lo) = 0U


/******************************************************************************
* MACROS:
*   C__U64SHLU64C6_LT32(v_h, v_l, csh, csh32)
*   C__U64SHLU64C6_EQ32(v_h, v_l)
*   C__U64SHLU64C6_GT32(v_h, v_l, csh32)
*
* NOTE:
*   The input values are modified.
*   Use these macros only with temporary variables.
*   These macros do not have a return value.
******************************************************************************/

#define C__U64SHLU64C6_LT32(hi, lo, csh, csh32)\
    (hi) = (UInt32)((hi) << (csh)) + (UInt32)((lo) >> (csh32));\
    (lo) = (UInt32)((lo) << (csh))

#define C__U64SHLU64C6_EQ32(hi, lo)\
    (hi) = (lo);\
    (lo) = 0U

#define C__U64SHLU64C6_GT32(hi, lo, csh32)\
    (hi) = (UInt32)((lo) << (csh32));\
    (lo) = 0U


/******************************************************************************
* MACROS:
*   C__I64SHLU64C6_LT32(v_h, v_l, csh, csh32, r_h, r_l)
*   C__I64SHLU64C6_EQ32(v_l, r_h, r_l)
*   C__I64SHLU64C6_GT32(v_l, csh32, r_h, r_l)
*
* NOTE:
*   These macros do not have a return value.
******************************************************************************/

#define C__I64SHLU64C6_LT32(v_h, v_l, csh, csh32, r_h, r_l)\
    (r_h) = (Int32)( (UInt32)((v_h) << (csh)) + (UInt32)((v_l) >> (csh32)) );\
    (r_l) = (UInt32)((v_l) << (csh))

#define C__I64SHLU64C6_EQ32(v_l, r_h, r_l)\
    (r_h) = (Int32)(v_l);\
    (r_l) = 0U

#define C__I64SHLU64C6_GT32(v_l, csh32, r_h, r_l)\
    (r_h) = (Int32)((v_l) << (csh32));\
    (r_l) = 0U


/******************************************************************************
* MACROS:
*   C__U64SHLI64C6_LT32(v_h, v_l, csh, csh32, r_h, r_l)
*   C__U64SHLI64C6_EQ32(v_l, r_h, r_l)
*   C__U64SHLI64C6_GT32(v_l, csh32, r_h, r_l)
*
* NOTE:
*   These macros do not have a return value.
******************************************************************************/

#define C__U64SHLI64C6_LT32(v_h, v_l, csh, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v_h) << (csh)) + (UInt32)((UInt32)(v_l) >> (csh32));\
    (r_l) = (UInt32)((v_l) << (csh))

#define C__U64SHLI64C6_EQ32(v_l, r_h, r_l)\
    (r_h) = (v_l);\
    (r_l) = 0U

#define C__U64SHLI64C6_GT32(v_l, csh32, r_h, r_l)\
    (r_h) = (UInt32)((UInt32)(v_l) << (csh32));\
    (r_l) = 0U


/******************************************************************************
* GENERAL:
*   Generic rules, with saturation
*   (Wo <= 32) && (Wx <= 32)
******************************************************************************/

/******************************************************************************
* MACROS:
*   C__I32SHLI32C6_SATb(v, csh, maxIn, minIn)
*   C__I32SHLI32C6_SATu(v, csh, maxIn)
*   C__I32SHLI32C6_SATl(v, csh, minIn)
*
*   C__I32SHLI16C6_SATb(v, csh, maxIn, minIn)
*   C__I32SHLI16C6_SATu(v, csh, maxIn)
*   C__I32SHLI16C6_SATl(v, csh, minIn)
*
*   C__I32SHLI8C6_SATb(v, csh, maxIn, minIn)
*   C__I32SHLI8C6_SATu(v, csh, maxIn)
*   C__I32SHLI8C6_SATl(v, csh, minIn)
*
*
*   C__I16SHLI32C6_SATb(v, csh, maxIn, minIn)
*   C__I16SHLI32C6_SATu(v, csh, maxIn)
*   C__I16SHLI32C6_SATl(v, csh, minIn)
*
*   C__I16SHLI16C6_SATb(v, csh, maxIn, minIn)
*   C__I16SHLI16C6_SATu(v, csh, maxIn)
*   C__I16SHLI16C6_SATl(v, csh, minIn)
*
*   C__I16SHLI8C6_SATb(v, csh, maxIn, minIn)
*   C__I16SHLI8C6_SATu(v, csh, maxIn)
*   C__I16SHLI8C6_SATl(v, csh, minIn)
*
*
*   C__I8SHLI32C6_SATb(v, csh, maxIn, minIn)
*   C__I8SHLI32C6_SATu(v, csh, maxIn)
*   C__I8SHLI32C6_SATl(v, csh, minIn)
*
*   C__I8SHLI16C6_SATb(v, csh, maxIn, minIn)
*   C__I8SHLI16C6_SATu(v, csh, maxIn)
*   C__I8SHLI16C6_SATl(v, csh, minIn)
*
*   C__I8SHLI8C6_SATb(v, csh, maxIn, minIn)
*   C__I8SHLI8C6_SATu(v, csh, maxIn)
*   C__I8SHLI8C6_SATl(v, csh, minIn)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1  ;  minIn = ~maxIn
*               2^csh
******************************************************************************/

#define C__I32SHLI32C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int32)(maxIn)) ? (Int32)INT32MAX : ( ((v) < (Int32)(minIn)) ? (Int32)INT32MIN : (Int32)((v) << (csh)) ) )

#define C__I32SHLI32C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (Int32)INT32MAX : (Int32)((v) << (csh)) )

#define C__I32SHLI32C6_SATl(v, csh, minIn)\
    ( ((v) < (Int32)(minIn)) ? (Int32)INT32MIN : (Int32)((v) << (csh)) )


#define C__I32SHLI16C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int16)(maxIn)) ? (Int32)INT32MAX : ( ((v) < (Int16)(minIn)) ? (Int32)INT32MIN : (Int32)((Int32)(v) << (csh)) ) )

#define C__I32SHLI16C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (Int32)INT32MAX : (Int32)((Int32)(v) << (csh)) )

#define C__I32SHLI16C6_SATl(v, csh, minIn)\
    ( ((v) < (Int16)(minIn)) ? (Int32)INT32MIN : (Int32)((Int32)(v) << (csh)) )


#define C__I32SHLI8C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int8)(maxIn)) ? (Int32)INT32MAX : ( ((v) < (Int8)(minIn)) ? (Int32)INT32MIN : (Int32)((Int32)(v) << (csh)) ) )

#define C__I32SHLI8C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (Int32)INT32MAX : (Int32)((Int32)(v) << (csh)) )

#define C__I32SHLI8C6_SATl(v, csh, minIn)\
    ( ((v) < (Int8)(minIn)) ? (Int32)INT32MIN : (Int32)((Int32)(v) << (csh)) )


#define C__I16SHLI32C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int32)(maxIn)) ? (Int16)INT16MAX : ( ((v) < (Int32)(minIn)) ? (Int16)INT16MIN : (Int16)((Int32)(v) << (csh)) ) )

#define C__I16SHLI32C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (Int16)INT16MAX : (Int16)((Int32)(v) << (csh)) )

#define C__I16SHLI32C6_SATl(v, csh, minIn)\
    ( ((v) < (Int32)(minIn)) ? (Int16)INT16MIN : (Int16)((Int32)(v) << (csh)) )


#define C__I16SHLI16C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int16)(maxIn)) ? (Int16)INT16MAX : ( ((v) < (Int16)(minIn)) ? (Int16)INT16MIN : (Int16)((v) << (csh)) ) )

#define C__I16SHLI16C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (Int16)INT16MAX : (Int16)((v) << (csh)) )

#define C__I16SHLI16C6_SATl(v, csh, minIn)\
    ( ((v) < (Int16)(minIn)) ? (Int16)INT16MIN : (Int16)((v) << (csh)) )


#define C__I16SHLI8C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int8)(maxIn)) ? (Int16)INT16MAX : ( ((v) < (Int8)(minIn)) ? (Int16)INT16MIN : (Int16)((Int16)(v) << (csh)) ) )

#define C__I16SHLI8C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (Int16)INT16MAX : (Int16)((Int16)(v) << (csh)) )

#define C__I16SHLI8C6_SATl(v, csh, minIn)\
    ( ((v) < (Int8)(minIn)) ? (Int16)INT16MIN : (Int16)((Int16)(v) << (csh)) )


#define C__I8SHLI32C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int32)(maxIn)) ? (Int8)INT8MAX : ( ((v) < (Int32)(minIn)) ? (Int8)INT8MIN : (Int8)((v) << (csh)) ) )

#define C__I8SHLI32C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (Int8)INT8MAX : (Int8)((v) << (csh)) )

#define C__I8SHLI32C6_SATl(v, csh, minIn)\
    ( ((v) < (Int32)(minIn)) ? (Int8)INT8MIN : (Int8)((v) << (csh)) )


#define C__I8SHLI16C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int16)(maxIn)) ? (Int8)INT8MAX : ( ((v) < (Int16)(minIn)) ? (Int8)INT8MIN : (Int8)((v) << (csh)) ) )

#define C__I8SHLI16C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (Int8)INT8MAX : (Int8)((v) << (csh)) )

#define C__I8SHLI16C6_SATl(v, csh, minIn)\
    ( ((v) < (Int16)(minIn)) ? (Int8)INT8MIN : (Int8)((v) << (csh)) )


#define C__I8SHLI8C6_SATb(v, csh, maxIn, minIn)\
    ( ((v) > (Int8)(maxIn)) ? (Int8)INT8MAX : ( ((v) < (Int8)(minIn)) ? (Int8)INT8MIN : (Int8)((v) << (csh)) ) )

#define C__I8SHLI8C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (Int8)INT8MAX : (Int8)((v) << (csh)) )

#define C__I8SHLI8C6_SATl(v, csh, minIn)\
    ( ((v) < (Int8)(minIn)) ? (Int8)INT8MIN : (Int8)((v) << (csh)) )


/******************************************************************************
* MACROS:
*   C__U32SHLU32C6_SATu(v, csh, maxIn)
*
*   C__U32SHLU16C6_SATu(v, csh, maxIn)
*
*   C__U32SHLU8C6_SATu(v, csh, maxIn)
*
*
*   C__U16SHLU32C6_SATu(v, csh, maxIn)
*
*   C__U16SHLU16C6_SATu(v, csh, maxIn)
*
*   C__U16SHLU8C6_SATu(v, csh, maxIn)
*
*
*   C__U8SHLU32C6_SATu(v, csh, maxIn)
*
*   C__U8SHLU16C6_SATu(v, csh, maxIn)
*
*   C__U8SHLU8C6_SATu(v, csh, maxIn)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1
*               2^csh
******************************************************************************/

#define C__U32SHLU32C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt32)(maxIn)) ? (UInt32)UINT32MAX : (UInt32)((v) << (csh)) )

#define C__U32SHLU16C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt16)(maxIn)) ? (UInt32)UINT32MAX : (UInt32)((UInt32)(v) << (csh)) )

#define C__U32SHLU8C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt8)(maxIn)) ? (UInt32)UINT32MAX : (UInt32)((UInt32)(v) << (csh)) )

#define C__U16SHLU32C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt32)(maxIn)) ? (UInt16)UINT16MAX : (UInt16)((v) << (csh)) )

#define C__U16SHLU16C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt16)(maxIn)) ? (UInt16)UINT16MAX : (UInt16)((v) << (csh)) )

#define C__U16SHLU8C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt8)(maxIn)) ? (UInt16)UINT16MAX : (UInt16)((UInt16)(v) << (csh)) )

#define C__U8SHLU32C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt32)(maxIn)) ? (UInt8)UINT8MAX : (UInt8)((v) << (csh)) )

#define C__U8SHLU16C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt16)(maxIn)) ? (UInt8)UINT8MAX : (UInt8)((v) << (csh)) )

#define C__U8SHLU8C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt8)(maxIn)) ? (UInt8)UINT8MAX : (UInt8)((v) << (csh)) )


/******************************************************************************
* MACROS:
*   C__I32SHLU32C6_SATu(v, csh, maxIn)
*
*   C__I32SHLU16C6_SATu(v, csh, maxIn)
*
*   C__I32SHLU8C6_SATu(v, csh, maxIn)
*
*
*   C__I16SHLU32C6_SATu(v, csh, maxIn)
*
*   C__I16SHLU16C6_SATu(v, csh, maxIn)
*
*   C__I16SHLU8C6_SATu(v, csh, maxIn)
*
*
*   C__I8SHLU32C6_SATu(v, csh, maxIn)
*
*   C__I8SHLU16C6_SATu(v, csh, maxIn)
*
*   C__I8SHLU8C6_SATu(v, csh, maxIn)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1
*               2^csh
******************************************************************************/

#define C__I32SHLU32C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt32)(maxIn)) ? (Int32)INT32MAX : (Int32)((v) << (csh)) )

#define C__I32SHLU16C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt16)(maxIn)) ? (Int32)INT32MAX : (Int32)((UInt32)(v) << (csh)) )

#define C__I32SHLU8C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt8)(maxIn)) ? (Int32)INT32MAX : (Int32)((UInt32)(v) << (csh)) )

#define C__I16SHLU32C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt32)(maxIn)) ? (Int16)INT16MAX : (Int16)((v) << (csh)) )

#define C__I16SHLU16C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt16)(maxIn)) ? (Int16)INT16MAX : (Int16)((v) << (csh)) )

#define C__I16SHLU8C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt8)(maxIn)) ? (Int16)INT16MAX : (Int16)((UInt16)(v) << (csh)) )

#define C__I8SHLU32C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt32)(maxIn)) ? (Int8)INT8MAX : (Int8)((v) << (csh)) )

#define C__I8SHLU16C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt16)(maxIn)) ? (Int8)INT8MAX : (Int8)((v) << (csh)) )

#define C__I8SHLU8C6_SATu(v, csh, maxIn)\
    ( ((v) > (UInt8)(maxIn)) ? (Int8)INT8MAX : (Int8)((v) << (csh)) )


/******************************************************************************
* MACROS:
*   C__U32SHLI32C6_SATb(v, csh, maxIn)
*   C__U32SHLI32C6_SATu(v, csh, maxIn)
*   C__U32SHLI32C6_SATl(v, csh)
*
*   C__U32SHLI16C6_SATb(v, csh, maxIn)
*   C__U32SHLI16C6_SATu(v, csh, maxIn)
*   C__U32SHLI16C6_SATl(v, csh)
*
*   C__U32SHLI8C6_SATb(v, csh, maxIn)
*   C__U32SHLI8C6_SATu(v, csh, maxIn)
*   C__U32SHLI8C6_SATl(v, csh)
*
*
*   C__U16SHLI32C6_SATb(v, csh, maxIn)
*   C__U16SHLI32C6_SATu(v, csh, maxIn)
*   C__U16SHLI32C6_SATl(v, csh)
*
*   C__U16SHLI16C6_SATb(v, csh, maxIn)
*   C__U16SHLI16C6_SATu(v, csh, maxIn)
*   C__U16SHLI16C6_SATl(v, csh)
*
*   C__U16SHLI8C6_SATb(v, csh, maxIn)
*   C__U16SHLI8C6_SATu(v, csh, maxIn)
*   C__U16SHLI8C6_SATl(v, csh)
*
*
*   C__U8SHLI32C6_SATb(v, csh, maxIn)
*   C__U8SHLI32C6_SATu(v, csh, maxIn)
*   C__U8SHLI32C6_SATl(v, csh)
*
*   C__U8SHLI16C6_SATb(v, csh, maxIn)
*   C__U8SHLI16C6_SATu(v, csh, maxIn)
*   C__U8SHLI16C6_SATl(v, csh)
*
*   C__U8SHLI8C6_SATb(v, csh, maxIn)
*   C__U8SHLI8C6_SATu(v, csh, maxIn)
*   C__U8SHLI8C6_SATl(v, csh)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1
*               2^csh
******************************************************************************/

#define C__U32SHLI32C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (UInt32)UINT32MAX : ( ((v) < 0) ? (UInt32)0 : (UInt32)((UInt32)(v) << (csh)) ) )

#define C__U32SHLI32C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (UInt32)UINT32MAX : (UInt32)((UInt32)(v) << (csh)) )

#define C__U32SHLI32C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt32)0 : (UInt32)((UInt32)(v) << (csh)) )


#define C__U32SHLI16C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (UInt32)UINT32MAX : ( ((v) < 0) ? (UInt32)0 : (UInt32)((UInt32)(v) << (csh)) ) )

#define C__U32SHLI16C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (UInt32)UINT32MAX : (UInt32)((UInt32)(v) << (csh)) )

#define C__U32SHLI16C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt32)0 : (UInt32)((UInt32)(v) << (csh)) )


#define C__U32SHLI8C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (UInt32)UINT32MAX : ( ((v) < 0) ? (UInt32)0 : (UInt32)((UInt32)(v) << (csh)) ) )

#define C__U32SHLI8C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (UInt32)UINT32MAX : (UInt32)((UInt32)(v) << (csh)) )

#define C__U32SHLI8C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt32)0 : (UInt32)((UInt32)(v) << (csh)) )


#define C__U16SHLI32C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (UInt16)UINT16MAX : ( ((v) < 0) ? (UInt16)0 : (UInt16)((UInt16)(v) << (csh)) ) )

#define C__U16SHLI32C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (UInt16)UINT16MAX : (UInt16)((UInt16)(v) << (csh)) )

#define C__U16SHLI32C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt16)0 : (UInt16)((UInt16)(v) << (csh)) )


#define C__U16SHLI16C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (UInt16)UINT16MAX : ( ((v) < 0) ? (UInt16)0 : (UInt16)((UInt16)(v) << (csh)) ) )

#define C__U16SHLI16C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (UInt16)UINT16MAX : (UInt16)((UInt16)(v) << (csh)) )

#define C__U16SHLI16C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt16)0 : (UInt16)((UInt16)(v) << (csh)) )


#define C__U16SHLI8C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (UInt16)UINT16MAX : ( ((v) < 0) ? (UInt16)0 : (UInt16)((UInt16)(v) << (csh)) ) )

#define C__U16SHLI8C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (UInt16)UINT16MAX : (UInt16)((UInt16)(v) << (csh)) )

#define C__U16SHLI8C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt16)0 : (UInt16)((UInt16)(v) << (csh)) )


#define C__U8SHLI32C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (UInt8)UINT8MAX : ( ((v) < 0) ? (UInt8)0 : (UInt8)((UInt8)(v) << (csh)) ) )

#define C__U8SHLI32C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int32)(maxIn)) ? (UInt8)UINT8MAX : (UInt8)((UInt8)(v) << (csh)) )

#define C__U8SHLI32C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt8)0 : (UInt8)((UInt8)(v) << (csh)) )


#define C__U8SHLI16C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (UInt8)UINT8MAX : ( ((v) < 0) ? (UInt8)0 : (UInt8)((UInt8)(v) << (csh)) ) )

#define C__U8SHLI16C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int16)(maxIn)) ? (UInt8)UINT8MAX : (UInt8)((UInt8)(v) << (csh)) )

#define C__U8SHLI16C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt8)0 : (UInt8)((UInt8)(v) << (csh)) )


#define C__U8SHLI8C6_SATb(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (UInt8)UINT8MAX : ( ((v) < 0) ? (UInt8)0 : (UInt8)((UInt8)(v) << (csh)) ) )

#define C__U8SHLI8C6_SATu(v, csh, maxIn)\
    ( ((v) > (Int8)(maxIn)) ? (UInt8)UINT8MAX : (UInt8)((UInt8)(v) << (csh)) )

#define C__U8SHLI8C6_SATl(v, csh)\
    ( ((v) < 0) ? (UInt8)0 : (UInt8)((UInt8)(v) << (csh)) )


/******************************************************************************
* GENERAL:
*   Generic rules, with saturation
*   (Wo <= 32) && (Wx == 64)
******************************************************************************/

/******************************************************************************
* MACROS:
*   C__I32SHLI64C6_SATb(v_h, v_l, csh, maxIn_l, minIn_l)
*   C__I32SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)
*   C__I32SHLI64C6_SATl(v_h, v_l, csh, minIn_l)
*
*   C__I16SHLI64C6_SATb(v_h, v_l, csh, maxIn_l, minIn_l)
*   C__I16SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)
*   C__I16SHLI64C6_SATl(v_h, v_l, csh, minIn_l)
*
*   C__I8SHLI64C6_SATb(v_h, v_l, csh, maxIn_l, minIn_l)
*   C__I8SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)
*   C__I8SHLI64C6_SATl(v_h, v_l, csh, minIn_l)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1  ;  minIn = ~maxIn
*               2^csh
******************************************************************************/

#define C__I32SHLI64C6_SATb(v_h, v_l, csh, maxIn_l, minIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (Int32)INT32MAX :\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)(minIn_l))) ) ? (Int32)INT32MIN :\
    (Int32)((v_l) << (csh)) ) )

#define C__I32SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (Int32)INT32MAX :\
    (Int32)((v_l) << (csh)) )

#define C__I32SHLI64C6_SATl(v_h, v_l, csh, minIn_l)\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)(minIn_l))) ) ? (Int32)INT32MIN :\
    (Int32)((v_l) << (csh)) )


#define C__I16SHLI64C6_SATb(v_h, v_l, csh, maxIn_l, minIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (Int16)INT16MAX :\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)(minIn_l))) ) ? (Int16)INT16MIN :\
    (Int16)((v_l) << (csh)) ) )

#define C__I16SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (Int16)INT16MAX :\
    (Int16)((v_l) << (csh)) )

#define C__I16SHLI64C6_SATl(v_h, v_l, csh, minIn_l)\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)(minIn_l))) ) ? (Int16)INT16MIN :\
    (Int16)((v_l) << (csh)) )


#define C__I8SHLI64C6_SATb(v_h, v_l, csh, maxIn_l, minIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (Int8)INT8MAX :\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)(minIn_l))) ) ? (Int8)INT8MIN :\
    (Int8)((v_l) << (csh)) ) )

#define C__I8SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (Int8)INT8MAX :\
    (Int8)((v_l) << (csh)) )

#define C__I8SHLI64C6_SATl(v_h, v_l, csh, minIn_l)\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)(minIn_l))) ) ? (Int8)INT8MIN :\
    (Int8)((v_l) << (csh)) )


/******************************************************************************
* MACROS:
*   C__U32SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)
*
*   C__U16SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)
*
*   C__U8SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1
*               2^csh
******************************************************************************/

#define C__U32SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(maxIn_l)) ) ? (UInt32)UINT32MAX :\
    (UInt32)((v_l) << (csh)) )

#define C__U16SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(maxIn_l)) ) ? (UInt16)UINT16MAX :\
    (UInt16)((v_l) << (csh)) )

#define C__U8SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(maxIn_l)) ) ? (UInt8)UINT8MAX :\
    (UInt8)((v_l) << (csh)) )


/******************************************************************************
* MACROS:
*   C__I32SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)
*
*   C__I16SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)
*
*   C__I8SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1
*               2^csh
******************************************************************************/

#define C__I32SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(maxIn_l)) ) ? (Int32)INT32MAX :\
    (Int32)((v_l) << (csh)) )

#define C__I16SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(maxIn_l)) ) ? (Int16)INT16MAX :\
    (Int16)((v_l) << (csh)) )

#define C__I8SHLU64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(maxIn_l)) ) ? (Int8)INT8MAX :\
    (Int8)((v_l) << (csh)) )


/******************************************************************************
* MACROS:
*   C__U32SHLI64C6_SATb(v_h, v_l, csh, maxIn_l)
*   C__U32SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)
*   C__U32SHLI64C6_SATl(v_h, v_l, csh)
*
*   C__U16SHLI64C6_SATb(v_h, v_l, csh, maxIn_l)
*   C__U16SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)
*   C__U16SHLI64C6_SATl(v_h, v_l, csh)
*
*   C__U8SHLI64C6_SATb(v_h, v_l, csh, maxIn_l)
*   C__U8SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)
*   C__U8SHLI64C6_SATl(v_h, v_l, csh)
*
* NOTE:
*   For efficency reasons and to avoid side effects the input values should not be expressions.
*
*           2^(Wresult-1)
*   maxIn = ------------- - 1
*               2^csh
******************************************************************************/

#define C__U32SHLI64C6_SATb(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (UInt32)UINT32MAX :\
    ( ((v_h) < 0) ? (UInt32)0 : (UInt32)((v_l) << (csh)) ) )

#define C__U32SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (UInt32)UINT32MAX :\
    (UInt32)((v_l) << (csh)) )

#define C__U32SHLI64C6_SATl(v_h, v_l, csh)\
    ( ((v_h) < 0) ? (UInt32)0 : (UInt32)((v_l) << (csh)) )


#define C__U16SHLI64C6_SATb(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (UInt16)UINT16MAX :\
    ( ((v_h) < 0) ? (UInt16)0 : (UInt16)((v_l) << (csh)) ) )

#define C__U16SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (UInt16)UINT16MAX :\
    (UInt16)((v_l) << (csh)) )

#define C__U16SHLI64C6_SATl(v_h, v_l, csh)\
    ( ((v_h) < 0) ? (UInt16)0 : (UInt16)((v_l) << (csh)) )


#define C__U8SHLI64C6_SATb(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (UInt8)UINT8MAX :\
    ( ((v_h) < 0) ? (UInt8)0 : (UInt8)((v_l) << (csh)) ) )

#define C__U8SHLI64C6_SATu(v_h, v_l, csh, maxIn_l)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(maxIn_l))) ) ? (UInt8)UINT8MAX :\
    (UInt8)((v_l) << (csh)) )

#define C__U8SHLI64C6_SATl(v_h, v_l, csh)\
    ( ((v_h) < 0) ? (UInt8)0 : (UInt8)((v_l) << (csh)) )


#endif /* #ifndef DSFXP_SHL_H */
