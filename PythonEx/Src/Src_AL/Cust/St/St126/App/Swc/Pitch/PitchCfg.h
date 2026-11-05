#ifndef __PITCHCFG_H__
  #define __PITCHCFG_H__

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
  /// \file  PitchCfg.h
  ///
  /// \brief
  ///
  /// \descr
  ///
  ///         Additional information can be found in the design description (Link:
  ///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
  ///
  /// \author Ott, Peter ALRT/EEG-PM2 * (otp2rt)
  ///         mailTo:Peter.Ott@al-lighting.com
  //-----------------------------------------------------------------------------
  #include <Std_Types.h>
  #include <Cfg/Cfg.h>


  //=============================================================================
  // defines
  //=============================================================================
  #define PITCH_UsePitchCalc   // do angle calculation based on displacement
  //#define PITCH_SupportSignalImplausible  // create error




  // displacement configuration               Sens0 port                      Sens1 port
  #define PITCH_DisplacementCfg       { RtePort_Displacement_Frnt_Idx, RtePort_Displacement_Rear_Idx }
  #define PITCH_SensRawCfg            { RtePort_SensRaw_Frnt_Idx,      RtePort_SensRaw_Rear_Idx      }


  // pitch measurement          number of          port of 1st sensor          opt. port of
  //                             sensors                                        2nd sensor
  #define PITCH_FrntSensCfg    {    1,       RtePort_Displacement_Frnt_Idx,  (tRtePortIndex) 0 }
  #define PITCH_RearSensCfg    {    1,       RtePort_Displacement_Rear_Idx,  (tRtePortIndex) 0 }


  // analog sensor errors       signal low     signal high    signal invalid
  #define PITCH_ErrSensCfg  { { Sens_E_FrntLo, Sens_E_FrntHi, DEM_Invalid_EventId },   /* Sens0 */ \
                              { Sens_E_RearLo, Sens_E_RearHi, DEM_Invalid_EventId } }  /* Sens1 */

  // analog sensor errors           signal not plausible
  //#define PITCH_ErrSensPlauCfg  { Sens_E_PlauRearR   ,    /* Sens0 */ \
  //                                Sens_E_PlauFrntR     }  /* Sens1 */

  #define PITCH_ErrMissingCalibCfg   DEM_Invalid_EventId  // not used yet

#endif // __PITCHCFG_H__
