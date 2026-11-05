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
/// \file  CddTle94x1_Regs.h
///
/// \brief  SBC complex device driver
///
/// \descr  System Basic Chip
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan@marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TLE94X1_REGS_2021_03_08_H_
#define CDD_TLE94X1_REGS_2021_03_08_H_

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>

//=============================================================================
// Default Definitions
//=============================================================================

// CONTROL REGISTERS - Read/Write
// General Control Registers
#define  CDDTLE94X1_REGS_M_S_CTRL_ADR                 0x01U // Mode- and Supply Control
#define  CDDTLE94X1_REGS_HW_CTRL_0_ADR                0x02U // Mode- and Supply Control 0
#define  CDDTLE94X1_REGS_WD_CTRL_ADR                  0x03U // Watchdog Control
#define  CDDTLE94X1_REGS_BUS_CTRL_0_ADR               0x04U // Bus Control 0
#define  CDDTLE94X1_REGS_WK_CTRL_0_ADR                0x06U // Internal Wake Input Control 0
#define  CDDTLE94X1_REGS_WK_CTRL_1_ADR                0x07U // External Wake Source Control 1
#define  CDDTLE94X1_REGS_WK_PUPD_CTRL_ADR             0x08U // Wake Input Level Control
#define  CDDTLE94X1_REGS_BUS_CTRL_3_ADR               0x0BU // Bus Control 3
#define  CDDTLE94X1_REGS_TIMER_CTRL_ADR               0x0CU // Timer Control 0
#define  CDDTLE94X1_REGS_HW_CTRL_1_ADR                0x0EU // Hardware Control 1
#define  CDDTLE94X1_REGS_HW_CTRL_2_ADR                0x0FU // Hardware Control 2
#define  CDDTLE94X1_REGS_GPIO_CTRL_ADR                0x17U // GPIO Configuration Control
#define  CDDTLE94X1_REGS_PWM_CTRL_ADR                 0x18U // PWM Configuration Control
#define  CDDTLE94X1_REGS_PWM_FREQ_CTRL_ADR            0x1CU // PWM Frequency Configuration Control
#define  CDDTLE94X1_REGS_HW_CTRL_3_ADR                0x1DU // Hardware Control 3
#define  CDDTLE94X1_REGS_SYS_STAT_CTRL_0_ADR          0x1EU // System Status Control Low Byte
#define  CDDTLE94X1_REGS_SYS_STAT_CTRL_1_ADR          0x1FU // System Status Control High Byte

