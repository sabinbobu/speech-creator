/**
 * @file       $RCSfile: fit.h $
 * @brief      This file contains macro definitions for fitting an input value into an output type.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.11 $ $Date: 2016/10/27 11:46:31CEST $
 */

/* Note:
 *   The macro name represents the implemented operation:
 *    C__<output_type>FIT<input_type>_SAT[{l|u}]
 *
 *    output_type            : U8, U16, U32,      I8, I16, I32,
 *     input_type            : U8, U16, U32, U64, I8, I16, I32, I64
 *
 *
 *   The parameters are classified with three keywords.
 *
 *    Parameter  Description                    Properties
 *    --------------------------------------------------------------------------
 *    v          input                          rVars,  NoConsts, NoComplexExpr
 *    v_h        upper part of a 64-bit input   rVars,  NoConsts, NoComplexExpr
 *    v_l        lower part of a 64-bit input   rVars,  NoConsts, NoComplexExpr
 *    csatval    upper implementation limit (positive),
 *               the negative value is used
 *               from tllimits.h                rVars,  Consts,   NoComplexExpr
 *
 *   For compatibility reasons csatval is currently not replaced by values 
 *   from tllimits.h in all cases.
 */


#ifndef DSFXP_FIT_H
#define DSFXP_FIT_H


/******************************************************************************
*
* GENERAL:
*   Macros to fit a type into a type with a smaller width
*
******************************************************************************/

/******************************************************************************
*
* MACROS:
*   C__I32FITI64_SAT(v_h, v_l, csatval)
*   C__I32FITI64_SATu(v_h, v_l, csatval)
*   C__I32FITI64_SATl(v_h, v_l, csatval)
*
*   C__I16FITI64_SAT(v_h, v_l, csatval)
*   C__I16FITI64_SATu(v_h, v_l, csatval)
*   C__I16FITI64_SATl(v_h, v_l, csatval)
*
*   C__I8FITI64_SAT(v_h, v_l, csatval)
*   C__I8FITI64_SATu(v_h, v_l, csatval)
*   C__I8FITI64_SATl(v_h, v_l, csatval)
*
*   C__I32FITU64_SAT(v_h, v_l, csatval)
*   C__I32FITU64_SATu(v_h, v_l, csatval)
*
*   C__I16FITU64_SAT(v_h, v_l, csatval)
*   C__I16FITU64_SATu(v_h, v_l, csatval)
*
*   C__I8FITU64_SAT(v_h, v_l, csatval)
*   C__I8FITU64_SATu(v_h, v_l, csatval)
*
*   C__U32FITI64_SAT(v_h, v_l, csatval)
*   C__U32FITI64_SATu(v_h, v_l, csatval)
*   C__U32FITI64_SATl(v_h, v_l, csatval)
*
*   C__U16FITI64_SAT(v_h, v_l, csatval)
*   C__U16FITI64_SATu(v_h, v_l, csatval)
*   C__U16FITI64_SATl(v_h, v_l, csatval)
*
*   C__U8FITI64_SAT(v_h, v_l, csatval)
*   C__U8FITI64_SATu(v_h, v_l, csatval)
*   C__U8FITI64_SATl(v_h, v_l, csatval)
*
*   C__U32FITU64_SAT(v_h, v_l, csatval)
*   C__U32FITU64_SATu(v_h, v_l, csatval)
*
*   C__U16FITU64_SAT(v_h, v_l, csatval)
*   C__U16FITU64_SATu(v_h, v_l, csatval)
*
*   C__U8FITU64_SAT(v_h, v_l, csatval)
*   C__U8FITU64_SATu(v_h, v_l, csatval)
*
*
*   C__I16FITI32_SAT(v, csatval)
*   C__I16FITI32_SATu(v, csatval)
*   C__I16FITI32_SATl(v, csatval)
*
*   C__I8FITI32_SAT(v, csatval)
*   C__I8FITI32_SATu(v, csatval)
*   C__I8FITI32_SATl(v, csatval)
*
*   C__I16FITU32_SAT(v, csatval)
*   C__I16FITU32_SATu(v, csatval)
*
*   C__I8FITU32_SAT(v, csatval)
*   C__I8FITU32_SATu(v, csatval)
*
*   C__U16FITI32_SAT(v, csatval)
*   C__U16FITI32_SATu(v, csatval)
*   C__U16FITI32_SATl(v, csatval)
*
*   C__U8FITI32_SAT(v, csatval)
*   C__U8FITI32_SATu(v, csatval)
*   C__U8FITI32_SATl(v, csatval)
*
*   C__U16FITU32_SAT(v, csatval)
*   C__U16FITU32_SATu(v, csatval)
*
*   C__U8FITU32_SAT(v, csatval)
*   C__U8FITU32_SATu(v, csatval)
*
*
*   C__I8FITI16_SAT(v, csatval)
*   C__I8FITI16_SATu(v, csatval)
*   C__I8FITI16_SATl(v, csatval)
*
*   C__I8FITU16_SAT(v, csatval)
*   C__I8FITU16_SATu(v, csatval)
*
*   C__U8FITI16_SAT(v, csatval)
*   C__U8FITI16_SATu(v, csatval)
*   C__U8FITI16_SATl(v, csatval)
*
*   C__U8FITU16_SAT(v, csatval)
*   C__U8FITU16_SATu(v, csatval)
*
*
* NOTE:
*   The input values are used more than once inside the macro body.
*   Thus, for performance reasons, the input values should be no expressions.
*
******************************************************************************/

