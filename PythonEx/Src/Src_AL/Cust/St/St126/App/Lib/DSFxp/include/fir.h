/**
 * @file       $RCSfile: fir.h $
 * @brief      This file contains macro definitions and function declarations for FIR filter calculations.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.19 $ $Date: 2017/04/06 09:26:24CEST $
 */

/* Note:
 *   The macro/function name represents the implemented operation:
 *     Syntax: (C__|F__) + <result type> + <OPERATION> + <accu width> [+ _SAT] + _ + <input type> + [CB] + <coefficients' type>
 *
 *   C macro names begin with "C__" and C function names begin with "F__".
 *   CB means a circular buffer is used.
 *
 * Macros:
 *   C__I8FIR8_I8I8()
 *   C__I8FIR8_SAT_I8I8()
 *   C__I16FIR16_I8I8()
 *   C__I16FIR16_SAT_I8I8()
 *   C__I32FIR32_SAT_I8I8()
 *   C__I32FIR32_I8I8()
 *   C__I64FIR64_I8I8()
 *   C__I64FIR64_SAT_I8I8()
 *   C__I16FIR16_I8I16()
 *   C__I16FIR16_I16I16()
 *   C__I16FIR16_SAT_I8I16()
 *   C__I16FIR16_SAT_I16I16()
 *   C__I32FIR32_I8I16()
 *   C__I32FIR32_I16I16()
 *   C__I32FIR32_SAT_I8I16()
 *   C__I32FIR32_SAT_I16I16()
 *   C__I64FIR64_I8I16()
 *   C__I64FIR64_I16I16()
 *   C__I64FIR64_SAT_I8I16()
 *   C__I64FIR64_SAT_I16I16()
 *   C__I32FIR32_I8I32()
 *   C__I32FIR32_I16I32()
 *   C__I32FIR32_I32I32()
 *   C__I32FIR32_SAT_I8I32()
 *   C__I32FIR32_SAT_I16I32()
 *   C__I32FIR32_SAT_I32I32()
 *   C__I64FIR64_I8I32()
 *   C__I64FIR64_I16I32()
 *   C__I64FIR64_I32I32()
 *   C__I64FIR64_SAT_I8I32()
 *   C__I64FIR64_SAT_I16I32()
 *   C__I64FIR64_SAT_I32I32()
 *   C__F32FIR32_F32F32()
 *   C__F64FIR64_F64F64()
 *
 *   C__U8FIR8_U8CBU8()
 *   C__U8FIR8_SAT_U8CBU8()
 *   C__U16FIR16_U8CBU8()
 *   C__U16FIR16_SAT_U8CBU8()
 *   C__U32FIR32_SAT_U8CBU8()
 *   C__U32FIR32_U8CBU8()
 *   C__U64FIR64_U8CBU8()
 *   C__U64FIR64_SAT_U8CBU8()
 *   C__U16FIR16_U8CBU16()
 *   C__U16FIR16_U16CBU16()
 *   C__U16FIR16_SAT_U8CBU16()
 *   C__U16FIR16_SAT_U16CBU16()
 *   C__U32FIR32_U8CBU16()
 *   C__U32FIR32_U16CBU16()
 *   C__U32FIR32_SAT_U8CBU16()
 *   C__U32FIR32_SAT_U16CBU16()
 *   C__U64FIR64_U8CBU16()
 *   C__U64FIR64_U16CBU16()
 *   C__U64FIR64_SAT_U8CBU16()
 *   C__U64FIR64_SAT_U16CBU16()
 *   C__U32FIR32_U8CBU32()
 *   C__U32FIR32_U16CBU32()
 *   C__U32FIR32_U32CBU32()
 *   C__U32FIR32_SAT_U8CBU32()
 *   C__U32FIR32_SAT_U16CBU32()
 *   C__U32FIR32_SAT_U32CBU32()
 *   C__U64FIR64_U8CBU32()
 *   C__U64FIR64_U16CBU32()
 *   C__U64FIR64_U32CBU32()
 *   C__U64FIR64_SAT_U8CBU32()
 *   C__U64FIR64_SAT_U16CBU32()
 *   C__U64FIR64_SAT_U32CBU32()
 *
 * Function declarations:
 *   F__I8FIR8_I8I8()
 *   F__I8FIR8_SAT_I8I8()
 *   F__I16FIR16_I8I8()
 *   F__I16FIR16_SAT_I8I8()
 *   F__I32FIR32_I8I8()
 *   F__I32FIR32_SAT_I8I8()
 *   F__I64FIR64_I8I8()
 *   F__I64FIR64_SAT_I8I8()
 *   F__I16FIR16_I8I16()
 *   F__I16FIR16_I16I16()
 *   F__I16FIR16_SAT_I8I16()
 *   F__I16FIR16_SAT_I16I16()
 *   F__I32FIR32_I8I16()
 *   F__I32FIR32_I16I16()
 *   F__I32FIR32_SAT_I8I16()
 *   F__I32FIR32_SAT_I16I16()
 *   F__I64FIR64_I8I16()
 *   F__I64FIR64_I16I16()
 *   F__I64FIR64_SAT_I8I16()
 *   F__I64FIR64_SAT_I16I16()
 *   F__I32FIR32_I8I32()
 *   F__I32FIR32_I16I32()
 *   F__I32FIR32_I32I32()
 *   F__I32FIR32_SAT_I8I32()
 *   F__I32FIR32_SAT_I16I32()
 *   F__I32FIR32_SAT_I32I32()
 *   F__I64FIR64_I8I32()
 *   F__I64FIR64_I16I32()
 *   F__I64FIR64_I32I32()
 *   F__I64FIR64_SAT_I8I32()
 *   F__I64FIR64_SAT_I16I32()
 *   F__I64FIR64_SAT_I32I32()
 *   F__U8FIR8_U8U8()
 *   F__U8FIR8_SAT_U8U8()
 *   F__U16FIR16_U8U8()
 *   F__U16FIR16_SAT_U8U8()
 *   F__U32FIR32_U8U8()
 *   F__U32FIR32_SAT_U8U8()
 *   F__U64FIR64_U8U8()
 *   F__U64FIR64_SAT_U8U8()
 *   F__U16FIR16_U8U16()
 *   F__U16FIR16_U16U16()
 *   F__U16FIR16_SAT_U8U16()
 *   F__U16FIR16_SAT_U16U16()
 *   F__U32FIR32_U8U16()
 *   F__U32FIR32_U16U16()
 *   F__U32FIR32_SAT_U8U16()
 *   F__U32FIR32_SAT_U16U16()
 *   F__U64FIR64_U8U16()
 *   F__U64FIR64_U16U16()
 *   F__U64FIR64_SAT_U8U16()
 *   F__U64FIR64_SAT_U16U16()
 *   F__U32FIR32_U8U32()
 *   F__U32FIR32_U16U32()
 *   F__U32FIR32_U32U32()
 *   F__U32FIR32_SAT_U8U32()
 *   F__U32FIR32_SAT_U16U32()
 *   F__U32FIR32_SAT_U32U32()
 *   F__U64FIR64_U8U32()
 *   F__U64FIR64_U16U32()
 *   F__U64FIR64_U32U32()
 *   F__U64FIR64_SAT_U8U32()
 *   F__U64FIR64_SAT_U16U32()
 *   F__U64FIR64_SAT_U32U32()
 *   F__F32FIR32_F32F32()
 *   F__F64FIR64_F64F64()
 *   F__I8FIR8_I8CBI8()
 *   F__I8FIR8_SAT_I8CBI8()
 *   F__I16FIR16_I8CBI8()
 *   F__I16FIR16_SAT_I8CBI8()
 *   F__I32FIR32_I8CBI8()
 *   F__I32FIR32_SAT_I8CBI8()
 *   F__I64FIR64_I8CBI8()
 *   F__I64FIR64_SAT_I8CBI8()
 *   F__I16FIR16_I8CBI16()
 *   F__I16FIR16_I16CBI16()
 *   F__I16FIR16_SAT_I8CBI16()
 *   F__I16FIR16_SAT_I16CBI16()
 *   F__I32FIR32_I8CBI16()
 *   F__I32FIR32_I16CBI16()
 *   F__I32FIR32_SAT_I8CBI16()
 *   F__I32FIR32_SAT_I16CBI16()
 *   F__I64FIR64_I8CBI16()
 *   F__I64FIR64_I16CBI16()
 *   F__I64FIR64_SAT_I8CBI16()
 *   F__I64FIR64_SAT_I16CBI16()
 *   F__I32FIR32_I8CBI32()
 *   F__I32FIR32_I16CBI32()
 *   F__I32FIR32_I32CBI32()
 *   F__I32FIR32_SAT_I8CBI32()
 *   F__I32FIR32_SAT_I16CBI32()
 *   F__I32FIR32_SAT_I32CBI32()
 *   F__I64FIR64_I8CBI32()
 *   F__I64FIR64_I16CBI32()
 *   F__I64FIR64_I32CBI32()
 *   F__I64FIR64_SAT_I8CBI32()
 *   F__I64FIR64_SAT_I16CBI32()
 *   F__I64FIR64_SAT_I32CBI32()
 *   F__U8FIR8_U8CBU8()
 *   F__U8FIR8_SAT_U8CBU8()
 *   F__U16FIR16_U8CBU8()
 *   F__U16FIR16_SAT_U8CBU8()
 *   F__U32FIR32_U8CBU8()
 *   F__U32FIR32_SAT_U8CBU8()
 *   F__U64FIR64_U8CBU8()
 *   F__U64FIR64_SAT_U8CBU8()
 *   F__U16FIR16_U8CBU16()
 *   F__U16FIR16_U16CBU16()
 *   F__U16FIR16_SAT_U8CBU16()
 *   F__U16FIR16_SAT_U16CBU16()
 *   F__U32FIR32_U8CBU16()
 *   F__U32FIR32_U16CBU16()
 *   F__U32FIR32_SAT_U8CBU16()
 *   F__U32FIR32_SAT_U16CBU16()
 *   F__U64FIR64_U8CBU16()
 *   F__U64FIR64_U16CBU16()
 *   F__U64FIR64_SAT_U8CBU16()
 *   F__U64FIR64_SAT_U16CBU16()
 *   F__U32FIR32_U8CBU32()
 *   F__U32FIR32_U16CBU32()
 *   F__U32FIR32_U32CBU32()
 *   F__U32FIR32_SAT_U8CBU32()
 *   F__U32FIR32_SAT_U16CBU32()
 *   F__U32FIR32_SAT_U32CBU32()
 *   F__U64FIR64_U8CBU32()
 *   F__U64FIR64_U16CBU32()
 *   F__U64FIR64_U32CBU32()
 *   F__U64FIR64_SAT_U8CBU32()
 *   F__U64FIR64_SAT_U16CBU32()
 *   F__U64FIR64_SAT_U32CBU32()
 *   F__F32FIR32_F32CBF32()
 *   F__F64FIR64_F64CBF64()
 */


