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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
//=============================================================================
// Typedef
//=============================================================================
typedef unsigned short                tun16Percent_1_328;

//=============================================================================
// Stub function declarations
//=============================================================================
void    IoHwAbUser_SetHss_Error       (boolean boSettingValue);
void    IoHwAbUser_SetHss_Sen         (boolean boSettingValue);
uint8   CDDVND7140_ECUVARCFG_aHSS_Type(uint8 ucIdx);
uint32  LPTMR0_GetTimeElapsed         (const uint32 ulStartValue);
void    IoHwAbUser_GetHss0Sense       (uint32* unDiagVal);
void    IoHwAbUser_GetHss1Sense       (uint32* unDiagVal);
void    IoHwAbUser_SetHss_En1         (tun16Percent_1_328 unTgtVal);
void    IoHwAbUser_SetHss_En2         (tun16Percent_1_328 unTgtVal);
uint16  Cod_HSS1Shor2GndThr           (void);
uint16  Cod_HSS1Shor2VbatThr          (void);
uint16  Cod_HSS1OpenLoadThr           (void);
uint16  Cod_HSS2Shor2GndThr           (void);
uint16  Cod_HSS2Shor2VbatThr          (void);
uint16  Cod_HSS2OpenLoadThr           (void);
uint16  Cod_HSS3Shor2GndThr           (void);
uint16  Cod_HSS3Shor2VbatThr          (void);
uint16  Cod_HSS3OpenLoadThr           (void);
boolean Cod_DiagValid                 (void);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern boolean                        IoHwAbUser_SetHss_Error_Param1;
extern boolean                        IoHwAbUser_SetHss_Sen_Param1;
extern uint32                         IoHwAbUser_GetHss0Sense_Param1;
extern uint32                         IoHwAbUser_GetHss1Sense_Param1;
extern uint8                          CDDVND7140_ECUVARCFG_aHSS_Type_Param1;
extern uint32                         LPTMR0_GetTimeElapsed_Param1;
extern tun16Percent_1_328             IoHwAbUser_SetHss_En1_Param1;
extern tun16Percent_1_328             IoHwAbUser_SetHss_En2_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint8                          CDDVND7140_ECUVARCFG_aHSS_Type_RetVal;
extern uint32                         LPTMR0_GetTimeElapsed_RetVal;
extern uint16                         Cod_HSS1Shor2GndThr_RetVal;
extern uint16                         Cod_HSS1Shor2VbatThr_RetVal;
extern uint16                         Cod_HSS1OpenLoadThr_RetVal;
extern uint16                         Cod_HSS2Shor2GndThr_RetVal;
extern uint16                         Cod_HSS2Shor2VbatThr_RetVal;
extern uint16                         Cod_HSS2OpenLoadThr_RetVal;
extern uint16                         Cod_HSS3Shor2GndThr_RetVal;
extern uint16                         Cod_HSS3Shor2VbatThr_RetVal;
extern uint16                         Cod_HSS3OpenLoadThr_RetVal;
extern boolean                        Cod_DiagValid_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8                          IoHwAbUser_SetHss_Error_HitCount;
extern uint8                          IoHwAbUser_SetHss_Sen_HitCount;
extern uint8                          CDDVND7140_ECUVARCFG_aHSS_Type_HitCount;
extern uint8                          LPTMR0_GetTimeElapsed_HitCount;
extern uint8                          IoHwAbUser_GetHss0Sense_HitCount;
extern uint8                          IoHwAbUser_GetHss1Sense_HitCount;
extern uint8                          IoHwAbUser_SetHss_En1_HitCount;
extern uint8                          IoHwAbUser_SetHss_En2_HitCount;
extern uint8                          Cod_HSS1Shor2GndThr_HitCount;
extern uint8                          Cod_HSS1Shor2VbatThr_HitCount;
extern uint8                          Cod_HSS1OpenLoadThr_HitCount;;
extern uint8                          Cod_HSS2Shor2GndThr_HitCount;
extern uint8                          Cod_HSS2Shor2VbatThr_HitCount;
extern uint8                          Cod_HSS2OpenLoadThr_HitCount;
extern uint8                          Cod_HSS3Shor2GndThr_HitCount;
extern uint8                          Cod_HSS3Shor2VbatThr_HitCount;
extern uint8                          Cod_HSS3OpenLoadThr_HitCount;
extern uint8                          Cod_DiagValid_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
