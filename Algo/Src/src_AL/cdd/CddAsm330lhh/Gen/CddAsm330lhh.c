/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh.c
* Description:
*   Core AUTOSAR-style CDD implementation for ASM330LHH.
*   The module provides initialization, configuration, conversion and
*   diagnostic supervision services with explicit DET reporting points.
*****************************************************************************
*/

#include <Std_Types.h>
#include <Spi.h>
#include <../Api/CddAsm330lhh.h>
#include <../Api/CddAsm330lhh_Cb.h>
#include <../Cfg/CddAsm330lhh_Cfg.h>
#include <../Cfg/CddAsm330lhh_RoutCfg.h>
#include <../Gen/CddAsm330lhh_Types.h>
#include <../Gen/CddAsm330lhh_Com.h>

/*
*****************************************************************************
* Conversion and register window constants
*****************************************************************************
*/
#define CDDASM330LHH_REG_SNAPSHOT_LEN      (16u)

#define CDDASM330LHH_ODR_12_5HZ_BITS       (0x10u)
#define CDDASM330LHH_ODR_26HZ_BITS         (0x20u)
#define CDDASM330LHH_ODR_52HZ_BITS         (0x30u)
#define CDDASM330LHH_ODR_104HZ_BITS        (0x40u)
#define CDDASM330LHH_ODR_208HZ_BITS        (0x50u)
#define CDDASM330LHH_ODR_416HZ_BITS        (0x60u)
#define CDDASM330LHH_ODR_833HZ_BITS        (0x70u)
#define CDDASM330LHH_ODR_1660HZ_BITS       (0x80u)

#define CDDASM330LHH_ACCEL_FS_2G_BITS      (0x00u)
#define CDDASM330LHH_ACCEL_FS_16G_BITS     (0x04u)
#define CDDASM330LHH_ACCEL_FS_4G_BITS      (0x08u)
#define CDDASM330LHH_ACCEL_FS_8G_BITS      (0x0Cu)

#define CDDASM330LHH_GYRO_FS_250DPS_BITS   (0x00u)
#define CDDASM330LHH_GYRO_FS_125DPS_BITS   (0x02u)
#define CDDASM330LHH_GYRO_FS_500DPS_BITS   (0x04u)
#define CDDASM330LHH_GYRO_FS_1000DPS_BITS  (0x08u)
#define CDDASM330LHH_GYRO_FS_2000DPS_BITS  (0x0Cu)

#define CDDASM330LHH_TEMP_OFFSET_CDEG      (2500)
#define CDDASM330LHH_TEMP_SENS_NUM         (100)
#define CDDASM330LHH_TEMP_SENS_DEN         (256)

#define ctadCddAsm330lhh_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddAsm330lhh_MemMap.h>

/*
*****************************************************************************
* Global module state
*****************************************************************************
*/
static CddAsm330lhh_DriverStateType CddAsm330lhh_State;

#define ctadCddAsm330lhh_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddAsm330lhh_MemMap.h>

static boolean CddAsm330lhh_StateValid = FALSE;

#define ctadCddAsm330lhh_START_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

/*
*****************************************************************************
* Function: CddAsm330lhh_ReportDetError
* Purpose : Single entry point to report DET errors.
*****************************************************************************
*/
static void CddAsm330lhh_ReportDetError(uint8 ApiId, uint8 ErrorId)
{
#if (CDDASM330LHH_DEV_ERROR_DETECT == STD_ON)
  CDDASM330LHH_DET_REPORT_ERROR(CDDASM330LHH_MODULE_ID, CDDASM330LHH_INSTANCE_ID, ApiId, ErrorId);
#else
  (void)ApiId;
  (void)ErrorId;
#endif
}