#define C__I32FITI64_SAT(v_h, v_l, csatval)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval))) ) ? (Int32)(csatval) :\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)0x80000000U)) ) ? (Int32)INT32MIN : (Int32)(v_l) ) )
#define C__I32FITI64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval))) ) ? (Int32)(csatval) : (Int32)(v_l) )
#define C__I32FITI64_SATl(v_h, v_l, csatval)\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)0x80000000U)) ) ? (Int32)INT32MIN : (Int32)(v_l) )

#define C__I16FITI64_SAT(v_h, v_l, csatval)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval))) ) ? (Int16)(csatval) :\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)0xFFFF8000U)) ) ? (Int16)INT16MIN : (Int16)(v_l) ) )
#define C__I16FITI64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval))) ) ? (Int16)(csatval) : (Int16)(v_l) )
#define C__I16FITI64_SATl(v_h, v_l, csatval)\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)0xFFFF8000U)) ) ? (Int16)INT16MIN : (Int16)(v_l) )

#define C__I8FITI64_SAT(v_h, v_l, csatval)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval))) ) ? (Int8)(csatval) :\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)0xFFFFFF80U)) ) ? (Int8)INT8MIN : (Int8)(v_l) ) )
#define C__I8FITI64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval))) ) ? (Int8)(csatval) : (Int8)(v_l) )
#define C__I8FITI64_SATl(v_h, v_l, csatval)\
    ( ( ((v_h) < -1)||(((v_h) == -1)&&((v_l) < (UInt32)0xFFFFFF80U)) ) ? (Int8)INT8MIN : (Int8)(v_l) )

#define C__I32FITU64_SAT(v_h, v_l, csatval)\
        C__I32FITU64_SATu(v_h, v_l, csatval)
#define C__I32FITU64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(csatval)) ) ? (Int32)(csatval) : (Int32)(v_l) )

#define C__I16FITU64_SAT(v_h, v_l, csatval)\
    C__I16FITU64_SATu(v_h, v_l, csatval)
#define C__I16FITU64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(csatval)) ) ? (Int16)(csatval) : (Int16)(v_l) )

#define C__I8FITU64_SAT(v_h, v_l, csatval)\
    C__I8FITU64_SATu(v_h, v_l, csatval)
#define C__I8FITU64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(csatval)) ) ? (Int8)(csatval) : (Int8)(v_l) )

#define C__U32FITI64_SAT(v_h, v_l, csatval)\
    ( ((v_h) > 0) ? (UInt32)(csatval) : ( ((v_h) < 0) ? (UInt32)UINT32MIN : (UInt32)(v_l) ) )
#define C__U32FITI64_SATu(v_h, v_l, csatval)\
    ( ((v_h) > 0) ? (UInt32)(csatval) : (UInt32)(v_l) )
#define C__U32FITI64_SATl(v_h, v_l, csatval)\
    ( ((v_h) < 0) ? (UInt32)UINT32MIN : (UInt32)(v_l) )

#define C__U16FITI64_SAT(v_h, v_l, csatval)\
    ( (((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval)))) ? (UInt16)(csatval) : ( ((v_h) < 0) ?\
    (UInt16)UINT16MIN : (UInt16)(v_l) ) )
#define C__U16FITI64_SATu(v_h, v_l, csatval)\
    ( (((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval)))) ? (UInt16)(csatval) : (UInt16)(v_l) )
#define C__U16FITI64_SATl(v_h, v_l, csatval)\
    ( ((v_h) < 0) ? (UInt16)UINT16MIN : (UInt16)(v_l) )

#define C__U8FITI64_SAT(v_h, v_l, csatval)\
    ( (((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval)))) ? (UInt8)(csatval) : ( ((v_h) < 0) ?\
    (UInt8)UINT8MIN : (UInt8)(v_l) ) )
