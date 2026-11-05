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
#include <Nvm.h>
//=============================================================================
// Typedefs
//=============================================================================

typedef struct
{
  //input
  boolean boReq_Input;
  TIMER ulTimeMs_Input;
  //internal
  TIMER ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsCtrlSwi_TimerCfg;

//=============================================================================
// Module global variables
//=============================================================================
extern  tNvmPara_CodingArea    Coding_Dummy = { 0u };
extern  tParaFct0_Cmd          Coding_State;
extern  uint8                  CtrlSwi_ucDelayErrorDetectionTimer[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
extern  uint16                 CtrlSwi_ucDelaySwitchOnTimer[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
extern  boolean                CtrlSwi_aboCddSwiTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
extern  tieHssState            CtrlSwi_aboAppMTargetState[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
extern  tsRteHssTarget         CtrlSwi_CpmFanReq;
extern  tsRte_SwitchStatus     CtrlSwi_aSwitchStatus[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
extern  tsRte_HssStatus        CtrlSwi_aHssStatus;
extern  tisCtrlSwiState        CtrlSwi_sState;
extern  tisCtrlSwiVoltState    CtrlSwi_sVoltState;
extern  tisDiagControl_CtrlSwi CtrlSwi_sDiagControl;
extern  tisCtrlSwiErrState     CtrlSwi_sErrState;
extern  boolean                CtrlSwi_boCodingValid;
extern uint16                  CtrlSwi_aucSwitchOnDelay[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
extern uint8                   CtrlSwi_aErrorDebounce[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
// Coding validity check
extern boolean                 CtrlSwi_boIsCodingValid;
// Coding variables
extern tNvmPara_Fan1Block      CtrlSwi_sCodingParam;
extern uint8                   CtrlSwi_ucDebounce9V;
extern uint8                   CtrlSwi_ucDebounce18V;
// Error flags for all 3 errors: Sh2gnd, OpenLoad, Sh2Vbat
extern uint8                   CtrlSwi_Sh2GndFlag;
extern uint8                   CtrlSwi_OpenLoadFlag;
extern uint8                   CtrlSwi_Sh2VbatFlag;
extern uint8                   CtrlSwi_ucErrTimeout[3];

//=============================================================================
// Module function declarations
//=============================================================================
extern void                    CtrlSwi_ReadRTEPorts(void);
extern void                    CtrlSwi_CheckExternalTakeover(uint8 ucHssChannel);
extern void                    CtrlSwi_OperateOutputWithVoltState(uint8 ucHssChannel);
extern void                    CtrlSwi_CheckDelayErrorDetectionTimer(uint8 ucHssChannel);
extern void                    CtrlSwi_CheckDelaySwitchOnTimer(uint8 ucHssChannel);
extern void                    CtrlSwi_DTCHandling(void);
extern void                    CtrlSwi_UpdateSh2GndFlag(void);
extern void                    CtrlSwi_UpdateOpenLoadFlag(void);
extern void                    CtrlSwi_UpdateSh2VbatFlag(void);
extern void                    CtrlSwi_Sh2GndHandlingFans(void);
extern void                    CtrlSwi_OpenLoadHandlingFans(void);
extern void                    CtrlSwi_Sh2VbatHandlingFans(void);
extern void                    CtrlSwi_UpdateSwitchOnTimeCounter(uint8 ucHssChannel);
extern void                    CtrlSwi_SwitchOutput(uint8 ucHssChannel, boolean boSwitch);
extern void                    CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(uint8 channelNo, uint8 switchOutput);
extern void                    CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(uint8 channelNo);
extern void                    CtrlSwi_Diag_CheckAllErrors(uint8 ucHssChannel, boolean boActualState, boolean boDiagDelayDisabled);
extern void                    CtrlSwi_Diag_CheckShort2GndDuringOn(uint8 ucHssChannel);
extern void                    CtrlSwi_Diag_CheckShort2VbatDuringOff(uint8 ucHssChannel);
extern void                    CtrlSwi_Diag_CheckOpenloadDuringOn(uint8 ucHssChannel);
extern void                    CtrlSwi_Diag_CheckSmRgbErrors(void);
extern void                    roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(uint8 channelNo, uint8 switchOutput);
extern void                    roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(uint8 channelNo);

//=============================================================================
// Module function parameter stubs
//=============================================================================
uint8	                         CtrlSwi_CheckExternalTakeover_Param1;
uint8	                         CtrlSwi_OperateOutputWithVoltState_Param1;
uint8	                         CtrlSwi_CheckDelayErrorDetectionTimer_Param1;
uint8	                         CtrlSwi_CheckDelaySwitchOnTimer_Param1;
uint8	                         CtrlSwi_UpdateSwitchOnTimeCounter_Param1;
uint8	                         CtrlSwi_SwitchOutput_Param1;
boolean                        CtrlSwi_SwitchOutput_Param2;
uint8	                         CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1;
uint8	                         CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2;
uint8	                         CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1;
uint8	                         CtrlSwi_Diag_CheckShort2GndDuringOn_Param1;
uint8	                         CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1;
uint8	                         CtrlSwi_Diag_CheckOpenloadDuringOn_Param1;
uint8	                         CtrlSwi_Diag_CheckAllErrors_Param1;
boolean                        CtrlSwi_Diag_CheckAllErrors_Param2;
boolean                        CtrlSwi_Diag_CheckAllErrors_Param3;
tParaFct0_Cmd                  CtrlSwi_ParaFct0_Param1;
tNvmPara_CodingArea            CtrlSwi_ParaFct0_Param2;
uint8                          CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1;
uint8                          roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param1;
uint8                          roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param2;
uint8                          roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_Param1;
boolean                        CtrlSwi_ErrorTimers_Param1;
TIMER                          CtrlSwi_ErrorTimers_Param2;
sint8                          CtrlSwi_ErrorTimers_Param3;
tsCtrlSwi_TimerCfg*            CtrlSwi_HandleMaturationTime_Param1;
sint8                          CtrlSwi_HandleMaturationTime_Param2;
uint8                          CtrlSwi_CheckErrRetryTimer_Param1;
uint8                          CtrlSwi_ErrRetryStatergy_Param1;
teRte_SysVolt_Results          ucFanLastOperatingVoltageRange;

//=============================================================================
// Module function return value stubs
//=============================================================================
uint8                          CtrlSwi_Get_ETAT_FEE_Ret_Val;
boolean                        CtrlSwi_DataValid_RetVal;
uint8                          Rte_Write_CtrlSwi_TgtValue_SMRGB_RetVal;
uint8                          CtrlSwi_ErrorTimers_RetVal;
boolean                        CtrlSwi_HandleMaturationTime_RetVal;

#endif // TEST_2023_08_25_H_

// EOF
