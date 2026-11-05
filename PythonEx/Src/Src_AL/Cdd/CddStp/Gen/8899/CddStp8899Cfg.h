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
/// \file  CddStp8899Cfg.h
///
/// \brief
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

#ifndef _CDDSTP8899CFG_H
  #define _CDDSTP8899CFG_H


  #include <8899/CddStp8899Types.h>


  #define CDDSTP8899_StepModeMS            (0x02u) // uS 1/8  FS
//CHS  #define CDDSTP8899_StepModeHS       (0x05u) // HS not compensated
  #define CDDSTP8899_StepModeHS            (0x04u) // HS     compensated //CHS

  #define CDDSTP8899_StepModeTS_MS         (0x02u) // uS 1/8  FS for TestStep in case of micro step mode
  #define CDDSTP8899_StepModeTS_HS         (0x00u) // uS 1/32 FS for TestStep in case of half  step mode

  #define CDDSTP8899_MSPMask_TS_MS         (0x04u) // HS 1/8  FS TestStep MicroStepPosition mask (bit 2)
  #define CDDSTP8899_MSPMask_TS_HS         (0x01u) // uS 1/32 FS TestStep MicroStepPosition mask (bit 0)



  // ---------------------------------------------------------------------------
  // current values [mA] - note: DRV8899 IRUN is used (not IHOLD)

  #define  _IA0059_ (0x00u)
  #define  _IA0071_ (0x01u)
  #define  _IA0084_ (0x02u)
  #define  _IA0100_ (0x03u)
  #define  _IA0119_ (0x04u)
  #define  _IA0141_ (0x05u)
  #define  _IA0168_ (0x06u)
  #define  _IA0200_ (0x07u)
  #define  _IA0238_ (0x08u)
  #define  _IA0283_ (0x09u)
  #define  _IA0336_ (0x0Au)
  #define  _IA0400_ (0x0Bu)
  #define  _IA0476_ (0x0Cu)
  #define  _IA0566_ (0x0Du)
  #define  _IA0673_ (0x0Eu)
  #define  _IA0800_ (0x0Fu)
  
  #define CDDSTP8899_CurAmpltHold_NTVer    _IA0100_ // VER: hold current normal temperature
  #define CDDSTP8899_CurAmpltHold_LTVer    _IA0800_ // VER: hold current low temperature
  #define CDDSTP8899_CurAmpltHold_HTVer    _IA0059_ // VER: hold current high temperature
  #define CDDSTP8899_CurAmpltHold_NTHor    _IA0100_ // HOR: hold current normal temperature
  #define CDDSTP8899_CurAmpltHold_LTHor    _IA0800_ // HOR: hold current low temperature
  #define CDDSTP8899_CurAmpltHold_HTHor    _IA0059_ // HOR: hold current high temperature
  #define CDDSTP8899_CurAmpltHold_NTSht    _IA0100_ // SHT: hold current normal temperature
  #define CDDSTP8899_CurAmpltHold_LTSht    _IA0800_ // SHT: hold current low temperature
  #define CDDSTP8899_CurAmpltHold_HTSht    _IA0059_ // SHT: hold current high temperature
  
  #define CDDSTP8899_CurAmpltRunMS_NTVer   _IA0476_ // VER: us                 normal temperature
  #define CDDSTP8899_CurAmpltRunMS_LTVer   _IA0800_ // VER: us                 low temperature
  #define CDDSTP8899_CurAmpltRunMS_HTVer   _IA0476_ // VER: us                 high temperature
  #define CDDSTP8899_CurAmpltRunMS_NTHor   _IA0476_ // HOR: us                 normal temperature
  #define CDDSTP8899_CurAmpltRunMS_LTHor   _IA0800_ // HOR: us                 low temperature
  #define CDDSTP8899_CurAmpltRunMS_HTHor   _IA0476_ // HOR: us                 high temperature
  #define CDDSTP8899_CurAmpltRunMS_NTSht   _IA0476_ // SHT: us                 normal temperature
  #define CDDSTP8899_CurAmpltRunMS_LTSht   _IA0800_ // SHT: us                 low temperature  
  #define CDDSTP8899_CurAmpltRunMS_HTSht   _IA0476_ // SHT: us                 high temperature

  #define CDDSTP8899_CurAmpltRunNC_NTVer   _IA0476_ // VER: HS not compensated normal temperature
  #define CDDSTP8899_CurAmpltRunNC_LTVer   _IA0566_ // VER: HS not compensated low temperature
  #define CDDSTP8899_CurAmpltRunNC_HTVer   _IA0400_ // VER: HS not compensated high temperature
  #define CDDSTP8899_CurAmpltRunNC_NTHor   _IA0476_ // HOR: HS not compensated normal temperature
  #define CDDSTP8899_CurAmpltRunNC_LTHor   _IA0566_ // HOR: HS not compensated low temperature
  #define CDDSTP8899_CurAmpltRunNC_HTHor   _IA0476_ // HOR: HS not compensated high temperature
  #define CDDSTP8899_CurAmpltRunNC_NTSht   _IA0476_ // SHT: HS not compensated normal temperature
  #define CDDSTP8899_CurAmpltRunNC_LTSht   _IA0566_ // SHT: HS not compensated low temperature
  #define CDDSTP8899_CurAmpltRunNC_HTSht   _IA0400_ // SHT: HS not compensated high temperature
  
  #define CDDSTP8899_CurAmpltRunHS_NTVer   _IA0630_ // VER: HS     compensated normal temperature
  #define CDDSTP8899_CurAmpltRunHS_LTVer   _IA0825_ // VER: HS     compensated low temperature
  #define CDDSTP8899_CurAmpltRunHS_HTVer   _IA0476_ // VER: HS     compensated high temperature
  #define CDDSTP8899_CurAmpltRunHS_NTHor   _IA0800_ // HOR: HS     compensated normal temperature
  #define CDDSTP8899_CurAmpltRunHS_LTHor   _IA0825_ // HOR: HS     compensated low temperature
  #define CDDSTP8899_CurAmpltRunHS_HTHor   _IA0800_ // HOR: HS     compensated high temperature
  #define CDDSTP8899_CurAmpltRunHS_NTSht   _IA0630_ // SHT: HS     compensated normal temperature
  #define CDDSTP8899_CurAmpltRunHS_LTSht   _IA0825_ // SHT: HS     compensated low temperature  
  #define CDDSTP8899_CurAmpltRunHS_HTSht   _IA0476_ // SHT: HS     compensated high temperature

  #define CDDSTP8899_CurAmpltRunTS         _IA0059_ /* --- test steps for Shorted coil / Openload detection --- */ 
  
  #define CDDSTP8899_CurAmpltRef_NTVer     CDDSTP8899_CurAmpltRunMS_LTVer // VER: normal temperature
  #define CDDSTP8899_CurAmpltRef_LTVer     CDDSTP8899_CurAmpltRunMS_LTVer // VER: low temperature
  #define CDDSTP8899_CurAmpltRef_HTVer     CDDSTP8899_CurAmpltRunMS_LTVer // VER: high temperature
  #define CDDSTP8899_CurAmpltRef_NTHor     CDDSTP8899_CurAmpltRunMS_LTHor // HOR: normal temperature
  #define CDDSTP8899_CurAmpltRef_LTHor     CDDSTP8899_CurAmpltRunMS_LTHor // HOR: low temperature
  #define CDDSTP8899_CurAmpltRef_HTHor     CDDSTP8899_CurAmpltRunMS_LTHor // HOR: high temperature
  #define CDDSTP8899_CurAmpltRef_NTSht     CDDSTP8899_CurAmpltRunMS_LTSht // SHT: normal temperature
  #define CDDSTP8899_CurAmpltRef_LTSht     CDDSTP8899_CurAmpltRunMS_LTSht // SHT: low temperature  
  #define CDDSTP8899_CurAmpltRef_HTSht     CDDSTP8899_CurAmpltRunMS_LTSht // SHT: high temperature

  // CReg1
  #define CDDSTP8899_SiThr                 (0x00u) // threshold level for stall detection cleared: stall detection is disabled
  #define CDDSTP8899_NXTP                  (0x00u) // push button pin, no generating next step in position table
  #define CDDSTP8899_RHBP                  (0x01u) // polarity of RunHoldB pin: inversion - if (RHB pin = GND): IRUN is used (not IHOLD)
  #define CDDSTP8899_DIRP       CDDSTP8899_DirNeg // direction control polarity: counter clockwise
  
  // CReg2
  #define CDDSTP8899_Ihold                 (0x00u) // Hold current 0 mA - note: DRV8899 IRUN is used (not IHOLD)

  // CReg3
  #define CDDSTP8899_SLP                   (0x00u) // active mode and not sleep mode
  #define CDDSTP8899_EMC                   (0x02u) // 2: 190 ns  1: 120 ns  0: 80 ns (Tbrise)
  #define CDDSTP8899_DIAGEN                (0x01u) // enables diagnosis at rising edge of MOTEN bit
  #define CDDSTP8899_EnhBemfEn             (0x00u) // disables enhanced BEMF measurement and motion interrupt

