/**
 * @file       $RCSfile: sumprot.h $
 * @brief      This file contains several macro definitions for the addition and subtraction with 32bit values.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.12 $ $Date: 2017/05/31 16:13:15CEST $
 */

/* Note:
 * - C-macros are characterized by a leading "C__".
 *   Ansi-C-functions are characterized by a leading "F__".
 *
 * - The macro/function-name represents the implemented operation(s):
 *      (C__|F__) + output_type + OPERATION + input_type [+ input_type] + _PROT
 *
 *   C__U32ADDI32I32_PROT():   Addition of 32bit numbers
 *   C__U32ADDI32U32_PROT():   Addition of 32bit numbers
 *   C__I32ADDI32U32_PROT():   Addition of 32bit numbers
 *   C__U32SUBU32I32_PROT():   Substraction of 32bit numbers
 *   C__U32SUBI32I32_PROT():   Substraction of 32bit numbers
 *   C__I32SUBI32U32_PROT():   Substraction of 32bit numbers
 *   C__I32SUBU32I32_PROT():   Substraction of 32bit numbers
 *   C__I32SUBU32U32_PROT():   Substraction of 32bit numbers
 *
 *   C__U32ADDI16U32_PROT():   Addition of 32bit numbers
 *   C__I32ADDI16U32_PROT():   Addition of 32bit numbers
 *   C__U32SUBU32I16_PROT():   Substraction of 32bit numbers
 *   C__U32SUBI32I16_PROT():   Substraction of 32bit numbers
 *   C__I32SUBU32U16_PROT():   Substraction of 32bit numbers
 */


#ifndef  DSFXP_SUMPROT_H
#define  DSFXP_SUMPROT_H

#define C__U32ADDI32I32_PROT(s1, s2)\
(((s1) < 0)\
     ? ((UInt32)(s2) - (UInt32)(-(s1)))\
     : (((s2) < 0)\
           ? ((UInt32)(s1) - (UInt32)(-(s2)))\
           : ((UInt32)(s1) + (UInt32)(s2))))


#define C__U32ADDI32U32_PROT(s1, s2)\
(((s1) >= 0)\
     ? ((s2) + (UInt32)(s1))\
     : (((s1) == (Int32)INT32MIN)\
          ? ((s2) - (UInt32)INT32MAX - 1U)\
          : ((s2) - (UInt32)(-(s1)))))

#define C__U32ADDI16U32_PROT(s1, s2)\
(((s1) >= 0)\
     ? ((s2) + (UInt32)(s1))\
     : ((s2) - (UInt32)(-((Int32)(s1)))))


#define C__I32ADDI32U32_PROT(s1, s2)\
 (((s1) >= 0)\
      ? ((Int32)((s2) + (UInt32)(s1)))\
      : (((s1) == (Int32)INT32MIN)\
           ? ((Int32)((s2) - (UInt32)INT32MAX - 1U))\
           : ((Int32)((s2) - (UInt32)(-(s1))))))

#define C__I32ADDI16U32_PROT(s1, s2)\
 (((s1) >= 0)\
      ? ((Int32)((s2) + (UInt32)(s1)))\
      : ((Int32)((s2) - (UInt32)(-((Int32)(s1))))))


#define C__U32SUBU32I32_PROT(s1, s2)\
(((s2) >= 0)\
     ? ((s1) - (UInt32)(s2))\
     : (((s2) == (Int32)INT32MIN)\
          ? ((s1) + (UInt32)INT32MAX + 1U)\
          : ((s1) + (UInt32)(-(s2)))))

#define C__U32SUBU32I16_PROT(s1, s2)\
(((s2) >= 0)\
     ? ((s1) - (UInt32)(s2))\
     : ((s1) + (UInt32)(-((Int32)(s2)))))


#define C__U32SUBI32I32_PROT(s1, s2)\
((((s1) < 0) || ((s2) >= 0))\
     ? ((UInt32)(Int32)((s1) - (s2)))\
     : (((s2) == (Int32)INT32MIN)\
          ? ((UInt32)((UInt32)(s1) + (UInt32)INT32MAX + 1U))\
          : ((UInt32)(s1) + (UInt32)(-(s2)))))

#define C__U32SUBI32I16_PROT(s1, s2)\
((((s1) < 0) || ((s2) >= 0))\
     ? ((UInt32)(Int32)((s1) - (Int32)(s2)))\
     : ((UInt32)(s1) + (UInt32)(-((Int32)(s2)))))


#define C__I32SUBI32U32_PROT(s1, s2)\
(((s2) <= (UInt32)INT32MAX)\
     ? ((s1) - (Int32)(s2))\
     : (((Int32)((s2) - (UInt32)INT32MAX - 1U) == (s1))\
          ? (Int32)INT32MIN\
          : (-(Int32)((s2) - (UInt32)(s1)))))


#define C__I32SUBU32I32_PROT(s1, s2)\
(((s1) <= (UInt32)INT32MAX)\
     ? ((Int32)(s1) - (s2))\
     : ((Int32)((s1) - (UInt32)(s2))))


#define C__I32SUBU32U32_PROT(s1, s2)\
(((s1) >= (s2))\
     ? ((Int32)((s1) - (s2)))\
     : ((((s2) > (UInt32)INT32MAX) && (((s2) - (UInt32)INT32MAX - 1U) == (s1)))\
          ? (Int32)INT32MIN\
          : (-(Int32)((s2) - (s1)))))

#define C__I32SUBU32U16_PROT(s1, s2)\
(((s1) >= (s2))\
     ? ((Int32)((s1) - (s2)))\
     : (-(Int32)((s2) - (s1))))


#endif /* DSFXP_SUMPROT_H */
