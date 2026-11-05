/**
 * @file       $RCSfile: tl_math.h $
 * @brief      This file definines prototype of hypot function for double and single precision.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2012, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2013/05/08 12:45:02CEST $
 */

/* Note:
 *   Calculates the hypotenuse.
 *   C__HYPOT(x, y);
 *   C__HYPOTF(x, y);
 */


#ifndef TL_MATH_H
#define TL_MATH_H

//#include <math.h>

/* hypot */
#define C__HYPOT(x, y)\
    sqrt( ((x)*(x)) + ((y)*(y)) )


/* hypotf */
#define C__HYPOTF(x, y)\
    sqrtf( ((x)*(x)) + ((y)*(y)) )

#endif /* #ifndef TL_MATH_H */
