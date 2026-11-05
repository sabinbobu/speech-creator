/**
 * @file       $RCSfile: MUL64_14.c $
 * @brief      This file contains function for 64-bit multiplication.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.2 $ $Date: 2017/04/05 15:49:59CEST $
 */

#include "dsfxp.h"


/******************************************************************************
*
* FUNCTION:
*   void F__I64MULI32U16(Int32 f1, UInt16 f2, UInt32 *r_h, UInt32 *r_l)
*
* DESCRIPTION:
*   Multiplies f1 by f2 with 64bit result.
*
* PARAMETERS:
*   typ      name    meaning
*   Int32    f1      1. factor
*   UInt16   f2      2. factor
*   Int32    *r_h    64bit - result (high-part)
*   UInt32   *r_l    64bit - result (low-part)
*
* NOTE:
* f1               * f2 =
* (f1H*2^16 + f1L) * f2 =
* f1H*2^16*f2 + f1L*f2
*
* shifted by  64    48    32    16    0 Bits
* |-----|-----|-----|-----|-----|-----|
*                   |    f1H*f2 |     |
*                         |    f1L*f2 |
* |-----|-----|-----|-----|-----|-----|
*             |<   r_h   >|<   r_l   >|
*
*   Converts negative numbers with Booth-algorithm.
*
******************************************************************************/
void F__I64MULI32U16(Int32 f1, UInt16 f2, Int32 *r_h, UInt32 *r_l)
{

    C__I64MULI32U16(f1, f2, *r_h, *r_l);

}/*END F__I64MULI32U16()*/