// Selective Wake Control Registers
#define  CDDTLE94X1_REGS_SWK_CTRL_ADR                 0x20U // CAN Selective Wake Control
#define  CDDTLE94X1_REGS_SWK_BTL0_CTRL_ADR            0x21U // SWK Bit Timing Logic Control1
#define  CDDTLE94X1_REGS_SWK_BTL1_CTRL_ADR            0x22U // SWK Bit Timing Logic Control2
#define  CDDTLE94X1_REGS_SWK_ID3_CTRL_ADR             0x23U // SWK WUF Identifier bits 28...21
#define  CDDTLE94X1_REGS_SWK_ID2_CTRL_ADR             0x24U // SWK WUF Identifier bits 20...13
#define  CDDTLE94X1_REGS_SWK_ID0_CTRL_ADR             0x26U // SWK WUF Identifier bits 4...0
#define  CDDTLE94X1_REGS_SWK_MASK_ID3_CTRL_ADR        0x27U // SWK WUF Identifier Mask bits 28...21
#define  CDDTLE94X1_REGS_SWK_MASK_ID2_CTRL_ADR        0x28U // SWK WUF Identifier Mask bits 20...13
#define  CDDTLE94X1_REGS_SWK_ID1_CTRL_ADR             0x25U // SWK WUF Identifier bits 12...5
#define  CDDTLE94X1_REGS_SWK_MASK_ID1_CTRL_ADR        0x29U // SWK WUF Identifier Mask bits 12...5
#define  CDDTLE94X1_REGS_SWK_MASK_ID0_CTRL_ADR        0x2AU // SWK WUF Identifier Mask bits 4...0
#define  CDDTLE94X1_REGS_SWK_DLC_CTRL_ADR             0x2BU // SWK Frame Data Length Code Control
#define  CDDTLE94X1_REGS_SWK_DATA7_CTRL               0x2CU // SWK Datat7 Register
#define  CDDTLE94X1_REGS_SWK_DATA6_CTRL               0x2DU // SWK Datat6 Register
#define  CDDTLE94X1_REGS_SWK_DATA5_CTRL               0x2EU // SWK Datat5 Register
#define  CDDTLE94X1_REGS_SWK_DATA4_CTRL               0x2FU // SWK Datat4 Register
#define  CDDTLE94X1_REGS_SWK_DATA3_CTRL               0x30U // SWK Datat3 Register
#define  CDDTLE94X1_REGS_SWK_DATA2_CTRL               0x31U // SWK Datat2 Register
#define  CDDTLE94X1_REGS_SWK_DATA1_CTRL               0x32U // SWK Datat1 Register
#define  CDDTLE94X1_REGS_SWK_DATA0_CTRL               0x33U // SWK Datat0 Register
#define  CDDTLE94X1_REGS_SWK_CAN_FD_CTRL              0x34U // CAN FD Configuration Control Register
#define  CDDTLE94X1_REGS_SWK_OSC_TRIM_CTRL            0x38U // SWK Oscillator Trimming Register
#define  CDDTLE94X1_REGS_SWK_OPT_CTRL                 0x39U // Selective Wake Options Register
#define  CDDTLE94X1_REGS_SWK_OSC_CAL_H_STAT           0x3AU // SWK Oscillator Calibration High Register
#define  CDDTLE94X1_REGS_SWK_OSC_CAL_L_STAT           0x3BU // SWK Oscillator Calibration Low Register
#define  CDDTLE94X1_REGS_SWK_CDR_CTRL1                0x3CU // CDR Control 1 Register
#define  CDDTLE94X1_REGS_SWK_CDR_CTRL2                0x3DU // CDR Control 2 Register
#define  CDDTLE94X1_REGS_SWK_CDR_LIMIT_HIGH_CTRL      0x3EU // SWK CDR Upper Limit Control
#define  CDDTLE94X1_REGS_SWK_CDR_LIMIT_LOW_CTRL       0x3FU // SWK CDR Lower Limit Control


// STATUS REGISTERS - Read/Clear
// General Status Registers
#define  CDDTLE94X1_REGS_SUP_STAT_1_ADR               0x40U // Supply Voltage Fail Status 1
#define  CDDTLE94X1_REGS_SUP_STAT_0_ADR               0x41U // Supply Voltage Fail Status 0
#define  CDDTLE94X1_REGS_THERM_STAT_ADR               0x42U // Thermal Protection Status
#define  CDDTLE94X1_REGS_DEV_STAT_ADR                 0x43U // Device Information Status
#define  CDDTLE94X1_REGS_BUS_STAT_ADR                 0x44U // Bus Communication Status 0
#define  CDDTLE94X1_REGS_WK_STAT_0_ADR                0x46U // Wake-up Source and Information Status 0
#define  CDDTLE94X1_REGS_WK_STAT_1_ADR                0x47U // Wake-up Source and Information Status 1
#define  CDDTLE94X1_REGS_WK_LVL_STAT_ADR              0x48U // Wake-up Input Level - !!! READ ONLY
#define  CDDTLE94X1_REGS_GPIO_OC_STAT_ADR             0x54U // GPIO Overcurrent Status
#define  CDDTLE94X1_REGS_GPIO_OL_STAT_ADR             0x55U // GPIO Open-Load Status

// Selective Wake Status Registers
#define  CDDTLE94X1_REGS_SWK_STAT                     0x70U // Selective Wake Status
#define  CDDTLE94X1_REGS_SWK_ECNT_STAT                0x71U // SWK Status
#define  CDDTLE94X1_REGS_SWK_CDR_STAT1                0x72U // CDR Status 1 Register
#define  CDDTLE94X1_REGS_SWK_CDR_STAT2                0x73U // CDR Status 2 Register

// FAMILY AND PRODUCT INFORMATION REGISTER - Read ONLY
#define  CDDTLE94X1_REGS_FAM_PROD_STAT_ADR            0x7EU // Family and Product Identification Register

