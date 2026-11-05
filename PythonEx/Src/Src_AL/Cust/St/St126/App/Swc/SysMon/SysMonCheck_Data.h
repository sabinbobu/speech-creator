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
/// \file  SysMonCheck_Data.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_MON_CHECK_DATA_2021_11_01_H_
#define SYS_MON_CHECK_DATA_2021_11_01_H_

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>
#include <SysMon_Types.h>
#include <CddEft.h>

//-----------------------------------------------------------------------------
// externs
//-----------------------------------------------------------------------------
extern CONST_AL  tNvmPara_CodingArea*              SysMonCheck_Data_pCodingArea;

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define FUSA_FS_BEHAVIOUR_ASIL_INVALID              (uint8)    2u
#define FUSA_DRVxx_MIN_PWM_ASIL_INVALID_LOW         (uint8)    0u
#define FUSA_DRVxx_MIN_PWM_ASIL_INVALID_HIGH        (uint8)  201u
#define FUSA_DRVxx_MIN_CURRENT_ASIL_INVALID_LOW     (uint16)   0u
#define FUSA_DRVxx_MIN_CURRENT_ASIL_INVALID_HIGH    (uint16)3001u

#define SYSMONCHECK_DATA_CRC_RAM_CHECK_MS                    200u

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
#define SYSMONCHECK_DATA_MAX_LBFUSI_AND_TI_CHANNELS  (uint8)   6u
#elif defined (CFG_VARIANT_ECO)
#define SYSMONCHECK_DATA_MAX_LBFUSI_AND_TI_CHANNELS  (uint8)   2u
#endif

//-----------------------------------------------------------------------------
// Access to EFT data
//-----------------------------------------------------------------------------
// API access
#define SYSMONCHECK_DATA_EftDataValid()                             CddEft_DataValid()  //CddEft_DataValid()
#define SYSMONCHECK_DATA_ECUVARCFG_ucAssignedOutput(Device,Channel) EFT_ECUVARCFG_Tps92520[Device].aDrv[Channel].ucAssignedOutput
#define SYSMONCHECK_DATA_ECUVARCFG_unImax(Device,Channel)           EFT_ECUVARCFG_Tps92520[Device].aDrv[Channel].unImax

// Number of TPS92520 devices
#define SYSMONCHECK_DATA_Cfg_NbOfDevices        6u
// Number of channel by TPS92520 device
#define SYSMONCHECK_DATA_Cfg_NbOfChannels       2u
// Define for channel not being populated
#define SYSMONCHECK_DATA_CHANNEL_NOT_SUPPORTED  0u

//-----------------------------------------------------------------------------
// typedef
//-----------------------------------------------------------------------------

// Enum for SysMon Valid Data Parameters
typedef enum
{
  SysMonCheck_Data_FuSaParamUnknown = 0u,
  SysMonCheck_Data_FuSaParamValid,
  SysMonCheck_Data_FuSaParamInvalid
}tSysMonCheck_Data_FuSaParamValid;


typedef struct tSysMonCheck_Data_LedChParam
{
  SysMonCheck_Data_tLFName  eName;
  uint16                    unMinPwmDuty;
  uint16                    unMinCurrent;
  uint32                    ulLedUnderVoltValue;
  uint32                    ulLedOverVoltValue;
}tSysMonCheck_Data_LedChParam;

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void                             SysMonCheck_Data_SetCodingDataSatus(boolean boIsCodingDataValid);
void                             SysMonCheck_Data_Cycle10ms_FuSaMonitoring(void);
boolean                          SysMonCheck_Data_CodingDataValidation(void);
tSysMonCheck_Data_LedChParam*    SysMonCheck_Data_GetaLEDChParamPtr(void);
tSysMonCheck_Data_FuSaParamValid SysMonCheck_Data_AreFuSaParamValid(void);
boolean                          SysMonCheck_Data_IsCodingDataValid(void);
boolean                          SysMonCheck_Data_IsTurnIndicatorFuSa(uint8 ucFuSaIdx);
boolean                          SysMonCheck_Data_AreFuSaParam_Invalid(void);
uint8                            SysMonCheck_Data_Get_ucFUSA_LB_FS_BEHAVIOUR_ASIL(void);
uint8                            SysMonCheck_Data_Get_ucFUSA_TI_FS_BEHAVIOUR_ASIL(void);
boolean                          SysMonCheck_Data_Get_IsLowBeamEnabled(void);
boolean                          SysMonCheck_Data_Get_IsTurnIndEnabled(void);
boolean                          SysMonCheck_Data_Get_Crc32RamFailure(void);
boolean                          SysMonCheck_Data_Get_Crc32RomFailure(void);
boolean                          SysMonCheck_Data_GetCrc32IntegrityCheck(void);
tsSysMon_Error                   SysMonCheck_Data_Get_CodingDataDebounce(void);
uint16                           SysMonCheck_Data_CheckAndSetCodingData(boolean boIsCodingDataValid);
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
boolean                          SysMonCheck_Data_Get_TiScrollingPresent(void);
#endif // CFG_VARIANT_FULL

#endif // SYS_MON_CHECK_DATA_2021_11_01_H_