#define C__U8FITI64_SATu(v_h, v_l, csatval)\
    ( (((v_h) > 0)||(((v_h) == 0)&&((v_l) > (UInt32)(csatval)))) ? (UInt8)(csatval) : (UInt8)(v_l) )
#define C__U8FITI64_SATl(v_h, v_l, csatval)\
    ( ((v_h) < 0) ? (UInt8)UINT8MIN : (UInt8)(v_l) )

#define C__U32FITU64_SAT(v_h, v_l, csatval)\
    C__U32FITU64_SATu(v_h, v_l, csatval)
#define C__U32FITU64_SATu(v_h, v_l, csatval)\
    ( ((v_h) > 0U) ? (UInt32)(csatval) : (UInt32)(v_l) )

#define C__U16FITU64_SAT(v_h, v_l, csatval)\
    C__U16FITU64_SATu(v_h, v_l, csatval)
#define C__U16FITU64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(csatval)) ) ? (UInt16)(csatval) : (UInt16)(v_l) )

#define C__U8FITU64_SAT(v_h, v_l, csatval)\
    C__U8FITU64_SATu(v_h, v_l, csatval)
#define C__U8FITU64_SATu(v_h, v_l, csatval)\
    ( ( ((v_h) > 0U)||((v_l) > (UInt32)(csatval)) ) ? (UInt8)(csatval) : (UInt8)(v_l) )


#define C__I16FITI32_SAT(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (Int16)(csatval) : ( ((v) < (Int32)INT16MIN) ? (Int16)INT16MIN : (Int16)(v) ) )
#define C__I16FITI32_SATu(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (Int16)(csatval) : (Int16)(v) )
#define C__I16FITI32_SATl(v, csatval)\
    ( ((v) < (Int32)INT16MIN) ? (Int16)INT16MIN : (Int16)(v) )

#define C__I8FITI32_SAT(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (Int8)(csatval) : ( ((v) < (Int32)INT8MIN) ? (Int8)INT8MIN : (Int8)(v) ) )
#define C__I8FITI32_SATu(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (Int8)(csatval) : (Int8)(v) )
#define C__I8FITI32_SATl(v, csatval)\
    ( ((v) < (Int32)INT8MIN) ? (Int8)INT8MIN : (Int8)(v) )

#define C__I16FITU32_SAT(v, csatval)\
    C__I16FITU32_SATu(v, csatval)
#define C__I16FITU32_SATu(v, csatval)\
    ( ((v) > (UInt32)(csatval)) ? (Int16)(csatval) : (Int16)(v) )

#define C__I8FITU32_SAT(v, csatval)\
    C__I8FITU32_SATu(v, csatval)
#define C__I8FITU32_SATu(v, csatval)\
    ( ((v) > (UInt32)(csatval)) ? (Int8)(csatval) : (Int8)(v) )

#define C__U16FITI32_SAT(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (UInt16)(csatval) : ( ((v) < 0) ? 0U : (UInt16)(v) ) )
#define C__U16FITI32_SATu(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (UInt16)(csatval) : (UInt16)(v) )
#define C__U16FITI32_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt16)(v) )

#define C__U8FITI32_SAT(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (UInt8)(csatval) : ( ((v) < 0) ? 0U : (UInt8)(v) ) )
#define C__U8FITI32_SATu(v, csatval)\
    ( ((v) > (Int32)(csatval)) ? (UInt8)(csatval) : (UInt8)(v) )
#define C__U8FITI32_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt8)(v) )

#define C__U16FITU32_SAT(v, csatval)\
    C__U16FITU32_SATu(v, csatval)
#define C__U16FITU32_SATu(v, csatval)\
    ( ((v) > (UInt32)(csatval)) ? (UInt16)(csatval) : (UInt16)(v) )

#define C__U8FITU32_SAT(v, csatval)\
    C__U8FITU32_SATu(v, csatval)
#define C__U8FITU32_SATu(v, csatval)\
    ( ((v) > (UInt32)(csatval)) ? (UInt8)(csatval) : (UInt8)(v) )


#define C__I8FITI16_SAT(v, csatval)\
    ( ((v) > (Int16)(csatval)) ? (Int8)(csatval) : ( ((v) < (Int16)INT8MIN) ? (Int8)INT8MIN : (Int8)(v) ) )
#define C__I8FITI16_SATu(v, csatval)\
    ( ((v) > (Int16)(csatval)) ? (Int8)(csatval) : (Int8)(v) )
#define C__I8FITI16_SATl(v, csatval)\
    ( ((v) < (Int16)INT8MIN) ? (Int8)INT8MIN : (Int8)(v) )

