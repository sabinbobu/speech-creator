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
#include <AL_Helper.h>

// Headers of the Module
#include <ctaaCtrlLed.h>
#include <CtrlLed.h>
#include <CtrlLed_Data.h>
#include <CtrlLed_Diag.h>
#include <CtrlLed_Rte.h>
#include <CtrlLed_Types.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//CtrlLed.c
#define CTRLLED_SCALING_65535       0xFFFFU
#define CTRLLED_SCALING_32768       0x8000U
#define CTRLLED_SCALING_1000        0x03E8U
#define CTRLLED_SCALING_10000       0x2710U
#define CTRLLED_SCALING_200         0x00C8U
#define CTRLLED_CHANNEL_OFF         0U

//CtrlLed_Data.c
#define CTRLLED_SET_DTC             1U
#define CTRLLED_RESETSET_DTC        2U
#define CTRLLED_NO_DTC_ACTION       3U

//=============================================================================
// Module global variables
//=============================================================================

//CtrlLed.c
extern tsCtrlled_CodingData        CtrlLed_sCodingData;
extern boolean                     CtrlLed_boCodMap_OK;
extern tsCtrlled_InternalHandlings CtrlLed_sInternalHandling;
extern uint8                       CtrlLed_ucCntFbit;

//CtrlLed_Data.c
extern tNvmPara_CodingArea*  CtrlLed_pCodingArea;
extern uint8 ucUnitGroupCnt;

//CtrlLed_Diag.c
extern tsCtrlLed_DtcChList      asDTC_List[];
extern tsCtrlLed_ReactionChList asReaction_List[];
extern tsCtrlLed_DtcMtxHbLbList asMtx_DTC_List[];
extern uint8                    asReactionPxl_List[];

//=============================================================================
// Module function declarations
//=============================================================================

// CtrlLed.c
extern void     CtrlLed_Buck_Handling(void);
extern void     CtrlLed_FindBuckId(uint8_fast ucIdx, uint16 *punInput, uint8 *pucBuckNumber, uint8 *pucBuckId);
extern uint16   CtrlLed_CalcRamp  (CONST_AL uint8_fast ucIdx, CONST_AL uint16 unTgtIntensity, CONST_AL uint16 unTgtRampMs);
extern uint16   CtrlLed_GammaCurve(uint16 unIntensity, CONST_AL uint16 *punGammaY);
extern uint16   CtrlLed_DoRampInterpolation(uint32 ulCurrentTime, uint16 unStartPoint_Ms, uint16 unTgtPoint_Ms, uint16 unStartPoint_Int, uint16 unTgtPoint_Int);
extern void     CtrlLed_Matrix_Handling(void);
extern void     CtrlLed_CheckLight(uint8_fast ucIdx, uint8 ucIll, uint8 ucLmmPxl, uint16 *punDutyInt);
extern uint16   CtrlLed_Handle_MatrixCh(CONST_AL uint8_fast ucIdxIl, uint16 unTgtInt);
extern teCtrlLed_MatrixVoltCnd CtrlLed_MatrixVoltCond(uint8 ucVoltRange);
extern uint8    CtrlLed_CountSetBucks(uint16 unVal);
extern void     CtrlLed_GetBuckId(uint16 unVal, uint8 unMaxBuck, uint8* pucData);
extern uint16   CtrlLed_Handle_NonMatrixCh(uint8_fast ucIdx, uint8_fast ucIdxIl, uint16 unTgtInt, uint16 unTgtRamp);
extern uint16   CtrlLed_DutyCalculation(CONST_AL uint8_fast ucIdx, CONST_AL uint8_fast ucIdxIl);
extern uint16   CtrlLed_CurrentCalculation(CONST_AL uint8_fast ucIdx);
extern uint16   CtrlLed_CalculateGamma(uint16 unIntensity, uint8 ucIll);