/*
*****************************************************************************
* Function: CddAsm330lhh_MapOdrToBits
* Purpose : Map logical ODR enum to register field value.
*****************************************************************************
*/
static uint8 CddAsm330lhh_MapOdrToBits(CddAsm330lhh_OdrType Odr)
{
  uint8 OdrBits = 0u;

  switch (Odr)
  {
    case CDDASM330LHH_ODR_OFF:
      OdrBits = 0u;
      break;
    case CDDASM330LHH_ODR_12_5HZ:
      OdrBits = CDDASM330LHH_ODR_12_5HZ_BITS;
      break;
    case CDDASM330LHH_ODR_26HZ:
      OdrBits = CDDASM330LHH_ODR_26HZ_BITS;
      break;
    case CDDASM330LHH_ODR_52HZ:
      OdrBits = CDDASM330LHH_ODR_52HZ_BITS;
      break;
    case CDDASM330LHH_ODR_104HZ:
      OdrBits = CDDASM330LHH_ODR_104HZ_BITS;
      break;
    case CDDASM330LHH_ODR_208HZ:
      OdrBits = CDDASM330LHH_ODR_208HZ_BITS;
      break;
    case CDDASM330LHH_ODR_416HZ:
      OdrBits = CDDASM330LHH_ODR_416HZ_BITS;
      break;
    case CDDASM330LHH_ODR_833HZ:
      OdrBits = CDDASM330LHH_ODR_833HZ_BITS;
      break;
    case CDDASM330LHH_ODR_1660HZ:
      OdrBits = CDDASM330LHH_ODR_1660HZ_BITS;
      break;
    default:
      OdrBits = 0u;
      break;
  }

  return OdrBits;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_MapAccelFsToBits
* Purpose : Map accelerometer full scale enum to register field value.
*****************************************************************************
*/
static uint8 CddAsm330lhh_MapAccelFsToBits(CddAsm330lhh_AccelFsType FullScale)
{
  uint8 FsBits = CDDASM330LHH_ACCEL_FS_2G_BITS;

  switch (FullScale)
  {
    case CDDASM330LHH_ACCEL_FS_2G:
      FsBits = CDDASM330LHH_ACCEL_FS_2G_BITS;
      break;
    case CDDASM330LHH_ACCEL_FS_4G:
      FsBits = CDDASM330LHH_ACCEL_FS_4G_BITS;
      break;
    case CDDASM330LHH_ACCEL_FS_8G:
      FsBits = CDDASM330LHH_ACCEL_FS_8G_BITS;
      break;
    case CDDASM330LHH_ACCEL_FS_16G:
      FsBits = CDDASM330LHH_ACCEL_FS_16G_BITS;
      break;
    default:
      FsBits = CDDASM330LHH_ACCEL_FS_2G_BITS;
      break;
  }

  return FsBits;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_MapGyroFsToBits
* Purpose : Map gyroscope full scale enum to register field value.
*****************************************************************************
*/
static uint8 CddAsm330lhh_MapGyroFsToBits(CddAsm330lhh_GyroFsType FullScale)
{
  uint8 FsBits = CDDASM330LHH_GYRO_FS_250DPS_BITS;

  switch (FullScale)
  {
    case CDDASM330LHH_GYRO_FS_125DPS:
      FsBits = CDDASM330LHH_GYRO_FS_125DPS_BITS;
      break;
    case CDDASM330LHH_GYRO_FS_250DPS:
      FsBits = CDDASM330LHH_GYRO_FS_250DPS_BITS;
      break;
    case CDDASM330LHH_GYRO_FS_500DPS:
      FsBits = CDDASM330LHH_GYRO_FS_500DPS_BITS;
      break;
    case CDDASM330LHH_GYRO_FS_1000DPS:
      FsBits = CDDASM330LHH_GYRO_FS_1000DPS_BITS;
      break;
    case CDDASM330LHH_GYRO_FS_2000DPS:
      FsBits = CDDASM330LHH_GYRO_FS_2000DPS_BITS;
      break;
    default:
      FsBits = CDDASM330LHH_GYRO_FS_250DPS_BITS;
      break;
  }

  return FsBits;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_BytesToS16
* Purpose : Compose signed 16-bit value from little-endian bytes.
*****************************************************************************
*/
static sint16 CddAsm330lhh_BytesToS16(uint8 Lsb, uint8 Msb)
{
  return (sint16)(((uint16)Msb << 8u) | (uint16)Lsb);
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ConvertAccelToMg
* Purpose : Convert accelerometer raw sample to mg.
*****************************************************************************
*/
static sint32 CddAsm330lhh_ConvertAccelToMg(sint16 Raw, CddAsm330lhh_AccelFsType FullScale)
{
  sint32 Sensitivity_ugPerLsb;

  switch (FullScale)
  {
    case CDDASM330LHH_ACCEL_FS_2G:
      Sensitivity_ugPerLsb = 61;
      break;
    case CDDASM330LHH_ACCEL_FS_4G:
      Sensitivity_ugPerLsb = 122;
      break;
    case CDDASM330LHH_ACCEL_FS_8G:
      Sensitivity_ugPerLsb = 244;
      break;
    case CDDASM330LHH_ACCEL_FS_16G:
      Sensitivity_ugPerLsb = 488;
      break;
    default:
      Sensitivity_ugPerLsb = 61;
      break;
  }

  return ((sint32)Raw * Sensitivity_ugPerLsb) / 1000;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ConvertGyroToMdps
* Purpose : Convert gyroscope raw sample to mdps.
*****************************************************************************
*/
static sint32 CddAsm330lhh_ConvertGyroToMdps(sint16 Raw, CddAsm330lhh_GyroFsType FullScale)
{
  sint32 Sensitivity_udpsPerLsb;

  switch (FullScale)
  {
    case CDDASM330LHH_GYRO_FS_125DPS:
      Sensitivity_udpsPerLsb = 4375;
      break;
    case CDDASM330LHH_GYRO_FS_250DPS:
      Sensitivity_udpsPerLsb = 8750;
      break;
    case CDDASM330LHH_GYRO_FS_500DPS:
      Sensitivity_udpsPerLsb = 17500;
      break;
    case CDDASM330LHH_GYRO_FS_1000DPS:
      Sensitivity_udpsPerLsb = 35000;
      break;
    case CDDASM330LHH_GYRO_FS_2000DPS:
      Sensitivity_udpsPerLsb = 70000;
      break;
    default:
      Sensitivity_udpsPerLsb = 8750;
      break;
  }

  return ((sint32)Raw * Sensitivity_udpsPerLsb) / 1000;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ValidateAccelConfig
* Purpose : Validate accelerometer configuration boundaries.
*****************************************************************************
*/
static boolean CddAsm330lhh_ValidateAccelConfig(const CddAsm330lhh_AccelConfigType* AccelCfgPtr)
{
  return (boolean)((AccelCfgPtr != NULL_PTR) &&
                   (AccelCfgPtr->Odr <= CDDASM330LHH_ODR_1660HZ) &&
                   (AccelCfgPtr->FullScale <= CDDASM330LHH_ACCEL_FS_16G));
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ValidateGyroConfig
* Purpose : Validate gyroscope configuration boundaries.
*****************************************************************************
*/
static boolean CddAsm330lhh_ValidateGyroConfig(const CddAsm330lhh_GyroConfigType* GyroCfgPtr)
{
  return (boolean)((GyroCfgPtr != NULL_PTR) &&
                   (GyroCfgPtr->Odr <= CDDASM330LHH_ODR_1660HZ) &&
                   (GyroCfgPtr->FullScale <= CDDASM330LHH_GYRO_FS_2000DPS));
}

#define CDDASM330LHH_SPI_START_RETRY_LIMIT  (100u)

static Std_ReturnType CddAsm330lhh_StartTransfer(CddAsm330lhh_PendingOpType PendingOp,
                                                 CddAsm330lhh_DriverModeType TransferMode,
                                                 uint8 RegAddr,
                                                 uint8 Data,
                                                 uint8 Length)
{
  Std_ReturnType Ret = E_NOT_OK;

  CDDASM330LHH_ENTER_CRITICAL();
  CddAsm330lhh_State.PendingOp = PendingOp;
  CddAsm330lhh_State.SpiState = CDDASM330LHH_SPI_PENDING;
  CddAsm330lhh_State.DriverMode = TransferMode;
  CDDASM330LHH_EXIT_CRITICAL();

  if (PendingOp == CDDASM330LHH_OP_READ_REG)
  {
    Ret = CddAsm330lhh_Com_StartReadReg(RegAddr);
  }
  else if (PendingOp == CDDASM330LHH_OP_WRITE_REG)
  {
    Ret = CddAsm330lhh_Com_StartWriteReg(RegAddr, Data);
  }
  else if (PendingOp == CDDASM330LHH_OP_READ_BURST)
  {
    Ret = CddAsm330lhh_Com_StartReadBurst(RegAddr, Length);
  }

  CDDASM330LHH_ENTER_CRITICAL();
  if (Ret == E_OK)
  {
    CddAsm330lhh_State.StartRetryCount = 0u;
  }
  else
  {
    CddAsm330lhh_State.PendingOp = CDDASM330LHH_OP_NONE;
    CddAsm330lhh_State.SpiState = CDDASM330LHH_SPI_IDLE;
    CddAsm330lhh_State.DriverMode =
      (TransferMode == CDDASM330LHH_DRIVER_INIT_TRANSFER) ? CDDASM330LHH_DRIVER_INIT_START :
      (TransferMode == CDDASM330LHH_DRIVER_READ_TRANSFER) ? CDDASM330LHH_DRIVER_READ_START :
      (TransferMode == CDDASM330LHH_DRIVER_WRITE_TRANSFER) ? CDDASM330LHH_DRIVER_WRITE_START :
      CDDASM330LHH_DRIVER_DEINIT_START;
    CddAsm330lhh_State.StartRetryCount++;
  }
  CDDASM330LHH_EXIT_CRITICAL();

  return Ret;
}

static void CddAsm330lhh_FailOperation(CddAsm330lhh_DriverModeType FailedMode)
{
  CDDASM330LHH_ENTER_CRITICAL();
  CddAsm330lhh_State.LastSpiTransferOk = FALSE;
  CddAsm330lhh_State.PendingOp = CDDASM330LHH_OP_NONE;
  CddAsm330lhh_State.SpiState = CDDASM330LHH_SPI_FAILED;
  CddAsm330lhh_State.PendingWriteCount = 0u;
  CddAsm330lhh_State.PendingWriteIndex = 0u;
  CddAsm330lhh_State.WriteAction = CDDASM330LHH_WRITE_NONE;

  if ((FailedMode == CDDASM330LHH_DRIVER_INIT_START) ||
      (FailedMode == CDDASM330LHH_DRIVER_INIT_TRANSFER))
  {
    CddAsm330lhh_State.Initialized = FALSE;
    CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_FAILED;
    CddAsm330lhh_State.InitStatus = CDDASM330LHH_INIT_FAILED;
  }
  else if ((FailedMode == CDDASM330LHH_DRIVER_DEINIT_START) ||
           (FailedMode == CDDASM330LHH_DRIVER_DEINIT_TRANSFER))
  {
    CddAsm330lhh_State.Initialized = FALSE;
    CddAsm330lhh_State.InitStatus = CDDASM330LHH_INIT_FAILED;
    CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_FAILED;
  }
  else
  {
    CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_READY;
  }
  CDDASM330LHH_EXIT_CRITICAL();

  CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_MAINFUNCTION, CDDASM330LHH_E_COMM);
}

static Std_ReturnType CddAsm330lhh_QueueWrites(CddAsm330lhh_WriteActionType Action,
                                                const uint8* RegisterPtr,
                                                const uint8* ValuePtr,
                                                uint8 Count,
                                                const CddAsm330lhh_AccelConfigType* AccelCfgPtr,
                                                const CddAsm330lhh_GyroConfigType* GyroCfgPtr,
                                                CddAsm330lhh_PowerModeType PowerMode,
                                                uint8 Ctrl1,
                                                uint8 Ctrl2)
{
  Std_ReturnType Ret = E_NOT_OK;
  uint8 Index = 0u;

  if ((RegisterPtr != NULL_PTR) && (ValuePtr != NULL_PTR) &&
      (Count > 0u) && (Count <= 2u))
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if ((CddAsm330lhh_StateValid != FALSE) &&
        (CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_READY) &&
        (CddAsm330lhh_State.DataReady == FALSE))
    {
      for (Index = 0u; Index < Count; Index++)
      {
        CddAsm330lhh_State.PendingWriteReg[Index] = RegisterPtr[Index];
        CddAsm330lhh_State.PendingWriteValue[Index] = ValuePtr[Index];
      }
      CddAsm330lhh_State.PendingWriteCount = Count;
      CddAsm330lhh_State.PendingWriteIndex = 0u;
      CddAsm330lhh_State.WriteAction = Action;
      CddAsm330lhh_State.RequestedPowerMode = PowerMode;
      CddAsm330lhh_State.PendingCtrl1 = Ctrl1;
      CddAsm330lhh_State.PendingCtrl2 = Ctrl2;
      if (AccelCfgPtr != NULL_PTR)
      {
        CddAsm330lhh_State.PendingAccelCfg = *AccelCfgPtr;
      }
      if (GyroCfgPtr != NULL_PTR)
      {
        CddAsm330lhh_State.PendingGyroCfg = *GyroCfgPtr;
      }
      CddAsm330lhh_State.DriverMode =
        (Action == CDDASM330LHH_WRITE_DEINIT) ?
        CDDASM330LHH_DRIVER_DEINIT_START : CDDASM330LHH_DRIVER_WRITE_START;
      CddAsm330lhh_State.StartRetryCount = 0u;
      Ret = E_OK;
    }
    CDDASM330LHH_EXIT_CRITICAL();
  }

  return Ret;
}

static void CddAsm330lhh_DecodeLatestSample(const uint8* RxBufferPtr)
{
  CddAsm330lhh_RawDataType RawData;
  uint8 Index = 0u;

  for (Index = 0u; Index < CDDASM330LHH_REG_SNAPSHOT_LEN; Index++)
  {
    CddAsm330lhh_State.RawDataBuffer[Index] = RxBufferPtr[(uint8)(Index + 1u)];
  }

  RawData.StatusReg = CddAsm330lhh_State.RawDataBuffer[0];
  RawData.TempRaw = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[2],
                                            CddAsm330lhh_State.RawDataBuffer[3]);
  RawData.Gx = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[4],
                                      CddAsm330lhh_State.RawDataBuffer[5]);
  RawData.Gy = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[6],
                                      CddAsm330lhh_State.RawDataBuffer[7]);
  RawData.Gz = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[8],
                                      CddAsm330lhh_State.RawDataBuffer[9]);
  RawData.Ax = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[10],
                                      CddAsm330lhh_State.RawDataBuffer[11]);
  RawData.Ay = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[12],
                                      CddAsm330lhh_State.RawDataBuffer[13]);
  RawData.Az = CddAsm330lhh_BytesToS16(CddAsm330lhh_State.RawDataBuffer[14],
                                      CddAsm330lhh_State.RawDataBuffer[15]);

  CDDASM330LHH_ENTER_CRITICAL();
  CddAsm330lhh_State.LatestRawData = RawData;
  CddAsm330lhh_State.LatestScaledData.StatusReg = RawData.StatusReg;
  CddAsm330lhh_State.LatestScaledData.Ax_mg =
    CddAsm330lhh_ConvertAccelToMg(RawData.Ax, CddAsm330lhh_State.ActiveAccelCfg.FullScale);
  CddAsm330lhh_State.LatestScaledData.Ay_mg =
    CddAsm330lhh_ConvertAccelToMg(RawData.Ay, CddAsm330lhh_State.ActiveAccelCfg.FullScale);
  CddAsm330lhh_State.LatestScaledData.Az_mg =
    CddAsm330lhh_ConvertAccelToMg(RawData.Az, CddAsm330lhh_State.ActiveAccelCfg.FullScale);
  CddAsm330lhh_State.LatestScaledData.Gx_mdps =
    CddAsm330lhh_ConvertGyroToMdps(RawData.Gx, CddAsm330lhh_State.ActiveGyroCfg.FullScale);
  CddAsm330lhh_State.LatestScaledData.Gy_mdps =
    CddAsm330lhh_ConvertGyroToMdps(RawData.Gy, CddAsm330lhh_State.ActiveGyroCfg.FullScale);
  CddAsm330lhh_State.LatestScaledData.Gz_mdps =
    CddAsm330lhh_ConvertGyroToMdps(RawData.Gz, CddAsm330lhh_State.ActiveGyroCfg.FullScale);
  CddAsm330lhh_State.LatestScaledData.Temp_cdeg =
    (((sint32)RawData.TempRaw * CDDASM330LHH_TEMP_SENS_NUM) /
     CDDASM330LHH_TEMP_SENS_DEN) + CDDASM330LHH_TEMP_OFFSET_CDEG;
  CddAsm330lhh_State.DataReady = TRUE;
  CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_SAMPLE_READY;
  CddAsm330lhh_State.LastSpiTransferOk = TRUE;
  CDDASM330LHH_EXIT_CRITICAL();
}

