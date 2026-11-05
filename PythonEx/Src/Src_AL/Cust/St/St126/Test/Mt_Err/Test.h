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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <Bsw/Err/ErrCust_Types.h>
#include <ErrCust_RteAccess.h>
#include <ErrCust_Cfg.h>

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================
#define ERRCUST_STATUS_CONFIRMED_DTC                    (uint8)0x08u
#define ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE           (uint8)0x02u
#define ERRCUST_MIN_AGE                                 0u
#define ERRCUST_FREEZE_FRAME_DATA_ENTRIES               10u
#define ERRCUST_MAX_AGE                                 ERRCUST_FREEZE_FRAME_DATA_ENTRIES
#define ERRCUST_DTC_AVAILABLE_FOR_FFD                   0xFFu
#define ERRCUST_YOUNGEST_AGE_FFD                        1u
#define ERRCUST_01_VOLTAGE_REZOLUTION                   100u 
#define ERRCUST_MAX_ACCEPTED_VOLTAGE_V                  255u
#define ERRCUST_MAX_ACCEPTED_VOLTAGE_MV                 ERRCUST_MAX_ACCEPTED_VOLTAGE_V * ERRCUST_01_VOLTAGE_REZOLUTION
#define ERRCUST_ALL_GROUP_OF_DTCS                       0xFFFFFFu
#define ERRCUST_GRP_P                                   (uint32)0x000000
#define ERRCUST_MPU_ACCESS_FAULT_HOOK_ACTIVATION        20212022u
#define DEM_STATUS_TEST_FAILED                          0x0001u
#define ERRCUST_DTC_AGING_COUNTER_MAX                   40u
#define ERRCUST_STATUS_TEST_PASSED                      (uint8)0x80u
#define ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE    (uint8)0x40u
#define ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR   (uint8)0x10u
#define ERRCUST_STATUS_TEST_FAILED                      (uint8)0x01u
#define ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR          (uint8)0x20u

//=============================================================================
// Module global variables
//=============================================================================
extern uint8                                  ErrCust_ucDtcIndex;
extern uint8                                  ErrCust_aucStatus[];
extern boolean                                ErrCust_boLeft;
extern boolean                                ErrCust_boNvmDirtyErrCust;
extern uint8                                  ErrCust_aPsRefList[];
extern boolean                                ErrCust_boNvmDirtyFreezeFrameData;
extern uint32                                 ErrCust_ulMPU_Trigger_Fault_Hook;
extern tsErrCust_PsDtcs                       ErrCust_aPsDtcs[3];


boolean                                       boCodingReady;
boolean                                       ErrCust_boCodingValidity;
//=============================================================================
// Module function declarations
//=============================================================================
extern uint32                          ErrCust_ConvertValueSint2Int(sint32 slInValue, uint8 ucbitLength);
extern void                            ErrCust_RteAccess_Read_CtrlStp_ActStatStp(tsErrCust_TypesActStatStp *psActStatStp);
extern void                            ErrCust_CaptureAftermarketAttitudeEcuData(tsErrCust_AftermarketAttitudeEcuData* psOutputData);
extern void                            ErrCust_CaptureAftermarketLvlEcuData(tsErrCust_AftermarketLvlEcuData* psOutputData);
extern void                            ErrCust_CaptureAftermarketContextEcuData(tsErrCust_AftermarketContextEcuData* psOutputData);
extern void                            ErrCust_CaptureFreezeFrameData(uint8 ucPsError);
extern sint32                          ErrCust_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength);
extern void                            ErrCust_ResetDtcIndex(void);
extern uint8                           ErrCust_GetStatusOfDtc(uint8 ucDtcIndex);
extern void                            ErrCust_Init(void);
extern void                            ErrCust_ErrHandling(uint16 unAlecId, uint8 ucAlecStatus);
extern teErrCust_Types_Clear           ErrCust_ucGetClearMemoryType(uint32 ulDtcCode);
extern boolean                         ErrCust_ClearMemory(uint8* pucDtcCode);
extern uint8                           ErrCust_ucGetStatusOfDTC(uint8 ucDtcIndex);
extern void                            ErrCust_SetAvailableDtc(uint8* pucBuf, uint8 ucDTCStatusMask);
extern uint8                           ErrCust_ucGetErrorCount(uint8 ucDTCStatusMask);
extern void                            ErrCust_ClearAllErrCustAndDemEventIds(void);
extern void                            ErrCust_ClearFreezeFrameData(uint8 ucFreezeFrameIdx);
extern void                            ErrCust_Cycle0(void);
extern uint32                          ErrCust_ulGetDtcCode(uint8 ucDtcIndex);
extern uint8                           ErrCust_GetActualErrorIndex(uint16 unAlecId);
extern void                            ErrCust_MapDtc(teErrCust_IxPsError* peRefList);
extern Std_ReturnType                  (*ErrCust_apfnReadTgtBinningClass_sVal_List[ERRCUST_NO_OF_LED_CHANNELS]) (tsRte_Binning0* psTgtBinningVal);
extern uint8                           ErrCust_GetNTCBinningErrorPerChannel(uint8_fast ucIdx, tsErrCust_RbinFailLightFunc sRBINNTCFail);
extern Std_ReturnType                  ErrCust_ReadTgtBinningVal(uint8_fast ucIdx, tsRte_Binning0* sTgtBinningVal);
extern uint8                           ErrCust_Get_BinningClass(uint8_fast ucIdx);
extern Std_ReturnType                  ErrCust_ReadNtcVal(tsRte_NTCTemperature* sNtcVal);
extern uint8                           ErrCust_Get_NTC(uint8_fast ucIdx);
extern boolean                         ErrCust_CodingDataValidation(void);
extern boolean                         ErrCust_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);