//*****************************************************************************
//                    C O N T R O L  R E G I S T E R S
//*****************************************************************************

typedef struct
{
  uint8 bVCC1_RT       : 2; // VCC1 Reset Threshold Control
  uint8 bVCC1_OV_RST   : 1; // VCC1 Over Voltage leading to Reset / Fail-Safe Mode enable
  uint8 bVCC2_ON       : 2; // VCC2 Mode Control
  uint8 bReserved_1    : 1; // Reserved, always reads as 0
  uint8 bMODE          : 2; // SBC Mode Control

} tsTle94x1_Reg_M_S_CTRL_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  { 
    tsTle94x1_Reg_M_S_CTRL_Bit   sBit; // bit access to the register data
    uint8                        ucWord;// word access to the register data
  } uData;
} tsTle94x1_Access_M_S_CTRL_Register;

//-----------------------------------------------------------------------------

typedef struct 
{
  uint8 bCFG1           : 1; // Configuration Select 1
  uint8 bReserved_1     : 1; // Reserved, always reads as 0
  uint8 bCP_EN          : 1; // Charge Pump Output Enable
  uint8 bReserved_2     : 2; // Reserved, always reads as 0
  uint8 bFO_ON          : 1; // Failure Output activation
  uint8 bSOFT_RESET_RST : 1; // Soft Reset Configuration
  uint8 bReserved_1_1   : 1; // Reserved, always reads as 0

} tsTle94x1_Reg_HW_CTRL_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  { 
    tsTle94x1_Reg_HW_CTRL_0_Bit   sBit; // bit access to the register data
    uint8                         ucWord;// word access to the register data
  } uData;
} tsTle94x1_Access_HW_CTRL_0_Register;

//-----------------------------------------------------------------------------

typedef struct 
{
  uint8 bWD_TIMER        : 3; // Watchdog Timer Period
  uint8 bReserved_1      : 1; // Reserved, always reads as 0
  uint8 bWD_EN_WK_BUS    : 1; // Watchdog Enable after Bus (CAN) Wake-up in SBC Stop Mode
  uint8 bWD_WIN          : 1; // Watchdog Type Selection
  uint8 bWD_STM_EN_0     : 1; // Watchdog Deactivation during Stop Mode, bit 0
  uint8 bCHECKSUM        : 1; // Watchdog Setting Check Sum Bit
} tsTle94x1_Reg_WD_CTRL_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  { 
    tsTle94x1_Reg_WD_CTRL_Bit   sBit;  // bit access to the register data
    uint8                       ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_WD_CTRL_Register;

//-----------------------------------------------------------------------------

typedef struct 
{
  uint8 bCAN           : 2; // HS-CAN Module Modes
  uint8 bReserved_6    : 6; // Reserved, always reads as 0
} tsTle94x1_Reg_BUS_CTRL_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  { 
    tsTle94x1_Reg_BUS_CTRL_0_Bit  sBit;   // bit access to the register data
    uint8                         ucWord;  // word access to the register data
  } uData;
} tsTle94x1_Access_BUS_CTRL_0_Register;

//-----------------------------------------------------------------------------

