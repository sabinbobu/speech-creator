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
  /// \file  CddStp88XXTemp.h
  ///
  ///  \brief  Definitions for CddStp88XX temperature state machine
  ///
  ///  \descr  
  ///
  /// \author Wuesteney, Ulrich ALRT/EEG-PM2 * (wu82rt)
  ///         mailTo:ulrich.wuesteney[A]al-lighting.com       
  ///         J. Kling ALRT-EES6 (f84304b)
  //-----------------------------------------------------------------------------

#ifndef __CDDSTP88XXTEMP_H__
#define __CDDSTP88XXTEMP_H__

  #include <stdbool.h>

  // ---------------------------------------------------------------------------
  // type definitions
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // Stepper Temperature states and flags
  // ---------------------------------------------------------------------------

  typedef enum
  {
    CddStp88XX_eStateTempInit       = 0,  // must be 0 (init. value)
    CddStp88XX_eStateTempNorm,     // 1
    CddStp88XX_eStateTempLow,      // 2
    CddStp88XX_eStateTempHigh,     // 3
    CddStp88XX_eMaxStatesTemp      // 4 // numbers of states = end of states for state machine table
  } tStateTempCddStp88XX;


  // Transition function informations
  typedef struct
  {
    const tStateTempCddStp88XX         eNewState;
    const ptTransitionFctPtrCddStp88XX ptTransitionFct;
  } tTempTransitionCddStp88XX;

  
  typedef struct
  {
    const uint8                             ucCount;
    const tTempTransitionCddStp88XX *const pTransition;
    const tStateFctPtrCddStp88XX           pStateFct;
  } tTempStateMachineCddStp88XXSF;
  //---------------------------------------------------------------------------
  
  
  // ---------------------------------------------------------------------------
  // externals
  // ---------------------------------------------------------------------------

  extern tCddStpTempState       CddStp88XX_aeTemp        [CFA_CNT_STP_88XX];
  extern tsRte_CddStpActual        CddStp_ActAll;


  // ---------------------------------------------------------------------------
  // prototypes
  // ---------------------------------------------------------------------------
  INLINE bool CddStpTemp_IsHighTemp(uint8 ucIx)
  {
    return (bool)(CddStp88XX_aeTemp[ucIx] == CddStp_eTempState_HighTemp);
  }

  void CddStp8899Temp_CheckLowTemp(void);
  void CddStp88XXTemp_StateMachine(uint8 ucIx, const tCommandCddStp88XX eCmd);

#endif // __CDDSTP88XXTEMP_H__