/*ctaaErrCust.c*/
extern void                            riErrCust_Init();
extern void                            rpErrCust_Cycle0();

/*ErrCust_RteAccess.c*/
extern void                            ErrCust_RteAccess_Read_FctR_TI_FctErrState(boolean *boErrCust_RteAccess_Lgt_TI_State);
extern void                            ErrCust_RteAccess_Read_FctR_LgtFctErrState(tsErrCust_LgtFctState *psErrCust_RteAccess_LgtFctState);
extern void                            ErrCust_RteAccess_Read_FctR_LgtFctStatus(tsErrCust_LgtFctStatus *psErrCust_RteAccess_LgtFctStatus);
extern void                            ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(teErrCust_Types_MountingSide *peEcuSide);


//=============================================================================
// Module function parameter stubs
//=============================================================================
sint32                                 ErrCust_ConvertValueSint2Int_Param1;
uint8                                  ErrCust_ConvertValueSint2Int_Param2;
sint32                                 ErrCust_ConvertValueInt2Sint_Param1;
uint8                                  ErrCust_ConvertValueInt2Sint_Param2;
uint8                                  ErrCust_GetStatusOfDtc_Param1;
uint8                                  ErrCust_ResetDtcIndex_Param1;
uint32                                 ErrCust_ucGetClearMemoryType_Param1;
uint8                                  ErrCust_ClearMemory_Param1[3];
uint8                                  ErrCust_ClearFreezeFrameData_Param1;
uint8                                  ErrCust_CaptureFreezeFrameData_Param1;
tsErrCust_AftermarketAttitudeEcuData   ErrCust_CaptureAftermarketAttitudeEcuData_Param1;
tsErrCust_AftermarketLvlEcuData        ErrCust_CaptureAftermarketLvlEcuData_Param1;
tsErrCust_AftermarketContextEcuData    ErrCust_CaptureAftermarketContextEcuData_Param1;
uint16                                 ErrCust_ErrHandling_Param1;
uint8                                  ErrCust_ErrHandling_Param2;
uint8                                  ErrCust_ucGetStatusOfDTC_Param1;
uint8                                  ErrCust_SetAvailableDtc_Param1[3];
uint8                                  ErrCust_SetAvailableDtc_Param2;
uint8                                  ErrCust_ucGetErrorCount_Param1;
uint8                                  ErrCust_ulGetDtcCode_Param1;
uint16                                 ErrCust_GetActualErrorIndex_Param1;
teErrCust_IxPsError                    ErrCust_MapDtc_Param1[250];
uint8_fast                             ErrCust_GetNTCBinningErrorPerChannel_Param1;
tsErrCust_RbinFailLightFunc            ErrCust_GetNTCBinningErrorPerChannel_Param2;
uint8                                  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[100];
uint8                                  ErrCust_ReadTgtBinningVal_Param1;
tsRte_Binning0*                        ErrCust_ReadTgtBinningVal_Param2;
uint8                                  ErrCust_Get_BinningClass_Param1;
tsRte_NTCTemperature                   ErrCust_ReadNtcVal_Param1;
uint8                                  ErrCust_Get_NTC_Param1;
tParaFct0_Cmd                          ErrCust_Data_ParaFct0_Param1;
tNvmPara_CodingArea                    ErrCust_Data_ParaFct0_Param2;

//ErrCust_RteAccess
boolean                                ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1;
tsErrCust_LgtFctState                  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1;
tsErrCust_LgtFctStatus                 ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1;
teErrCust_Types_MountingSide           ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1;
tsErrCust_TypesActStatStp              ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
uint32                                 ErrCust_ConvertValueSint2Int_RetVal;
sint32                                 ErrCust_ConvertValueInt2Sint_RetVal;
uint8                                  ErrCust_GetStatusOfDtc_RetVal;
teErrCust_Types_Clear                  ErrCust_ucGetClearMemoryType_RetVal;
boolean                                ErrCust_ClearMemory_RetVal;
uint8                                  ErrCust_ucGetStatusOfDTC_RetVal;
uint8                                  ErrCust_ucGetErrorCount_RetVal;
uint8                                  ErrCust_ulGetDtcCode_RetVal;
uint8                                  ErrCust_GetActualErrorIndex_RetVal;
uint8                                  ErrCust_GetNTCBinningErrorPerChannel_RetVal;
Std_ReturnType                         ErrCust_ReadTgtBinningVal_RetVal;
uint8                                  ErrCust_Get_BinningClass_RetVal;
Std_ReturnType                         ErrCust_ReadNtcVal_RetVal;
uint8                                  ErrCust_Get_NTC_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_02_RetVal;
boolean                                ErrCust_CodingDataValidation_RetVal;
boolean                                ErrCust_Data_ParaFct0_RetVal;


#endif // TEST_2023_08_25_H_