static void CddAsm330lhh_ProcessCompletion(void)
{
  boolean CompletionPending = FALSE;
  boolean CompletionSucceeded = FALSE;
  CddAsm330lhh_DriverModeType CompletedMode = CDDASM330LHH_DRIVER_UNINIT;
  CddAsm330lhh_InitStepType CompletedInitStep = CDDASM330LHH_INIT_STEP_WHO_AM_I;
  const uint8* RxBufferPtr = NULL_PTR;

  CDDASM330LHH_ENTER_CRITICAL();
  if (CddAsm330lhh_State.CompletionPending != FALSE)
  {
    CompletionPending = TRUE;
    CompletionSucceeded = CddAsm330lhh_State.CompletionSucceeded;
    CompletedMode = CddAsm330lhh_State.DriverMode;
    CompletedInitStep = CddAsm330lhh_State.InitStep;
    CddAsm330lhh_State.CompletionPending = FALSE;
    CddAsm330lhh_State.SpiState =
      (CompletionSucceeded != FALSE) ? CDDASM330LHH_SPI_IDLE : CDDASM330LHH_SPI_FAILED;
    CddAsm330lhh_State.PendingOp = CDDASM330LHH_OP_NONE;
  }
  CDDASM330LHH_EXIT_CRITICAL();

  if (CompletionPending == FALSE)
  {
    return;
  }

  if (CompletionSucceeded == FALSE)
  {
    CddAsm330lhh_FailOperation(CompletedMode);
    return;
  }

  RxBufferPtr = CddAsm330lhh_Com_GetRxBuffer();
  CddAsm330lhh_State.LastSpiTransferOk = TRUE;

  if (CompletedMode == CDDASM330LHH_DRIVER_INIT_TRANSFER)
  {
    if (CompletedInitStep == CDDASM330LHH_INIT_STEP_WHO_AM_I)
    {
      CDDASM330LHH_ENTER_CRITICAL();
      CddAsm330lhh_State.DeviceId = RxBufferPtr[1];
      CDDASM330LHH_EXIT_CRITICAL();
      if (CddAsm330lhh_State.DeviceId != CDDASM330LHH_EXPECTED_WHO_AM_I)
      {
        CddAsm330lhh_State.LastSpiTransferOk = FALSE;
        CddAsm330lhh_FailOperation(CompletedMode);
        CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_INIT, CDDASM330LHH_E_HW);
        return;
      }
    }

    CDDASM330LHH_ENTER_CRITICAL();
    CddAsm330lhh_State.InitStep = (CddAsm330lhh_InitStepType)(CompletedInitStep + 1u);
    if (CddAsm330lhh_State.InitStep == CDDASM330LHH_INIT_STEP_DONE)
    {
      CddAsm330lhh_State.Initialized = TRUE;
      CddAsm330lhh_State.InitStatus = CDDASM330LHH_INIT_READY;
      CddAsm330lhh_State.PowerMode = CDDASM330LHH_POWER_NORMAL;
      CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_READY;
    }
    else
    {
      CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_INIT_START;
    }
    CDDASM330LHH_EXIT_CRITICAL();
  }
  else if (CompletedMode == CDDASM330LHH_DRIVER_READ_TRANSFER)
  {
    CddAsm330lhh_DecodeLatestSample(RxBufferPtr);
  }
  else if ((CompletedMode == CDDASM330LHH_DRIVER_WRITE_TRANSFER) ||
           (CompletedMode == CDDASM330LHH_DRIVER_DEINIT_TRANSFER))
  {
    boolean DeInitComplete = FALSE;

    CDDASM330LHH_ENTER_CRITICAL();
    CddAsm330lhh_State.PendingWriteIndex++;
    if (CddAsm330lhh_State.PendingWriteIndex >= CddAsm330lhh_State.PendingWriteCount)
    {
      if (CddAsm330lhh_State.WriteAction == CDDASM330LHH_WRITE_ACCEL)
      {
        CddAsm330lhh_State.Ctrl1XlShadow = CddAsm330lhh_State.PendingCtrl1;
        CddAsm330lhh_State.ActiveAccelCfg = CddAsm330lhh_State.PendingAccelCfg;
      }
      else if (CddAsm330lhh_State.WriteAction == CDDASM330LHH_WRITE_GYRO)
      {
        CddAsm330lhh_State.Ctrl2GShadow = CddAsm330lhh_State.PendingCtrl2;
        CddAsm330lhh_State.ActiveGyroCfg = CddAsm330lhh_State.PendingGyroCfg;
      }
      else if (CddAsm330lhh_State.WriteAction == CDDASM330LHH_WRITE_POWER)
      {
        CddAsm330lhh_State.Ctrl1XlShadow = CddAsm330lhh_State.PendingCtrl1;
        CddAsm330lhh_State.Ctrl2GShadow = CddAsm330lhh_State.PendingCtrl2;
        CddAsm330lhh_State.PowerMode = CddAsm330lhh_State.RequestedPowerMode;
      }
      else if (CddAsm330lhh_State.WriteAction == CDDASM330LHH_WRITE_DEINIT)
      {
        DeInitComplete = TRUE;
        CddAsm330lhh_State.Initialized = FALSE;
        CddAsm330lhh_State.InitStatus = CDDASM330LHH_INIT_UNINITIALIZED;
        CddAsm330lhh_State.PowerMode = CDDASM330LHH_POWER_OFF;
        CddAsm330lhh_State.Ctrl1XlShadow = 0u;
        CddAsm330lhh_State.Ctrl2GShadow = 0u;
        CddAsm330lhh_State.Ctrl3CShadow = 0u;
        CddAsm330lhh_State.ConfigPtr = NULL_PTR;
      }

      CddAsm330lhh_State.PendingWriteCount = 0u;
      CddAsm330lhh_State.PendingWriteIndex = 0u;
      CddAsm330lhh_State.WriteAction = CDDASM330LHH_WRITE_NONE;
      CddAsm330lhh_State.DriverMode =
        (CompletedMode == CDDASM330LHH_DRIVER_DEINIT_TRANSFER) ?
        CDDASM330LHH_DRIVER_UNINIT : CDDASM330LHH_DRIVER_READY;
    }
    else
    {
      CddAsm330lhh_State.DriverMode =
        (CompletedMode == CDDASM330LHH_DRIVER_DEINIT_TRANSFER) ?
        CDDASM330LHH_DRIVER_DEINIT_START : CDDASM330LHH_DRIVER_WRITE_START;
    }
    CDDASM330LHH_EXIT_CRITICAL();
    if (DeInitComplete != FALSE)
    {
      CddAsm330lhh_Com_DeInit();
    }
  }
}