#define C__I8FITU16_SAT(v, csatval)\
    C__I8FITU16_SATu(v, csatval)
#define C__I8FITU16_SATu(v, csatval)\
    ( ((v) > (UInt16)(csatval)) ? (Int8)(csatval) : (Int8)(v) )

#define C__U8FITI16_SAT(v, csatval)\
    ( ((v) > (Int16)(csatval)) ? (UInt8)(csatval) : ( ((v) < 0) ? 0U : (UInt8)(v) ) )
#define C__U8FITI16_SATu(v, csatval)\
    ( ((v) > (Int16)(csatval)) ? (UInt8)(csatval) : (UInt8)(v) )
#define C__U8FITI16_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt8)(v) )

#define C__U8FITU16_SAT(v, csatval)\
    C__U8FITU16_SATu(v, csatval)
#define C__U8FITU16_SATu(v, csatval)\
    ( ((v) > (UInt16)(csatval)) ? (UInt8)(csatval) : (UInt8)(v) )



/******************************************************************************
*
* GENERAL:
*   Macros to fit a type into a type with the same width
*
******************************************************************************/

/******************************************************************************
*
* MACRO(s):
*   C__I32FITU32_SAT(v, csatval)
*   C__I32FITU32_SATu(v, csatval)
*
*   C__U32FITI32_SAT(v, csatval)
*   C__U32FITI32_SATl(v, csatval)
*
*
*   C__I16FITU16_SAT(v, csatval)
*   C__I16FITU16_SATu(v, csatval)
*
*   C__U16FITI16_SAT(v, csatval)
*   C__U16FITI16_SATl(v, csatval)
*
*
*   C__I8FITU8_SAT(v, csatval)
*   C__I8FITU8_SATu(v, csatval)
*
*   C__U8FITI8_SAT(v, csatval)
*   C__U8FITI8_SATl(v, csatval)
*
*
* NOTE:
*   The input value is used more than once inside the macro body.
*   Thus, for performance reasons, the input value should be no expression.
*
******************************************************************************/

#define C__I32FITU32_SAT(v, csatval)\
    C__I32FITU32_SATu(v, csatval)
#define C__I32FITU32_SATu(v, csatval)\
    ( ((v) > (UInt32)INT32MAX) ? (Int32)(csatval) : (Int32)(v) )

#define C__U32FITI32_SAT(v, csatval)\
    C__U32FITI32_SATl(v, csatval)
#define C__U32FITI32_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt32)(v) )


#define C__I16FITU16_SAT(v, csatval)\
    C__I16FITU16_SATu(v, csatval)
#define C__I16FITU16_SATu(v, csatval)\
    ( ((v) > (UInt16)INT16MAX) ? (Int16)(csatval) : (Int16)(v) )

#define C__U16FITI16_SAT(v, csatval)\
    C__U16FITI16_SATl(v, csatval)
#define C__U16FITI16_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt16)(v) )


#define C__I8FITU8_SAT(v, csatval)\
    C__I8FITU8_SATu(v, csatval)
#define C__I8FITU8_SATu(v, csatval)\
    ( ((v) > (UInt8)INT8MAX) ? (Int8)(csatval) : (Int8)(v) )

#define C__U8FITI8_SAT(v, csatval)\
    C__U8FITI8_SATl(v, csatval)
#define C__U8FITI8_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt8)(v) )



/******************************************************************************
*
* GENERAL:
*   Macros to fit a type into a type with a larger width
*
******************************************************************************/

/******************************************************************************
*
* MACRO(s):
*   C__U32FITI16_SAT()
*   C__U32FITI16_SATl()
*
*   C__U32FITI8_SAT()
*   C__U32FITI8_SATl()
*
*   C__U16FITI8_SAT()
*   C__U16FITI8_SATl()
*
*
* NOTE:
*   The input value is used more than once inside the macro body.
*   Thus, for performance reasons, the input value should be no expression.
*
******************************************************************************/

#define C__U32FITI16_SAT(v, csatval)\
    C__U32FITI16_SATl(v, csatval)
#define C__U32FITI16_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt32)(v) )


#define C__U32FITI8_SAT(v, csatval)\
    C__U32FITI8_SATl(v, csatval)
#define C__U32FITI8_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt32)(v) )


#define C__U16FITI8_SAT(v, csatval)\
    C__U16FITI8_SATl(v, csatval)
#define C__U16FITI8_SATl(v, csatval)\
    ( ((v) < 0) ? 0U : (UInt16)(v) )


#endif /* #ifndef DSFXP_FIT_H */
