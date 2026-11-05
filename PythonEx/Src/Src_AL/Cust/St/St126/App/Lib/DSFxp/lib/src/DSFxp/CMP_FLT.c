/**
 * @file       $RCSfile: CMP_FLT.c $
 * @brief      This file contains function F__EQFLT for compare Float32.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.9 $ $Date: 2017/05/26 09:13:28CEST $
 */

#include "dsfxp.h"


#ifndef TL_NO_FLOATS
#include "float.h"
#ifndef FLT_EPSILON
/* definition of FLT_EPSILON, if not defined in compiler float.h */
#define FLT_EPSILON 1e-5f
#endif
#ifndef FLT_MIN
/* definition of FLT_MIN, if not defined in compiler float.h */
#define FLT_MIN 1e-37f
#endif

Int8 F__EQFLT(Float32 v1, Float32 v2)
{
    Int8 retval;
    const Float32 approxEps = (FLT_MIN + FLT_EPSILON) * 0.5f;

    if (((v1 < -approxEps) && (v2 > approxEps)) || ((v1 > approxEps) && (v2 < -approxEps)))
    {
        /* with different sign is v1 != v2; the relative error is 2 */
        retval = (Int8)0;
    }
    else
    {
        Float32 diff, v1_pos, v2_pos;

        if (v1 > v2)
        {
            diff = v1 - v2;
        }
        else
        {
            diff = v2 - v1;
        }
        if (v1 < 0.0f)
        {
            v1_pos = -v1;
        }
        else
        {
            v1_pos = v1;
        }
        if (v2 < 0.0f)
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
            if ((FLOAT32MAX - v1_pos) < v2_pos)
            {
                /* prevent overflow of v1_pos + v2_pos */
                diff = diff / FLOAT32MAX;
            }
            else
            {
                diff = diff / (v1_pos + v2_pos);
            }
            if (diff <= (FLT_EPSILON * 0.5f))
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
#endif /* TL_NO_FLOATS */
