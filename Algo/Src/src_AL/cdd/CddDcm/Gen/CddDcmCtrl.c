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
// \file   CddDcmCtrl.c
//
// \brief  "Monitored" DC motor driver, supporting two indipendent instances
//
// \descr  "Monitored" DC motor driver (OutDcm2):
//          Output value for each motor drive will be monitored for regulation,
//          optional: detection of low/high error at output for each DC Motor
//
// \author Braun, Martin ALRT/EEG-CA (bnm2rt)
//         Traulsen, Alf ALRT/EEG-CA (taf2rt)
//         Paland, Marco ALRT/EEG-PM2 (pm88rt)
//-----------------------------------------------------------------------------


// *****************************************************************************
// includes 
// *****************************************************************************

#include <Std_Types.h>
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Rte.h>, <Cfg/Cfg.h>, <UtilUtility.h>, <IoHwAbUser.h>, <Nvm.h> */
#include <stdlib.h>

#include "CddDcm_Cfg.h"     // project specific DCM configuration
#include "CddDcmHal.h"
#include "CddDcm.h"
#include "CddDcmCtrl.h"



#define CddCtrlDCM_HOOK_FCT_PERIOD_TIME_MS       (20u)
#ifndef UNIT_TEST
#define CddCtrlDCM_CYCLE_CTRL_TIME_COUNT         (1000u / CddCtrlDCM_HOOK_FCT_PERIOD_TIME_MS)
#else
#define CddCtrlDCM_CYCLE_CTRL_TIME_COUNT         (2u)
#endif

#define CddCtrl_CyclicAlarmPeriod                CddCtrlDCM_HOOK_FCT_PERIOD_TIME_MS

#define CDDDCM_ZeroPosition          800  // keep at 800. If zero position is 200, use option "CFG_Dcm_Reverse" instead
#define CDDDCM_MIN_LEVEL_ASL_ADJUST -300  // initial value
// Note: Parameter MAX_LEVEL_ASL_ADJUST not supported by SAVAC

tDcMotorDataStruct NvmInit_ParaDcMotorDataDefault = {false, false, CtrlDcm_PosUnknown} ;

tDcMotorCharacteristicStruct NvmInit_ParaDcMotorCharacteristicDefault = 
          { 0,  // ucHeader[2]
            32,      // ucMaxAdjustingTime, worst case speed for Dc motor
                     // drive or maximum time for 0-100 %Ubat
                     //   [0.01 s/%Ubat] = [1s / 100%Ubat]
            0        // invalid flag
          };


//=============================================================================
// variable definitions
//=============================================================================

STATIC_AL sint16           Para_nMinLevelAslAdjust = CDDDCM_MIN_LEVEL_ASL_ADJUST;

STATIC_AL boolean          CddDcmCtrl_boEepromUpdated = TRUE;
STATIC_AL tCtrlDcmState    CddDcmCtrl_eState;
STATIC_AL tCtrlDcmVoltage  CddDcmCtrl_eVoltage;

STATIC_AL sint16           CddDcmCtrl_nOldPos;
STATIC_AL sint16           CddDcmCtrl_nHighestPos;
STATIC_AL sint16           CddDcmCtrl_nLowestPos;

STATIC_AL boolean          CddDcmCtrl_boAlarmActive;
STATIC_AL uint16           CddDcmCtrl_unAdjustingTime;
STATIC_AL uint16           CddDcmCtrl_unTimeoutCounter;

#define CddDcmCtrl_ErrInit  -1
STATIC_AL sint16           CddDcmCtrl_nErrCnt_ms = CddDcmCtrl_ErrInit;
STATIC_AL sint16           CddDcmCtrl_nErrCntLow;
STATIC_AL sint16           CddDcmCtrl_nErrCntHigh;

//=============================================================================
// macro for reverse polarity
//=============================================================================

#define CFG_OPT_DCM       1u
#define CFG_Dcm_Reverse   1u

#if (CFG_OPT_DCM & CFG_Dcm_Reverse)
  #define LEVEL(x)  (1000u - (x))
#elif (CFG_OPT_DCM & CFG_Dcm_ReverseByParaFlag)
  #define LEVEL(x)  CtrlDcmOutputLevelReverseCalc_(x)
#else
  #define LEVEL(x)  (x)
#endif

//=============================================================================
// local function prototypes
//=============================================================================