typedef struct 
{
  uint8 bReserved_2    : 2; // Reserved, always reads as 0
  uint8 bWD_STM_EN_1   : 1; // Watchdog Deactivation during Stop Mode, bit 1
  uint8 bReserved_3    : 3; // Reserved, always reads as 0
  uint8 bTIMER_WK_EN   : 1; // Wake Source Control (for cyclic wake)
  uint8 bReserved_1    : 1; // Reserved, always reads as 0

} tsTle94x1_Reg_WK_CTRL_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  { 
    tsTle94x1_Reg_WK_CTRL_0_Bit   sBit;  // bit access to the register data
    uint8                         ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_WK_CTRL_0_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bWK_EN         : 1; // WK Wake Source Control
  uint8 bReserved_4    : 4; // Reserved, always reads as 0
  uint8 bWK_MEAS       : 1; // Wake / Voltage Sensing Selection
  uint8 bReserved_1    : 1; // Reserved, always reads as 0
  uint8 bINT_GLOBAL    : 1; // Global Interrupt Configuration

} tsTle94x1_Reg_WK_CTRL_1_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_WK_CTRL_1_Bit   sBit;  // bit access to the register data
    uint8                         ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_WK_CTRL_1_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bWK_PUPD       : 2;  // WK Pull-Up / Pull-Down Configuration
  uint8 bReserved_4    : 4;  // Reserved, always reads as 0
  uint8 bGPIO_WK_PUPD  : 2;  // GPIO WK Pull-Up / Pull-Down Configuration
} tsTle94x1_Reg_WK_PUPD_CTRL_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  { 
    tsTle94x1_Reg_WK_PUPD_CTRL_Bit  sBit;  // bit access to the register data
    uint8                           ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_WK_PUPD_CTRL_Register;

//-----------------------------------------------------------------------------

typedef struct 
{
  uint8 bReserved_4    : 4; // Reserved, always reads as 0
  uint8 bCAN_FLASH     : 1; // HS-CAN Flash Mode activation
  uint8 bReserved_3    : 3; // Reserved, always reads as 0
} tsTle94x1_Reg_BUS_CTRL_3_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_BUS_CTRL_3_Bit  sBit;  // bit access to the register data
    uint8                         ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_BUS_CTRL_3_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bReserved_3 : 3;  // Reserved, always reads as 0
  uint8 bCFG_LOCK_0 : 1;  // Configuration Lock Bit -Level 0
  uint8 bRSTN_DEL   : 1;  // Reset Delay Time Selection
  uint8 bTSD2_DEL   : 1;  // TSD2 Minumum Waiting Time Selection
  uint8 bReserved_1 : 1;  // Reserved, always reads as 0
  uint8 bRSTN_HYS   : 1;  // VCC1 Undervoltag Reset Hysteresis Selection
} tsTle94x1_Reg_HW_CTRL_1_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_HW_CTRL_1_Bit   sBit;  // bit access to the register data
    uint8                         ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_HW_CTRL_1_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bCFG_LOCK_1    : 1; // Configuration Lock Bit - Level 1
  uint8 bReserved_1    : 1; // Reserved, always reads as 0
  uint8 bSS_MOD_FR     : 2; // Spread Spectrum Modulation Frequency Setting of intergrated
  uint8 bI_PEAK_TH     : 1; // VCC1 Active Peak Threshold Selction
  uint8 bTwoMHZ_FREQ   : 3; // SMPS and Charge Pump Switching Frequency Setting
} tsTle94x1_Reg_HW_CTRL_2_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_HW_CTRL_2_Bit  sBit;  // bit access to the register data
    uint8                        ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_HW_CTRL_2_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bGPIO        : 3; // GPIO Configuration
  uint8 bReserved_5  : 5; // Reserved, always reads as 0
} tsTle94x1_Reg_GPIO_CTRL_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_GPIO_CTRL_Bit  sBit;  // bit access to the register data
    uint8                        ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_GPIO_CTRL_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bPWM_DC           : 8; // GPIO Configuration
} tsTle94x1_Reg_PWM_CTRL_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_PWM_CTRL_Bit   sBit;  // bit access to the register data
    uint8                        ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_PWM_CTRL_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bICC1_LIM_ADJ   : 2; // Confgiration of ICC1 current limitation
  uint8 bTSD_THR        : 1; // Thermal Shutdown Threshold (TSD1& TSD2) Configuration
  uint8 bReserved_5     : 5; // Reserved, always reads as 0
} tsTle94x1_Reg_HW_CTRL_3_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_HW_CTRL_3_Bit   sBit;  // bit access to the register data
    uint8                         ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_HW_CTRL_3_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bTIMER_PER     : 4; // Timer Period Configuration
  uint8 bTIMER_ON      : 3; // Timer On-Time Configruation
  uint8 bReserved_1    : 1; // Reserved, always reads as 0

} tsTle94x1_Reg_TIMER_CTRL_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_TIMER_CTRL_0_Bit  sBit;  // bit access to the register data
    uint8                           ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_TIMER_CTRL_0_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bSYS_STAT_L                : 8; // System Status Control Low Byte (bit0=LSB; bit7=MSB)
} tsTle94x1_Reg_SYS_STATUS_CTRL_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_SYS_STATUS_CTRL_0_Bit  sBit;  // bit access to the register data
    uint8                                ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_SYS_STATUS_CTRL_0_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bSYS_STAT_H                : 8; // System Status Control High Byte (bit0=LSB; bit7=MSB)
} tsTle94x1_Reg_SYS_STATUS_CTRL_1_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_SYS_STATUS_CTRL_1_Bit  sBit; // bit access to the register data
    uint8                                ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_SYS_STATUS_CTRL_1_Register;