/*
*****************************************************************************
* Function: CddAsm330lhh_Init
* Purpose : Initialize module and configure sensor at startup.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_Init(const CddAsm330lhh_ConfigType* CfgPtr)
{
  Std_ReturnType Ret = E_NOT_OK;

  if ((CfgPtr != NULL_PTR) &&
      (CddAsm330lhh_ValidateAccelConfig(&CfgPtr->AccelInit) != FALSE) &&
      (CddAsm330lhh_ValidateGyroConfig(&CfgPtr->GyroInit) != FALSE))
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if ((CddAsm330lhh_StateValid == FALSE) ||
        (CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_UNINIT) ||
        (CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_FAILED) ||
        (CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_READY))
    {
      CddAsm330lhh_StateValid = TRUE;
      CddAsm330lhh_State.Initialized = FALSE;
      CddAsm330lhh_State.LastSpiTransferOk = FALSE;
      CddAsm330lhh_State.SpiState = CDDASM330LHH_SPI_IDLE;
      CddAsm330lhh_State.PendingOp = CDDASM330LHH_OP_NONE;
      CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_INIT_START;
      CddAsm330lhh_State.InitStatus = CDDASM330LHH_INIT_PENDING;
      CddAsm330lhh_State.InitStep = CDDASM330LHH_INIT_STEP_WHO_AM_I;
      CddAsm330lhh_State.CompletionPending = FALSE;
      CddAsm330lhh_State.CompletionSucceeded = FALSE;
      CddAsm330lhh_State.DataReady = FALSE;
      CddAsm330lhh_State.PowerMode = CDDASM330LHH_POWER_OFF;
      CddAsm330lhh_State.WriteAction = CDDASM330LHH_WRITE_NONE;
      CddAsm330lhh_State.PendingWriteCount = 0u;
      CddAsm330lhh_State.PendingWriteIndex = 0u;
      CddAsm330lhh_State.ConfigPtr = CfgPtr;
      CddAsm330lhh_State.ActiveAccelCfg = CfgPtr->AccelInit;
      CddAsm330lhh_State.ActiveGyroCfg = CfgPtr->GyroInit;
      CddAsm330lhh_State.Ctrl3CShadow = 0u;
      if (CfgPtr->EnableAutoIncrement != FALSE)
      {
        CddAsm330lhh_State.Ctrl3CShadow |= CDDASM330LHH_CTRL3_IF_INC;
      }
      if (CfgPtr->EnableBlockDataUpdate != FALSE)
      {
        CddAsm330lhh_State.Ctrl3CShadow |= CDDASM330LHH_CTRL3_BDU;
      }
      CddAsm330lhh_State.Ctrl1XlShadow =
        (uint8)(CddAsm330lhh_MapOdrToBits(CfgPtr->AccelInit.Odr) |
                CddAsm330lhh_MapAccelFsToBits(CfgPtr->AccelInit.FullScale));
      CddAsm330lhh_State.Ctrl2GShadow =
        (uint8)(CddAsm330lhh_MapOdrToBits(CfgPtr->GyroInit.Odr) |
                CddAsm330lhh_MapGyroFsToBits(CfgPtr->GyroInit.FullScale));
      CddAsm330lhh_State.StartRetryCount = 0u;
      Ret = E_OK;
    }
    CDDASM330LHH_EXIT_CRITICAL();

    if (Ret == E_OK)
    {
      CddAsm330lhh_Com_Init(CfgPtr);
    }
    else
    {
      CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_INIT, CDDASM330LHH_E_COMM);
    }
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_INIT, CDDASM330LHH_E_PARAM_CONFIG);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_GetInitStatus
* Purpose : Return current asynchronous initialization status.
*****************************************************************************
*/
CddAsm330lhh_InitStatusType CddAsm330lhh_GetInitStatus(void)
{
  CddAsm330lhh_InitStatusType Status = CDDASM330LHH_INIT_UNINITIALIZED;

  CDDASM330LHH_ENTER_CRITICAL();
  if (CddAsm330lhh_StateValid != FALSE)
  {
    Status = CddAsm330lhh_State.InitStatus;
  }
  CDDASM330LHH_EXIT_CRITICAL();

  return Status;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_DeInit
* Purpose : Queue asynchronous sensor shutdown.
*****************************************************************************
*/
void CddAsm330lhh_DeInit(void)
{
  const uint8 Registers[2] = { CDDASM330LHH_REG_CTRL1_XL, CDDASM330LHH_REG_CTRL2_G };
  const uint8 Values[2] = { 0u, 0u };

  if (CddAsm330lhh_QueueWrites(CDDASM330LHH_WRITE_DEINIT, Registers, Values, 2u,
                               NULL_PTR, NULL_PTR, CDDASM330LHH_POWER_OFF, 0u, 0u) != E_OK)
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_DEINIT, CDDASM330LHH_E_COMM);
  }
}