// jk-never used  #define CDDSTP8899_StTo                  (0x00u) // no max. difference between two successive FS next pulse periods, else after this time the BEMF sample is taken to verify stall

  // CReg4
  #define CDDSTP8899_OpenDis               (0x01u) // Open Coil detection status is flagged but drivers control remain active for both coils
  #define CDDSTP8899_OpenDet               (0x00u) // Open Coil detection detection time is 5 ms

  #define CDDSTP8899_SpThr                 (0x00u) // no speed threshold: BEMF measurement and stall detection is activated when speed register value is less or equal SpThr value

  // CReg6
  #define CDDSTP8899_UV2Thr                (0x00u) // under voltage level 5.98 V (not used, see CDDSTP8899_UV2IntEn and CDDSTP8899_UV2MIntEn)
  #define CDDSTP8899_UV1Thr                (0x00u) // under voltage level 5.98 V (used,     see CDDSTP8899_UV1IntEn)
  
  // CReg7
  #define CDDSTP8899_UV3MIntEn             (0x00u) // disable under voltage 3 detection and motion interrupt
  #define CDDSTP8899_UV3IntEn              (0x01u) // enable  under voltage 3 detection interrupt at voltage level 5.98 V (fix)
  #define CDDSTP8899_UV2MIntEn             (0x00u) // disable under voltage 2 detection and motion interrupt
  #define CDDSTP8899_UV2IntEn              (0x00u) // disable under voltage 2 detection interrupt
  #define CDDSTP8899_UV1IntEn              (0x00u) // disable under voltage 1 detection interrupt
  #define CDDSTP8899_BemfResIntEn          (0x00u) // disable BEMF result interrupt
  // jk-obsolet #define CDDSTP8899_BemfGain   CDDSTP8899_BG0_25 // 0.25 instead of 0.5 gain of BEMF measurement level
  #define CDDSTP8899_AD4_                  (0x00u) // AD4 in CR7 is cleared
  #define CDDSTP8899_AD4A                  (0x01u) // AD4 in CR7 is set
  
  
#endif // _CDDSTP8899CFG_H