STATIC_AL boolean CddDcmCtrl_CtrlMsgChannel(tDcmCtrlMsg Msg);
STATIC_AL void    CddDcmCtrl_ServiceMotor(sint16 nPos);
STATIC_AL uint16  CddDcmCtrl_GetAdjustingTime(sint16 nPos, sint16 nLowestPos, sint16 nHighestPos);
STATIC_AL void    CddDcmCtrl_AlarmSet(uint16 unTimeout);
STATIC_AL void    CddDcmCtrl_Continue(void);
STATIC_AL void    CddDcmCtrl_DisableChannel(void);
STATIC_AL void    CddDcmCtrl_UpdateEepromData(uint8 byPositionStatus, sint16 nTargetPosition);
STATIC_AL boolean CddDcmCtrl_IsMovingChannel(void);
STATIC_AL void    CddDcmCtrl_ResetErrorDetection_(void);

//=============================================================================
// function definitions
//=============================================================================

STATIC_AL void CddDcmCtrl_BbSettingStart(sint16 nPos)
{
  tDcmStateMsg DcmStateMsg;
  tDcmPosMsg   DcmPosMsg;
  
  (void)Rte_Read_DcmState0_Port(&DcmStateMsg);
  (void)Rte_Read_DcmPos0_Port(&DcmPosMsg);

  DcmStateMsg.Bit.IsMoving = 1;
  DcmStateMsg.Bit.IsReady  = 0;
  (void)Rte_Write_DcmState0_Port(&DcmStateMsg);

  DcmPosMsg.nPos           = nPos;
  (void)Rte_Write_DcmPos0_Port(&DcmPosMsg);
}

STATIC_AL void CddDcmCtrl_BbSettingStop_(void)
{
  tDcmStateMsg DcmStateMsg;

  (void)Rte_Read_DcmState0_Port(&DcmStateMsg);
  DcmStateMsg.Bit.IsMoving = 0;
  DcmStateMsg.Bit.IsReady  = 1;
  (void)Rte_Write_DcmState0_Port(&DcmStateMsg);
}

STATIC_AL void CddDcmCtrl_BbSettingDisable_(void)
{
  tDcmStateMsg DcmStateMsg;

  (void)Rte_Read_DcmState0_Port(&DcmStateMsg);
  DcmStateMsg.Bit.IsMoving = 0;
  (void)Rte_Write_DcmState0_Port(&DcmStateMsg);
}

STATIC_AL void CddDcmCtrl_BbSettingVoltOnOff_(uint8 ucOnOff)
{
  tDcmStateMsg DcmStateMsg;
  // supply voltage always identical for both DC-Motors

  (void)Rte_Read_DcmState0_Port(&DcmStateMsg);
  DcmStateMsg.Bit.IsOn = ucOnOff;
  (void)Rte_Write_DcmState0_Port(&DcmStateMsg);
}

STATIC_AL void CddDcmCtrl_BbSettingErr_OnOff_(uint8 ucOnOff)
{
  tDcmStateMsg DcmStateMsg;

  (void)Rte_Read_DcmState0_Port(&DcmStateMsg);
  DcmStateMsg.Bit.ErrElec = ucOnOff;
  (void)Rte_Write_DcmState0_Port(&DcmStateMsg);
}

STATIC_AL void CddDcmCtrl_BbSettingInit_(sint16 nPos)
{
  tDcmStateMsg DcmStateMsg;
  tDcmPosMsg   DcmPosMsg;
  
  DcmPosMsg.nPos = nPos;
  
  (void)Rte_Read_DcmState0_Port(&DcmStateMsg);
  // valid position
  DcmStateMsg.Bit.IsReady = 1;
  (void)Rte_Write_DcmState0_Port(&DcmStateMsg);
  (void)Rte_Write_DcmPos0_Port(&DcmPosMsg);
}


//-----------------------------------------------------------------------------
/// \brief  cyclical call of CtrlDcm (by IpdAct)
///
/// \descr  cyclical call of CtrlDcm (by IpdAct),
///         every CddCtrl_CyclicAlarmPeriod [ms]:
///         - check for writing of Eeprom data
///         - optional: error detection
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_CyclicAlarm(void)
{
  // period [ms] see CddCtrl_CyclicAlarmPeriod

  // check for writing of Eeprom data
  if (CddDcmCtrl_boEepromUpdated == FALSE)  // should be called periodically
  {
    if (ILCU_LvlAdp_NvM_WriteBlock((NvM_BlockIdType)NvmBlockDcMotorDataId, (void*)&NvmBlockDcMotorData) == E_OK) /* ILCU_PORT: NvM_WriteBlock collides with ILCU NvM; RAM-only stub */
    {
      CddDcmCtrl_boEepromUpdated = TRUE;
    }
  }

  CddDcmCtrl_DoErrorDetection();
}


