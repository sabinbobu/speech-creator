/**
 * @file       $RCSfile: DIV64s05.c $
 * @brief      This file contains function F__U64sDIVU64sU32 for division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.12 $ $Date: 2017/06/07 11:14:13CEST $
 */

#include "dsfxp.h"


#ifdef LITTLE_ENDIAN    /* Target with little-endian architecture */

/* divide unsigned UInt64s by UInt32 */
UInt64s F__U64sDIVU64sU32(const UInt64s *U, UInt32 v)
{
    UInt64s quotQ;

    /* first, make sure v is not a short */
    if(v <= (UInt32)UINT16MAX)
    {
        quotQ = F__U64sDIVU64sU16(U, (UInt16)v);
    }
    else
    {
        UInt8 i = 0U;
        Int8 j;
        UInt16 q[4], d[5];
        UInt32 a, d0d3L, d0d3H;

        a = v;
        /* normalize the divisor */
        while ((a & 0x80000000UL) == 0UL)
        {
            a <<= 1U;
            i++;
        }

        /* and the dividend */
        d[4] = 0U;              /* initialization necessary if i=0 */
        if(i != 0U) /* avoid shift by 32 bits */
        {
            d[4] = (UInt16)(U->hi >> (32U - i));
        }
        d0d3H = U->hi << i;
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
        q[3] = 0U;
        for(j=2; j>-1; j--)
        {
            q[j] = div3by2(&d[j], a);
        }
        quotQ.lo = (UInt32)(((UInt32)q[1] << 16) + (UInt32)q[0]);
        quotQ.hi = (UInt32)(((UInt32)q[3] << 16) + (UInt32)q[2]);
    }
    return(quotQ);
}

#else                   /* Target with big-endian architecture */

/* divide unsigned UInt64s by UInt32 */
UInt64s F__U64sDIVU64sU32(const UInt64s *U, UInt32 v)
{
    UInt64s quotQ;

    /* first, make sure v is not a short */
    if(v <= (UInt32)UINT16MAX)
    {
        quotQ = F__U64sDIVU64sU16(U, (UInt16)v);
    }
    else
    {
        UInt8 i = 0U;
        Int8 j;
        UInt16 q[4], d[5];
        UInt32 a, d0d3L, d0d3H;

        a = v;
        /* normalize the divisor */
        while ((a & 0x80000000UL) == 0UL)
        {
            a <<= 1U;
            i++;
        }

        /* and the dividend */
        d[0] = 0U;              /* initialization necessary if i=0 */
        if(i != 0U) /* avoid shift by 32 bits */
        {
            d[0] = (UInt16)(U->hi >> (32U - i));
        }
        d0d3H = U->hi << i;
        if(i != 0U) /* avoid shift by 32 bits */
        {
            d0d3H += (U->lo >> (32U - i));
        }
        d0d3L = U->lo << i;

        d[1]   = (UInt16)((UInt32)(d0d3H) >> 16U);
        d[2]   = (UInt16)(d0d3H);
        d[3]   = (UInt16)((UInt32)(d0d3L) >> 16U);
        d[4]   = (UInt16)(d0d3L);

        /* start the division loop */
        q[0] = 0U;
        for(j=1; j<4; j++)
        {
            q[j] = div3by2(&d[j-1], a);
        }
        quotQ.hi = (UInt32)(((UInt32)q[0] << 16) + (UInt32)q[1]);
        quotQ.lo = (UInt32)(((UInt32)q[2] << 16) + (UInt32)q[3]);
    }
    return(quotQ);
}

#endif
