#ifndef _WDG_CFG_H_
#define _WDG_CFG_H_
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
/// \file  Wdg_Cfg.h
///
/// \brief
//
/// \author Cretu Vladut-Ioan, ALRO-CJ
//  
//-----------------------------------------------------------------------------


//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Types
//=============================================================================
// Control Status Register (CS)
typedef struct
{
  uint32 bOpMode_Stop : 1;               ///< The modes in which the WDOG is functional
  uint32 bOpMode_Wait : 1;               ///< The modes in which the WDOG is functional
  uint32 bOpMode_Dbg : 1;                ///< The modes in which the WDOG is functional
  uint32 bTest : 2;                      ///< The modes in which the WDOG is functional
  uint32 bUpdateEnable : 1;              ///< If true, further updates of the WDOG are enabled
  uint32 bInterruptEnable : 1;           ///< If true, an interrupt request is generated before reset
  uint32 bWdgEnable : 1;                 ///< If true, wdog is enabled
  uint32 bClockSource : 2;               ///< The clock source of the WDOG
  uint32 bRcs : 1;                       ///< If true, reconfiguration was complete
  uint32 bUnlock : 1;                    ///< If true (read-only) the watchdog was unlocked in order to be configured.
  uint32 bPrescaler : 1;                 ///< If true, a fixed 256 prescaling of the ///< counter reference clock is enabled
  uint32 bCMD32EN : 1;                   ///< If true, 
  uint32 bFlg : 1;                       ///< This bit is an interrupt indicator when INT is set in control and status register 1.
  uint32 bWinEnable : 1;                 ///< If true, window mode is enabled
  uint32 bReserved : 16;
}Wdg_Reg1_Control_Status_Register;


// Counter Register (CNT) - Stores the unlock sequence and the trigger value
typedef union
{
  Wdg_Reg1_Control_Status_Register sCtrlSts_Reg;
  uint32 ulRaw;
}uControlStatus_Register;


typedef struct
{
  uint32 bCNT_LOW : 8;
  uint32 bCNT_HIGH : 8;
  uint32 bReserved : 16;    
}Wdg_Reg2_Counter_Register;


typedef struct
{
  uint32 bTOVAL_VALUE : 16;     
  uint32 bReserved : 16;        
}Wdg_Reg3_Timeout_Value_Register;

// Timeout Value Register (TOVAL) - Stores the value to set the timeout period of the watchdog
typedef union
{
  Wdg_Reg3_Timeout_Value_Register sTotal_Counter_Register;
  uint32 ulRaw;
}uWdg_Reg3_Timeout_Value_Register;

typedef struct
{
  //START WIN REGISTER
  uint32 bWIN_VALUE : 16; 
  uint32 bReserved : 16;  
}Wdg_Reg4_Window_Register;

// Window Register (WIN) - Stores the value to set the timeout period of the watchdog
typedef union
{
  Wdg_Reg4_Window_Register sWindow_Register;
  uint32 ulRaw;
}uWdg_Reg4_Window_Register;


typedef union
{
  Wdg_Reg2_Counter_Register        sCounter_Reg;
  uint32 ulRaw;
}uWdg_Reg2_Counter_Register;

//Watchdog registers
typedef struct
{
  uControlStatus_Register          uControlStatus_Reg;
  uWdg_Reg2_Counter_Register       uCounter_Reg;
  uWdg_Reg3_Timeout_Value_Register uTimeout_Value_Reg;
  uWdg_Reg4_Window_Register        uWindow_Value_Reg;

}Wdg_InstanceCfgType;

/// Callback functions types definition used in generic files
typedef void(*Wdg_IsrFunctionType)(void);

#endif // _WDG_CFG_H_

// EOF
