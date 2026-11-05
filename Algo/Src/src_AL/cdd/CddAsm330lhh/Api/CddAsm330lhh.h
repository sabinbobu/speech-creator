/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh.h
* Description:
*   Public API for the ASM330LHH Complex Device Driver (CDD).
*   The module exposes initialization, configuration, acquisition and
*   basic diagnostic services for an SPI-connected inertial sensor.
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_2026_07_07_H_
#define CDD_ASM330LHH_2026_07_07_H_

#include <Std_Types.h>
#include <../Cfg/CddAsm330lhh_Cfg.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
*****************************************************************************
* Version information
*****************************************************************************
*/
#define CDDASM330LHH_VERSION_MAJOR   1u
#define CDDASM330LHH_VERSION_MINOR   0u
#define CDDASM330LHH_VERSION_PATCH   0u

/*
*****************************************************************************
* Enumerations for runtime control and register-level configuration mapping
*****************************************************************************
*/
typedef enum
{
  CDDASM330LHH_POWER_OFF = 0u,
  CDDASM330LHH_POWER_NORMAL = 1u
} CddAsm330lhh_PowerModeType;

typedef enum
{
  CDDASM330LHH_INIT_UNINITIALIZED = 0u,
  CDDASM330LHH_INIT_PENDING,
  CDDASM330LHH_INIT_READY,
  CDDASM330LHH_INIT_FAILED
} CddAsm330lhh_InitStatusType;

typedef enum
{
  CDDASM330LHH_ODR_OFF = 0u,
  CDDASM330LHH_ODR_12_5HZ,
  CDDASM330LHH_ODR_26HZ,
  CDDASM330LHH_ODR_52HZ,
  CDDASM330LHH_ODR_104HZ,
  CDDASM330LHH_ODR_208HZ,
  CDDASM330LHH_ODR_416HZ,
  CDDASM330LHH_ODR_833HZ,
  CDDASM330LHH_ODR_1660HZ
} CddAsm330lhh_OdrType;

typedef enum
{
  CDDASM330LHH_ACCEL_FS_2G = 0u,
  CDDASM330LHH_ACCEL_FS_4G,
  CDDASM330LHH_ACCEL_FS_8G,
  CDDASM330LHH_ACCEL_FS_16G
} CddAsm330lhh_AccelFsType;

typedef enum
{
  CDDASM330LHH_GYRO_FS_125DPS = 0u,
  CDDASM330LHH_GYRO_FS_250DPS,
  CDDASM330LHH_GYRO_FS_500DPS,
  CDDASM330LHH_GYRO_FS_1000DPS,
  CDDASM330LHH_GYRO_FS_2000DPS
} CddAsm330lhh_GyroFsType;

/*
*****************************************************************************
* Configuration structures
*****************************************************************************
*/
typedef struct
{
  CddAsm330lhh_OdrType Odr;
  CddAsm330lhh_AccelFsType FullScale;
} CddAsm330lhh_AccelConfigType;

typedef struct
{
  CddAsm330lhh_OdrType Odr;
  CddAsm330lhh_GyroFsType FullScale;
} CddAsm330lhh_GyroConfigType;

/*
*****************************************************************************
* Data containers for raw and converted samples
*****************************************************************************
*/
typedef struct
{
  sint16 Ax;
  sint16 Ay;
  sint16 Az;
  sint16 Gx;
  sint16 Gy;
  sint16 Gz;
  sint16 TempRaw;
  uint8 StatusReg;
} CddAsm330lhh_RawDataType;

typedef struct
{
  sint32 Ax_mg;
  sint32 Ay_mg;
  sint32 Az_mg;
  sint32 Gx_mdps;
  sint32 Gy_mdps;
  sint32 Gz_mdps;
  sint32 Temp_cdeg;
  uint8 StatusReg;
} CddAsm330lhh_ScaledDataType;

typedef struct
{
  boolean EnableBlockDataUpdate;
  boolean EnableAutoIncrement;
  CddAsm330lhh_AccelConfigType AccelInit;
  CddAsm330lhh_GyroConfigType GyroInit;
} CddAsm330lhh_ConfigType;

/*
*****************************************************************************
* Extern default configuration for simple integration projects
*****************************************************************************
*/
extern const CddAsm330lhh_ConfigType CddAsm330lhh_Config_Default;

#define ctadCddAsm330lhh_START_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

/*
*****************************************************************************
* Function: CddAsm330lhh_Init
* Purpose : Start asynchronous module and sensor initialization.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_Init(const CddAsm330lhh_ConfigType* CfgPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_GetInitStatus
* Purpose : Retrieve asynchronous initialization state without waiting.
*****************************************************************************
*/
CddAsm330lhh_InitStatusType CddAsm330lhh_GetInitStatus(void);

/*
*****************************************************************************
* Function: CddAsm330lhh_DeInit
* Purpose : Queue asynchronous module de-initialization.
*****************************************************************************
*/
void CddAsm330lhh_DeInit(void);

/*
*****************************************************************************
* Function: CddAsm330lhh_MainFunction
* Purpose : Advance initialization, read, and configuration state machines.
*****************************************************************************
*/
void CddAsm330lhh_MainFunction(void);

/*
*****************************************************************************
* Function: CddAsm330lhh_GetDeviceId
* Purpose : Return the identifier cached during asynchronous initialization.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_GetDeviceId(uint8* DeviceIdPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_SetPowerMode
* Purpose : Queue an asynchronous OFF/NORMAL power-mode change.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_SetPowerMode(CddAsm330lhh_PowerModeType PowerMode);

/*
*****************************************************************************
* Function: CddAsm330lhh_ConfigureAccel
* Purpose : Queue asynchronous accelerometer ODR and full-scale configuration.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ConfigureAccel(const CddAsm330lhh_AccelConfigType* AccelCfgPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_ConfigureGyro
* Purpose : Queue asynchronous gyroscope ODR and full-scale configuration.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ConfigureGyro(const CddAsm330lhh_GyroConfigType* GyroCfgPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_ReadRawData
* Purpose : Retrieve the latest completed raw sample without starting an SPI read.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ReadRawData(CddAsm330lhh_RawDataType* RawDataPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_ReadScaledData
* Purpose : Retrieve the latest completed scaled sample without starting an SPI read.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ReadScaledData(CddAsm330lhh_ScaledDataType* ScaledDataPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_StartRead
* Purpose : Queue a non-blocking sensor sample acquisition.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_StartRead(void);

/*
*****************************************************************************
* Function: CddAsm330lhh_GetLatestSample
* Purpose : Retrieve and consume the latest completed scaled sample.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_GetLatestSample(CddAsm330lhh_ScaledDataType* SamplePtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_RunBasicSelfTest
* Purpose : Perform a basic communication-oriented self-check.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_RunBasicSelfTest(boolean* PassedPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_IsInitialized
* Purpose : Report current module initialization state.
*****************************************************************************
*/
boolean CddAsm330lhh_IsInitialized(void);

#define ctadCddAsm330lhh_STOP_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif /* CDD_ASM330LHH_2026_07_07_H_ */