//CtrlLed_Data.c
extern boolean  CtrlLed_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern boolean  CtrlLed_Data_DriverMap(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
extern boolean  CtrlLed_Data_Matrix(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
extern boolean  CtrlLed_Data_Get_UnitGroup(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
extern void     CtrlLed_Data_Process_MultiUnits(uint8 ucDrvIdIdx, uint8_fast ucIdxLu, tsCtrlled_CodingData *psCodingData);
extern void     CtrlLed_Data_Process_SingleUnits(uint8 *pucData, uint8 ucDrvIdIdx, uint8_fast ucIdxLu, tsCtrlled_CodingData *psCodingData);
extern boolean  CtrlLed_Data_Led1(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
extern boolean  CtrlLed_Data_LmmX(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
extern boolean  CtrlLed_Data_AnimaMap(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
extern boolean(*CtrlLed_Data_apfnDataMap_List[]) (CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData* psCodingData);

// CtrlLed_Diag.c
extern tsCtrlLed_ChannelSettings CtrlLed_Diag_DisableError_Cmd (uint8_fast ucIdx, CONST_AL boolean boVinStatus, uint16 unCurrent);
extern void     CtrlLed_HandleChannelErrors(uint8_fast ucIl, uint8_fast ucChannel, uint8 ucErr, boolean boNewReq);
extern void     CtrlLed_ReportDtc(uint8 ucDtcState, uint16 *punPrvCh, uint8_fast ucIl, uint8_fast ucCh, uint16 *punActCh);
extern void     CtrlLed_Diag_SetChannelDtc(uint8 ucChannelName, uint8 ucErr);
extern void     CtrlLed_Diag_ResetDtc(uint8 ucChannelName, uint16 *punPrvCh, uint8_fast ucIl, uint8_fast ucCh);
extern uint8    CtrlLed_Diag_CountErrorBitPos(uint16 unVal);
extern boolean  CtrlLed_Diag_ChReacBuckErr(uint8_fast ucIl, uint8_fast ucCh, boolean boNewLightReq, uint8 ucErr);
extern void     CtrlLed_GetHss3DiagStatus(uint8 *pucData);
extern uint8    CtrlLed_Diag_Check_MtxVccx_Eeprom_Fault(boolean boVccxGnd, boolean boVccxBat, tsRte_MtxEeprom_ErrStatus sMtxEeprom_ErrStatus);
extern void     CtrlLed_SetResetMtxDtc(boolean boDtcStatus, uint8_fast ucRow);
extern void     CtrlLed_SetMtxDtc(uint8_fast ucRow, uint8_fast ucErr, boolean boHbStatus);
extern void     CtrlLed_ResetMtxDtc(uint8_fast ucRow, uint8_fast ucErr);

// CtrlLed_Rte.c
extern Std_ReturnType(*CtrlLed_Rte_apfnReadTgtBinningClass_sVal_List[CTRLLED_CFG_BASIC_LED_CH]) (tsRte_Binning0* psTgtBinningVal);
extern Std_ReturnType CtrlLed_Rte_ReadTgtBinningVal(uint8_fast ucIdx, tsRte_Binning0* sTgtBinningVal);
extern Std_ReturnType CtrlLed_RteAccess_Get_EcuSide(teCtrlLed_EcuSide* eEcuSide);

//=============================================================================
// Module function parameter stubs
//=============================================================================

//CtrlLed.c
uint8_fast CtrlLed_FindBuckId_Param1;
uint16     CtrlLed_FindBuckId_Param2;
uint8      CtrlLed_FindBuckId_Param3;
uint8      CtrlLed_FindBuckId_Param4;
uint8      CtrlLed_MatrixVoltCond_Param1;
uint8      CtrlLed_CalcRamp_Param1;
uint16     CtrlLed_CalcRamp_Param2;
uint16     CtrlLed_CalcRamp_Param3;
uint8      CtrlLed_GammaCurve_Param1;
uint16     CtrlLed_GammaCurve_Param2;
uint32     CtrlLed_DoRampInterpolation_Param1;
uint16     CtrlLed_DoRampInterpolation_Param2;
uint16     CtrlLed_DoRampInterpolation_Param3;
uint16     CtrlLed_DoRampInterpolation_Param4;
uint16     CtrlLed_DoRampInterpolation_Param5;
uint8_fast CtrlLed_CheckLight_Param1;
uint8      CtrlLed_CheckLight_Param2;
uint8      CtrlLed_CheckLight_Param3;
uint16     CtrlLed_CheckLight_Param4;
uint16     CtrlLed_CountSetBucks_Param1;
uint16     CtrlLed_GetBuckId_Param1;
uint8      CtrlLed_GetBuckId_Param2;
uint8      CtrlLed_GetBuckId_Param3;
uint8_fast CtrlLed_Handle_NonMatrixCh_Param1;
uint8_fast CtrlLed_Handle_NonMatrixCh_Param2;
uint16     CtrlLed_Handle_NonMatrixCh_Param3;
uint16     CtrlLed_Handle_NonMatrixCh_Param4;
uint32     CtrlLed_Handle_MatrixCh_Param1;
uint16     CtrlLed_Handle_MatrixCh_Param2;
uint8_fast CtrlLed_DutyCalculation_Param1;
uint8_fast CtrlLed_DutyCalculation_Param2;
uint8_fast CtrlLed_CurrentCalculation_Param1;
uint16     CtrlLed_CalculateGamma_Param1;
uint8      CtrlLed_CalculateGamma_Param2;

//CtrlLed_Data.c
tParaFct0_Cmd         CtrlLed_ParaFct0_Param1;
tNvmPara_CodingArea*  CtrlLed_ParaFct0_Param2;
tsCtrlled_CodingData* CtrlLed_CodMap_Param1;
uint8                 CtrlLed_Data_DriverMap_Param1;
tsCtrlled_CodingData* CtrlLed_Data_DriverMap_Param2;
uint8                 CtrlLed_Data_Matrix_Param1;
tsCtrlled_CodingData* CtrlLed_Data_Matrix_Param2;
uint8                 CtrlLed_Data_Led1_Param1;
tsCtrlled_CodingData* CtrlLed_Data_Led1_Param2;
uint8                 CtrlLed_Data_LmmX_Param1;
tsCtrlled_CodingData* CtrlLed_Data_LmmX_Param2;
uint8                 CtrlLed_Data_Get_UnitGroup_Param1;
tsCtrlled_CodingData* CtrlLed_Data_Get_UnitGroup_Param2;
uint8*                CtrlLed_Data_Process_SingleUnits_Param1;
uint8                 CtrlLed_Data_Process_SingleUnits_Param2;
uint8_fast            CtrlLed_Data_Process_SingleUnits_Param3;
tsCtrlled_CodingData* CtrlLed_Data_Process_SingleUnits_Param4;
uint8                 CtrlLed_Data_Process_MultiUnits_Param1;
uint8_fast            CtrlLed_Data_Process_MultiUnits_Param2;
tsCtrlled_CodingData* CtrlLed_Data_Process_MultiUnits_Param3;
uint8                 CtrlLed_Data_AnimaMap_Param1;
tsCtrlled_CodingData* CtrlLed_Data_AnimaMap_Param2;
uint8_fast            CtrlLed_CurrentUpdates_Param1;
uint8                 CtrlLed_CurrentUpdates_Param2;
tsCtrlled_CodingData *CtrlLed_CurrentUpdates_Param3;
uint8                 CtrlLed_Data_apfnDataMap_List_Param1;
tsCtrlled_CodingData  CtrlLed_Data_apfnDataMap_List_Param2;
uint8_fast            CtrlLed_GetAndCheckLedName_Param1;
uint8_fast            CtrlLed_GetAndCheckLedName_Param2;

//CtrlLed_Diag.c
uint8_fast    CtrlLed_Diag_DisableError_Cmd_Param1;
boolean       CtrlLed_Diag_DisableError_Cmd_Param2;
uint16        CtrlLed_Diag_DisableError_Cmd_Param3;
uint8_fast    CtrlLed_Diag_ChReacBuckErr_Param1;
uint8_fast    CtrlLed_Diag_ChReacBuckErr_Param2;
boolean       CtrlLed_Diag_ChReacBuckErr_Param3;
uint8         CtrlLed_Diag_ChReacBuckErr_Param4;
uint8_fast    CtrlLed_HandleChannelErrors_Param1;
uint8_fast    CtrlLed_HandleChannelErrors_Param2;
uint8         CtrlLed_HandleChannelErrors_Param3;
boolean       CtrlLed_HandleChannelErrors_Param4;
uint8         CtrlLed_ReportDtc_Param1;
uint16*       CtrlLed_ReportDtc_Param2;
uint8_fast    CtrlLed_ReportDtc_Param3;
uint8_fast    CtrlLed_ReportDtc_Param4;
uint16*       CtrlLed_ReportDtc_Param5;
uint16        CtrlLed_Diag_CountErrorBitPos_Param1;
uint8         CtrlLed_Diag_SetChannelDtc_Param1;
uint8         CtrlLed_Diag_SetChannelDtc_Param2;
uint8         CtrlLed_Diag_ResetDtc_Param1;
uint16*       CtrlLed_Diag_ResetDtc_Param2;
uint8_fast    CtrlLed_Diag_ResetDtc_Param3;
uint8_fast    CtrlLed_Diag_ResetDtc_Param4;
uint8_fast    CtrlLed_Diag_ErrorHandler_Param1;
uint8_fast    CtrlLed_Diag_ErrorHandler_Param2;
uint16        CtrlLed_Diag_ErrorHandler_Param3;
uint16        CtrlLed_Diag_ErrorHandler_Param4;
boolean       CtrlLed_SetResetMtxDtc_Param1;
uint8_fast    CtrlLed_SetResetMtxDtc_Param2;
uint8_fast    CtrlLed_SetMtxDtc_Param1;
uint8_fast    CtrlLed_SetMtxDtc_Param2;
boolean       CtrlLed_SetMtxDtc_Param3;
uint8_fast    CtrlLed_ResetMtxDtc_Param1;
uint8_fast    CtrlLed_ResetMtxDtc_Param2;
uint8         CtrlLed_GetMatrixError_Param1;
uint8         CtrlLed_GetMatrixError_Param2;
uint8         CtrlLed_GetMatrixError_Param3;
uint8*        CtrlLed_GetHss3DiagStatus_Param1;

//CtrlLed_Rte.c
uint8_fast                CtrlLed_Rte_Get_BinningClass_Param1;
tsCtrlLed_CodingParam     CtrlLed_RteAccess_Get_CodingPara_Param1;
uint8_fast                CtrlLed_RteAccess_Get_ChannelState_Param1;
tsCtrlLed_aChannelState   CtrlLed_RteAccess_Get_ChannelState_Param2;
tsCtrlLed_ChannelSettings CtrlLed_RteAccess_Set_ChannelSettings_Param1;
uint8_fast                CtrlLed_RteAccess_Set_IlluminantsStatus_Param1;
uint16                    CtrlLed_RteAccess_Set_IlluminantsStatus_Param2;
boolean                   CtrlLed_RteAccess_Set_IlluminantsStatus_Param3;
uint8                     CtrlLed_RteAccess_Set_IlluminantsStatus_Param4;
uint8                     CtrlLed_RteAccess_Get_MatrixLuErrors_Param1;
tuCtrlLed_bErr*           CtrlLed_RteAccess_Get_MatrixLuErrors_Param2;
boolean                   CtrlLed_RteAccess_Get_MatrixVccxErrors_Param1;
boolean                   CtrlLed_RteAccess_Get_MatrixVccxErrors_Param2;
teCtrlLed_EcuSide*        CtrlLed_RteAccess_Get_EcuSide_Param1;
uint8_fast                CtrlLed_Rte_ReadTgtBinningVal_Param1;
tsRte_Binning0*           CtrlLed_Rte_ReadTgtBinningVal_Param2;
boolean                   CtrlLed_RteAccess_Get_MatrixSystemMode_Param1;
uint8                     CtrlLed_RteAccess_Get_HSS3_Status_Param1;
boolean                   CtrlLed_RteAccess_Get_HSS3_Status_Param2;
uint16                    CtrlLed_RteAccess_Set_HSS3_Duty_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

//CtrlLed.c
uint16  CtrlLed_CalcRamp_RetVal;
uint16  CtrlLed_GammaCurve_RetVal;
uint16  CtrlLed_DoRampInterpolation_RetVal;
uint8   CtrlLed_CountSetBucks_RetVal;
uint16  CtrlLed_Handle_NonMatrixCh_RetVal;
uint16  CtrlLed_Handle_MatrixCh_RetVal;
uint16  CtrlLed_DutyCalculation_RetVal;
uint16  CtrlLed_CurrentCalculation_RetVal;
uint16  CtrlLed_CalculateGamma_RetVal;
tsCtrlled_CodingData*         CtrlLed_pfCodingData_RetVal;
tsCtrlled_InternalHandlings*  CtrlLed_pfInternalHandling_RetVal;
teCtrlLed_MatrixVoltCnd       CtrlLed_MatrixVoltCond_RetVal;

//CtrlLed_Data.c
boolean   CtrlLed_ParaFct0_RetVal;
boolean   CtrlLed_Data_DriverMap_RetVal;
boolean   CtrlLed_Data_Matrix_RetVal;
boolean   CtrlLed_Data_Led1_RetVal;
boolean   CtrlLed_Data_LmmX_RetVal;
boolean   CtrlLed_Data_Get_UnitGroup_RetVal;
boolean   CtrlLed_Data_AnimaMap_RetVal;
boolean   CtrlLed_Data_apfnDataMap_List_RetVal;
boolean   CtrlLed_CodingDataValidation_RetVal;
boolean   CtrlLed_CodMap_RetVal;
uint8     CtrlLed_GetAndCheckLedName_RetVal;
boolean   CtrlLed_CurrentUpdates_RetVal;

//CtrlLed_Diag.c
tsCtrlLed_ChannelSettings CtrlLed_Diag_DisableError_Cmd_RetVal;
uint8                     CtrlLed_ReportChReactionAndDtc_RetVal;
tsCtrlLed_ErrorHandler    CtrlLed_Diag_ErrorHandler_RetVal;
boolean                   CtrlLed_Diag_MtxVccx_Eeprom_RetVal;
boolean                   CtrlLed_Diag_ChReacBuckErr_RetVal;
uint8                     CtrlLed_Diag_CountErrorBitPos_RetVal;
boolean                   CtrlLed_GetMatrixError_RetVal;

//CtrlLed_Rte.c
uint8           CtrlLed_Rte_Get_BinningClass_RetVal;
uint16          CtrlLed_RteAccess_Read_Vbat_RetVal;
uint8           CtrlLed_RteAccess_Get_ECU_Side_RetVal;
Std_ReturnType  CtrlLed_RteAccess_Get_EcuSide_RetVal;
Std_ReturnType  CtrlLed_Rte_ReadTgtBinningVal_RetVal;
uint8           CtrlLed_RteAccess_VoltageRange_RetVal;
boolean         CtrlLed_RteAccess_Get_DD01_Diag_Status_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

//CtrlLed.c
boolean                 boMultipleBuckErr;
tsCtrlLed_ErrorHandler  sCtrlLed_ErrorHandler;
tsCtrlLed_RampValues    sRampValues[CTRLLED_CFG_LED_CHANNELS_NR];
uint16                  unStartPoint_Int[CTRLLED_CFG_LED_CHANNELS_NR];
uint32                  ulTimerGetTimeSince_us[CTRLLED_CFG_LED_CHANNELS_NR];
boolean                 boDimInProgress[CTRLLED_CFG_LED_CHANNELS_NR];
teCtrlLed_MatrixVoltCnd eMtxVoltCnd;

//CtrlLed_Data.c
uint16  unBitFlag;
uint8   ucLu;

//CtrlLed_Diag.c
boolean boMtxEeprom_Fault_Prv;
boolean CtrlLed_Force_InvalidCoding;
uint8   CtrlLed_ForceReset;


#endif // TEST_2023_08_25_H_
