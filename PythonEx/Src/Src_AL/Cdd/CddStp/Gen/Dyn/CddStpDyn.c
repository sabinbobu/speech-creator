//  ***************************************************************************
//
//  (C) Automotive-Lighting Reutlingen GmbH  -  ALRT/EEG4
//      Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
//  ***************************************************************************

/// ---------------------------------------------------------------------------
///
///  \file    CddStpDyn.c
///
///  \author  Peter Ott ALRT/EEG4 (otp2rt)
///
///  \owner   Peter Ott ALRT/EEG4 (otp2rt)
///
///  \date    31.05.2007
///
///  \brief   
///
///  \descr   
///
/// ---------------------------------------------------------------------------

#include <Std_Types.h>
//#include <../Gen/CddStpDynBuf.h>
#include <CddStpDynBuf.h>

#include <AL_Helper.h> //-- STATIC_AL
#include <UtilUtility.h>

#include <UtilBase_Atomic.h>

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#include <../Cdd/CddStp/CddStpData.h>
#include <../Cdd/CddStp/Cfg/CddStp_Cfg.h>
#include <../Cdd/CddStp/CddStpPrj.h>
#else // Unit-Tests!
  #define CFA_CNT_STP_88XX   (4u)
  #define CFA_CNT_STP_ONBRD  (4u)
  #include <CddStpPrj.h>
  #include <CddStpData.h>
#endif

#include <8899/CddStp8899Cfg.h>
#include <88XX/CddStp88XX_HalStp.h>
#include <8899/CddStp8899Com.h>