//-----------------------------------------------------------------------------
/// \brief  Update Eeprom data (RamCopy)
///
/// \descr  -
///
/// \param  byPositionStatus 
/// \param  nTargetPosition 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_UpdateEepromData(uint8 byPositionStatus, sint16 nTargetPosition)
{
  switch(byPositionStatus)
  {
    case CtrlDcm_MotorStarted:  // always when Motor is started.
    {
      if ( NvmBlockDcMotorData.boMotorStarted
          == NvmBlockDcMotorData.boMotorStopped )
      {
        NvmBlockDcMotorData.boMotorStarted = !NvmBlockDcMotorData.boMotorStarted;
      }

      NvmBlockDcMotorData.nPosition = nTargetPosition;

      CddDcmCtrl_boEepromUpdated = FALSE;

      break;
    }

    case CtrlDcm_MotorStopped:    // only when TargetPosition is reached.
    {
      if(NvmBlockDcMotorData.boMotorStarted != NvmBlockDcMotorData.boMotorStopped )
      {
        NvmBlockDcMotorData.boMotorStopped = !NvmBlockDcMotorData.boMotorStopped;
      }

      NvmBlockDcMotorData.nPosition = nTargetPosition;

      CddDcmCtrl_boEepromUpdated = FALSE;

      break;
    }

    default:
    {
      break;
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  calculate adjusting time for DC motor drive (in seconds)
///
/// \descr  -
///
/// \param  nPos 
/// \param  nLowestPos 
/// \param  nHighestPos 
///
/// \return uint16 
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddDcmCtrl_GetAdjustingTime(sint16 nPos, sint16 nLowestPos, sint16 nHighestPos)
{
  uint16 unAdjustingTime;
  sint16 nLowDiffAbs  = nPos - nLowestPos;
  sint16 nHighDiffAbs = nHighestPos - nPos;

  uint16 unLowDiff = (uint16)(UTIL_ABS(nLowDiffAbs));   // [ promill ]
  uint16 unHighDiff= (uint16)(UTIL_ABS(nHighDiffAbs));  // [ promill ]
  unAdjustingTime = (uint16)((unHighDiff >= unLowDiff) ? (uint16)(CtrlDcm_MaxAdjustingTime * unHighDiff) :  (uint16)(CtrlDcm_MaxAdjustingTime * unLowDiff));  // [ ms ]

  unAdjustingTime /= 1024U;   // return seconds, 1024 considerd in definition of
                              // CtrlDcm_MaxAdjustingTime
  unAdjustingTime++;          // round up, the value has now a minimum of 1

 #if (CtrlDcm_LowestAdjTime > 1)
  // care for minimum time period of motor adjusting
  unAdjustingTime = max(unAdjustingTime,CtrlDcm_LowestAdjTime);
 #endif

  return unAdjustingTime;
}


//-----------------------------------------------------------------------------
/// \brief  execute state machine for DC motor drive
///
/// \descr  execute state machine for DC motor drive:
///         Start motor adjusting (-> HalDcm), stop after adjusting time.
///         If necessary first moving down with offset before final position
///         drive.
///         Update positioning information.
///         (Take care of limitation for DC motor driving range.)
///
/// \param  nPos 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_ServiceMotor(sint16 nPos)
{
  sint16 nCtrlGetDcMotorMinPos;
  
  switch (CddDcmCtrl_eState)
  {
    case CtrlDcm_StateMovingDown:
    {
      uint16 unAdjustingTime;
      sint16 nTemp = nPos;    // store target pos

      CddDcmCtrl_UpdateEepromData(CtrlDcm_MotorStarted, nPos);
      
      CddDcmCtrl_BbSettingStart(nPos);

      nPos -= CtrlDcm_Offset;

      nCtrlGetDcMotorMinPos = CtrlGetDcMotorMinPos_();

      // Not exceed reflector swivelling range
      nPos = max(nPos,nCtrlGetDcMotorMinPos);
      
      unAdjustingTime = CddDcmCtrl_GetAdjustingTime(nPos, CddDcmCtrl_nLowestPos, CddDcmCtrl_nHighestPos);

      CddDcmCtrl_nLowestPos = min(CddDcmCtrl_nLowestPos,nPos);

      CddDcmHal_SetOutpLevelChannel(LEVEL((uint16)nPos));
      CddDcmHal_EnableChannel(TRUE);

      // real intermediate moving down before moving up to target pos
                                             // minimum limitation causes that low pos is already target pos
                                             // -> skip moving up states, prepare already for finishing adjusting
      CddDcmCtrl_eState = (nTemp != nPos) ? CtrlDcm_StateMovingPause : CtrlDcm_StateMovingDone;

      CddDcmCtrl_AlarmSet(unAdjustingTime);
      
      break;
    }

    case CtrlDcm_StateMovingPause:
    {
      sint16 nTemp = nPos;  // store target pos

      nPos -= CtrlDcm_Offset;
      
      nCtrlGetDcMotorMinPos = CtrlGetDcMotorMinPos_();

      // Not exceed reflector swivel range
      nPos = max(nPos,nCtrlGetDcMotorMinPos);

      CddDcmCtrl_nHighestPos = nPos;    // Update max and min positions (pos. reached)
      CddDcmCtrl_nLowestPos  = nPos;

      nPos = nTemp;  // restore target pos

      CddDcmCtrl_eState = CtrlDcm_StateMovingUp;   // -> execute immediately
      // No break !!
    } //lint -e(616) -fallthrough control flows into case/default.
    
    case CtrlDcm_StateMovingUp: //PRQA S 2003, 1 // fallthrough control flows into case/default.
    {
      uint16 unAdjustingTime;

      CddDcmCtrl_UpdateEepromData(CtrlDcm_MotorStarted, nPos);

      CddDcmCtrl_BbSettingStart(nPos);

      unAdjustingTime = CddDcmCtrl_GetAdjustingTime(nPos, CddDcmCtrl_nLowestPos, CddDcmCtrl_nHighestPos);

      CddDcmCtrl_nHighestPos = max(CddDcmCtrl_nHighestPos,nPos);

      CddDcmHal_SetOutpLevelChannel(LEVEL((uint16)nPos));
      CddDcmHal_EnableChannel(TRUE);

      CddDcmCtrl_eState = CtrlDcm_StateMovingDone;
      CddDcmCtrl_AlarmSet(unAdjustingTime);

      break;
    }

    case CtrlDcm_StateMovingDone:
    {
      CddDcmCtrl_UpdateEepromData(CtrlDcm_MotorStopped, nPos);

      CddDcmCtrl_BbSettingStop_();

      CddDcmCtrl_nHighestPos = nPos;    // Update max and min positions (pos reached)
      CddDcmCtrl_nLowestPos  = nPos;

      CddDcmCtrl_eState = CtrlDcm_StateNotActive;  // -> execute immediately
      // No break !!
    }

    case CtrlDcm_StateNotActive:  //PRQA S 2003, 1 // fallthrough control flows into case/default.
    {
      CddDcmHal_DisableAndPwmOffChannel();

      break;
    }

    case CtrlDcm_StateLocked:
    case CtrlDcm_StateErrorOff:
    default:
      // CtrlDcm_StateLocked, CtrlDcm_StateErrorOff: do nothing
      break;
  }
} // PRQA S 5324 1 // HIS metrics no of distinct fct calls


//-----------------------------------------------------------------------------
/// \brief  call for evaluating Ctrl messsage data
///
/// \descr  call for evaluating Ctrl messsage data:
///         start new DC motor positioning if necessary
///
/// \param  - 
///
/// \return boolean 
//-----------------------------------------------------------------------------
STATIC_AL boolean CddDcmCtrl_CtrlMsgChannel(tDcmCtrlMsg Msg)
{
  boolean boMotorRequired;
  sint16 nDeltaPos, ntemp;

  // check for error clear request
  if (Msg.Bit.ErrClr != 0u)
  {
    if(CddDcmCtrl_eState == CtrlDcm_StateErrorOff)
    {
      // set actual positioning as completely unknown
      CddDcmCtrl_nOldPos     = CtrlDcm_PosUnknown;
      CddDcmCtrl_nHighestPos = CtrlDcm_PosRangeMax;
      CddDcmCtrl_nLowestPos  = CtrlDcm_PosRangeMin;
      // "enable" state machine for DC motor 
      CddDcmCtrl_eState      = CtrlDcm_StateNotActive;
    }
    else
    {
      // error clear under regular condition
      // (only new motor drive shall be prepared)

      // abort (possible) actual motor drive
      CddDcmCtrl_DisableChannel();
      // take care for new motor drive with at least hysteresis delta
      // (- delta must exceed CtrlDcm_Threshold
      //  - for directly driving up care for CtrlDcm_Hysteresis,
      //    otherwise first move down)
      CddDcmCtrl_nOldPos = CtrlDcm_PosUnknown;
      CddDcmCtrl_nHighestPos = CddDcmCtrl_nHighestPos + CtrlDcm_Hysteresis;
      
       // range limitation for Ram variable CddDcmCtrl_nHighestPos
      // (So in case of targeting maximum value, no first move down 
      //  and hysteresis delta are guarantueed.
      //  Functional restriction as for minimum and around minimum value.)      
      CddDcmCtrl_nHighestPos = min(CddDcmCtrl_nHighestPos,CtrlDcm_PosRangeMax);
      // keep state machine unchanged (CddDcmCtrl_eState)
    }
    CddDcmCtrl_BbSettingErr_OnOff_(0);
  }
  //else: no action (normal evaluation of Ctrl message)

  // Control state? (voltage not "on" or stop (not "active")
  //                 or motor drive direction undefined
  //                 or prj-spec. condition not fullfilled)
  if( (CddDcmCtrl_eVoltage != CtrlDcm_VoltOn) || (Msg.Bit.Active  == 0u) )
  {
    CddDcmCtrl_DisableChannel();
    CddDcmCtrl_eState = CtrlDcm_StateLocked;
  }
  else if(CddDcmCtrl_eState == CtrlDcm_StateLocked)
  {
    CddDcmCtrl_Continue();
  }
  else
  {
    // do nothing
  }

  // Min/Max Limit position:
  // In case the Msg.Val.nPos value is outside the min and max value
  // then it will be adusted/set to the min or max limit.
  ntemp = CtrlGetDcMotorMaxPos_();
  Msg.Val.nPos = min(Msg.Val.nPos, ntemp);

  ntemp = CtrlGetDcMotorMinPos_();
  Msg.Val.nPos = max(Msg.Val.nPos, ntemp);

  // New position?
  nDeltaPos = Msg.Val.nPos - CddDcmCtrl_nOldPos;
  if(nDeltaPos < 0)
  {
    nDeltaPos *= (-1);
  }
 
  if( (nDeltaPos >= CtrlDcm_Threshold) && (CddDcmCtrl_eState != CtrlDcm_StateLocked) )
  {
    CddDcmHal_DisableAndPwmOffChannel();

    CddDcmCtrl_nOldPos = Msg.Val.nPos;                       // Store new position

   // limit highest position for move-up/down decision
   // by used range (of parameter), not by maximum allowed range (of defines)
   sint16 nHighestPosInUsedRange = CtrlGetDcMotorMaxPos_();
   
   nHighestPosInUsedRange = min(nHighestPosInUsedRange,CddDcmCtrl_nHighestPos);

   if(Msg.Val.nPos >= nHighestPosInUsedRange)  // Move up ?
   {
     CddDcmCtrl_eState = CtrlDcm_StateMovingUp;  // Set State-Machine-Entry
   }
   else                                // Move down?
   {
     CddDcmCtrl_eState = CtrlDcm_StateMovingDown;  // Set State-Machine-Entry
   }
  
   boMotorRequired = TRUE;
    //return TRUE; // new ServiceMotor required
  }
  else
  {
    boMotorRequired = FALSE;
    //return FALSE; // no ServiceMotor required
  }

  return boMotorRequired;
}

//-----------------------------------------------------------------------------
/// \brief  call for evaluating Ctrl messsage data
///
/// \descr  call for evaluating Ctrl messsage data:
///         start new DC motor positioning if necessary
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void CddDcmCtrl_CtrlMsg(void)
{
  tDcmCtrlMsg Msg = { 0 };
  tsRte_CtrlDcmTarget sTgtPos = { 0 };

  (void)Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(&sTgtPos);

  Msg.Bit.nPos = (sint16)(CDDDCM_ZeroPosition - ((600 * (sint32)sTgtPos.sDcmTarget.nPosition) / Para_nMinLevelAslAdjust)); // Para_nMinLevelAslAdjust project specific
  Msg.Bit.Active = (sTgtPos.sDcmTarget.boStop == FALSE) ? 1u : 0u;
  Msg.Bit.ErrClr = 0;

  if (CddDcmCtrl_CtrlMsgChannel(Msg) != FALSE)
  {
    CddDcmCtrl_ServiceMotor(CddDcmCtrl_nOldPos); // Start State-Machine
  }
}
  

// ??? Noch richtig einbauen in W:\Alx1main\Alx1\Code\Src\Cust\St\Ps34\Swc\Sys\Volt
// Diese Fct wurde wahrscheinlich frueher als Event aufgerufen, wird erst noch vereifacht gepollt.
// Auch keine 100m ms Entprellung drin (nur der Eingangsfilter / Sw) wird hier genutzt.
void CddDcmCtrl_VoltChange(void)
{
  tCtrlDcmVoltage  CtrlDcm_eVoltageOld = CddDcmCtrl_eVoltage;
  tiu32Voltage_mV           unDiagVbat_mV;
  
  // Get the actual VBAT (KL15) level
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&unDiagVbat_mV);
  
  if ( (unDiagVbat_mV > 8590u) && (unDiagVbat_mV < 17690u) )
  {
    CddDcmCtrl_BbSettingVoltOnOff_(1u);
    CddDcmCtrl_eVoltage = CtrlDcm_VoltOn;
  }
  else
  {
    CddDcmCtrl_BbSettingVoltOnOff_(0u);
    CddDcmCtrl_eVoltage = CtrlDcm_VoltOff;    
  }
  
  if (CtrlDcm_eVoltageOld != CddDcmCtrl_eVoltage)
  {
    CddDcmCtrl_CtrlMsg();
  }    
}


//-----------------------------------------------------------------------------
/// \brief  disable DC motor driver
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_DisableChannel(void)
{
  CddDcmHal_DisableAndPwmOffChannel();
  CddDcmCtrl_BbSettingDisable_();
}

//-----------------------------------------------------------------------------
/// \brief  disable DC motor driver
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void CddDcmCtrl_Disable(void)
{
  CddDcmCtrl_DisableChannel();
}


//-----------------------------------------------------------------------------
/// \brief  start 1-s-Alarm for DC motor adjusting
///
/// \descr  -
///
/// \param  unTimeout 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_AlarmSet(uint16 unTimeout)
{
  CddDcmCtrl_boAlarmActive    = TRUE;
  CddDcmCtrl_unAdjustingTime  = unTimeout;
  CddDcmCtrl_unTimeoutCounter = 0u;
}


//-----------------------------------------------------------------------------
/// \brief  check 1-s-Alarm if DC motor adjusting is elapsed
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_AlarmTimeout(void)
{
  boolean boServiceMotorReq0 = FALSE;
  
  if ( CddDcmCtrl_boAlarmActive != FALSE )
  {
    // Check if channel 0 adjusting expired
    if(++CddDcmCtrl_unTimeoutCounter >= CddDcmCtrl_unAdjustingTime)
    {
      CddDcmCtrl_boAlarmActive = FALSE;      // inactivate alarm
      boServiceMotorReq0 = TRUE;
    }
  }

  if ( boServiceMotorReq0 != FALSE )
  {
    CddDcmCtrl_ServiceMotor(CddDcmCtrl_nOldPos);    // Call State-Machine (cont'd)
  }

}


//-----------------------------------------------------------------------------
/// \brief  re-initiate state machine and data (for enabling DC motor driver)
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_Continue(void)
{
  CddDcmHal_DisableAndPwmOffChannel();
  CddDcmCtrl_eState   = CtrlDcm_StateNotActive;

  if ( NvmBlockDcMotorData.boMotorStarted != NvmBlockDcMotorData.boMotorStopped )
  {
    CddDcmCtrl_nOldPos = CtrlDcm_PosUnknown;
  }
}


//-----------------------------------------------------------------------------
/// \brief  init fct call for each channel
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddDcmCtrl_InitChannel(void)
{
  CddDcmCtrl_eState = CtrlDcm_StateNotActive;

  if(( NvmBlockDcMotorData.boMotorStarted != NvmBlockDcMotorData.boMotorStopped ) 
       || ( CtrlDcm_PosUnknown == NvmBlockDcMotorData.nPosition ) )
  {
    // motor positioning of last power-on incomplete or unknown
    CddDcmCtrl_nOldPos     = CtrlDcm_PosUnknown;
    CddDcmCtrl_nHighestPos = CtrlDcm_PosRangeMax;
    CddDcmCtrl_nLowestPos  = CtrlDcm_PosRangeMin;
  }
  else
  {
    // valid and definite motor positioning of last power-on
    CddDcmCtrl_nOldPos     = NvmBlockDcMotorData.nPosition;
    CddDcmCtrl_nHighestPos = NvmBlockDcMotorData.nPosition;
    CddDcmCtrl_nLowestPos  = NvmBlockDcMotorData.nPosition;
    CddDcmCtrl_BbSettingInit_(CddDcmCtrl_nOldPos);
  }
}


void CddDcmCtrl_DoErrorDetection(void)
{
  uint8 ucDcmVoltageState;
  static tsRte_DcmStatusError CddDcmCtrl_sErrorStatus = { FALSE, FALSE };

  // error detection
  if (CddDcmCtrl_eState != CtrlDcm_StateErrorOff)
  {
    if (CddDcmCtrl_IsMovingChannel() != FALSE)
    {
      // evaluation for error detection

      // handle detection time
      if (CddDcmCtrl_nErrCnt_ms <= 0)
      {
        // start evaluating
        CddDcmCtrl_nErrCnt_ms = (sint16)CddCtrl_CyclicAlarmPeriod;
        // reset HalDcm voltage evaluation and CtrlDcm error counting
        CddDcmHal_ResetVoltageState();
        CddDcmCtrl_nErrCntLow = 0;
        CddDcmCtrl_nErrCntHigh = 0;
      }
      else if ((sint16)CtrlDcm_ErrorTime <= CddDcmCtrl_nErrCnt_ms)
      {
        // necessary time for error verification already elapsed
        CddDcmCtrl_nErrCnt_ms = (sint16)CtrlDcm_ErrorTime;
      }
      else
      {
        CddDcmCtrl_nErrCnt_ms += (sint16)CddCtrl_CyclicAlarmPeriod;
      }

      // evaluate actual voltage state(s)
      ucDcmVoltageState = CddDcmHal_GetVoltageState();

      if (HALDCM_LEVEL_OK == ucDcmVoltageState)
      {
        // Ok case -> decrement both counter
        // (negative value is sufficient for error-free,
        //  limit decrementing to avoid overflow)
        if (CddDcmCtrl_nErrCntLow >= 0)
        {
          CddDcmCtrl_nErrCntLow -= (sint16)CddCtrl_CyclicAlarmPeriod;
        }
        if (CddDcmCtrl_nErrCntHigh >= 0)
        {
          CddDcmCtrl_nErrCntHigh -= (sint16)CddCtrl_CyclicAlarmPeriod;
        }
      }
      else if (HALDCM_LEVEL_LOW == ucDcmVoltageState)
      {
        // low error case -> increment low counter (keep high counter unchanged)
        // (no overflow of psoitive value possibel because of error limit)
        CddDcmCtrl_nErrCntLow += (sint16)CddCtrl_CyclicAlarmPeriod;
      }
      else if (HALDCM_LEVEL_HIGH == ucDcmVoltageState)
      {
        // high error case -> increment high counter (keep low counter unchanged)
        // (no overflow of psoitive value possibel because of error limit)
        CddDcmCtrl_nErrCntHigh += (sint16)CddCtrl_CyclicAlarmPeriod;
      }
      else
      {
        //keep counter unchanged
      }

      // analyse for error verification and status of AL EC
      if ((sint16)CtrlDcm_ErrorTime <= CddDcmCtrl_nErrCnt_ms)
      {
        // necessary time for error verification is elapsed
#define CtrlDcm_ErrorLimit ((CtrlDcm_ErrorTime * 8u)/10u)
            // 80% is limit for verified error

        if (CddDcmCtrl_nErrCntLow >= (sint16)CtrlDcm_ErrorLimit)
        {
          // -> low error is verified as active
          //ErrLogSetStatus(CtrlDcm_aIxAlEcLow[ucDcmChannel], ERRLOG_Active);
          Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_GND, DEM_EVENT_STATUS_FAILED);
          CddDcmCtrl_sErrorStatus.boElecGND = TRUE;
          // -> set state CtrlDcm_StateErrorOff for verified error case
          // (will be used as marker below)
          CddDcmCtrl_eState = CtrlDcm_StateErrorOff;
          // -> high error can no more be detected, will be handled below
        }
        else if (CddDcmCtrl_nErrCntHigh >= (sint16)CtrlDcm_ErrorLimit)
        {
          // -> high error is verified as active
          //ErrLogSetStatus(CtrlDcm_aIxAlEcHigh[ucDcmChannel], ERRLOG_Active);
          Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_BAT, DEM_EVENT_STATUS_FAILED);
          CddDcmCtrl_sErrorStatus.boElecBAT = TRUE;
          // -> set state CtrlDcm_StateErrorOff for verified error case
          // (will be used as marker below)
          CddDcmCtrl_eState = CtrlDcm_StateErrorOff;
          // -> low error can no more be detected, will be handled below
        }
        else
        {
          //both AL EC types are absent
          //ErrLogSetStatus(CtrlDcm_aIxAlEcLow[ucDcmChannel], ERRLOG_Absent);
          //ErrLogSetStatus(CtrlDcm_aIxAlEcHigh[ucDcmChannel], ERRLOG_Absent);
          Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_GND, DEM_EVENT_STATUS_PASSED);
          Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_BAT, DEM_EVENT_STATUS_PASSED);
          CddDcmCtrl_sErrorStatus.boElecGND = FALSE;
          CddDcmCtrl_sErrorStatus.boElecGND = FALSE;
        }

        // error verified -> initiate error reaction
        if (CddDcmCtrl_eState == CtrlDcm_StateErrorOff)
        {
          // abort and disable DC driver (including PWM signal off)
          CddDcmCtrl_DisableChannel();
          // Already disabled and Pwm switched off in the prev. function call.
          //HalDcmDisableAndPwmOff();

          CddDcmCtrl_BbSettingErr_OnOff_(1);
        }
        // else: go on detecting
      }
      else
      {
        // necessary time for error verification not yet elapsed
#define CtrlDcm_WarnLimit        ((CtrlDcm_ErrorTime * 1u)/10u)
            // 10% is warn limit
#define CtrlDcm_ErrCntMinTime    (5u * CddCtrl_CyclicAlarmPeriod)
#if(CtrlDcm_ErrCntMinTime < CtrlDcm_WarnLimit)
#error CtrlDcmMon: timing value conflict (by configuration)
#endif

// counter below 0 -> error absent
// else:
//   at least "min" cycles
//     counter below WarnLimit and at least 5 cycles -> error absent
//     else: -> error maybe
//   else: (don't care until "min" cycles elapsed)
        if (CddDcmCtrl_nErrCntLow < 0)
        {
          //ErrLogSetStatus(CtrlDcm_aIxAlEcLow[ucDcmChannel], ERRLOG_Absent);
          Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_GND, DEM_EVENT_STATUS_PASSED);
          CddDcmCtrl_sErrorStatus.boElecGND = FALSE;
        }
        else if ((sint16)CtrlDcm_ErrCntMinTime <= CddDcmCtrl_nErrCnt_ms)
        {
          if (CddDcmCtrl_nErrCntLow < (sint16)CtrlDcm_WarnLimit)
          {
            //ErrLogSetStatus(CtrlDcm_aIxAlEcLow[ucDcmChannel], ERRLOG_Absent);
            Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_GND, DEM_EVENT_STATUS_PASSED);
            CddDcmCtrl_sErrorStatus.boElecGND = FALSE;
          }
          else
          {
            //ErrLogSetStatus(CtrlDcm_aIxAlEcLow[ucDcmChannel], ERRLOG_Maybe);
          }
        }
        else
        {
          // wait for information
        }

        if (CddDcmCtrl_nErrCntHigh < 0)
        {
          //ErrLogSetStatus(CtrlDcm_aIxAlEcHigh[ucDcmChannel], ERRLOG_Absent);
          Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_BAT, DEM_EVENT_STATUS_PASSED);
          CddDcmCtrl_sErrorStatus.boElecBAT = FALSE;
        }
        else if ((sint16)CtrlDcm_ErrCntMinTime <= CddDcmCtrl_nErrCnt_ms)
        {
          if (CddDcmCtrl_nErrCntHigh < (sint16)CtrlDcm_WarnLimit)
          {
            //ErrLogSetStatus(CtrlDcm_aIxAlEcHigh[ucDcmChannel], ERRLOG_Absent);
            Rte_Call_DemPrj_ReportErrorStatus((uint16)DCMotor_SC_BAT, DEM_EVENT_STATUS_PASSED);
            CddDcmCtrl_sErrorStatus.boElecBAT = FALSE;
          }
          else
          {
            //ErrLogSetStatus(CtrlDcm_aIxAlEcHigh[ucDcmChannel], ERRLOG_Maybe);
          }
        }
        else
        {
          // wait for information
        }

      }
    }
    else // not moving
    {
      // actually no error detection running because no motor adjusting
      if (CddDcmCtrl_nErrCnt_ms >= 0)
      {
        CddDcmCtrl_ResetErrorDetection_();
      }
    }
  }
  //else: error sate <Off> -> keep Active for detected AL EC (or NoDetecting
  //                          after clearing error information) and
  //                          keep NoDetecting for other AL ECs
  (void)Rte_Write_CddDcm_ErrorStatus(&CddDcmCtrl_sErrorStatus);
  //PRQA S 5310,5316, 5324, 5330, 5336 2 // STPTH = 1095, exceeds threshold for Number of paths
}

