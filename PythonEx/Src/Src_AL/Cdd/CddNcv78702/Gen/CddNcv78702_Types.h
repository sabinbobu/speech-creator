//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddNcv78702_Types.h
///
/// \brief Types specific description for NCV78702
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_TYPES_2021_03_26_H_
#define CDD_NCV78702_TYPES_2021_03_26_H_


//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>


//=============================================================================
// Defines
//=============================================================================
#define CDDNCV78702_BOOST_DIV3_DIV2_reserved  0u  // reserved values for driver 3
#define CDDNCV78702_BOOST_VLIMTH3_reserved    0u
#define CDDNCV78702_BOOST3_EN_reserved        0u
#define CDDNCV78702_P_DISTRIBUTION3_Reserved  0u

#define CDDNCV78702_BOOST_VSETPOINT_Init      1u  // init value
#define CDDNCV78702_BOOSTx_EN_Disable         0u  // init value

#define CDDNCV78702_ReadCmd  0x0000u // MSB (bit position 15) set to '0'
#define CDDNCV78702_WriteCmd 0x8000u // MSB (bit position 15) set to '1'

#define CDDNCV78702_ShiftReadAddr(x)  (uint16) (CDDNCV78702_ReadCmd  | (uint16) (x << 10u))
#define CDDNCV78702_ShiftWriteAddr(x) (uint16) (CDDNCV78702_WriteCmd | (uint16) (x << 11u))

#define CDDNCV78702_ReadReg0x00Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x00u)
#define CDDNCV78702_ReadReg0x01Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x01u)
#define CDDNCV78702_ReadReg0x02Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x02u)
#define CDDNCV78702_ReadReg0x03Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x03u)
#define CDDNCV78702_ReadReg0x04Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x04u)
#define CDDNCV78702_ReadReg0x05Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x05u)
#define CDDNCV78702_ReadReg0x06Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x06u)
#define CDDNCV78702_ReadReg0x07Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x07u)
#define CDDNCV78702_ReadReg0x08Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x08u)
#define CDDNCV78702_ReadReg0x09Addr  CDDNCV78702_ShiftReadAddr((uint16) 0x09u)
#define CDDNCV78702_ReadReg0x0AAddr  CDDNCV78702_ShiftReadAddr((uint16) 0x0Au)
#define CDDNCV78702_ReadReg0x0BAddr  CDDNCV78702_ShiftReadAddr((uint16) 0x0Bu)
#define CDDNCV78702_ReadReg0x0CAddr  CDDNCV78702_ShiftReadAddr((uint16) 0x0Cu)
#define CDDNCV78702_ReadReg0x0DAddr  CDDNCV78702_ShiftReadAddr((uint16) 0x0Du)

#define CDDNCV78702_WriteReg0x00Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x00u)
#define CDDNCV78702_WriteReg0x01Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x01u)
#define CDDNCV78702_WriteReg0x02Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x02u)
#define CDDNCV78702_WriteReg0x03Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x03u)
#define CDDNCV78702_WriteReg0x04Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x04u)
#define CDDNCV78702_WriteReg0x05Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x05u)
#define CDDNCV78702_WriteReg0x06Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x06u)
#define CDDNCV78702_WriteReg0x07Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x07u)
#define CDDNCV78702_WriteReg0x08Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x08u)
#define CDDNCV78702_WriteReg0x09Addr  CDDNCV78702_ShiftWriteAddr((uint16) 0x09u)
#define CDDNCV78702_WriteReg0x0AAddr  CDDNCV78702_ShiftWriteAddr((uint16) 0x0Au)
#define CDDNCV78702_WriteReg0x0BAddr  CDDNCV78702_ShiftWriteAddr((uint16) 0x0Bu)
#define CDDNCV78702_WriteReg0x0CAddr  CDDNCV78702_ShiftWriteAddr((uint16) 0x0Cu)
#define CDDNCV78702_WriteReg0x0DAddr  CDDNCV78702_ShiftWriteAddr((uint16) 0x0Du)


//=============================================================================
// Type definition for Configuration and control registers
//=============================================================================
#define LOW_BYTE_FIRST 1
#define CPU_BYTE_ORDER LOW_BYTE_FIRST
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)

// ADDR 0x00
typedef struct tCddNcv78702_Bit_Reg0x00
{
  uint16 biNOP     : 10 ;
  uint16 biUNUSED  : 6  ;
}tCddNcv78702_Bit_Reg0x00;