#ifndef DSFXP_FIR_H
#define DSFXP_FIR_H


/******************************************************************************
 *
 * MACRO:
 *   C__I8FIR8_I8I8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int8    Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I8FIR8_I8I8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    Int8*    Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) +=(Int8)((Int16) *Aux_DelayLine * (Int16) *Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I8FIR8_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int8    Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I8FIR8_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    Int16    Mul;\
    Int8*    Aux_DelayLine;\
    Int8 const  *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    \
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = ((Int16)*Aux_DelayLine * (Int16)*Aux_Coeff) + (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu)  = C__I8SATI16_SATb(Mul,INT8MAX,INT8MIN);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_I8I8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_I8I8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    Int8*  Aux_DelayLine;\
    Int8 const  *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff    = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int16)*Aux_DelayLine * (Int16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    Int16    Mul;\
    Int16    Accu_1;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int16)*Aux_DelayLine * (Int16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + Mul;\
        \
        if(((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0))\
        {\
            (Accu) = INT16MAX;\
        }\
        else\
        {\
            if(((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0))\
            {\
                (Accu) = INT16MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    Int16    Mul;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    Int32    Accu_1;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int16)*Aux_DelayLine * (Int16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + (Int32)Mul;\
        \
        if(((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0))\
        {\
            (Accu) = INT32MAX;\
        }\
        else\
        {\
            if(((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0))\
            {\
                (Accu) = INT32MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I8I8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I8I8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += ((Int32)*Aux_DelayLine * (Int32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8I8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_I8I8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    UInt16   i;\
    Int16    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int16)*Aux_DelayLine * (Int16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32(Accu_h,Accu_l,(Int32)Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I8I8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    UInt16   i;\
    Int16    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int16)*Aux_DelayLine * (Int16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32_SAT(Accu_h, Accu_l, (Int32)(Mul), Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I16FIR16_I8I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_I8I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) +=(Int16)((Int32)*Aux_DelayLine * (Int32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I16FIR16_I16I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_I16I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int16)((Int32)*Aux_DelayLine * (Int32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I16FIR16_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__I16SATI32_SATb(Mul,INT16MAX,INT16MIN);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I16FIR16_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__I16SATI32_SATb(Mul,INT16MAX,INT16MIN);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_I8I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I8I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_I16I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I16I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    Int32     Accu_1;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + Mul;\
        \
        if ( ((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0) )\
        {\
            (Accu) = INT32MAX;\
        }\
        else\
        {\
            if ( ((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0) )\
            {\
                (Accu) = INT32MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int16*      Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    Int32     Accu_1;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + Mul;\
        \
        if(((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0))\
        {\
            (Accu) = INT32MAX;\
        }\
        else\
        {\
            if(((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0))\
            {\
                (Accu) = INT32MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_I8I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I16I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_I16I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/

#define C__I64FIR64_SAT_I8I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32_SAT(Accu_h, Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/

#define C__I64FIR64_SAT_I16I16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32_SAT(Accu_h, Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I8I32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I8I32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    Int32     Mul;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int32)(*Aux_DelayLine) * (*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_I16I32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I16I32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    Int32     Mul;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int32)(*Aux_DelayLine) * (*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_I32I32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I32I32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    Int32     Mul;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (*Aux_DelayLine) * (*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_SAT_I8I32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I8I32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul_h;\
    UInt32    Mul_l;\
    Int32     Accu_h;\
    UInt32    Accu_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__I64ADDI64I32(Mul_h, Mul_l, (Accu), Accu_h, Accu_l);\
        (Accu) = C__I32FITI64_SAT(Accu_h, Accu_l, INT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_SAT_I16I32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I16I32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul_h;\
    UInt32    Mul_l;\
    Int32     Accu_h;\
    UInt32    Accu_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__I64ADDI64I32(Mul_h, Mul_l, (Accu), Accu_h, Accu_l);\
        (Accu) = C__I32FITI64_SAT(Accu_h, Accu_l, INT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__I32FIR32_SAT_I32I32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I32I32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul_h;\
    UInt32    Mul_l;\
    Int32     Accu_h;\
    UInt32    Accu_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32(*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__I64ADDI64I32(Mul_h, Mul_l, (Accu), Accu_h, Accu_l);\
        (Accu) = C__I32FITI64_SAT(Accu_h, Accu_l, INT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_I8I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I16I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_I16I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I32I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_I32I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32(*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I8I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I8I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I16I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I16I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I32I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable (high word)
 *   UInt32  Accu_l     accumulation variable (low  word)
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I32I32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32(*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

#ifndef TL_NO_FLOATS
/******************************************************************************
 *
 * MACRO:
 *  C__F32FIR32_F32F32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type     name       meaning
 *   Float32  Input      current Input
 *   UInt16   NTabs      number of tabs
 *   Float32* DelayLine  address of DelayLine vector
 *   Float32* Coeff      address of Coefficients vector
 * RETURNS:
 *   Float32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__F32FIR32_F32F32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Float32*  Aux_DelayLine;\
    Float32 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0.0F;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += *(Aux_DelayLine) * *(Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}
#endif /* TL_NO_FLOATs */

