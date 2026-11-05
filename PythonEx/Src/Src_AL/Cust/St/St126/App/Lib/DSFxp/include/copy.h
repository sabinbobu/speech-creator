/**
 * @file       $RCSfile: copy.h $
 * @brief      This file contains macro definitions the negation with 64bit values.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.6 $ $Date: 2016/12/01 08:24:43CET $
 */

/* Note:
 * - C-macros are characterized by a leading "C__".
 *   Ansi-C-functions are characterized by a leading "F__".
 * - The macro/function-name represents the implemented operation(s):
 *	(C__|F__) + output_type + OPERATION + input_type [+ input_type] [+ _SAT]
 *
 *   C__I64COPYI64():             copy value 64bit->64bit
 *   C__U64COPYU64():             copy value 64bit->64bit
 *   C__I64COPYI32():             copy value 32bit->64bit
 *   C__I64COPYU32():             copy value 32bit->64bit
 *   C__U64COPYU32():             copy value 32bit->64bit
 */


#ifndef DSFXP_COPY_H
#define DSFXP_COPY_H

/******************************************************************************
*
* MACRO:
*   C__I64COPYI64(v_h, v_l, r_h, r_l)
*   C__U64COPYU64(v_h, v_l, r_h, r_l)
*   C__I64COPYU64(v_h, v_l, r_h, r_l)
*   C__U64COPYI64(v_h, v_l, r_h, r_l)
*
* DESCRIPTION:
*   Copies a 64 bit value to a 64bit value
*
* PARAMETERS:
*   type    name    meaning
*  xInt32   v_h    upper 32bit of the input value
*  UInt32   v_l    lower 32bit of the input value
*
* RETURNS:
*  yInt32   r_h    upper 32bit of the result
*  UInt32   r_l    lower 32bit of the result
*
******************************************************************************/
#define C__I64COPYI64(v_h, v_l, r_h, r_l)\
{\
    (r_h) = (v_h);\
    (r_l) = (v_l);\
}/* END C__I64COPYI64() */

#define C__U64COPYU64(v_h, v_l, r_h, r_l)\
{\
    (r_h) = (v_h);\
    (r_l) = (v_l);\
}/* END C__U64COPYU64() */

#define C__I64COPYU64(v_h, v_l, r_h, r_l)\
{\
    (r_h) = (Int32)(v_h);\
    (r_l) = (v_l);\
}/* END C__I64COPYU64() */

#define C__U64COPYI64(v_h, v_l, r_h, r_l)\
{\
    (r_h) = (UInt32)(v_h);\
    (r_l) = (v_l);\
}/* END C__U64COPYI64() */


/******************************************************************************
*
* MACRO:
*   C__I64COPYI32(v, r_h, r_l)
*   C__I64COPYU32(v, r_h, r_l)
*   C__U64COPYU32(v, r_h, r_l)
*   C__U64COPYI32(v, r_h, r_l)
*
* DESCRIPTION:
*   Copies a 32 bit value to a 64bit value
*
* PARAMETERS:
*   type    name    meaning
*  xInt32   v       input value
*
* RETURNS:
*  yInt32   r_h    upper 32bit of the result
*  UInt32   r_l    lower 32bit of the result
*
******************************************************************************/
#define C__I64COPYI32(v, r_h, r_l)\
{\
    (r_h) = ((v) < 0) ? (Int32)(-1) : (Int32)(0);\
    (r_l) = (UInt32)(v);\
}/* END C__I64COPYI32() */

#define C__I64COPYU32(v, r_h, r_l)\
{\
    (r_h) = 0;\
    (r_l) = (v);\
}/* END C__I64COPYU32() */

#define C__U64COPYU32(v, r_h, r_l)\
{\
    (r_h) = 0U;\
    (r_l) = (v);\
}/* END C__U64COPYU32() */

#define C__U64COPYI32(v, r_h, r_l)\
{\
    (r_h) = 0U;\
    (r_l) = (UInt32)(v);\
}/* END C__U64COPYI32() */


#endif /* #ifndef DSFXP_COPY_H */
