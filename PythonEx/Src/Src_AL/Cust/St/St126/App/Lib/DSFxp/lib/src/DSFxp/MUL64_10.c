/**
 * @file       $RCSfile: MUL64_10.c $
 * @brief      This file contains function for 64-bit multiplication.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2015, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.3 $ $Date: 2015/08/05 15:23:41CEST $
 */

#include "dsfxp.h"

/******************************************************************************
*
* FUNCTION:
*   void F__U64MULI64I32(Int32 f1_h, UInt32 f1_l, Int32 f2, UInt32 *r_h, UInt32 *r_l)
*
* DESCRIPTION:
*   Multiplies f1 by f2 with 64-bit result.
*
* PARAMETERS:
*   typ      name    meaning
*   Int32    f1_h    1. factor (high-part)
*   UInt32   f1_l    1. factor (low-part)
*   Int32    f2      2. factor
*   UInt32   *r_h    64bit - result (high-part)
*   UInt32   *r_l    64bit - result (low-part)
*
* NOTE:
* f1                                                 * f2 =
* (f1_h*2^32                 + f1_l)                 * f2 =
* ((f1_hH*2^16 + f1_hL)*2^32 + f1_lH*2^16 + f1_lL)   * (f2H*2^16 + f2L) =
* (f1_hH*2^48 + f1_hL*2^32   + f1_lH*2^16 + f1_lL)   * (f2H*2^16 + f2L) =
*
* f1_hH*f2H*2^64 + f1_hL*f2H*2^48 + f1_lH*f2H*2^32 + f1_lL*f2H*2^16 +
* f1_hH*f2L*2^48 + f1_hL*f2L*2^32 + f1_lH*f2L*2^16 + f1_lL*f2L
*
* shifted by  64    48    32    16    0 Bits
* |-----|-----|-----|-----|-----|-----|
* |  f1_hH*f2H|     |     |     |     |
*       |  f1_hL*f2H|     |     |     |
*             |  f1_lH*f2H|     |     |
*                   |  f1_lL*f2H|     |
*       |  f1_hH*f2L|     |     |     |
*             |  f1_hL*f2L|     |     |
*                   |  f1_lH*f2L|     |
*                         |  f1_lL*f2L|
* |-----|-----|-----|-----|-----|-----|
*             |<   r_h   >|<   r_l   >|
*
*   Converts negative numbers with Booth-algorithm.
*
******************************************************************************/
void F__U64MULI64I32(Int32 f1_h, UInt32 f1_l, Int32 f2, UInt32 *r_h, UInt32 *r_l)
{

    C__U64MULI64I32(f1_h, f1_l, f2, *r_h, *r_l);

}/*END F__U64MULI64I32()*/