// ADDR 0x01
typedef struct tCddNcv78702_Bit_Reg0x01
{
  uint16 biBOOST_SKCL       : 2 ;
  uint16 biBOOST_OTA_GAIN   : 2 ;
  uint16 biVDRIVE_VSETPOINT : 4 ;
  uint16 biVBOOST_VGATE_THR : 1 ;
  uint16 biBOOST_DIV3_DIV2  : 1 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x01;

// ADDR 0x02
typedef struct tCddNcv78702_Bit_Reg0x02
{
  uint16 biBOOST_VLIMTH1  : 2 ;
  uint16 biBOOST_VLIMTH2  : 2 ;
  uint16 biBOOST_VLIMTH3  : 2 ;
  uint16 biBOOST_SLPCTRL  : 3 ;
  uint16 biZero           : 1 ;
  uint16 biUNUSED         : 6 ;
}tCddNcv78702_Bit_Reg0x02;

// ADDR 0x03
typedef struct tCddNcv78702_Bit_Reg0x03
{
  uint16 biBOOST_OVERVOLTSD_THR : 7 ;
  uint16 biBOOST_SRCINV         : 1 ;
  uint16 biBOOST_MULTI_PHASE_MD : 2 ;
  uint16 biUNUSED               : 6 ;
}tCddNcv78702_Bit_Reg0x03;


// ADDR 0x04
typedef struct tCddNcv78702_Bit_Reg0x04
{
  uint16 biBOOST_VSETPOINT  : 7 ;
  uint16 biFSO_BST_FREQ     : 3 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x04;

// ADDR 0x05
typedef struct tCddNcv78702_Bit_Reg0x05
{
  uint16 biBOOST1_EN        : 1 ;
  uint16 biBOOST2_EN        : 1 ;
  uint16 biBOOST3_EN        : 1 ;
  uint16 biFSO_MD           : 3 ;
  uint16 biADC_TEMP_THR     : 3 ;
  uint16 biTSD_AUT_RCVR_EN  : 1 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x05;

// ADDR 0x06
typedef struct tCddNcv78702_Bit_Reg0x06
{
  uint16 biVDD_ENA          : 1 ;
  uint16 biFSO_ENABLE_SEL   : 1 ;
  uint16 biVBOOST_TOFF_SET  : 3 ;
  uint16 biVBOOST_TON_SET   : 3 ;
  uint16 biBOOST_OV_REACT   : 2 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x06;

// ADDR 0x07
typedef struct tCddNcv78702_Bit_Reg0x07
{
  uint16 biP_DISTRIBUTION1  : 5 ;
  uint16 biP_DISTRIBUTION2  : 5 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x07;

// ADDR 0x08
typedef struct tCddNcv78702_Bit_Reg0x08
{
  uint16 biP_DISTRIBUTION3  : 5 ;
  uint16 biVDRIVE_UV_THR    : 3 ;
  uint16 biZero             : 2 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x08;

// ADDR 0x09
typedef struct tCddNcv78702_Bit_Reg0x09
{
  uint16 biOTP_OPERATION    : 2 ;
  uint16 biOTP_ADDR         : 3 ;
  uint16 biOTP_BIAS_L       : 1 ;
  uint16 biOTP_BIAS_H       : 1 ;
  uint16 biZero             : 3 ;
  uint16 biUNUSED           : 6 ;
}tCddNcv78702_Bit_Reg0x09;

//=============================================================================
// Type definition for status registers
//=============================================================================

// ADDR 0x0A...0x0D common READ frame bits
typedef struct tCddNcv78702_Bit_ReadFrame
{
  uint16 biData           : 10 ;
  uint16 biFSO            :  1 ;
  uint16 biTW             :  1 ;
  uint16 biTSD            :  1 ;
  uint16 biBOOSTFAIL      :  1 ;
  uint16 biTEMPOUT        :  1 ;
  uint16 biSPIERR         :  1 ;
}tCddNcv78702_Bit_ReadFrame;

// ADDR 0x0A
typedef struct tCddNcv78702_Bit_Reg0x0A
{
  uint16 biTW             : 1 ;
  uint16 biTSD            : 1 ;
  uint16 biSPIERR         : 1 ;
  uint16 biTEMP_OUT       : 1 ;
  uint16 biBOOST_OV       : 1 ;
  uint16 biBOOST1_STATUS  : 1 ;
  uint16 biBOOST2_STATUS  : 1 ;
  uint16 biBOOST3_STATUS  : 1 ;
  uint16 biODD_PARITY     : 1 ;
  uint16 biHWR            : 1 ;
  uint16 biUNUSED         : 6 ;
}tCddNcv78702_Bit_Reg0x0A;

// ADDR 0x0B
typedef struct tCddNcv78702_Bit_Reg0x0B
{
  uint16 biFSO            : 1 ;
  uint16 biOTP_FAIL       : 1 ;
  uint16 biOTP_ACTIVE     : 1 ;
  uint16 biVBSTDIV_UV     : 1 ;
  uint16 biVDRIVE_NOK     : 1 ;
  uint16 biENABLE1_STATUS : 1 ;
  uint16 biENABLE2_STATUS : 1 ;
  uint16 biENABLE3_STATUS : 1 ;
  uint16 biODD_PARITY     : 1 ;
  uint16 biZero           : 1 ;
  uint16 biUNUSED         : 6 ;
}tCddNcv78702_Bit_Reg0x0B;

// ADDR 0x0C
typedef struct tCddNcv78702_Bit_Reg0x0C
{
  uint16 biOTP_DATA : 10;
  uint16 biUNUSED   : 6 ;
}tCddNcv78702_Bit_Reg0x0C;

// ADDR 0x0D
typedef struct tCddNcv78702_Bit_Reg0x0D
{
  uint16 biREVID  : 8 ;
  uint16 biZero   : 2 ;
  uint16 biUNUSED : 6 ;
}tCddNcv78702_Bit_Reg0x0D;

#else
  #error CPU_BYTE_ORDER == HIGH_BYTE_FIRST not supported
#endif  //(CPU_BYTE_ORDER == LOW_BYTE_FIRST)

// R/W registers
typedef union tCddNcv78702_Reg0x00 { tCddNcv78702_Bit_Reg0x00 Bit; uint16 unRaw; } tCddNcv78702_Reg0x00;
typedef union tCddNcv78702_Reg0x01 { tCddNcv78702_Bit_Reg0x01 Bit; uint16 unRaw; } tCddNcv78702_Reg0x01;
typedef union tCddNcv78702_Reg0x02 { tCddNcv78702_Bit_Reg0x02 Bit; uint16 unRaw; } tCddNcv78702_Reg0x02;
typedef union tCddNcv78702_Reg0x03 { tCddNcv78702_Bit_Reg0x03 Bit; uint16 unRaw; } tCddNcv78702_Reg0x03;
typedef union tCddNcv78702_Reg0x04 { tCddNcv78702_Bit_Reg0x04 Bit; uint16 unRaw; } tCddNcv78702_Reg0x04;
typedef union tCddNcv78702_Reg0x05 { tCddNcv78702_Bit_Reg0x05 Bit; uint16 unRaw; } tCddNcv78702_Reg0x05;
typedef union tCddNcv78702_Reg0x06 { tCddNcv78702_Bit_Reg0x06 Bit; uint16 unRaw; } tCddNcv78702_Reg0x06;
typedef union tCddNcv78702_Reg0x07 { tCddNcv78702_Bit_Reg0x07 Bit; uint16 unRaw; } tCddNcv78702_Reg0x07;
typedef union tCddNcv78702_Reg0x08 { tCddNcv78702_Bit_Reg0x08 Bit; uint16 unRaw; } tCddNcv78702_Reg0x08;
typedef union tCddNcv78702_Reg0x09 { tCddNcv78702_Bit_Reg0x09 Bit; uint16 unRaw; } tCddNcv78702_Reg0x09;

// R registers
typedef union tCddNcv78702_Reg0x0A { tCddNcv78702_Bit_Reg0x0A Bit; tCddNcv78702_Bit_ReadFrame Frame; uint16 unRaw; } tCddNcv78702_Reg0x0A;
typedef union tCddNcv78702_Reg0x0B { tCddNcv78702_Bit_Reg0x0B Bit; tCddNcv78702_Bit_ReadFrame Frame; uint16 unRaw; } tCddNcv78702_Reg0x0B;
typedef union tCddNcv78702_Reg0x0C { tCddNcv78702_Bit_Reg0x0C Bit; tCddNcv78702_Bit_ReadFrame Frame; uint16 unRaw; } tCddNcv78702_Reg0x0C;
typedef union tCddNcv78702_Reg0x0D { tCddNcv78702_Bit_Reg0x0D Bit; tCddNcv78702_Bit_ReadFrame Frame; uint16 unRaw; } tCddNcv78702_Reg0x0D;


#endif // CDD_NCV78702_TYPES_2021_03_26_H_
