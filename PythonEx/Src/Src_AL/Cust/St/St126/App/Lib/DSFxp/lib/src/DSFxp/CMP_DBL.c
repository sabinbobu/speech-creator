/**
 * @file       $RCSfile: CMP_DBL.c $
 * @brief      This file contains function F__EQDBL for compare Float64.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.8 $ $Date: 2017/05/26 09:13:28CEST $
 */

#include "dsfxp.h"


#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)
#include "float.h"
#ifndef DBL_EPSILON
/* definition of DBL_EPSILON, if not defined in compiler float.h */
#define DBL_EPSILON 1e-9
#endif
#ifndef DBL_MIN
/* definition of DBL_MIN, if not defined in compiler float.h */
#define DBL_MIN 1e-37
#endif

Int8 F__EQDBL(Float64 v1, Float64 v2)
{
    Int8 retval;
    const Float64 approxEps = (DBL_MIN + DBL_EPSILON) * 0.5;

    if (((v1 < -approxEps) && (v2 > approxEps)) || ((v1 > approxEps) && (v2 < -approxEps)))
    {
        /* with different sign is v1 != v2; the relative error is 2 */
        retval = (Int8)0;
    }
    else
    {
        Float64 diff, v1_pos, v2_pos;

        if (v1 > v2)
        {
            diff = v1 - v2;
        }
        else
        {
            diff = v2 - v1;
        }
        if (v1 < 0.0)
        {
            v1_pos = -v1;
        }
        else
        {
            v1_pos = v1;
        }
        if (v2 < 0.0)
        {
            v2_pos = -v2;
        }
        else
        {
            v2_pos = v2;
        }

        if ((v1_pos <= approxEps) && (v2_pos <= approxEps))
        {
            retval = (Int8)1;
        }
        else
        {
            if ((FLOAT64MAX - v1_pos) < v2_pos)
            {
                /* prevent overflow of v1_pos + v2_pos */
                diff = diff / FLOAT64MAX;
            }
            else
            {
                diff = diff / (v1_pos + v2_pos);
            }
            if (diff <= (DBL_EPSILON * 0.5))
            {
                retval = (Int8)1;
            }
            else
            {
                retval = (Int8)0;
            }
        }
    }
    return(retval);
}
#endif /* TL_NO_FLOAT64 */
