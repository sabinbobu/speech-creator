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
  /// \file  _CddStp88XX.h
  ///
  /// \brief  Global definitions and types of complex driver DRV88XX
  ///
  /// \descr  
  ///
  /// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
  ///         J. Kling ALRT-EES6 (f84304b)
  //-----------------------------------------------------------------------------

#ifndef ___CDDSTP88XX_H__
#define ___CDDSTP88XX_H__

  // #include <Alx1_div/Alx1_Hal_Dxx_Util/Util_Lit_Types.h>
  // jk: new
  // ---------------------------------------------------------------------------
/// \descr state action
///
typedef enum 
{
  ActEntry,         ///< entry action  
  ActDo,            ///< do activity
  ActExit           ///< exit action 
}
tAction;



  // optimize code in case of array size 1
  #if (CFA_CNT_STP_88XX== 1)
    #define CDDSTP88XX_OptimizeArrayIndex(x) ((void)(x)); ((x) = 0);
  #else
    #define CDDSTP88XX_OptimizeArrayIndex(x)
  #endif
  

  // ---------------------------------------------------------------------------
  // 
  // ---------------------------------------------------------------------------
  // Definitions for Dem event types

  // Stp Dem event types
  typedef enum
  {
    CddStp88XX_eDemEType_OL           = 0, // - Open_Load (ErrElecOL)
    CddStp88XX_eDemEType_SC,         // 1     - Shortcut (pIsSCCntMax & ErrElecSC)
    CddStp88XX_eDemEType_Driver,     // 2     - stepper driver defect (call from CAT1-ISR is not possible)
    CddStp88XX_eDemEType_Pos,        // 3     - hori. stepper/PSense: position error
    CddStp88XX_eDemEType_TempSD,     // 4     - thermal shutdown (OTS / ErrTherm)
    CddStp88XX_eDemEType_TempWarn,   // 5     - thermal warning info
    CddStp88XX_eDemEType_RefUVolt,   // 6     - break of reference run because of undervoltage (SysVoltOff)
    CddStp88XX_eDemEType_MoveUVolt,  // 7     - break of run because of undervoltage (SysVoltUnder)
    CddStp88XX_eDemEType_MoveOvVolt, // 8     - break of run because of overvoltage (SysVoltOver)
    CddStp88XX_eMaxDemEType          // -> 9
  }
  tCddStp88XXDemErrorType;


  // ---------------------------------------------------------------------------
  // states and flags
  // ---------------------------------------------------------------------------

  typedef enum
  {
    CddStp88XX_eStateInit       = 0,  // must be 0 (init. value)
    CddStp88XX_eStateOff,      // 1
    CddStp88XX_eStateStby,     // 2
    CddStp88XX_eStateIdle,     // 3
    CddStp88XX_eStateMove,     // 4
    CddStp88XX_eStateRef1,     // 5
    CddStp88XX_eStateRef2,     // 6
    CddStp88XX_eStateRefWait,  // 7
    CddStp88XX_eStateTestStep, // 8
    CddStp88XX_eStateErr,      // 9
    CddStp88XX_eMaxStates      // 10 // numbers of states = end of states for state machine table
  } tStateCddStp88XX;

  typedef enum
  {
    _biSt00      =  0,  // dummy instead of tStateCddStp88XX bit 0
    _biSt01      =  1,  // dummy instead of tStateCddStp88XX bit 1
    _biSt02      =  2,  // dummy instead of tStateCddStp88XX bit 2
    _biSt03      =  3,  // dummy instead of tStateCddStp88XX bit 3
    _biDrvOn     =  4,  // driver switched on
    _biDoCalc    =  5,  // 
    _biReady     =  6,  // 
    _biMoving    =  7,  // 
    _biOffReq    =  8,  // state "off" requested in case of undervoltage
    _biRefActive =  9,  // referencing active
    _biDummy     = 10,  // corresponding to state "Dummy"
    _biRef1      = 11,  // corresponding to state "Ref1"
    _biRef2      = 12,  // corresponding to state "Ref2"
    _biRefWait   = 13,  // corresponding to state "RefWait"
    _biIdle      = 14,  // corresponding to state "Idle"
    _biStpOn     = 15   // stepper on or error state
  } tCddStpBitPos;

  #define _M_St00       ( (uint32)1 << _biSt00      )
  #define _M_St01       ( (uint32)1 << _biSt01      )
  #define _M_St02       ( (uint32)1 << _biSt02      )
  #define _M_St03       ( (uint32)1 << _biSt03      )
  #define _M_DrvOn      ( (uint32)1 << _biDrvOn     )
  #define _M_DoCalc     ( (uint32)1 << _biDoCalc    )
  #define _M_Ready      ( (uint32)1 << _biReady     )
  #define _M_Moving     ( (uint32)1 << _biMoving    )
  #define _M_OffReq     ( (uint32)1 << _biOffReq    )
  #define _M_RefActive  ( (uint32)1 << _biRefActive )
  #define _M_Dummy      ( (uint32)1 << _biDummy     )
  #define _M_Ref1       ( (uint32)1 << _biRef1      )
  #define _M_Ref2       ( (uint32)1 << _biRef2      )
  #define _M_RefWait    ( (uint32)1 << _biRefWait   )
  #define _M_Idle       ( (uint32)1 << _biIdle      )
  #define _M_StpOn      ( (uint32)1 << _biStpOn     )

  // state is defined by bits 0...3 (max. 16 states)
  #define _M_Stpstate   (  _M_St00  \
                         | _M_St01  \
                         | _M_St02  \
                         | _M_St03  )