//*****************************************************************************
//                    S T A T U S  R E G I S T E R S
//*****************************************************************************

typedef struct
{
  uint8 bVCC1_WARN     : 1; // VCC1 Undervoltage Prewarning
  uint8 bVCC1_OV       : 1; // VCC1 Overvoltage Detection
  uint8 bReserved_3    : 3; // Reserved, always reads as 0
  uint8 bVS_OV         : 1; // VS Overvoltage Detection
  uint8 bVS_UV         : 1; // VS Undervoltage Detection
  uint8 bReserved_1    : 1; // Reserved, always reads as 0

} tsTle94x1_Reg_SUP_STAT_1_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_SUP_STAT_1_Bit   sBit;  // bit access to the register data
    uint8                          ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_SUP_STAT_1_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bVCC1_UV       : 1; // VCC1 UV-Detection (due to VRTx reset)
  uint8 bReserved_1    : 1; // Reserved, always reads as 0
  uint8 bVCC1_SC       : 1; // VCC1 Short to GND Detection
  uint8 bVCC2_UV       : 1; // VCC2 Under Voltage Detection (VCC2, UV,f)
  uint8 bVCC2_OT       : 1; // VCC2 Over Temperature Detection
  uint8 bReserved_1_1  : 2; // Reserved, always reads as 0
  uint8 bPOR           : 1; // Power-On Reset Detection

} tsTle94x1_Reg_SUP_STAT_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_SUP_STAT_0_Bit   sBit;  // bit access to the register data
    uint8                          ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_SUP_STAT_0_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bTPW           : 1; // Thermal Pre Warning
  uint8 bTSD1          : 1; // TSD1 Thermal Shut-Down Detection
  uint8 bTSD2          : 1; // TSD2 Thermal Shut-Down Detection
  uint8 bTSD2_SAFE     : 1; // TSD2 Thermal Shut-Down Safe State Detection
  uint8 bReserved_4    : 4; // Reserved, always reads as 0

} tsTle94x1_Reg_THERM_STAT_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_THERM_STAT_Bit  sBit; // bit access to the register data
    uint8                         ucWord;// word access to the register data
  } uData;
} tsTle94x1_Access_THERM_STAT_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bVCAN_UV       : 1; // Under voltage CAN Bus Supply
  uint8 bCAN_FAIL      : 2; // CAN Failure Status
  uint8 bSYSERR        : 1; // SWK Sysem Error
  uint8 bCANTO         : 1; // CAN Time Out Detection
  uint8 bReserved_3    : 3; // Reserved, always reads as 0

} tsTle94x1_Reg_BUS_STAT_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_BUS_STAT_Bit   sBit;  // bit access to the register data
    uint8                        ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_BUS_STAT_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bFAILURE    : 1; // Actiavation of Fail Output FO
  uint8 bSPI_FAIL   : 1; // SPI Fail Information
  uint8 bWD_FAIL    : 2; // Number of WD-Failure Events
  uint8 bReserved_2 : 2; // Reserved, always reads as 0
  uint8 bDEV_STAT   : 2; // Device Status before Restart Mode

} tsTle94x1_Reg_DEV_STAT_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_DEV_STAT_Bit  sBit;  // bit access to the register data
    uint8                       ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_DEV_STAT_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bWK_WU         : 1; // Wake up via WK
  uint8 bReserved_3    : 3; // Reserved, always reads as 0
  uint8 bTIMER_WU      : 1; // Wake up via cyclic wake
  uint8 bCAN_WU        : 1; // Wake up via CAN_0 Bus
  uint8 bReserved_2    : 2; // Reserved, always reads as 0

} tsTle94x1_Reg_WK_STAT_0_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_WK_STAT_0_Bit  sBit;  // bit access to the register data
    uint8                        ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_WK_STAT_0_Register;

