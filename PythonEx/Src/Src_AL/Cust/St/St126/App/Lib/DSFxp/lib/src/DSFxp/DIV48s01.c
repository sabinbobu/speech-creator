/**
 * @file       $RCSfile: DIV48s01.c $
 * @brief      This file contains function div3by2 the main algorithm of division.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.7 $ $Date: 2017/06/02 11:43:51CEST $
 */

#include "dsfxp.h"


#ifdef LITTLE_ENDIAN    /* Target with little-endian architecture */

    /* divide three digits by two (used by multiword division) */
    UInt16 div3by2(UInt16 u[3], UInt32 v)
    {
        UInt32 q, ds_tmp32__;
        UInt16 vH, ds_tmp16__;
        UInt16 *p1 = (UInt16 *)&u[1];
        UInt16 *p0 = (UInt16 *)&u[0];
        UInt16 *p2 = (UInt16 *)&u[2];
        UInt32 tp1 = (UInt32)*p1 + ((UInt32)*p2 << 16U);

        /* get initial guess of q using high digit of v */
        vH = (UInt16)((UInt32)(v) >> 16U);
        q = tp1 / vH;
        q = (q < (UInt32)UINT16MAX) ? q : (UInt32)UINT16MAX;  /* min(q, UINT16MAX) */

        /* compute first remainder */
        tp1 -= q * vH;

        /* then second remainder */
        ds_tmp32__ = q * (UInt16)(v);
        ds_tmp16__ = u[0];
        u[0] -= (UInt16)(ds_tmp32__);
        if(u[0] > ds_tmp16__)
        {
            --tp1;
        }
        tp1 -= ((UInt32)(ds_tmp32__) >> 16U);

        *p2 = (UInt16)(tp1 >> 16U);
        *p1 = (UInt16)tp1;

        /* refine as needed */
        while((Int32)tp1 < 0)
        {
            --q;
            ds_tmp32__ = (UInt32)*p0 + ((UInt32)*p1 << 16U);
            ds_tmp32__ += v;
            *p1 = (UInt16)(ds_tmp32__ >> 16U);
            *p0 = (UInt16)ds_tmp32__;
            if(ds_tmp32__ < v)
            {
                ++u[2];
            }
            tp1 = (UInt32)*p1 + ((UInt32)*p2 << 16U);
        }
        *p1 = (UInt16)tp1;

        return((UInt16)q);
    }

#else                   /* Target with big-endian architecture */

    /* divide three digits by two (used by multiword division) */
    UInt16 div3by2(UInt16 u[3], UInt32 v)
    {
        UInt32 q, ds_tmp32__;
        UInt16 vH, ds_tmp16__;
        UInt16 *p1 = (UInt16 *)&u[0];
        UInt16 *p0 = (UInt16 *)&u[1];
        UInt16 *p2 = (UInt16 *)&u[2];
        UInt32 tp1 = (UInt32)*p0 + ((UInt32)*p1 << 16U);

        /* get initial guess of q using high digit of v */
        vH = (UInt16)((UInt32)(v) >> 16U);
        q = tp1 / vH;
        q = (q < (UInt32)UINT16MAX) ? q : (UInt32)UINT16MAX;  /* min(q, UINT16MAX) */

        /* compute first remainder */
        tp1 -= q * vH;

        /* then second remainder */
        ds_tmp32__ = q * (UInt16)(v);
        ds_tmp16__ = u[2];
        u[2] -= (UInt16)(ds_tmp32__);
        if(u[2] > ds_tmp16__)
        {
            --tp1;
        }
        tp1 -= ((UInt32)(ds_tmp32__) >> 16U);

        *p1 = (UInt16)(tp1 >> 16U);
        *p0 = (UInt16)tp1;

        /* refine as needed */
        while((Int32)tp1 < 0)
        {
            --q;
            ds_tmp32__ = (UInt32)*p2 + ((UInt32)*p0 << 16U);
            ds_tmp32__ += v;
            *p0 = (UInt16)(ds_tmp32__ >> 16U);
            *p2 = (UInt16)ds_tmp32__;
            if(ds_tmp32__ < v)
            {
                ++u[0];
            }
            tp1 = (UInt32)*p0 + ((UInt32)*p1 << 16U);
        }
        *p0 = (UInt16)tp1;

        return((UInt16)q);
    }

#endif