#if    (CFA_CNT_STP_88XX != 0)

  #include <CddStpCfg.h>      // incl. nothing
  #include <CddStpTypes.h>    // incl. '88XX/CddStp88XX_HalStp.h'

  #include <Dyn/_CddStpDyn.h>
  #include <Dyn/CddStpDyn.h>
  #include <Dyn/CddStpDynBuf.h>


  //  ---------------------------------------------------------------------------
  //  defines
  //  ---------------------------------------------------------------------------

  #define CDDSTPDYN_PrePostStepScale     (10000u)  // scaling of pre/post step parameters
  #define CDDSTPDYN_PrePostStepMin        (2000u)  // minimum step time because of SPI jitter
  #define CDDSTPDYN_PrePostStepMax       (65535u)  // maximum step time to avoid overflow
  #define CDDSTPDYN_PostStepAdd           (4000u)  // minimum delta between post step time and direction change time
  #define CDDSTPDYN_StpTableSize            (76u)  // maximum size for step table (according to slowest AL profile)
  #define CDDSTPDYN_ZeitUmkehrMin         (4000u)  // minimum value needed in case of wrong coding parameters
  #define CDDSTPDYN_AnzahlRef2Min           (16u)  // minimum value needed in case of wrong coding parameters


  //  ---------------------------------------------------------------------------
  //  constants
  //  ---------------------------------------------------------------------------



  //  ---------------------------------------------------------------------------
  //  types
  //  ---------------------------------------------------------------------------

  typedef struct
  {
    unsigned  biDummy1   : 16;   // do not use bit access to this variable
    unsigned  biDummy2   :  8;   // do not use bit access to this variable
    unsigned  biInit     :  1;   // reset dynamic calculation if this bit is set
    unsigned  biReserved :  7;
  }tStpTabRamBit;

  typedef struct
  {
    uint16  unMinPeriod;         // min. HS duration (frequency limitation)
    uint8   ucMaxIx;             // max. index to step table
    uint8   ucDummy;             // used for bitwise access
  }tStpTabRamVal;

  typedef union
  {
    tStpTabRamVal Val;           // use Val for initialization
    tStpTabRamBit Bit;
  }tStpTabRam;


  //  ---------------------------------------------------------------------------
  //  global variables (accessable for inline functions placed in header)
  //  ---------------------------------------------------------------------------
  
  STATIC_AL tStpTabRam StpTabRam[] =
  {
    // ulMinPeriod    maxIx   flags
    {{      0,        0xFF,     0 }}
    #if(CFA_CNT_STP_88XX == 2)
      ,{{   0,        0xFF,     0 }}
    #endif
  };

  STATIC_AL tStpTabRam*  CddStpDyn_pStpInfo;   // pointer to RAM area with info about actual 

  //  ---------------------------------------------------------------------------
  //  static variables
  //  ---------------------------------------------------------------------------

  // The lifetime of these variables is from the beginning to the end of "CddStpDyn_CalcNextSteps()"
  typedef struct
  {
    unsigned int  biFirstStep  : 1;
    unsigned int  biAboveResF1 : 1; // !resonance frequency 1 is lower  than 2!
    unsigned int  biAboveResF2 : 1; // !resonance frequency 2 is higher than 1!
    unsigned int  biStop       : 1;
  }tCddStpDynBits;

  // variables without indices (used in CddStpDyn_CalcNextSteps())
  STATIC_AL tCddStpDynBits      CddStpDyn_Bits;
  STATIC_AL uint8               CddStpDyn_ucIx;
  STATIC_AL sint32              CddStpDyn_lCurrentDir;
  STATIC_AL sint32              CddStpDyn_lStepsToDo;
  STATIC_AL uint8               CddStpDyn_ucActTabIx;

  STATIC_AL uint8               CddStpDyn_aucLastTabIx[CFA_CNT_STP_88XX];
  STATIC_AL uint16              CddStpDyn_aunHsZeit   [CFA_CNT_STP_88XX][CDDSTPDYN_StpTableSize];

  // The lifetime of these variables is 1 full referencing cycle               // number of steps for
  STATIC_AL uint16              CddStpDyn_unRefSteps  [CFA_CNT_STP_88XX];         //   - referencing

  STATIC_AL uint16              CddStp_unPreStepLen   [CFA_CNT_STP_88XX];         // length of pre step in microseconds
  STATIC_AL uint16              CddStp_unPostStepLen  [CFA_CNT_STP_88XX];         // length of post step in microseconds


  //  ---------------------------------------------------------------------------
  //  prototypes of static functions
  //  ---------------------------------------------------------------------------

  STATIC_AL void   CddStpDyn_CalcNormal(void);
  STATIC_AL void   CddStpDyn_CalcRef2(void);
  STATIC_AL void   CddStpDyn_CalcRef1(void);
  STATIC_AL void   CddStpDyn_PreStep(void);
  STATIC_AL void   CddStpDyn_GetStartConditions(void);
  STATIC_AL uint8  CddStpDyn_GetIx(uint8 ucIx, uint16 unStepTime);
  STATIC_AL uint16 CddStpDyn_GetStpTime(uint8 ucTabIx);
  STATIC_AL uint16 CddStpDyn_CalcNextHalfStepTime(uint8 ucIx, uint16 unT_n1);
  STATIC_AL /*obsolet: 'inline'*/ void   CddStpDyn_DecActTabIx(void);
  STATIC_AL /*obsolet: 'inline'*/ void   CddStpDyn_IncActTabIx(void);
  STATIC_AL /*obsolet: 'inline'*/ sint32 CddStpDyn_GetSign(sint32 lValue);


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  CddStpDyn_CalcNextHalfStepTime
  ///
  /// \descr  Calculates 1 step of the acceleration ramp
  ///
  /// \param  uint8  ucIx
  ///         uint16 unT_N1: last halfstep time [0.5us]
  ///
  ///         formula: T(n) = 1 / ((T(n-1) * Acc) + (1 / T(n-1)))
  ///
  ///         Assume halfstep time T in [0.5us], Vmin/Vmax in [HS/s] and Acc in [HS/s*s]
  ///         ulK = 10^12 / 2^8
  ///         unT_n = ulK / (((unT_n1 * unAcc) / 2^10) + (ulK / unT_n1))
  ///
  /// \return uint16: new halfstep time [0.5us]
  ///
  STATIC_AL uint16 CddStpDyn_CalcNextHalfStepTime(uint8 ucIx, uint16 unT_n1)
  {
    const uint32 ulK     = 3906250000uL;     // = 10^12 / 2^8;
    const uint32 ulAcc  = (Cod_LwrAcc() == 0u) ? 12000u : Cod_LwrAcc();
    const uint32 ulDenom = (((uint32) unT_n1 * ulAcc) / 1024u) + (ulK / unT_n1);

    (void)ucIx; //parameter not available for multiple steppers

    return (uint16) ((ulK + (ulDenom / 2u)) / ulDenom);  // divide and round
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  CddStpDyn_CodingDataValid                Measured Runtime: FX4L 136us incl. Interrupts
  ///
  /// \descr  This function is used to do calculations based on coding data.
  ///         Usually called in fct 'roCddStp_ParaFct0'/'CddStp88XX_ParaFct0' (jk-tbd: explicit temporarily called in fct 'CddStp88XX_Init_')
  ///
  /// \param  void
  ///
  /// \return -
  ///
  void CddStpDyn_CodingDataValid(void)
  {
    uint8 ucIx = 0; // LWR

    uint16 unT;
    uint8  ucTabIx;
    uint16 unPreStepLen;
    uint16 unPostStepLen;

    const uint32 ulVmin  = (Cod_LwrVmin() == 0u) ? 100u : Cod_LwrVmin();
    const uint32 ulVmax  = (Cod_LwrVmax() == 0u) ? 800u : Cod_LwrVmax();
    const uint16 unT_min = (uint16) ((2000000u + (ulVmax / 2u)) / ulVmax);  // calculate Tmin in [0.5us] and round
    unT                  = (uint16) ((2000000u + (ulVmin / 2u)) / ulVmin);  // calculate Tstart in [0.5us] and round

    // calculate step length in microseconds, use minimum value to avoid counter problems in case of coding
    // parameter is zero. See also the tolerance specification of pre and post step. Limit to 16bit
    unPreStepLen  = (uint16) UTIL_MIN(CDDSTPDYN_PrePostStepMax, CDDSTPDYN_PrePostStepScale * Cod_LwrVorbestZeit());   // [10ms] --> [1us]
    unPostStepLen = (uint16) UTIL_MIN(CDDSTPDYN_PrePostStepMax, CDDSTPDYN_PrePostStepScale * Cod_LwrNachbestZeit());  // [10ms] --> [1us]

    CddStp_unPreStepLen [ucIx] = UTIL_MAX(CDDSTPDYN_PrePostStepMin, unPreStepLen);  // do not allow 0 to avoid counter problems
    CddStp_unPostStepLen[ucIx] = UTIL_MAX(CDDSTPDYN_PrePostStepMin, unPostStepLen);

    // 1st entry (index 0) is time for direction change
    CddStpDyn_aunHsZeit[ucIx][0u] = (uint16) (1000u * Cod_LwrHsZeitUmkehr());

    if (CddStpDyn_aunHsZeit[ucIx][0u] < CDDSTPDYN_ZeitUmkehrMin)
    {
      CddStpDyn_aunHsZeit[ucIx][0u] = CDDSTPDYN_ZeitUmkehrMin;
    }
    
    // calculate halfstep table
    for(ucTabIx = 1u; ucTabIx < CDDSTPDYN_StpTableSize; ucTabIx++)
    {
      CddStpDyn_aucLastTabIx[ucIx] = ucTabIx;

      if(unT <= unT_min)
      {
        CddStpDyn_aunHsZeit[ucIx][ucTabIx] = (unT_min + 1u) / 2u;  // convert Vmax halfstep time to [us], round and store in step table
        break;
      }

      CddStpDyn_aunHsZeit  [ucIx][ucTabIx] = (unT + 1u) / 2u;         // convert to [us], round and store in step table

      unT = CddStpDyn_CalcNextHalfStepTime(ucIx, unT);  // calculate next halfstep time
    }
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  CddStpDyn_GetSign
  ///
  /// \descr  Extract sign of sint32 value
  ///
  /// \param  lValue
  ///
  /// \return sint32 1=positive, -1=negative
  ///
  STATIC_AL inline sint32 CddStpDyn_GetSign(sint32 lValue)
  {
    return (lValue > 0) ? 1 : -1;
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Increment actual table index
  ///
  /// \descr  Increment index by 1
  ///
  /// \param  none
  ///
  /// \return none
  ///
  STATIC_AL inline void CddStpDyn_IncActTabIx(void)
  {
    CddStpDyn_ucActTabIx++;
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Decrement actual table index
  ///
  /// \descr  Decrement index to step table.
  ///         Starting at odd number:
  ///           - decrement by 1
  ///         Starting at even number:
  ///           - decrement by 1 if (Cod_LwrBremsSchnell() == FALSE)
  ///           - decrement by 2 if (Cod_LwrBremsSchnell() == TRUE)
  ///
  ///         Realization:
  ///         First decrementig by 1. Now check actual index. Do an additional decrement
  ///         in case of 
  ///           a) odd number and
  ///           b) fast deceleration coding parameter is set
  ///
  /// \param  none
  ///
  /// \return none
  ///
  STATIC_AL inline void CddStpDyn_DecActTabIx(void)
  {
    CddStpDyn_ucActTabIx--;

    if((CddStpDyn_ucActTabIx & 0x01u) != 0u)  // odd number
    {
      CddStpDyn_ucActTabIx = (Cod_LwrBremsSchnell() != FALSE) ? (CddStpDyn_ucActTabIx - 1u)
                                                              :  CddStpDyn_ucActTabIx;
    }
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  get step table entry according to actual frequency limitations
  ///         as well as optional resonance frequency suppression
  ///
  /// \descr  
  ///
  /// \param  ucTabIx     Index into step table
  ///
  /// \return uint16   step time
  ///
  STATIC_AL uint16 CddStpDyn_GetStpTime(uint8 ucTabIx)
  {
    uint16 unStpTime = CddStpDyn_aunHsZeit[CddStpDyn_ucIx][ucTabIx];

    unStpTime = UTIL_MAX(unStpTime, CddStpDyn_pStpInfo->Val.unMinPeriod);  // limit frequency

    if(ucTabIx > 1u)  // do not allow frequency reduction lower than next table entry
    {
      uint16 unStpTimeMax = CddStpDyn_aunHsZeit[CddStpDyn_ucIx][ucTabIx - 1u];
      unStpTime = UTIL_MIN(unStpTime, unStpTimeMax);
    }

    // optimization 1st "if" returns TRUE at high speed
    if     (unStpTime <= Cod_LwrResHsZeitO2())              // f > f_high2
    {
      CddStpDyn_Bits.biAboveResF1 = 1;
      CddStpDyn_Bits.biAboveResF2 = 1;
    }
    else if(unStpTime <= Cod_LwrResHsZeitU2())              // f > f_low2
    {
      if(CddStpDyn_Bits.biAboveResF2 != FALSE)              // frequency within resonance area 2 (!higher than 1!), descending
      {
        unStpTime = Cod_LwrResHsZeitO2();                   // f_high2
      }
      else                                                  //                                                      ascending
      {
        unStpTime = Cod_LwrResHsZeitU2();                   // f_low2
      }
    }
    else if(unStpTime <= Cod_LwrResHsZeitO1())              // f > f_high1
    {
      CddStpDyn_Bits.biAboveResF1 = 1;
      CddStpDyn_Bits.biAboveResF2 = 0;
    }
    else if(unStpTime <= Cod_LwrResHsZeitU1())              // f > f_low1
    {
      if(CddStpDyn_Bits.biAboveResF1 != FALSE)              // frequency within resonance area 1 (!lower  than 2!), descending
      {
        unStpTime = Cod_LwrResHsZeitO1();                   // f_high1
      }
      else                             //                                                      ascending
      {
        unStpTime = Cod_LwrResHsZeitU1();                   // f_low1
      }
    }
    else                                                    // f < f_low1
    {
      CddStpDyn_Bits.biAboveResF1 = 0;
      CddStpDyn_Bits.biAboveResF2 = 0;
    }

    return unStpTime;
    
    //PRQA S 5336 1 // STMIF exceeded due to reuse of existing code
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  get step table index calculated by step time
  ///         return higher index if step time is between 2 table entries
  ///
  /// \descr  
  ///
  /// \param  uint8       ucIx
  ///         unStepTime  step time
  ///
  /// \return uint8       table index
  ///
  STATIC_AL uint8 CddStpDyn_GetIx(uint8 ucIx, uint16 unStepTime)
  {
    uint8 ucTabIx;

    // find matching table index
    for(ucTabIx = 1; ucTabIx < CddStpDyn_aucLastTabIx[ucIx]; ucTabIx++)   // Ix = 0 is post current time
    {
      if(unStepTime >= CddStpDyn_aunHsZeit[ucIx][ucTabIx])          // frequency equal or lower
      {
        break;
      }
    }

    return ucTabIx;  // last table index will be returned
  }


  // ---------------------------------------------------------------------------
  ///
  ///  \func   CddStpDyn_Init
  ///
  ///  \brief  Initialisation of complex driver stepper dynamic
  ///
  ///  \param  uint8   ucIx:     stepper instance
  ///          boolean boHsMode: indicates halfstep mode
  ///
  ///  \return none  
  ///
  ///  \descr  
  ///
  ///  \todo  
  ///
  ///  \bug  
  ///
  // ---------------------------------------------------------------------------
  void CddStpDyn_Init(uint8 ucIx, boolean boHsMode)  
  {  
    (void) boHsMode;

    CddStpDyn_pStpInfo = &StpTabRam[ucIx];          // get pointers for fast access to ROM and RAM
    CddStpDyn_pStpInfo->Bit.biInit = 1;             // ignore actual motor dynamic for next movement

    CddStpDyn_pStpInfo->Val.ucMaxIx     = CddStpDyn_aucLastTabIx[ucIx];
    CddStpDyn_pStpInfo->Val.unMinPeriod = CddStpDyn_aunHsZeit[ucIx][CddStpDyn_aucLastTabIx[ucIx]];
    CddStpDyn_unRefSteps[ucIx]          = 0;
  }


  // ---------------------------------------------------------------------------
  ///
  ///  \func   CddStpDyn_SetFreq
  ///
  ///  \brief  Set frequency by using transfered frequency and voltage values
  ///
  ///  \param  uint8            ucIx:     stepper instance
  ///          uint16           unTmin:   value for Vmax (halfstep duration in microseconds)
  ///          uint16           unVolt:   actual voltage
  ///
  ///  \return boolean frequency reduced by low voltage
  ///
  ///  \descr  
  ///
  ///  \todo  modification of ucMaxIx
  ///
  ///  \bug  
  ///
  // ---------------------------------------------------------------------------
  boolean CddStpDyn_SetFreq(uint8 ucIx, uint16 unTmin, uint16 unVolt)
  {
    boolean  boReduced   = FALSE;
    uint16   unVoltLimit = 100u * (uint16)Cod_StpSpannungRed();  // 0.1 V --> mV

    CddStpDyn_pStpInfo = &StpTabRam[ucIx];     // get pointers for fast access to ROM and RAM

    // Tmin contains the value of the commanded frequency

    if(unVolt < unVoltLimit)
    {
      // do reduction of frequency: add 500 us per 1000 mV (division by 2) to last step table entry
      uint16 unLimitByVolt = ((uint16)(unVoltLimit - unVolt) / 2u) + CddStpDyn_aunHsZeit[ucIx][CddStpDyn_aucLastTabIx[ucIx]];

      unTmin = UTIL_MAX(unLimitByVolt, unTmin);     // now we have the frequency value depending on voltage and commanded frequency

      boReduced   = TRUE;
    }

    unTmin = UTIL_MIN(unTmin, CDDSTP_MaxHsPeriod);  // must fit to 15 bit

    if(CddStpDyn_pStpInfo->Val.unMinPeriod != unTmin)
    {
      CddStpDyn_pStpInfo->Val.unMinPeriod = unTmin;
      CddStpDyn_pStpInfo->Val.ucMaxIx     = CddStpDyn_GetIx(ucIx, unTmin);
    }

    return boReduced;
  }


  // ---------------------------------------------------------------------------
  ///
  ///  \func   CddStpDyn_GetStartConditions
  ///
  ///  \brief  Get start conditions for calculation of next entires in stepping buffer
  ///
  ///  \param  none
  ///
  ///  \return none  
  ///
  ///  \descr  
  ///
  ///  \todo  
  ///
  ///  \bug  
  ///
  // ---------------------------------------------------------------------------
  STATIC_AL void CddStpDyn_GetStartConditions(void)
  {
    // first get information about start condition: have a look at the step history
    if(CddStpDyn_pStpInfo->Bit.biInit != FALSE)   // reset requested by user command
    {
      CddStpDyn_pStpInfo->Bit.biInit = 0;
      CddStpDyn_ucActTabIx           = 0;     // reset dynamic and begin new movement
      CddStpDyn_Bits.biFirstStep     = 1;
      CddStpDyn_Bits.biAboveResF1    = 0;
      CddStpDyn_Bits.biAboveResF2    = 0;
      CddStpDyn_lCurrentDir          = 0;
    }
    else
    {
      CddStpDynBuf_ReadLastEntry();

      if(CddStpDynBuf_IsPause() != FALSE)  // indicating that no direction is defined
      {
        // get last direction to detect direction change
        sint32 lLastDir       = CddStpDynBuf_GetDirection();
        CddStpDyn_lCurrentDir = CddStpDyn_GetSign(CddStpDyn_lStepsToDo);

        // consecutive pause steps found in buffer
        //   - no steps to do:    do not interrupt these steps, increment buffer pointer until last pause entry is found
        //   - direction change:  do not interrupt these steps, increment buffer pointer until last pause entry is found
        //   - same direction:    overwrite the following entries
        if((CddStpDyn_lStepsToDo == 0) || (lLastDir != CddStpDyn_lCurrentDir))
        {
          boolean boLastStep = CddStpDynBuf_IsLastStep();
          boolean boIsPause;
          boolean boIsSet;

          CddStpDynBuf_ReadActualEntry();

          boIsPause  = CddStpDynBuf_IsPause();
          boIsSet    = CddStpDynBuf_IsSet();

          while(  (    boLastStep == FALSE )    // old entry was not last step
               && (    boIsPause  != FALSE  )    // new entry is also "pause" --> 2 consecutive pauses
               && (    boIsSet    != FALSE  ) )  // new entry valid
          {
            boLastStep = CddStpDynBuf_IsLastStep(); // seems that this line is at wrong position - TBD

            CddStpDynBuf_IncBufIx();                // increment index to find "LastStep" entry
            CddStpDynBuf_ReadActualEntry();

            boIsPause  = CddStpDynBuf_IsPause();
            boIsSet    = CddStpDynBuf_IsSet();
          }

          CddStpDynBuf_ReadLastEntry();   // repeat reading of last entry because Index was modified
        }
      }
      else
      {
        CddStpDyn_lCurrentDir  = CddStpDynBuf_GetDirection();
      }

      CddStpDyn_ucActTabIx          = CddStpDynBuf_GetDynTableIx();
      CddStpDyn_Bits.biFirstStep    = (CddStpDynBuf_IsLastStep()   != FALSE) ? 1u : 0u;    // after last step a first step must follow
      CddStpDyn_Bits.biAboveResF1   = (CddStpDynBuf_IsAboveResF1() != FALSE) ? 1u : 0u;
      CddStpDyn_Bits.biAboveResF2   = (CddStpDynBuf_IsAboveResF2() != FALSE) ? 1u : 0u;
    }

    //PRQA S 5324 1 // STCAL exceeded due to reuse of existing code
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Calculate pre step
  ///
  /// \descr  
  ///
  /// \param  -
  ///
  /// \return -
  ///
  STATIC_AL void CddStpDyn_PreStep(void)
  {
    uint16 unT;
    #if(CFA_CNT_STP_ONBRD == 2)
    uint32  ulSchrittMod = (CddStpDyn_ucIx == CFG_Stp_IdxVer) ? Cod_LwrSchrittMod() : Cod_AhlSchrittMod();
    #else
    uint32  ulSchrittMod = Cod_LwrSchrittMod();
    #endif

    CddStpDyn_lCurrentDir = CddStpDyn_GetSign(CddStpDyn_lStepsToDo);

    // pre-step
    CddStpDynBuf_ClrHsEntry   ();           // prepare empty halfstep entry
    CddStpDynBuf_SetFirstStep (TRUE);
    CddStpDynBuf_SetPause     (TRUE);
    CddStpDynBuf_SetDirection (CddStpDyn_lCurrentDir);
    CddStpDynBuf_SetHsTime    (CddStp_unPreStepLen[CddStpDyn_ucIx]);
    CddStpDynBuf_WriteToBuffer();

    // 1st real step
    CddStpDynBuf_ClrHsEntry  ();            // prepare empty halfstep entry
    CddStpDynBuf_SetDirection(CddStpDyn_lCurrentDir);

    // no step intended in halfstep mode: use (short) dummy step
    if(ulSchrittMod == (uint32)NvmPara_eSchrittMod2) // halfstep mode
    {
      unT = CDDSTP_DummyStepTime;
    }
    else
    {
      unT = CddStpDyn_aunHsZeit[CddStpDyn_ucIx][1u];
    }

    CddStpDynBuf_SetHsTime(unT);
    CddStpDynBuf_WriteToBuffer();

    CddStpDyn_lStepsToDo -= CddStpDyn_lCurrentDir;
    
    //PRQA S 5324 1 // STCAL exceeded due to reuse of existing code
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Calculate referencing steps according to dynamic requirements
  ///
  /// \descr  If this function is called first, the number of halfsteps for a full referencing
  ///         scheme are calculated. Afterwards (and in all following calls) a clip of approx.
  ///         CDDSTP_DynCalcTime will be calculated and stored in the halfstep buffer.
  ///
  /// \param  -
  ///
  /// \return -
  ///
  STATIC_AL void CddStpDyn_CalcRef1(void)
  {
    STATIC_AL uint16  CddStpDyn_unRefNconst1 [CFA_CNT_STP_88XX];      //   - 1st movement at high speed
    STATIC_AL uint16  CddStpDyn_unRefNconst2 [CFA_CNT_STP_88XX];      //   - 2nd movement at low speed
    STATIC_AL uint8   CddStpDyn_ucRefNacc    [CFA_CNT_STP_88XX];      //   - acceleration phase
    STATIC_AL uint8   CddStpDyn_ucRefNdec1   [CFA_CNT_STP_88XX];      //   - deceleration between 1st and 2nd movement
    STATIC_AL uint8   CddStpDyn_ucRefNdec2   [CFA_CNT_STP_88XX];      //   - deceleration after 2nd movement

    if(CddStpDyn_lStepsToDo > 0)
    {
      // enlarge absolute value by 1 because n steps are represented by n+1 (including PreStep and LastStep)
      CddStpDyn_lStepsToDo++;
    }
    else if(CddStpDyn_lStepsToDo < 0)
    {
      // enlarge absolute value by 1 because n steps are represented by n+1 (including PreStep and LastStep)
      CddStpDyn_lStepsToDo--;
    }
    else// if(CddStpDyn_lStepsToDo == 0)
    {
      CddStpDyn_lStepsToDo += CddStpDyn_lCurrentDir;
    }

    if(CddStpDyn_unRefSteps[CddStpDyn_ucIx] == 0u)  // --> this function was called first time: do initialization
    {
      CddStpDyn_unRefSteps[CddStpDyn_ucIx] = ((uint16)((uint32) (UTIL_ABS(CddStpDyn_lStepsToDo))));  // number of commanded steps + last step

      CddStpDyn_ucRefNacc [CddStpDyn_ucIx] = CddStpDyn_GetIx(CddStpDyn_ucIx, Cod_LwrHsZeitRef1());
      CddStpDyn_ucRefNdec2[CddStpDyn_ucIx] = CddStpDyn_GetIx(CddStpDyn_ucIx, Cod_LwrHsZeitRef2()) + 1u;
      CddStpDyn_ucRefNdec1[CddStpDyn_ucIx] = (2u + CddStpDyn_ucRefNacc[CddStpDyn_ucIx]) - CddStpDyn_ucRefNdec2[CddStpDyn_ucIx];

      CddStpDyn_unRefNconst2[CddStpDyn_ucIx] = Cod_LwrHsAnzahlRef2();

      if (CddStpDyn_unRefNconst2[CddStpDyn_ucIx] < CDDSTPDYN_AnzahlRef2Min)
      {
        CddStpDyn_unRefNconst2[CddStpDyn_ucIx] = CDDSTPDYN_AnzahlRef2Min;
      }

      uint16 unSteps;
      unSteps =  (uint16)CddStpDyn_ucRefNacc   [CddStpDyn_ucIx]
               + (uint16)CddStpDyn_ucRefNdec1  [CddStpDyn_ucIx]
               + (uint16)CddStpDyn_ucRefNdec2  [CddStpDyn_ucIx]
               + (uint16)CddStpDyn_unRefNconst2[CddStpDyn_ucIx]
               + (uint16)1u;  // PreStep

      if (CddStpDyn_unRefSteps[CddStpDyn_ucIx] > unSteps)
      {
        CddStpDyn_unRefNconst1[CddStpDyn_ucIx] = CddStpDyn_unRefSteps[CddStpDyn_ucIx] - unSteps;
      }
      else
      {
        CddStpDyn_unRefNconst1[CddStpDyn_ucIx] = 0u; // minimum
      }

      CddStpDyn_PreStep();
    }

    // check overflow of actual position (p.e. in case of too short pre calculation time)
    if (Util_SameSign(CddStpDyn_lCurrentDir, CddStpDyn_lStepsToDo) == FALSE) // wrong direction
    {
      CddStpDynBuf_SetHsTime(CddStp_unPostStepLen[CddStpDyn_ucIx]);   // overwrite previous entry
      CddStpDynBuf_SetPause(TRUE);
      CddStpDynBuf_SetLastStep(TRUE);

      CddStpDynBuf_WriteToBuffer(); 
    }
    else
    {
      // prepare temporary storage with information that will not be changed in loop
      CddStpDynBuf_ClrHsEntry();
      CddStpDynBuf_SetDirection(CddStpDyn_lCurrentDir);

      // get absolute value for step counting
      CddStpDyn_lStepsToDo = UTIL_ABS(CddStpDyn_lStepsToDo);

      // set 1st referencing frequency as default
      CddStpDyn_pStpInfo->Val.unMinPeriod = Cod_LwrHsZeitRef1();

      do
      {
        uint32 ulStpCnt = CddStpDyn_unRefSteps[CddStpDyn_ucIx] - (uint32) CddStpDyn_lStepsToDo;

        if(ulStpCnt <= (uint32) CddStpDyn_ucRefNacc[CddStpDyn_ucIx])
        {
          // acceleration phase
          CddStpDyn_ucActTabIx = (uint8) ulStpCnt;
        }
        else if(ulStpCnt <= ((uint32)CddStpDyn_ucRefNacc[CddStpDyn_ucIx] + (uint32)CddStpDyn_unRefNconst1[CddStpDyn_ucIx]))
        {
          // 1st constant movement
          CddStpDyn_ucActTabIx = CddStpDyn_ucRefNacc[CddStpDyn_ucIx];
        }
        else if(ulStpCnt <= ( (uint32)CddStpDyn_ucRefNacc   [CddStpDyn_ucIx]
                            + (uint32)CddStpDyn_unRefNconst1[CddStpDyn_ucIx]
                            + (uint32)CddStpDyn_ucRefNdec1  [CddStpDyn_ucIx]) )
        {
          // deceleration from Fref1 to Fref2
          ulStpCnt -= ((uint32)CddStpDyn_ucRefNacc[CddStpDyn_ucIx] + (uint32)CddStpDyn_unRefNconst1[CddStpDyn_ucIx] + 1u);

          CddStpDyn_ucActTabIx = (uint8) ((uint32)CddStpDyn_ucRefNacc[CddStpDyn_ucIx] - ulStpCnt);
        }
        else if((uint32) CddStpDyn_lStepsToDo > (uint32) CddStpDyn_ucRefNdec2[CddStpDyn_ucIx])
        {
          // 2nd constant movement
          CddStpDyn_ucActTabIx = (1u + CddStpDyn_ucRefNacc[CddStpDyn_ucIx]) - CddStpDyn_ucRefNdec1[CddStpDyn_ucIx];

          // reduce frequency limitation to 2nd referencing frequency
          CddStpDyn_pStpInfo->Val.unMinPeriod = Cod_LwrHsZeitRef2();
        }
        else
        {
          // deceleration to 0
          CddStpDyn_ucActTabIx = (uint8) (uint32) CddStpDyn_lStepsToDo - 1u;
        }

        CddStpDynBuf_SetHsTime(CddStpDyn_GetStpTime(CddStpDyn_ucActTabIx));
        CddStpDynBuf_SetAboveResF1((CddStpDyn_Bits.biAboveResF1 != FALSE) ? TRUE : FALSE);
        CddStpDynBuf_SetAboveResF2((CddStpDyn_Bits.biAboveResF2 != FALSE) ? TRUE : FALSE);
        CddStpDynBuf_SetDynTableIx(CddStpDyn_ucActTabIx);                // not used

        if(CddStpDyn_lStepsToDo <= 1)   // if this condition is true, the entry is the last step of the movement
        {
          CddStpDynBuf_SetHsTime(CddStp_unPostStepLen[CddStpDyn_ucIx]);  // overwrite previous entry
          CddStpDynBuf_SetPause(TRUE);
          CddStpDynBuf_SetLastStep(TRUE);
        }

        CddStpDynBuf_WriteToBuffer();

        // check for sufficient buffer contents
        if(CddStpDynBuf_BufferFull() != FALSE)    // check for sufficient buffer contents
        {
          break;
        }

        CddStpDyn_lStepsToDo--;
      }
      while(CddStpDyn_lStepsToDo > 0);
    }

    //PRQA S 5310 4 // STPTH exceeded due to reuse of existing code
    //PRQA S 5324 3 // STCAL exceeded due to reuse of existing code
    //PRQA S 5336 2 // STMIF exceeded due to reuse of existing code
    //PRQA S 5330 1 // STST3 exceeded due to reuse of existing code
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Calculate steps for "Ref2" phase (leaving block position)
  ///
  /// \descr  Calculate all steps (typically 8) to leave block position after referencing
  ///
  /// \param  -
  ///
  /// \return -
  ///
  STATIC_AL void CddStpDyn_CalcRef2(void)
  {
    CddStpDyn_unRefSteps[CddStpDyn_ucIx] = 0;  // set back to initial value to indicate end of Ref1 phase

    CddStpDyn_PreStep();

    {
      // prepare temporary storage with information that will not be changed in loop
      CddStpDynBuf_ClrHsEntry();
      CddStpDynBuf_SetDirection(CddStpDyn_lCurrentDir);

      CddStpDyn_lStepsToDo = UTIL_ABS(CddStpDyn_lStepsToDo);
      // CddStpDyn_lStepsToDo now contains positive number of StepsToDo - 1

      //PRQA S 2461 1 // loop control variable has file scope due to reuse of existing code
      while(CddStpDyn_lStepsToDo > 0)
      {
        CddStpDyn_lStepsToDo--;
        CddStpDynBuf_SetHsTime(Cod_LwrHsZeitRef3());
        CddStpDynBuf_WriteToBuffer();
      }

      // make last buffer entry
      CddStpDynBuf_SetHsTime(CddStp_unPostStepLen[CddStpDyn_ucIx]);
      CddStpDynBuf_SetPause(TRUE);
      CddStpDynBuf_SetLastStep(TRUE);
      CddStpDynBuf_WriteToBuffer();
    }

    //PRQA S 5324 1 // STCAL exceeded due to reuse of existing code
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Calculate steps for normal movement
  ///
  /// \descr  Calculate steps for normal movement
  ///
  /// \param  -
  ///
  /// \return -
  ///
  STATIC_AL void CddStpDyn_CalcNormal(void)
  {
    uint32  ulAbsStepsToDo;
    boolean boIsLastStep;

    if(CddStpDyn_Bits.biFirstStep != FALSE)
    {
      CddStpDyn_lCurrentDir = CddStpDyn_GetSign(CddStpDyn_lStepsToDo);

      // pre-step
      CddStpDynBuf_ClrHsEntry   ();           // prepare empty halfstep entry
      CddStpDynBuf_SetDirection (CddStpDyn_lCurrentDir);
      CddStpDynBuf_SetFirstStep (TRUE);
      CddStpDynBuf_SetPause     (TRUE);
      CddStpDynBuf_SetHsTime    (CddStp_unPreStepLen[CddStpDyn_ucIx]);
      CddStpDynBuf_WriteToBuffer();
    }

    do
    {
      ulAbsStepsToDo = (uint32) UTIL_ABS(CddStpDyn_lStepsToDo);

      // prepare temporary storage with information that will not be changed in loop
      CddStpDynBuf_ClrHsEntry();

      if(CddStpDyn_ucActTabIx > 0u)  // movement in progress
      {
        uint32 ulDecStepsAct;   // number of decrement steps beginning at actual index position
        uint32 ulDecStepsNext;  // number of decrement steps beginning at index position (n+1)

        if(Cod_LwrBremsSchnell() == FALSE)
        {
          ulDecStepsAct  = (uint32)CddStpDyn_ucActTabIx;
          ulDecStepsNext = (uint32)CddStpDyn_ucActTabIx + 1u;
        }
        else
        {
          ulDecStepsAct  = ((uint32)CddStpDyn_ucActTabIx + 1u) / 2u;
          ulDecStepsNext = ((uint32)CddStpDyn_ucActTabIx + 2u) / 2u;
        }

        // check for all reasons that need to decrement table index
        if(  (Util_SameSign(CddStpDyn_lCurrentDir, CddStpDyn_lStepsToDo) == FALSE )  // wrong direction
          || (CddStpDyn_Bits.biStop                                      != FALSE )  // deceleration forced by stop bit in control message
          || (CddStpDyn_ucActTabIx > CddStpDyn_pStpInfo->Val.ucMaxIx              )  // deceleration forced by frequency limitation
          || (ulDecStepsAct > ulAbsStepsToDo)                                     )  // stopping exactly or with overshoot
        {
          if(CddStpDyn_ucActTabIx > 0u)
          {
            CddStpDyn_DecActTabIx();
          }
        }
        // if decrement is not necessary check if increment is possible
        else if( (CddStpDyn_ucActTabIx < (CddStpDyn_aucLastTabIx[CddStpDyn_ucIx]) )  // still within table range
              && (CddStpDyn_ucActTabIx < CddStpDyn_pStpInfo->Val.ucMaxIx          )  // no frequency limitation
              && (ulDecStepsNext <= ulAbsStepsToDo)                               )  // stopping after increment possible
        {
          CddStpDyn_IncActTabIx();
        }
        else
        {
          // do nothing
        }

        CddStpDynBuf_SetDirection (CddStpDyn_lCurrentDir);
        CddStpDynBuf_SetDynTableIx(CddStpDyn_ucActTabIx);
        CddStpDynBuf_SetAboveResF1((CddStpDyn_Bits.biAboveResF1 != FALSE) ? TRUE : FALSE);
        CddStpDynBuf_SetAboveResF2((CddStpDyn_Bits.biAboveResF2 != FALSE) ? TRUE : FALSE);

        if(CddStpDyn_ucActTabIx == 0u)  // now stopped
        {
          // divide into 4 parts to make it interruptible
          CddStpDynBuf_SetHsTime(CddStpDyn_aunHsZeit[CddStpDyn_ucIx][0u] / 4u);  // 25% of step time
          CddStpDynBuf_SetPause(TRUE);
          CddStpDynBuf_WriteToBuffer();       // write 1st part
          CddStpDynBuf_WriteToBuffer();       // write 2nd part
          CddStpDynBuf_WriteToBuffer();       // write 3rd part
          CddStpDynBuf_WriteToBuffer();       // write 4th part
        }
        else
        {
          CddStpDynBuf_SetHsTime(CddStpDyn_GetStpTime(CddStpDyn_ucActTabIx));
          CddStpDynBuf_WriteToBuffer();
        }
      }
      else  // (CddStpDyn_ucActTabIx == 0)
      {
        if((ulAbsStepsToDo == 0u) || (CddStpDyn_Bits.biStop != FALSE))
        {
          CddStpDynBuf_SetDirection(CddStpDyn_lCurrentDir);
          if (CddStp_unPostStepLen[CddStpDyn_ucIx] < ((CddStpDyn_aunHsZeit[CddStpDyn_ucIx][0u]) + CDDSTPDYN_PostStepAdd))  // avoid negative result because of parameter mismatch!
          {
            CddStpDynBuf_SetHsTime(CDDSTPDYN_PostStepAdd / 2u);                                                            // this entry will be used two times
          }
          else
          {
            CddStpDynBuf_SetHsTime((uint16)(CddStp_unPostStepLen[CddStpDyn_ucIx] - CddStpDyn_aunHsZeit[CddStpDyn_ucIx][0u]) / 2u); // subtract entry 0: this pause step is already done
          }                                                                                                                         // this entry will be used two times

          CddStpDynBuf_SetPause     (TRUE);
          CddStpDynBuf_WriteToBuffer();       // write 1st part (50%)

          CddStpDynBuf_SetLastStep  (TRUE);
          CddStpDynBuf_WriteToBuffer();       // write 2nd part (50%)
        }
        else  // (ulAbsStepsToDo > 0)
        {
          CddStpDyn_lCurrentDir = CddStpDyn_GetSign(CddStpDyn_lStepsToDo);

          CddStpDyn_IncActTabIx();

          CddStpDynBuf_SetDirection (CddStpDyn_lCurrentDir);
          CddStpDynBuf_SetDynTableIx(CddStpDyn_ucActTabIx);
          CddStpDynBuf_SetHsTime    (CddStpDyn_GetStpTime(CddStpDyn_ucActTabIx));
          CddStpDynBuf_SetAboveResF1((CddStpDyn_Bits.biAboveResF1 != FALSE) ? TRUE : FALSE);
          CddStpDynBuf_SetAboveResF2((CddStpDyn_Bits.biAboveResF2 != FALSE) ? TRUE : FALSE);
          CddStpDynBuf_WriteToBuffer();
        }
      }

      if (CddStpDynBuf_IsPause() == FALSE)    // buffer entry leads to movement
      {
        CddStpDyn_lStepsToDo -= CddStpDyn_lCurrentDir;
      }

      boIsLastStep = CddStpDynBuf_IsLastStep();
    }
    while((CddStpDynBuf_BufferFull() == FALSE) && (boIsLastStep == FALSE));
    
    //PRQA S 5324 2 // STCAL exceeded due to reuse of existing code
    //PRQA S 5330 1 // STST3 exceeded due to reuse of existing code
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief   Calculation of next entires in stepping buffer
  ///
  /// \descr  
  ///
  /// \param  ucIx             stepper instance
  /// \param  pHsBuf
  /// \param  ulBufIx
  /// \param  lTgtPos
  /// \param  lActPos
  /// \param  ulRemainingTicks
  /// \param  CalcMode
  ///
  /// \return -
  ///
  void CddStpDyn_CalcNextSteps(uint8 ucIx, tHsInfo* pHsBuf, uint32 ulBufIx, sint32 lTgtPos, sint32 lActPos, uint32 ulRemainingTicks, tCddStpDyn_CalcMode CalcMode)
  {
    CddStpDyn_ucIx        = ucIx;
    CddStpDyn_pStpInfo    = &StpTabRam[ucIx];            // get pointers for fast access to ROM and RAM
    CddStpDyn_lStepsToDo  = lTgtPos - lActPos;           // actual value of remaining halfsteps
    CddStpDyn_Bits.biStop = CalcMode.Bit.Stop;

    CddStpDynBuf_OpenBuffer(pHsBuf, ulBufIx, ulRemainingTicks);

    CddStpDyn_GetStartConditions();  // get start conditions using last buffer entry

    // check if we try to start a new motion while stepper is at target position
    if( ! ((CddStpDyn_Bits.biFirstStep != FALSE) && (CddStpDyn_lStepsToDo == 0)) )
    {
      if(CalcMode.Bit.Ref1 != FALSE)
      {
        CddStpDyn_CalcRef1();       // referencing on block using referencing profile Pr0 or Pr1
      }
      else if(CalcMode.Bit.Ref2 != FALSE)
      {
        CddStpDyn_CalcRef2();       // 1st movement after referencing: leaving block position
      }
      else
      {
        CddStpDyn_CalcNormal();     // step calculation for normal movement
      }
    }
    CddStpDynBuf_CloseBufferr(ulBufIx);

    //PRQA S 5328 2 // STPAR exceeded due to reuse of existing code
  }

#endif  // (CFA_CNT_STP_88XX != 0)

//EOF