#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)
/******************************************************************************
 *
 * MACRO:
 *  C__F64FIR64_F64F64(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type     name       meaning
 *   Float64  Input      current Input
 *   UInt16   NTabs      number of tabs
 *   Float64* DelayLine  address of DelayLine vector
 *   Float64* Coeff      address of Coefficients vector
 * RETURNS:
 *   Float64  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__F64FIR64_F64F64(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    Float64*  Aux_DelayLine;\
    Float64 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0.0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += *(Aux_DelayLine) * *(Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}
#endif /* TL_NO_FLOAT64 */

/******************************************************************************
 *
 * MACRO:
 *   C__I8FIR8_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int8    Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I8FIR8_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    Int8*    Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    \
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int8)((Int16) *Aux_DelayLine * (Int16) *Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I8FIR8_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int8    Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I8FIR8_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    Int16    Mul;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int16) *Aux_DelayLine * (Int16) *Aux_Coeff;\
        Mul += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__I8SATI16_SATb(Mul, INT8MAX, INT8MIN);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    \
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int16)*(Aux_DelayLine) * (Int16)*(Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    Int16    Mul;\
    Int16    Accu_1;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int16)*Aux_DelayLine * (Int16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + Mul;\
        \
        if ( ((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0) )\
        {\
            (Accu) = INT16MAX;\
        }\
        else\
        {\
            if ( ((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0) )\
            {\
                (Accu) = INT16MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    Int16    Mul;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    Int32    Accu_1;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    ((Accu)) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int16)*Aux_DelayLine * (Int16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + (Int32)Mul;\
        \
        if ( ((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0) )\
        {\
            ((Accu)) = INT32MAX;\
        }\
        else\
        {\
            if ( ((Accu) < 0) && (Mul < 0) && (Accu_1>= 0)  )\
            {\
                ((Accu)) = INT32MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += ((Int32)*Aux_DelayLine * (Int32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   Int32   Accu_h     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    UInt16   i;\
    Int16    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int16)*Aux_DelayLine * (Int16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32(Accu_h,Accu_l,(Int32)Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int8*   Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I8CBI8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int8*  Aux_DelayLine;\
    Int8 const *Aux_Coeff;\
    UInt16   i;\
    Int16    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int16)*Aux_DelayLine * (Int16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32_SAT(Accu_h, Accu_l, (Int32)(Mul), Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    \
    /* Accumulation */\
    (Accu) = 0;\
    \
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int16)((Int32)*Aux_DelayLine * (Int32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_SAT_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_SAT_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__I16SATI32_SATb(Mul,INT16MAX,INT16MIN);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int16)((Int32)*Aux_DelayLine * (Int32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I16FIR16_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int16   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I16FIR16_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    \
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__I16SATI32_SATb(Mul,INT16MAX,INT16MIN);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    Int32     Accu_1;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + Mul;\
        \
        if ( ((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0) )\
        {\
            (Accu) = INT32MAX;\
        }\
        else\
        {\
            if ( ((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0)  )\
            {\
                (Accu) = INT32MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int16       *Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    Int32     Accu_1;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Accu_1 = (Accu) + Mul;\
        \
        if ( ((Accu) >= 0) && (Mul >= 0) && (Accu_1 < 0) )\
        {\
            (Accu) = INT32MAX;\
        }\
        else\
        {\
            if ( ((Accu) < 0) && (Mul < 0) && (Accu_1 >= 0) )\
            {\
                (Accu) = INT32MIN;\
            }\
			else\
			{\
				(Accu) = Accu_1;\
			}\
        }\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I8CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32_SAT(Accu_h, Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int16*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I16CBI16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int16 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (Int32)*Aux_DelayLine * (Int32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I32_SAT(Accu_h, Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    Int32     Mul;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int32)(*Aux_DelayLine) * (*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    Int32     Mul;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (Int32)(*Aux_DelayLine) * (*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    Int32     Mul;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (*Aux_DelayLine) * (*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul_h;\
    UInt32    Mul_l;\
    Int32     Accu_h;\
    UInt32    Accu_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__I64ADDI64I32(Mul_h, Mul_l, (Accu), Accu_h, Accu_l);\
        (Accu) = C__I32FITI64_SAT(Accu_h, Accu_l, INT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul_h;\
    UInt32    Mul_l;\
    Int32     Accu_h;\
    UInt32    Accu_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__I64ADDI64I32(Mul_h, Mul_l, (Accu), Accu_h, Accu_l);\
        (Accu) = C__I32FITI64_SAT(Accu_h, Accu_l, INT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I32FIR32_SAT_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular and
 *   accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__I32FIR32_SAT_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32     Mul_h;\
    UInt32    Mul_l;\
    Int32     Accu_h;\
    UInt32    Accu_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32(*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__I64ADDI64I32(Mul_h, Mul_l, (Accu), Accu_h, Accu_l);\
        (Accu) = C__I32FITI64_SAT(Accu_h, Accu_l, INT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32(*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int8    Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int8*   DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I8CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int8*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I16CBI32(Input,NTabs,DelayLine,(Coeff),CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int16*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I16CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int16*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32((Int32)*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__I64FIR64_SAT_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and
 *   accumulation saturatoin
 *
 * PARAMETERS:
 *   type    name       meaning
 *   Int32   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   Int32*  DelayLine  address of DelayLine vector
 *   Int32*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__I64FIR64_SAT_I32CBI32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    Int32*   Aux_DelayLine;\
    Int32 const *Aux_Coeff;\
    UInt16    i;\
    Int32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__I64MULI32I32(*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__I64ADDI64I64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

#ifndef TL_NO_FLOATS
/******************************************************************************
 *
 * MACRO:
 *   C__F32FIR32_F32CBF32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type     name       meaning
 *   Float32  Input      current Input
 *   UInt16   NTabs      number of tabs
 *   Float32* DelayLine  address of DelayLine vector
 *   Float32* Coeff      address of Coefficients vector
 *   UInt16   CircCnt    state variable
 * RETURNS:
 *   Float32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__F32FIR32_F32CBF32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Float32*  Aux_DelayLine;\
    Float32 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0.0F;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) +=  *(Aux_DelayLine) * *(Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}
#endif /* TL_NO_FLOATs */

#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)
/******************************************************************************
 *
 * MACRO:
 *   C__F64FIR64_F64CBF64(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type     name       meaning
 *   Float64  Input      current Input
 *   UInt16   NTabs      number of tabs
 *   Float64* DelayLine  address of DelayLine vector
 *   Float64* Coeff      address of Coefficients vector
 *   UInt16   CircCnt    state variable
 * RETURNS:
 *   Float64  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__F64FIR64_F64CBF64(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    Float64*  Aux_DelayLine;\
    Float64 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0.0;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += *(Aux_DelayLine) * *(Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}
#endif /* TL_NO_FLOAT64 */

/******************************************************************************
 *
 * MACRO:
 *   C__U8FIR8_U8U8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt8   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U8FIR8_U8U8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    UInt8*    Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) +=(UInt8)((UInt16) *Aux_DelayLine * (UInt16) *Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U8FIR8_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt8   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U8FIR8_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    UInt16   Mul;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt16) *Aux_DelayLine * (UInt16) *Aux_Coeff;\
        Mul += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__U8FITU16_SAT(Mul,UINT8MAX);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U8U8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_U8U8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff    = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U8U8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    UInt16    Mul;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        if ( (Accu) < Mul )\
        {\
            (Accu) = UINT16MAX;\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    UInt16   Mul;\
    UInt8*   Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += (UInt32)Mul;\
        \
        if ( (Accu) < Mul )\
        {\
            (Accu) = UINT32MAX;\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U8U8(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U8U8(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16   i;\
    UInt8*   Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += ((UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U8U8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U8U8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    UInt16   i;\
    UInt16   Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (UInt16)*Aux_DelayLine * (UInt16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32(Accu_h,Accu_l,(UInt32)Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 * RETURNS:
 *   Int32   Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U8U8(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    UInt16   i;\
    UInt16   Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (UInt16)*Aux_DelayLine * (UInt16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32_SAT(Accu_h,Accu_l,(UInt32)Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U8U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_U8U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) +=(UInt16)((UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U16U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation.
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_U16U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) +=(UInt16)((UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_SAT_U8U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_SAT_U8U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        Mul  += (Accu);\
        (Accu)  = C__U16FITU32_SAT(Mul,UINT16MAX);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu)  = C__U16FITU32_SAT(Mul,UINT16MAX);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U8U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U8U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U16U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U16U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U8U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U8U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        \
        if ( (Accu) < Mul )\
        {\
            (Accu) = UINT32MAX;\
        }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        \
        if ( (Accu) < Mul )\
        {\
            (Accu) = UINT32MAX;\
            }\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U8U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U8U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U16U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U16U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U8U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U8U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32_SAT(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U16U16(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32_SAT(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *    C__U32FIR32_U8U32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U8U32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *    C__U32FIR32_U16U32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U16U32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     =  (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *    C__U32FIR32_U32U32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U32U32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U8U32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U8U32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, (UInt16)*Aux_DelayLine, Mul_h, Mul_l);\
        C__U64ADDU64U32(Mul_h, Mul_l, (Accu), Mul_h, Mul_l);\
        (Accu) = C__U32FITU64_SATu(Mul_h, Mul_l, UINT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *    C__U32FIR32_SAT_U16U32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U16U32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, *Aux_DelayLine, Mul_h, Mul_l);\
        C__U64ADDU64U32(Mul_h, Mul_l, (Accu), Mul_h, Mul_l);\
        (Accu) = C__U32FITU64_SATu(Mul_h, Mul_l, UINT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *    C__U32FIR32_SAT_U32U32(Input,NTabs,DelayLine,Coeff,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U32U32(Input,NTabs,DelayLine,Coeff,Accu)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U32(*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__U64ADDU64U32(Mul_h, Mul_l, (Accu), Mul_h, Mul_l);\
        (Accu) = C__U32FITU64_SATu(Mul_h, Mul_l, UINT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U8U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U8U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, (UInt16)*Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U16U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U16U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, *Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U32U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U32U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U32(*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U8U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U8U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, (UInt16)*Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U16U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U16U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, *Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U32U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U32U32(Input,NTabs,DelayLine,Coeff,Accu_h,Accu_l)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    Aux_DelayLine = (DelayLine);\
    Aux_Coeff     = (Coeff);\
    \
    /* Update */\
    for(i=0U;i<((NTabs)-1U);i++)\
    {\
        *Aux_DelayLine = *(Aux_DelayLine-1);\
        Aux_DelayLine--;\
    }\
    *Aux_DelayLine = (Input);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U32(*Aux_DelayLine,*Aux_Coeff,Mul_h,Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U8FIR8_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt8   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U8FIR8_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    UInt8*   Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine) + (UInt8)(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt8)((UInt16) *Aux_DelayLine * (UInt16) *Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U8FIR8_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt8   Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U8FIR8_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    UInt16   Mul;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine) + (UInt8)(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt16) *Aux_DelayLine * (UInt16) *Aux_Coeff;\
        Mul += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) = C__U8FITU16_SAT(Mul,UINT8MAX);\
        if(Aux_DelayLine > ((DelayLine) + (UInt8)((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt16)*(Aux_DelayLine) * (UInt16)*(Aux_Coeff);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + (UInt8)((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    UInt16   Mul;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        \
        if((Accu) < Mul)\
        {\
            (Accu) = UINT16MAX;\
        }\
        if(Aux_DelayLine > ((DelayLine) + (UInt8)((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    UInt32   Mul;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (UInt32)(UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) +=  Mul;\
        \
        if((Accu) < Mul)\
        {\
             (Accu) = UINT32MAX;\
        }\
        if(Aux_DelayLine > ((DelayLine) + (UInt8)((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16   i;\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    UInt16   i;\
    UInt16   Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (UInt16)*Aux_DelayLine * (UInt16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32(Accu_h,Accu_l,(UInt32)Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt8*  Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U8CBU8(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt8*  Aux_DelayLine;\
    UInt8 const *Aux_Coeff;\
    UInt16   i;\
    UInt16   Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul = (UInt16)*Aux_DelayLine * (UInt16) *Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32_SAT(Accu_h,Accu_l,(UInt32)Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt16)*Aux_DelayLine * (UInt16)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_SAT_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_SAT_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu)  = C__U16FITU32_SAT(Mul,UINT16MAX);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__U16FIR16_SAT_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt16  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U16FIR16_SAT_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Mul  += (Accu);\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu)  = C__U16FITU32_SAT(Mul,UINT16MAX);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__U32FIR32_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__U32FIR32_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__U32FIR32_SAT_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        \
        if((Accu) < Mul)\
        {\
            (Accu) = UINT32MAX;\
        }\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *  C__U32FIR32_SAT_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul  = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        (Accu) += Mul;\
        \
        if((Accu) < Mul)\
        {\
            (Accu) = UINT32MAX;\
        }\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    \
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U8CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32_SAT(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt16* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U16CBU16(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt16 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        Mul   = (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U32_SAT(Accu_h,Accu_l, Mul, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        (Accu) += (UInt32)*Aux_DelayLine * (UInt32)*Aux_Coeff;\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, (UInt16)*Aux_DelayLine, Mul_h, Mul_l);\
        C__U64ADDU64U32(Mul_h, Mul_l, (Accu), Mul_h, Mul_l);\
        (Accu) = C__U32FITU64_SATu(Mul_h, Mul_l, UINT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, *Aux_DelayLine, Mul_h, Mul_l);\
        C__U64ADDU64U32(Mul_h, Mul_l, (Accu), Mul_h, Mul_l);\
        (Accu) = C__U32FITU64_SATu(Mul_h, Mul_l, UINT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U32FIR32_SAT_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu       accumulation variable
 *
 ******************************************************************************/
#define C__U32FIR32_SAT_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32    Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    /* Accumulation */\
    (Accu) = 0U;\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U32(*Aux_DelayLine, *Aux_Coeff, Mul_h, Mul_l);\
        C__U64ADDU64U32(Mul_h, Mul_l, (Accu), Mul_h, Mul_l);\
        (Accu) = C__U32FITU64_SATu(Mul_h, Mul_l, UINT32MAX);\
        Aux_DelayLine++;Aux_Coeff++;\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16   i;\
    UInt32   Mul_h;\
    UInt32   Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, (UInt16)*Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, *Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U32(*Aux_DelayLine,*Aux_Coeff,Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt8   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt8*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U8CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt8*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, (UInt16)*Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt16   Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt16*  DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U16CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt16*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U16(*Aux_Coeff, *Aux_DelayLine, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}


/******************************************************************************
 *
 * MACRO:
 *   C__U64FIR64_SAT_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)
 *
 * DESCRIPTION:
 *   FIR - Filter calculation with circular buffer and accumulation saturation
 *
 * PARAMETERS:
 *   type    name       meaning
 *   UInt32  Input      current Input
 *   UInt16  NTabs      number of tabs
 *   UInt32* DelayLine  address of DelayLine vector
 *   UInt32* Coeff      address of Coefficients vector
 *   UInt16  CircCnt    state variable
 * RETURNS:
 *   UInt32  Accu_h     accumulation variable
 *   UInt32  Accu_l     accumulation variable
 *
 ******************************************************************************/
#define C__U64FIR64_SAT_U32CBU32(Input,NTabs,DelayLine,Coeff,CircCnt,Accu_h,Accu_l)\
{\
    UInt32*   Aux_DelayLine;\
    UInt32 const *Aux_Coeff;\
    UInt16    i;\
    UInt32   Mul_h;\
    UInt32    Mul_l;\
    \
    if((CircCnt)>0U) {(CircCnt)--;}\
    else          {(CircCnt) = (NTabs)-1U;}\
    \
    Aux_DelayLine = (DelayLine)+(CircCnt);\
    \
    /* Update  */\
    *Aux_DelayLine = (Input);\
    \
    /* Initiate */\
    Aux_Coeff = (Coeff);\
    \
    (Accu_h) = 0U;\
    (Accu_l) = 0U;\
    /* Accumulation */\
    for(i=0U;i<(NTabs);i++)\
    {\
        C__U64MULU32U32(*Aux_DelayLine,*Aux_Coeff, Mul_h, Mul_l);\
        Aux_DelayLine++;Aux_Coeff++;\
        C__U64ADDU64U64_SAT(Accu_h, Accu_l, Mul_h, Mul_l, Accu_h, Accu_l);\
        if(Aux_DelayLine > ((DelayLine) + ((NTabs)-1U))) {Aux_DelayLine = (DelayLine);}\
    }\
}

/*****************************************************************************
 *             FIR - Filter function declarations
 ******************************************************************************/

Int8  F__I8FIR8_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff);
Int8  F__I8FIR8_SAT_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff);
Int16 F__I16FIR16_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff);
Int16 F__I16FIR16_SAT_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff);
Int32 F__I32FIR32_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff);
Int32 F__I32FIR32_SAT_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff);
void  F__I64FIR64_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_SAT_I8I8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,Int32 *Result_h,UInt32 *Result_l);
Int16 F__I16FIR16_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff);
Int16 F__I16FIR16_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff);
Int16 F__I16FIR16_SAT_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff);
Int16 F__I16FIR16_SAT_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff);
Int32 F__I32FIR32_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff);
Int32 F__I32FIR32_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff);
Int32 F__I32FIR32_SAT_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff);
Int32 F__I32FIR32_SAT_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff);
void  F__I64FIR64_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_SAT_I8I16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_SAT_I16I16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,Int32 *Result_h,UInt32 *Result_l);
Int32 F__I32FIR32_I8I32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff);
Int32 F__I32FIR32_I16I32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff);
Int32 F__I32FIR32_I32I32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff);
Int32 F__I32FIR32_SAT_I8I32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff);
Int32 F__I32FIR32_SAT_I16I32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff);
Int32 F__I32FIR32_SAT_I32I32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff);
void  F__I64FIR64_I8I32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_I16I32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_I32I32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_SAT_I8I32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_SAT_I16I32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_SAT_I32I32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,Int32* Result_h,UInt32* Result_l);
UInt8  F__U8FIR8_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff);
UInt8  F__U8FIR8_SAT_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff);
UInt16 F__U16FIR16_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff);
UInt16 F__U16FIR16_SAT_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff);
UInt32 F__U32FIR32_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff);
UInt32 F__U32FIR32_SAT_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff);
void  F__U64FIR64_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_SAT_U8U8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt32 *Result_h,UInt32 *Result_l);
UInt16 F__U16FIR16_U8U16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff);
UInt16 F__U16FIR16_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff);
UInt16 F__U16FIR16_SAT_U8U16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff);
UInt16 F__U16FIR16_SAT_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff);
UInt32 F__U32FIR32_U8U16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff);
UInt32 F__U32FIR32_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff);
UInt32 F__U32FIR32_SAT_U8U16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff);
UInt32 F__U32FIR32_SAT_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff);
void  F__U64FIR64_U8U16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_SAT_U8U16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_SAT_U16U16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt32 *Result_h,UInt32 *Result_l);
UInt32 F__U32FIR32_U8U32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff);
UInt32 F__U32FIR32_U16U32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff);
UInt32 F__U32FIR32_U32U32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff);
UInt32 F__U32FIR32_SAT_U8U32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff);
UInt32 F__U32FIR32_SAT_U16U32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff);
UInt32 F__U32FIR32_SAT_U32U32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff);
void  F__U64FIR64_U8U32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_U16U32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_U32U32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_SAT_U8U32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_SAT_U16U32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_SAT_U32U32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt32* Result_h,UInt32* Result_l);
#ifndef TL_NO_FLOATS
Float32 F__F32FIR32_F32F32(Float32 Input,UInt16 NTabs,Float32* DelayLine,const Float32* Coeff);
#endif /* TL_NO_FLOATs */
#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)
Float64 F__F64FIR64_F64F64(Float64 Input,UInt16 NTabs,Float64* DelayLine,const Float64* Coeff);
#endif /* TL_NO_FLOAT64 */

