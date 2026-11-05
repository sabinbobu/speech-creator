/**
 * @file       $RCSfile: dsfxp.h $
 * @brief      This file contains include statements for all fixed-point header files.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2012, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.19 $ $Date: 2015/07/13 10:50:04CEST $
 */

/* Note:
 *  RELATED FILES:
 *    adv64.h
 *    cmp.h
 *    copy.h
 *    div.h
 *    fir.h
 *    fit.h
 *    mul.h
 *    neg.h
 *    sat.h
 *    shl.h
 *    shr.h
 *    sqrt.h
 *    sum.h
 *    sumprot.h
 *    trig.h
 *    tl_math.h
 *
 *    C-macros are characterized by a leading "C__".
 *    ANSI-C-functions are characterized by a leading "F__".
 *    The macro/function-name represents the implemented operation(s):
 *    (C__|F__) + output_type + OPERATION + input_type [+ input_type] [+ _SAT|_PROT]
 */


#ifndef DSFXP_H
#define DSFXP_H

// Patch AL: no floating point support
#define TL_NO_FLOATS

#ifdef VECU_CODE
   /* TL VECU Autosar */
   #ifdef TL_TYPES_DEFINED_IN_RTE_TYPE
      #include "Rte_Type.h"
   #else
      /* TL VECU Standard and SystemDesk */
      #include "tl_types.h"
   #endif
   #include "tllimits.h"
#else
   #ifndef RTE_TYPE_H
      #include "tl_types.h"
   #endif
   #include "tllimits.h"
#endif



#include "adv64.h"
#include "cmp.h"
#include "copy.h"
#include "div.h"
#include "fir.h"
#include "fit.h"
#include "mul.h"
#include "neg.h"
#include "sat.h"
#include "shl.h"
#include "shr.h"
#include "sqrt.h"
#include "sum.h"
#include "sumprot.h"
#include "trig.h"

#ifndef DSFXP_MATH_FREESTANDING_IMPLEMENTATION
 #include "tl_math.h"
#endif


#endif /* #ifndef DSFXP_H */
