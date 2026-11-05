/**
 * @file       $RCSfile: DIV64s07.c $
 * @brief      This file contains function F__U32DIVU64sU32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.13 $ $Date: 2017/06/06 08:52:22CEST $
 */

#include "dsfxp.h"


#ifdef LITTLE_ENDIAN    /* Target with little-endian architecture */

/* divide unsigned UInt64s by UInt32 */
UInt32 F__U32DIVU64sU32(const UInt64s *U, UInt32 v)
{
    UInt32 quotQ;

    /* first, make sure v is not a short */
    if(v <= (UInt32)UINT16MAX)
    {
        quotQ = (F__U32DIVU64sU16(U, (UInt16)v));
    }
    else
    {
        UInt8 i = 0U;
        Int8 j;
        UInt16 q[2], d[4];
        UInt32 a, d0d3L, d0d3H;

        d0d3H = U->hi;
        /* check if denominator fits in numerator to avoid overflow */
        if ((UInt32)d0d3H >= (UInt32)v)
        {
            a = d0d3H / v;
            d0d3H -= a * v;
        }

        a = v;
        /* normalize the divisor */
        while ((a & 0x80000000UL) == 0UL)
        {
            a <<= 1U;
            i++;
        }

        /* and the dividend */
        d0d3H <<= i;
        if(i != 0U) /* avoid shift by 32 bits */
        {
            d0d3H += (U->lo >> (32U - i));
        }
        d0d3L = U->lo << i;

        d[3]   = (UInt16)((UInt32)(d0d3H) >> 16U);
        d[2]   = (UInt16)(d0d3H);
        d[1]   = (UInt16)((UInt32)(d0d3L) >> 16U);
        d[0]   = (UInt16)(d0d3L);

        /* start the division loop */
        for(j=1; j>-1; j--)
        {
            q[j] = div3by2(&d[j], a);
        }
        quotQ = (UInt32)(((UInt32)q[1] << 16) + (UInt32)q[0]);
    }
    return(quotQ);
}

#else   /* Target with big-endian architecture */

/* divide unsigned UInt64s by UInt32 */
UInt32 F__U32DIVU64sU32(const UInt64s *U, UInt32 v)
{
    UInt32 quotQ;

    /* first, make sure v is not a short */
    if(v <= (UInt32)UINT16MAX)
    {
        quotQ = (F__U32DIVU64sU16(U, (UInt16)v));
    }
    else
    {
        UInt8 i = 0U;
        Int8 j;
        UInt16 q[2], d[4];
        UInt32 a, d0d3L, d0d3H;

        d0d3H = U->hi;
        /* check if denominator fits in numerator to avoid overflow */
        if ((UInt32)d0d3H >= (UInt32)v)
        {
            a = d0d3H / v;
            d0d3H -= a * v;
        }

        a = v;
        /* normalize the divisor */
        while ((a & 0x80000000UL) == 0UL)
        {
            a <<= 1U;
            i++;
        }

        /* and the dividend */
        d0d3H <<= i;
        if(i != 0U) /* avoid shift by 32 bits */
        {
            d0d3H += (U->lo >> (32U - i));
        }
        d0d3L = U->lo << i;

        d[0]   = (UInt16)((UInt32)(d0d3H) >> 16U);
        d[1]   = (UInt16)(d0d3H);
        d[2]   = (UInt16)((UInt32)(d0d3L) >> 16U);
        d[3]   = (UInt16)(d0d3L);

        /* start the division loop */
        for(j=0; j<2; j++)
        {
            q[j] = div3by2(&d[j], a);
        }
        quotQ = (UInt32)(((UInt32)q[0] << 16) + (UInt32)q[1]);
    }
    return(quotQ);
}

#endif