STATIC_AL void CddDcmCtrl_ResetErrorDetection_(void)
{
  // reset HalDcm voltage evaluation, CtrlDcm error counting and AL ECs
  CddDcmCtrl_nErrCnt_ms = CddDcmCtrl_ErrInit;

  CddDcmHal_ResetVoltageState();

  CddDcmCtrl_nErrCntLow     = 0;
  CddDcmCtrl_nErrCntHigh    = 0;
}

STATIC_AL boolean CddDcmCtrl_IsMovingChannel(void)
{
  return (boolean)(((CddDcmCtrl_eState == CtrlDcm_StateNotActive) ||
                    (CddDcmCtrl_eState == CtrlDcm_StateLocked)    ||
                    (CddDcmCtrl_eState == CtrlDcm_StateErrorOff))  ? FALSE : TRUE);
}


//-----------------------------------------------------------------------------
/// \brief  init fct call
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void CddDcmCtrl_Init(void)
{
  // switch off both PwmChannels
  CddDcmHal_DisableAndPwmOffChannel();

  CddDcmCtrl_eVoltage = CtrlDcm_VoltOff;
  CddDcmCtrl_InitChannel();
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr  -
///
/// \param  - 
///
/// \return void 
///
//-----------------------------------------------------------------------------
void CddDcmCtrl_Main(void)
{
  static uint8 ucSumCounter = 0;

  // Called every 1000ms
  if(++ucSumCounter >= CddCtrlDCM_CYCLE_CTRL_TIME_COUNT)
  {
    ucSumCounter = 0;
    CddDcmCtrl_AlarmTimeout();
  }

  CddDcmCtrl_CyclicAlarm();

  CddDcmCtrl_VoltChange();
  
  CddDcmCtrl_CtrlMsg();  // period call of controll???
}

