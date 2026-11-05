/**
 * @file       $RCSfile: MUL64_09.c $
 * @brief      This file contains function for 64-bit multiplication.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.3 $ $Date: 2015/08/05 15:23:41CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   void F__I64MULU32U32(UInt32 f1, UInt32 f2, Int32 *r_h, UInt32 *r_l)
*
* DESCRIPTION:
*   Multiplies f1 by f2 with 64bit result.
*
* PARAMETERS:
*   type     name    meaning
*   UInt32   f1      1. factor
*   UInt32   f2      2. factor
*   Int32    *r_h    64bit - result (high-part)
*   UInt32   *r_l    64bit - result (low-part)
*
* NOTE:
* f1                          * f2 =
* (f1H*2^16 + f1L)            * (f2H*2^16 + f2L) =
* f1H*f2H*2^32 + f1H*f2L*2^16 + f1L*f2H*2^16 + f1L*f2L
*
* shifted by  64    48    32	16    0 Bits
* |-----|-----|-----|-----|-----|-----|
*             |    f1H*f2H|     |     |
*                   |    f1H*f2L|     |
*                   |    f1L*f2H|     |
*                         |    f1L*f2L|
* |-----|-----|-----|-----|-----|-----|
*             |<   r_h   >|<   r_l   >|
*
******************************************************************************/
void F__I64MULU32U32(UInt32 f1, UInt32 f2, Int32 *r_h, UInt32 *r_l)
{

    C__I64MULU32U32(f1, f2, *r_h, *r_l);

}/*END F__U64MULU32U32()*/