/*
*****************************************************************************
* Function: CddAsm330lhh_MainFunction
* Purpose : Process SPI completion events and advance asynchronous operations.
*****************************************************************************
*/
void CddAsm330lhh_MainFunction(void)
{
  Std_ReturnType Ret = E_OK;
  CddAsm330lhh_DriverModeType Mode;
  CddAsm330lhh_InitStepType InitStep;
  uint8 RegAddr = 0u;
  uint8 Data = 0u;
  uint8 Length = CDDASM330LHH_REG_SNAPSHOT_LEN;

  CDDASM330LHH_ENTER_CRITICAL();
  if (CddAsm330lhh_StateValid == FALSE)
  {
    CDDASM330LHH_EXIT_CRITICAL();
    return;
  }
  CDDASM330LHH_EXIT_CRITICAL();

  CddAsm330lhh_ProcessCompletion();

  CDDASM330LHH_ENTER_CRITICAL();
  Mode = CddAsm330lhh_State.DriverMode;
  InitStep = CddAsm330lhh_State.InitStep;
  if ((Mode == CDDASM330LHH_DRIVER_WRITE_START) ||
      (Mode == CDDASM330LHH_DRIVER_DEINIT_START))
  {
    RegAddr = CddAsm330lhh_State.PendingWriteReg[CddAsm330lhh_State.PendingWriteIndex];
    Data = CddAsm330lhh_State.PendingWriteValue[CddAsm330lhh_State.PendingWriteIndex];
  }
  CDDASM330LHH_EXIT_CRITICAL();

  if (Mode == CDDASM330LHH_DRIVER_INIT_START)
  {
    if (InitStep == CDDASM330LHH_INIT_STEP_WHO_AM_I)
    {
      Ret = CddAsm330lhh_StartTransfer(CDDASM330LHH_OP_READ_REG,
                                       CDDASM330LHH_DRIVER_INIT_TRANSFER,
                                       CDDASM330LHH_REG_WHO_AM_I, 0u, 0u);
    }
    else if (InitStep == CDDASM330LHH_INIT_STEP_CTRL3)
    {
      Ret = CddAsm330lhh_StartTransfer(CDDASM330LHH_OP_WRITE_REG,
                                       CDDASM330LHH_DRIVER_INIT_TRANSFER,
                                       CDDASM330LHH_REG_CTRL3_C,
                                       CddAsm330lhh_State.Ctrl3CShadow, 0u);
    }
    else if (InitStep == CDDASM330LHH_INIT_STEP_CTRL1)
    {
      Ret = CddAsm330lhh_StartTransfer(CDDASM330LHH_OP_WRITE_REG,
                                       CDDASM330LHH_DRIVER_INIT_TRANSFER,
                                       CDDASM330LHH_REG_CTRL1_XL,
                                       CddAsm330lhh_State.Ctrl1XlShadow, 0u);
    }
    else if (InitStep == CDDASM330LHH_INIT_STEP_CTRL2)
    {
      Ret = CddAsm330lhh_StartTransfer(CDDASM330LHH_OP_WRITE_REG,
                                       CDDASM330LHH_DRIVER_INIT_TRANSFER,
                                       CDDASM330LHH_REG_CTRL2_G,
                                       CddAsm330lhh_State.Ctrl2GShadow, 0u);
    }
    else
    {
      CDDASM330LHH_ENTER_CRITICAL();
      CddAsm330lhh_State.Initialized = TRUE;
      CddAsm330lhh_State.InitStatus = CDDASM330LHH_INIT_READY;
      CddAsm330lhh_State.PowerMode = CDDASM330LHH_POWER_NORMAL;
      CddAsm330lhh_State.LastSpiTransferOk = TRUE;
      CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_READY;
      CDDASM330LHH_EXIT_CRITICAL();
    }
  }
  else if (Mode == CDDASM330LHH_DRIVER_READ_START)
  {
    Ret = CddAsm330lhh_StartTransfer(CDDASM330LHH_OP_READ_BURST,
                                     CDDASM330LHH_DRIVER_READ_TRANSFER,
                                     CDDASM330LHH_REG_STATUS_REG, 0u, Length);
  }
  else if ((Mode == CDDASM330LHH_DRIVER_WRITE_START) ||
           (Mode == CDDASM330LHH_DRIVER_DEINIT_START))
  {
    CddAsm330lhh_DriverModeType TransferMode =
      (Mode == CDDASM330LHH_DRIVER_DEINIT_START) ?
      CDDASM330LHH_DRIVER_DEINIT_TRANSFER : CDDASM330LHH_DRIVER_WRITE_TRANSFER;
    Ret = CddAsm330lhh_StartTransfer(CDDASM330LHH_OP_WRITE_REG,
                                     TransferMode, RegAddr, Data, 0u);
  }

  if ((Ret != E_OK) &&
      ((Mode == CDDASM330LHH_DRIVER_INIT_START) ||
       (Mode == CDDASM330LHH_DRIVER_READ_START) ||
       (Mode == CDDASM330LHH_DRIVER_WRITE_START) ||
       (Mode == CDDASM330LHH_DRIVER_DEINIT_START)))
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if (CddAsm330lhh_State.StartRetryCount >= CDDASM330LHH_SPI_START_RETRY_LIMIT)
    {
      CDDASM330LHH_EXIT_CRITICAL();
      CddAsm330lhh_FailOperation(Mode);
    }
    else
    {
      CDDASM330LHH_EXIT_CRITICAL();
    }
  }
}