//-----------------------------------------------------------------------------

typedef struct
{
  uint8 bWK_LVL          : 1; // Status of WK
  uint8 bReserved_3      : 3; // Reserved, always reads as 0
  uint8 bGPIO_LVL        : 1; // Status of GPOP if configured as GPIO
  uint8 bReserved_1      : 1; // Reserved, always reads as 0
  uint8 bCFG0_STATE      : 1; // Device Configruation Status on pin INTN
  uint8 bSBC_DEV_LVL     : 1; // Status of SBC Operating Mode at TEST PIN

} tsTle94x1_Reg_WK_LVL_STAT_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_WK_LVL_STAT_Bit  sBit;  // bit access to the register data
    uint8                          ucWord; // word access to the register data
  } uData;
} tsTle94x1_Access_WK_LVL_STAT_Register;

//***********************************************************************************************
//                    F A M I L Y AND P R O D U C T  I D E N T I FI C A T I O N  R E G I S T E R
//***********************************************************************************************

typedef struct
{
  uint8 bPROD        : 4; // SBC Product Identifier (bit0=LSB; bit3=MSB)
  uint8 bFAM         : 4; // SBC Family Identifier (bit4=LSB; bit7=MSB)

} tsTle94x1_Reg_FAM_PROD_STAT_Bit;

typedef struct
{
  uint8 ucAddress;
  union
  {
    tsTle94x1_Reg_FAM_PROD_STAT_Bit  sBit;   // bit access to the register data
    uint8                            ucWord;  // word access to the register data
  } uData;
} tsTle94x1_Access_FAM_PROD_STAT_Register;

#endif // __CDD_Tle94x1_REGS_H__

//Structure containing the structures to acess Tle94x1 control registers
typedef struct
{
  tsTle94x1_Access_M_S_CTRL_Register   M_S_CTRL_Register;
  tsTle94x1_Access_HW_CTRL_0_Register  HW_CTRL_0_Register;
  tsTle94x1_Access_HW_CTRL_1_Register  HW_CTRL_1_Register;
  tsTle94x1_Access_HW_CTRL_2_Register  HW_CTRL_2_Register;
  tsTle94x1_Access_HW_CTRL_3_Register  HW_CTRL_3_Register;
  tsTle94x1_Access_BUS_CTRL_0_Register BUS_CTRL_0_Register;
  tsTle94x1_Access_GPIO_CTRL_Register  GPIO_CTRL_Register;
  tsTle94x1_Access_PWM_CTRL_Register   PWM_CTRL_Register;
  tsTle94x1_Access_WD_CTRL_Register    WD_CTRL_Register;
  tsTle94x1_Access_WK_CTRL_0_Register  WK_CTRL_0_Register;
  tsTle94x1_Access_WK_CTRL_1_Register  WK_CTRL_1_Register;
} tsCddTle94x1_CtrlReg;

//Structure containing the structures to acess Tle94x1 status registers
typedef struct
{
  tsTle94x1_Access_SYS_STATUS_CTRL_0_Register  SYS_STATUS_CTRL_0_Register;
  tsTle94x1_Access_WK_STAT_0_Register          WK_STAT_0_Register;
  tsTle94x1_Access_SUP_STAT_0_Register         SUP_STAT_0_Register;
  tsTle94x1_Access_BUS_STAT_Register           BUS_STAT_Register;
  tsTle94x1_Access_DEV_STAT_Register           DEV_STAT_Register;
  tsTle94x1_Access_THERM_STAT_Register         THERM_STAT_Register;
  tsTle94x1_Access_WK_LVL_STAT_Register        WK_LVL_STAT_Register;
} tsCddTle94x1_StatReg;

typedef struct
{
  tsCddTle94x1_CtrlReg  CtrlTx;
  tsCddTle94x1_CtrlReg  CtrlRx;
  tsCddTle94x1_StatReg  StatTx;
  tsCddTle94x1_StatReg  StatRx;
}
tsCddTle94x1_DataMirror;

// EOF  CDD_TLE94X1_REGS_2021_03_08_H_
