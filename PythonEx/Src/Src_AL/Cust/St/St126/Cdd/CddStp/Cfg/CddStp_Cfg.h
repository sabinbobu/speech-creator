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
/// \file  CddStp_Cfg.h
///
/// \brief
///
//// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

#ifndef CDD_STP_CFG_H_
#define CDD_STP_CFG_H_

#define TYP_OS              (0u)
#define CFG_OPT_STATISTIC   (0u)


// driver (CFG_DRV_...)
#define CFG_Drv_None                     1U
#define CFG_Drv_Default                  2U
// driver (CFG_DRV_SER and CFG_DRV_SER2)
#define CFG_Drv_Extended                 3U
// driver (CFG_DRV_PSENS)
#define CFG_Drv_Alternative1             4U
#define CFG_Drv_Alternative2             5U


// stepper options (CFG_OPT_STP)
#define CFG_Stp_SupportSlaveAddr          0x0001U   // support different addresses depending on master/slave selection
#define CFG_Stp_IgnoreMissingPsens        0x0002U   // no position error if Psens missing
#define CFG_Stp_UseInvPsensPol            0x0004U   // use of dynamic configuration of interface function CxdStpXxx0/1_InvertPsensPolarity()
#define CFG_Stp_PsensDiag                 0x0008U   // diagnosis of position sensor available
#define CFG_Stp_SwitchPsensSigDiag        0x0010U   // CFG_Stp_PsensDiag without position sensor signal diagnosis and possibility to switch on by using CxdStpXxx0/1_SwitchPsensSignalDiag()
#define CFG_Stp_PosCorr                   0x0020U   // use position correction on LIN based systems (all onboard systems use position correction)
#define CFG_Stp_TimeoutLock               0x0040U   // lock timeout state after timeout error entry
#define CFG_Stp_OnAfterPowerOn            0x0080U   // switch on driver immediately after power on (Teststeps and hold current)

// CFG_TYP_STPXXXn (XXXn = VER0, HOR0, SHT0)
#define CFG_Stp_None                      1U
#define CFG_Stp_Prj                       2U
#define CFG_Stp_9942                      3U   // ST L9942
#define CFG_Stp_88XX                      4U   // ON DRV88XX
#define CFG_Stp_706XX                     5U   // ON DRV706xx (as external stepper via LIN-subbus)

// statistic options (CFG_OPT_STATISTIC)
#define CFG_Statistic_ExtendedStpLwr        0x0001U
#define CFG_Statistic_ExtendedStpKl         0x0002U
#define CFG_Statistic_ExtendedStpGlw        0x0004U
#define CFG_Statistic_ExtendedTl            0x0008U


// CL types (CFG_TYP_CL)
#define CFG_Cl_None                      1U
#define CFG_Cl_AlgPrj                    2U
#define CFG_Cl_Alg1                      3U
#define CFG_Cl_Alg2                      4U
#define CFG_Cl_Alg3                      5U


// 2 bit status information in signals
#define CFG_TYP_CL    CFG_Cl_None
#if    (CFG_TYP_CL == CFG_Cl_None)

  #define  LIT_SignalMissing    (0x00u)
  #define  LIT_SignalOk         (0x01u)
  #define  LIT_SignalError      (0x03u)

  //#define  LIT_SigWarn          (0x00u)  // do not change numbers:
  //#define  LIT_SigOk            (0x01u)  //   - 0x00 is used as initial value
  //#define  LIT_SigErrUnFix      (0x02u)  //   - numbers are used as indices
  //#define  LIT_SigErrFix        (0x03u)

#endif



//  -----------------------------------------------------------------------------------------------
//  stepper configuration

// jk-tbd
#define                                     CFG_Stp_CntVer         (1u)  // Number of Vertical   Steppers (LWR)
#define                                     CFG_Stp_CntHor         (0u)  // Number of Horizontal Steppers (AHL)
#define                                     CFG_Stp_CntSht         (0u)  // Number of Shutter    Steppers
#define                                     CFG_Stp_CntLlr         (0u)  // Number of Laser      Steppers

#define                        CFG_Stp_Cnt /*Daisy-Chain... :( */  (4u)  // (CFG_Stp_CntVer + CFG_Stp_CntHor + CFG_Stp_CntSht) // Number of Steppers

#define CFA_CNT_STP            (4u) // CFG_Stp_Cnt
#define CFA_CNT_STP_88XX       (4u) // CFG_Stp_Cnt
#define CFA_CNT_STP_ONBRD      (4u) // CFG_Stp_Cnt
#define CFA_CNT_STPVER0_ONBRD  CFG_Stp_CntVer
#define CFA_CNT_STPHOR0_ONBRD  CFG_Stp_CntHor
#define CFA_CNT_STPSHT0_ONBRD  CFG_Stp_CntSht

#define SUPPORT_NO             FALSE



#define CFG_Stp_IdxVer        (0u)                                       // Index  of Vertical   Stepper
#define CFG_Stp_IdxHor        (1u)                                       // Index  of Horizontal Stepper
#define CFG_Stp_IdxSht        (2u)                                       // Index  of Shutter    Stepper
#define CFG_Stp_IdxLlr        (3u)                                       // Index  of Laser      Stepper


#if (CFA_CNT_STPVER0_ONBRD == 1)
  #define CFG_DRV_STP_LWR                   CFG_Drv_Default
#else
  #define CFG_DRV_STP_LWR                   CFG_Drv_None
#endif
#if (CFA_CNT_STPHOR0_ONBRD == 1)
  #define CFG_DRV_STP_KL                    CFG_Drv_Default
#else
  #define CFG_DRV_STP_KL                    CFG_Drv_None
#endif
#if (CFA_CNT_STPSHT0_ONBRD == 1)
  #define CFG_DRV_STP_GLW                   CFG_Drv_Default
#else
  #define CFG_DRV_STP_GLW                   CFG_Drv_None
#endif
  


#define CFG_OPT_STP                       (0u) // CFG_Stp_OnAfterPowerOn


#endif // CDD_STP_CFG_H_

// EOF