/*
*****************************************************************************
* Function: CddAsm330lhh_GetDeviceId
* Purpose : Read sensor WHO_AM_I.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_GetDeviceId(uint8* DeviceIdPtr)
{
  Std_ReturnType Ret = E_NOT_OK;

  if (DeviceIdPtr != NULL_PTR)
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if ((CddAsm330lhh_StateValid != FALSE) &&
        (CddAsm330lhh_State.InitStatus == CDDASM330LHH_INIT_READY))
    {
      *DeviceIdPtr = CddAsm330lhh_State.DeviceId;
      Ret = E_OK;
    }
    CDDASM330LHH_EXIT_CRITICAL();
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_GETDEVICEID, CDDASM330LHH_E_PARAM_POINTER);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_SetPowerMode
* Purpose : Enable or disable output data generation.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_SetPowerMode(CddAsm330lhh_PowerModeType PowerMode)
{
  Std_ReturnType Ret = E_NOT_OK;
  uint8 Ctrl1Xl = 0u;
  uint8 Ctrl2G = 0u;
  const uint8 Registers[2] = { CDDASM330LHH_REG_CTRL1_XL, CDDASM330LHH_REG_CTRL2_G };
  uint8 Values[2] = { 0u, 0u };

  if ((PowerMode == CDDASM330LHH_POWER_OFF) ||
      (PowerMode == CDDASM330LHH_POWER_NORMAL))
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if (CddAsm330lhh_StateValid != FALSE)
    {
      Ctrl1Xl = (uint8)(CddAsm330lhh_State.Ctrl1XlShadow & (uint8)(~CDDASM330LHH_MASK_ODR));
      Ctrl2G = (uint8)(CddAsm330lhh_State.Ctrl2GShadow & (uint8)(~CDDASM330LHH_MASK_ODR));

      if (PowerMode == CDDASM330LHH_POWER_NORMAL)
      {
        Ctrl1Xl |= CddAsm330lhh_MapOdrToBits(CddAsm330lhh_State.ActiveAccelCfg.Odr);
        Ctrl2G |= CddAsm330lhh_MapOdrToBits(CddAsm330lhh_State.ActiveGyroCfg.Odr);
      }
    }
    CDDASM330LHH_EXIT_CRITICAL();
    if (CddAsm330lhh_StateValid != FALSE)
    {
      Values[0] = Ctrl1Xl;
      Values[1] = Ctrl2G;
      Ret = CddAsm330lhh_QueueWrites(CDDASM330LHH_WRITE_POWER, Registers, Values, 2u,
                                     NULL_PTR, NULL_PTR, PowerMode, Ctrl1Xl, Ctrl2G);
    }
    if (Ret != E_OK)
    {
      CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_SETPOWERMODE, CDDASM330LHH_E_COMM);
    }
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_SETPOWERMODE, CDDASM330LHH_E_PARAM_CONFIG);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ConfigureAccel
* Purpose : Apply accelerometer ODR/full-scale setup.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ConfigureAccel(const CddAsm330lhh_AccelConfigType* AccelCfgPtr)
{
  Std_ReturnType Ret = E_NOT_OK;
  uint8 NewCtrl1;
  const uint8 Register = CDDASM330LHH_REG_CTRL1_XL;

  if (CddAsm330lhh_ValidateAccelConfig(AccelCfgPtr) != FALSE)
  {
    NewCtrl1 = (uint8)(CddAsm330lhh_MapOdrToBits(AccelCfgPtr->Odr) |
                       CddAsm330lhh_MapAccelFsToBits(AccelCfgPtr->FullScale));
    Ret = CddAsm330lhh_QueueWrites(CDDASM330LHH_WRITE_ACCEL, &Register, &NewCtrl1, 1u,
                                   AccelCfgPtr, NULL_PTR, CDDASM330LHH_POWER_OFF,
                                   NewCtrl1, 0u);
    if (Ret != E_OK)
    {
      CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_CONFIGACCEL, CDDASM330LHH_E_COMM);
    }
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_CONFIGACCEL, CDDASM330LHH_E_PARAM_CONFIG);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ConfigureGyro
* Purpose : Apply gyroscope ODR/full-scale setup.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ConfigureGyro(const CddAsm330lhh_GyroConfigType* GyroCfgPtr)
{
  Std_ReturnType Ret = E_NOT_OK;
  uint8 NewCtrl2;
  const uint8 Register = CDDASM330LHH_REG_CTRL2_G;

  if (CddAsm330lhh_ValidateGyroConfig(GyroCfgPtr) != FALSE)
  {
    NewCtrl2 = (uint8)(CddAsm330lhh_MapOdrToBits(GyroCfgPtr->Odr) |
                       CddAsm330lhh_MapGyroFsToBits(GyroCfgPtr->FullScale));
    Ret = CddAsm330lhh_QueueWrites(CDDASM330LHH_WRITE_GYRO, &Register, &NewCtrl2, 1u,
                                   NULL_PTR, GyroCfgPtr, CDDASM330LHH_POWER_OFF,
                                   0u, NewCtrl2);
    if (Ret != E_OK)
    {
      CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_CONFIGGYRO, CDDASM330LHH_E_COMM);
    }
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_CONFIGGYRO, CDDASM330LHH_E_PARAM_CONFIG);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ReadRawData
* Purpose : Read and decode one complete sensor sample.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ReadRawData(CddAsm330lhh_RawDataType* RawDataPtr)
{
  Std_ReturnType Ret = E_NOT_OK;

  if (RawDataPtr != NULL_PTR)
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if ((CddAsm330lhh_StateValid != FALSE) &&
        (CddAsm330lhh_State.DataReady != FALSE))
    {
      *RawDataPtr = CddAsm330lhh_State.LatestRawData;
      CddAsm330lhh_State.DataReady = FALSE;
      CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_READY;
      Ret = E_OK;
    }
    CDDASM330LHH_EXIT_CRITICAL();
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_READRAWDATA, CDDASM330LHH_E_PARAM_POINTER);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_ReadScaledData
* Purpose : Convert raw sample to engineering units.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_ReadScaledData(CddAsm330lhh_ScaledDataType* ScaledDataPtr)
{
  return CddAsm330lhh_GetLatestSample(ScaledDataPtr);
}

Std_ReturnType CddAsm330lhh_StartRead(void)
{
  Std_ReturnType Ret = E_NOT_OK;

  CDDASM330LHH_ENTER_CRITICAL();
  if ((CddAsm330lhh_StateValid != FALSE) &&
      (CddAsm330lhh_State.Initialized != FALSE) &&
      ((CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_READ_START) ||
       (CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_READ_TRANSFER)))
  {
    Ret = E_OK;
  }
  else if ((CddAsm330lhh_State.Initialized != FALSE) &&
           (CddAsm330lhh_State.DriverMode == CDDASM330LHH_DRIVER_READY) &&
           (CddAsm330lhh_State.DataReady == FALSE))
  {
    CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_READ_START;
    CddAsm330lhh_State.StartRetryCount = 0u;
    Ret = E_OK;
  }
  CDDASM330LHH_EXIT_CRITICAL();

  if (Ret != E_OK)
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_READRAWDATA, CDDASM330LHH_E_COMM);
  }

  return Ret;
}

Std_ReturnType CddAsm330lhh_GetLatestSample(CddAsm330lhh_ScaledDataType* SamplePtr)
{
  Std_ReturnType Ret = E_NOT_OK;

  if (SamplePtr != NULL_PTR)
  {
    CDDASM330LHH_ENTER_CRITICAL();
    if ((CddAsm330lhh_StateValid != FALSE) &&
        (CddAsm330lhh_State.DataReady != FALSE))
    {
      *SamplePtr = CddAsm330lhh_State.LatestScaledData;
      CddAsm330lhh_State.DataReady = FALSE;
      CddAsm330lhh_State.DriverMode = CDDASM330LHH_DRIVER_READY;
      Ret = E_OK;
    }
    CDDASM330LHH_EXIT_CRITICAL();
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_READSCALEDDATA, CDDASM330LHH_E_PARAM_POINTER);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_RunBasicSelfTest
* Purpose : Minimal diagnostic check based on WHO_AM_I readback.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_RunBasicSelfTest(boolean* PassedPtr)
{
  uint8 DeviceId = 0u;
  Std_ReturnType Ret = E_NOT_OK;

  if (PassedPtr != NULL_PTR)
  {
    Ret = CddAsm330lhh_GetDeviceId(&DeviceId);
    if (Ret == E_OK)
    {
      *PassedPtr = (boolean)(DeviceId == CDDASM330LHH_EXPECTED_WHO_AM_I);
    }
    else
    {
      *PassedPtr = FALSE;
    }
  }
  else
  {
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_SELFTEST, CDDASM330LHH_E_PARAM_POINTER);
  }

  return Ret;
}

/*
*****************************************************************************
* Function: CddAsm330lhh_IsInitialized
* Purpose : Return module initialization flag.
*****************************************************************************
*/
boolean CddAsm330lhh_IsInitialized(void)
{
  boolean Initialized;
  CDDASM330LHH_ENTER_CRITICAL();
  Initialized = (CddAsm330lhh_StateValid != FALSE) ?
                CddAsm330lhh_State.Initialized : FALSE;
  CDDASM330LHH_EXIT_CRITICAL();
  return Initialized;
}

