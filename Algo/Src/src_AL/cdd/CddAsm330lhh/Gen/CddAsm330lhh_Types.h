/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_Types.h
* Description:
*   Internal constants and state representation used by driver core/COM layers.
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_TYPES_2026_07_07_H_
#define CDD_ASM330LHH_TYPES_2026_07_07_H_

#include <Std_Types.h>
#include <../Api/CddAsm330lhh.h>

/*
*****************************************************************************
* Register map and bit masks used by CDD low-level access
*****************************************************************************
*/
#define CDDASM330LHH_REG_WHO_AM_I          (0x0Fu)
#define CDDASM330LHH_REG_CTRL1_XL          (0x10u)
#define CDDASM330LHH_REG_CTRL2_G           (0x11u)
#define CDDASM330LHH_REG_CTRL3_C           (0x12u)
#define CDDASM330LHH_REG_STATUS_REG        (0x1Eu)
#define CDDASM330LHH_REG_OUT_TEMP_L        (0x20u)

#define CDDASM330LHH_SPI_READ_MASK         (0x80u)

#define CDDASM330LHH_CTRL3_SW_RESET        (0x01u)
#define CDDASM330LHH_CTRL3_IF_INC          (0x04u)
#define CDDASM330LHH_CTRL3_BDU             (0x40u)

#define CDDASM330LHH_MASK_ODR              (0xF0u)
#define CDDASM330LHH_MASK_ACCEL_FS         (0x0Cu)
#define CDDASM330LHH_MASK_GYRO_FS          (0x0Eu)

/*
*****************************************************************************
* Enumeration: CddAsm330lhh_SpiStateType
* Purpose  : Async SPI transfer state machine tracking.
*****************************************************************************
*/
typedef enum
{
  CDDASM330LHH_SPI_IDLE = 0u,
  CDDASM330LHH_SPI_PENDING,
  CDDASM330LHH_SPI_FAILED
} CddAsm330lhh_SpiStateType;

/*
*****************************************************************************
* Enumeration: CddAsm330lhh_PendingOpType
* Purpose  : Track which operation is awaiting SPI completion.
*****************************************************************************
*/
typedef enum
{
  CDDASM330LHH_OP_NONE = 0u,
  CDDASM330LHH_OP_READ_REG,
  CDDASM330LHH_OP_WRITE_REG,
  CDDASM330LHH_OP_READ_BURST
} CddAsm330lhh_PendingOpType;

typedef enum
{
  CDDASM330LHH_DRIVER_UNINIT = 0u,
  CDDASM330LHH_DRIVER_INIT_START,
  CDDASM330LHH_DRIVER_INIT_TRANSFER,
  CDDASM330LHH_DRIVER_READY,
  CDDASM330LHH_DRIVER_READ_START,
  CDDASM330LHH_DRIVER_READ_TRANSFER,
  CDDASM330LHH_DRIVER_SAMPLE_READY,
  CDDASM330LHH_DRIVER_WRITE_START,
  CDDASM330LHH_DRIVER_WRITE_TRANSFER,
  CDDASM330LHH_DRIVER_DEINIT_START,
  CDDASM330LHH_DRIVER_DEINIT_TRANSFER,
  CDDASM330LHH_DRIVER_FAILED
} CddAsm330lhh_DriverModeType;

typedef enum
{
  CDDASM330LHH_INIT_STEP_WHO_AM_I = 0u,
  CDDASM330LHH_INIT_STEP_CTRL3,
  CDDASM330LHH_INIT_STEP_CTRL1,
  CDDASM330LHH_INIT_STEP_CTRL2,
  CDDASM330LHH_INIT_STEP_DONE
} CddAsm330lhh_InitStepType;

typedef enum
{
  CDDASM330LHH_WRITE_NONE = 0u,
  CDDASM330LHH_WRITE_ACCEL,
  CDDASM330LHH_WRITE_GYRO,
  CDDASM330LHH_WRITE_POWER,
  CDDASM330LHH_WRITE_DEINIT
} CddAsm330lhh_WriteActionType;

/*
*****************************************************************************
* Structure: CddAsm330lhh_DriverStateType
* Purpose  : Runtime state machine, register shadow values, and SPI context.
*****************************************************************************
*/
typedef struct
{
  boolean Initialized;
  boolean LastSpiTransferOk;
  CddAsm330lhh_SpiStateType SpiState;
  CddAsm330lhh_PendingOpType PendingOp;
  CddAsm330lhh_DriverModeType DriverMode;
  CddAsm330lhh_InitStepType InitStep;
  CddAsm330lhh_WriteActionType WriteAction;
  CddAsm330lhh_InitStatusType InitStatus;
  CddAsm330lhh_PowerModeType RequestedPowerMode;
  boolean CompletionPending;
  boolean CompletionSucceeded;
  boolean DataReady;
  CddAsm330lhh_PowerModeType PowerMode;
  uint8 DeviceId;
  uint8 Ctrl1XlShadow;
  uint8 Ctrl2GShadow;
  uint8 Ctrl3CShadow;
  CddAsm330lhh_AccelConfigType ActiveAccelCfg;
  CddAsm330lhh_GyroConfigType ActiveGyroCfg;
  const CddAsm330lhh_ConfigType* ConfigPtr;
  uint8 RawDataBuffer[16];
  CddAsm330lhh_RawDataType LatestRawData;
  CddAsm330lhh_ScaledDataType LatestScaledData;
  uint8 PendingWriteCount;
  uint8 PendingWriteIndex;
  uint8 PendingWriteReg[2];
  uint8 PendingWriteValue[2];
  uint16 StartRetryCount;
  uint8 PendingCtrl1;
  uint8 PendingCtrl2;
  CddAsm330lhh_AccelConfigType PendingAccelCfg;
  CddAsm330lhh_GyroConfigType PendingGyroCfg;
} CddAsm330lhh_DriverStateType;

#endif /* CDD_ASM330LHH_TYPES_2026_07_07_H_ */