/*   FIR - Filter Functions with Circular Buffer  */
Int8  F__I8FIR8_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16 *Counter);
Int8  F__I8FIR8_SAT_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16 *Counter);
Int16 F__I16FIR16_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16 *Counter);
Int16 F__I16FIR16_SAT_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_SAT_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16 *Counter);
void F__I64FIR64_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16* Counter,Int32 *Result_h,UInt32 *Result_l);
void F__I64FIR64_SAT_I8CBI8(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int8* Coeff,UInt16* Counter,Int32 *Result_h,UInt32 *Result_l);
Int16 F__I16FIR16_I8CBI16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int16 F__I16FIR16_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int16 F__I16FIR16_SAT_I8CBI16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int16 F__I16FIR16_SAT_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_I8CBI16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_SAT_I8CBI16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_SAT_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16 *Counter);
void  F__I64FIR64_I8CBI16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,UInt16 *Counter,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16 *Counter,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_SAT_I8CBI16(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int16* Coeff,UInt16 *Counter,Int32 *Result_h,UInt32 *Result_l);
void  F__I64FIR64_SAT_I16CBI16(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int16* Coeff,UInt16 *Counter,Int32 *Result_h,UInt32 *Result_l);
Int32 F__I32FIR32_I8CBI32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_I16CBI32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_I32CBI32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_SAT_I8CBI32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_SAT_I16CBI32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff,UInt16 *Counter);
Int32 F__I32FIR32_SAT_I32CBI32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,UInt16 *Counter);
void  F__I64FIR64_I8CBI32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,UInt16 *Counter,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_I16CBI32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff,UInt16 *Counter,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_I32CBI32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,UInt16 *Counter,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_SAT_I8CBI32(Int8 Input,UInt16 NTabs,Int8* DelayLine,const Int32* Coeff,UInt16 *Counter,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_SAT_I16CBI32(Int16 Input,UInt16 NTabs,Int16* DelayLine,const Int32* Coeff,UInt16 *Counter,Int32* Result_h,UInt32* Result_l);
void  F__I64FIR64_SAT_I32CBI32(Int32 Input,UInt16 NTabs,Int32* DelayLine,const Int32* Coeff,UInt16 *Counter,Int32* Result_h,UInt32* Result_l);
UInt8  F__U8FIR8_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter);
UInt8  F__U8FIR8_SAT_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter);
UInt16 F__U16FIR16_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter);
UInt16 F__U16FIR16_SAT_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_SAT_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter);
void F__U64FIR64_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter,UInt32 *Result_h,UInt32 *Result_l);
void F__U64FIR64_SAT_U8CBU8(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt8* Coeff,UInt16 *Counter,UInt32 *Result_h,UInt32 *Result_l);
UInt16 F__U16FIR16_U8CBU16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt16 F__U16FIR16_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt16 F__U16FIR16_SAT_U8CBU16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt16 F__U16FIR16_SAT_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_U8CBU16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_SAT_U8CBU16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_SAT_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16 *Counter);
void  F__U64FIR64_U8CBU16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt16 *Counter,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16 *Counter,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_SAT_U8CBU16(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt16* Coeff,UInt16 *Counter,UInt32 *Result_h,UInt32 *Result_l);
void  F__U64FIR64_SAT_U16CBU16(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt16* Coeff,UInt16 *Counter,UInt32 *Result_h,UInt32 *Result_l);
UInt32 F__U32FIR32_U8CBU32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_U16CBU32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_U32CBU32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_SAT_U8CBU32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_SAT_U16CBU32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt16 *Counter);
UInt32 F__U32FIR32_SAT_U32CBU32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt16 *Counter);
void  F__U64FIR64_U8CBU32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff,UInt16 *Counter,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_U16CBU32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt16 *Counter,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_U32CBU32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt16 *Counter,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_SAT_U8CBU32(UInt8 Input,UInt16 NTabs,UInt8* DelayLine,const UInt32* Coeff,UInt16 *Counter,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_SAT_U16CBU32(UInt16 Input,UInt16 NTabs,UInt16* DelayLine,const UInt32* Coeff,UInt16 *Counter,UInt32* Result_h,UInt32* Result_l);
void  F__U64FIR64_SAT_U32CBU32(UInt32 Input,UInt16 NTabs,UInt32* DelayLine,const UInt32* Coeff,UInt16 *Counter,UInt32* Result_h,UInt32* Result_l);
#ifndef TL_NO_FLOATS
Float32 F__F32FIR32_F32CBF32(Float32 Input,UInt16 NTabs,Float32* DelayLine,const Float32* Coeff,UInt16 *Counter);
#endif /* TL_NO_FLOATs */
#if !defined(TL_NO_FLOATS) && !defined(TL_NO_FLOAT64)
Float64 F__F64FIR64_F64CBF64(Float64 Input,UInt16 NTabs,Float64* DelayLine,const Float64* Coeff,UInt16 *Counter);
#endif /* TL_NO_FLOAT64 */

#endif /* #ifndef DSFXP_FIR_H */