#if 0 /* Superseded by the sequence-end callback below. */
/*
*****************************************************************************
* Legacy job callback retained only as migration reference.
*****************************************************************************
*/
void CddAsm330lhh_NotifySpiJobEnd(boolean Success)
{
  Spi_JobResultType JobResult = SPI_JOB_FAILED;
  const uint8* RxBufferPtr = NULL_PTR;
  uint8 Index = 0u;

  CDDASM330LHH_ENTER_CRITICAL();

  /*
  ***************************************************************************
  * Query AUTOSAR SPI module for actual job result status.
  ***************************************************************************
  */
  JobResult = Spi_GetJobResult(CDDASM330LHH_SPI_JOB_ID);

  if ((JobResult == SPI_JOB_OK) && (Success == TRUE))
  {
    /*
    *************************************************************************
    * SPI transfer completed successfully. Extract data based on pending op.
    *************************************************************************
    */
    RxBufferPtr = CddAsm330lhh_Com_GetRxBuffer();

    if (CddAsm330lhh_State.PendingOp == CDDASM330LHH_OP_READ_REG)
    {
      /*
      ***********************************************************************
      * Single register read: data is in RxBuffer[1].
      * Store in the internal raw data buffer for later extraction.
      ***********************************************************************
      */
      if (RxBufferPtr != NULL_PTR)
      {
        CddAsm330lhh_State.RawDataBuffer[0] = RxBufferPtr[1];
      }
    }
    else if (CddAsm330lhh_State.PendingOp == CDDASM330LHH_OP_READ_BURST)
    {
      /*
      ***********************************************************************
      * Burst read: skip header byte, copy remaining data to state buffer.
      ***********************************************************************
      */
      if (RxBufferPtr != NULL_PTR)
      {
        for (Index = 0u; Index < CDDASM330LHH_REG_SNAPSHOT_LEN; Index++)
        {
          CddAsm330lhh_State.RawDataBuffer[Index] = RxBufferPtr[(uint8)(Index + 1u)];
        }
      }
    }

    CddAsm330lhh_State.SpiState = CDDASM330LHH_SPI_IDLE;
    CddAsm330lhh_State.PendingOp = CDDASM330LHH_OP_NONE;
  }
  else
  {
    /*
    *************************************************************************
    * SPI transfer failed. Mark state as failed.
    *************************************************************************
    */
    CddAsm330lhh_State.SpiState = CDDASM330LHH_SPI_FAILED;
    CddAsm330lhh_ReportDetError(CDDASM330LHH_SID_MAINFUNCTION, CDDASM330LHH_E_COMM);
  }

  CDDASM330LHH_EXIT_CRITICAL();
}
#endif

void CddAsm330lhh_SequenceEndNotification(void)
{
  Spi_SeqResultType SequenceResult;

  SequenceResult = Spi_GetSequenceResult(CDDASM330LHH_SPI_SEQUENCE_ID);
  CDDASM330LHH_ENTER_CRITICAL();
  if (CddAsm330lhh_State.SpiState == CDDASM330LHH_SPI_PENDING)
  {
    CddAsm330lhh_State.CompletionSucceeded = (boolean)(SequenceResult == SPI_SEQ_OK);
    CddAsm330lhh_State.CompletionPending = TRUE;
  }
  CDDASM330LHH_EXIT_CRITICAL();
}

#define ctadCddAsm330lhh_STOP_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>