/*
  //                                  state                     | _M_DrvOn | _M_StpOn | _M_DoCalc | _M_Ready | _M_Moving | _M_OffReq | _M_RefActive | _M_Dummy  | _M_Ref1 | _M_Ref2 | _M_RefWait | _M_Idle
  #define attr_StateOff     ((uint32) CddStp88XX_eStateOff     |    0     |    0     |    0      |    0     |    0      |    0      |      0       |    0      |    0    |    0    |    0       |    0    )
  #define attr_StateErr     ((uint32) CddStp88XX_eStateErr     |    0     | _M_StpOn |    0      |    0     |    0      |    0      |      0       |    0      |    0    |    0    |    0       |    0    )
  #define attr_StateRef1    ((uint32) CddStp88XX_eStateRef1    | _M_DrvOn | _M_StpOn | _M_DoCalc |    0     | _M_Moving | _M_OffReq | _M_RefActive |    0      | _M_Ref1 |    0    |    0       |    0    )
  #define attr_StateRef2    ((uint32) CddStp88XX_eStateRef2    | _M_DrvOn | _M_StpOn | _M_DoCalc |    0     | _M_Moving | _M_OffReq | _M_RefActive |    0      |    0    | _M_Ref2 |    0       |    0    )
  #define attr_StateRefWait ((uint32) CddStp88XX_eStateRefWait | _M_DrvOn | _M_StpOn |    0      |    0     | _M_Moving | _M_OffReq | _M_RefActive |    0      |    0    |    0    | _M_RefWait |    0    )
  #define attr_StateIdle    ((uint32) CddStp88XX_eStateIdle    | _M_DrvOn | _M_StpOn |    0      | _M_Ready |    0      |    0      |      0       |    0      |    0    |    0    |    0       | _M_Idle )
  #define attr_StateMove    ((uint32) CddStp88XX_eStateMove    | _M_DrvOn | _M_StpOn | _M_DoCalc |    0     | _M_Moving | _M_OffReq |      0       |    0      |    0    |    0    |    0       |    0    )
*/

/*// alternative definition by using enum
  typedef enum
  {                                // state                     | _M_DrvOn | _M_StpOn | _M_DoCalc | _M_Ready | _M_Moving | _M_OffReq | _M_RefActive | _M_Dummy  | _M_Ref1 | _M_Ref2 | _M_RefWait | _M_Idle
    attr_StateOff                   = CddStp88XX_eStateOff     |    0     |    0     |    0      |    0     |    0      |    0      |      0       |    0      |    0    |    0    |    0       |    0    ,
    attr_StateErr                   = CddStp88XX_eStateErr     |    0     | _M_StpOn |    0      |    0     |    0      |    0      |      0       |    0      |    0    |    0    |    0       |    0    ,
    attr_StateRef1                  = CddStp88XX_eStateRef1    | _M_DrvOn | _M_StpOn | _M_DoCalc |    0     | _M_Moving | _M_OffReq | _M_RefActive |    0      | _M_Ref1 |    0    |    0       |    0    ,
    attr_StateRef2                  = CddStp88XX_eStateRef2    | _M_DrvOn | _M_StpOn | _M_DoCalc |    0     | _M_Moving | _M_OffReq | _M_RefActive |    0      |    0    | _M_Ref2 |    0       |    0    ,
    attr_StateRefWait               = CddStp88XX_eStateRefWait | _M_DrvOn | _M_StpOn |    0      |    0     | _M_Moving | _M_OffReq | _M_RefActive |    0      |    0    |    0    | _M_RefWait |    0    ,
    attr_StateIdle                  = CddStp88XX_eStateIdle    | _M_DrvOn | _M_StpOn |    0      | _M_Ready |    0      |    0      |      0       |    0      |    0    |    0    |    0       | _M_Idle ,
    attr_StateMove                  = CddStp88XX_eStateMove    | _M_DrvOn | _M_StpOn | _M_DoCalc |    0     | _M_Moving | _M_OffReq |      0       |    0      |    0    |    0    |    0       |    0
  } tCddStpAttr;
*/

  //---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // Definitions for table state machine(s)

  // Command parameters of state machine call
  typedef enum
  {
    CddStp88XX_eCmdInit,
    CddStp88XX_eCmdMain,
    CddStp88XX_eCmdCtrl,
    CddStp88XX_eCmdEvent,
    CddStp88XX_eCmdPsens
  }
  tCommandCddStp88XX;


  // Transition function pointer
  typedef uint32 (*ptTransitionFctPtrCddStp88XX)(uint8, tCommandCddStp88XX);
  
  
  // Transition function informations
  typedef struct
  {
    const tStateCddStp88XX             eNewState;
    const ptTransitionFctPtrCddStp88XX ptTransitionFct;
  } tTransitionCddStp88XX;
  
  
/*// Simple StateMachine
  typedef struct
  {
    const uint8                         ucCount;
    const tTransitionCddStp88XX *const pTransition;
  } tStateMachineCddStp88XX;
*/

  typedef void (*tStateFctPtrCddStp88XX)(uint8, tAction);

  typedef struct
  {
    const uint8                        ucCount;
    const tTransitionCddStp88XX *const pTransition;
    const tStateFctPtrCddStp88XX       pStateFct;
  } tStateMachineCddStp88XXSF;
  //---------------------------------------------------------------------------



#endif // ___CDDSTP88XX_H__
