//-----------------------------------------------------------------------------
/// \file   Wdg_CfgPrj.c
/// \brief  Configuration source file for Wdg module
/// \author Alexandru Radu, ALRO-CJ
/// \note
//-----------------------------------------------------------------------------

///
///  @addtogroup WDG Wdg module documentation
///  @{
///

//=============================================================================
// Includes
//=============================================================================
#include "Wdg.h"
#include <Std_Types.h>
#include <AL_Helper.h>

// Watchdog configuration structures
Wdg_InstanceType Wdg_Instance =
{
   // Control Status register
   // Stop mode bit
   .uControlStatus_Reg.sCtrlSts_Reg.bOpMode_Stop = 0u ,
   // Wait mode bit
   .uControlStatus_Reg.sCtrlSts_Reg.bOpMode_Wait = 0u ,
   // Debug mode bit
   .uControlStatus_Reg.sCtrlSts_Reg.bOpMode_Dbg = 0u ,
   // Test bit
   .uControlStatus_Reg.sCtrlSts_Reg.bTest = 0u ,
   // Update enable bit
   .uControlStatus_Reg.sCtrlSts_Reg.bUpdateEnable = 1u ,
   // Interrupt enable bit
   .uControlStatus_Reg.sCtrlSts_Reg.bInterruptEnable = 0u ,
   // Wdgenable bit
   .uControlStatus_Reg.sCtrlSts_Reg.bWdgEnable = 1u ,
   // Clock source bit
   .uControlStatus_Reg.sCtrlSts_Reg.bClockSource = 1 ,
   // Reconfiguration bit
   .uControlStatus_Reg.sCtrlSts_Reg.bRcs = 0 ,
   // Unlock bit
   .uControlStatus_Reg.sCtrlSts_Reg.bUnlock = 0 ,
   // Prescaler bit
   .uControlStatus_Reg.sCtrlSts_Reg.bPrescaler = 0 ,
   // CMD32EN Bit
   .uControlStatus_Reg.sCtrlSts_Reg.bCMD32EN = 1 ,
   // Flag bit
   .uControlStatus_Reg.sCtrlSts_Reg.bFlg = 0 ,
   // WinEnable Bit
   .uControlStatus_Reg.sCtrlSts_Reg.bWinEnable = 0 ,
   // Reserved
   .uControlStatus_Reg.sCtrlSts_Reg.bReserved = 0,

   // Counter Reg
   .uCounter_Reg.ulRaw = WDG_UNLOCK_VALUE,

   // Timeout Value
   .uTimeout_Value_Reg.sTotal_Counter_Register.bTOVAL_VALUE = 25334u,    /*!< The window value */ //3800 means 30 miliseconds //25334 means 200 ms // 38000 = 300 ms
   .uTimeout_Value_Reg.sTotal_Counter_Register.bReserved = 0,    /*!< The timeout value */
   // Window Value
   .uWindow_Value_Reg.sWindow_Register.bWIN_VALUE = 1800u,     /*!< The window value */
   .uWindow_Value_Reg.sWindow_Register.bReserved = 0    /*!< The timeout value */
};


///@}
