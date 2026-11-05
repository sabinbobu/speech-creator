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
  /// \file  CddStpCfg.h
  ///
  /// \brief  
  ///
  /// \descr  
  ///
  ///         Additional information can be found in the design description (Link:
  ///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
  ///
  /// \author Wuesteney, Ulrich ALRT/EEG-PM2 * (wu82rt)
  ///         mailTo:ulrich.wuesteney[A]al-lighting.com       
  ///         J. Kling ALRT-EES6 (f84304b)
  //-----------------------------------------------------------------------------

#ifndef __CDDSTPCFG_H__
#define __CDDSTPCFG_H__

  //  -----------------------------------------------------------------------------------------------
  //  includes
  //  -----------------------------------------------------------------------------------------------

  //  -----------------------------------------------------------------------------------------------
  //  defines
  //  -----------------------------------------------------------------------------------------------

  //  -----------------------------------------------------------------------------------------------
  //  temperature state time definitions
  //  -----------------------------------------------------------------------------------------------

  #define CDDSTP_ErrPrealarmTime    (10u)   // (not supported)                       duration of thermal warning to set ErrPrealarm state message bit [s]

//#define CDDSTP_HighTempMinTime    (60u)   // (not supported for AMIS3062x) minimal duration of high temperature state [s]
//#define CDDSTP_LowTempDuration    (60u)   //                                       duration of low  temperature state [s]


  //  -----------------------------------------------------------------------------------------------
  //  position sensor definitions
  //  -----------------------------------------------------------------------------------------------

  // sensor polarity (only in combination with position sensor) // OnBoard
  // 1 = signal high at positive stepper positions
  #define CDDSTP_Ver_PsensPol 0 //tbd - NVM LWR configuration!
  #define CDDSTP_Hor_PsensPol 1 //tbd - NVM KL  configuration!
  #define CDDSTP_Sht_PsensPol 0 //tbd - NVM GLW configuration!

  // sensor polarity (only in combination with position sensor) // StpExt
  // 1 = signal high at positive stepper positions
  // (only as init values, load by biPsensPol of NVM StpExt)
  #define CDDSTP_Hor0_PsensPol 1
  #define CDDSTP_Hor1_PsensPol 0
  #define CDDSTP_Hor2_PsensPol 0
  #define CDDSTP_Hor3_PsensPol 0

  // definition of regulation slope (only in combination with position sensor) // OnBoard
  // this is the slope that is calibrated at headlamp production
  // 1 = regulation slope if target position is incremented
  #define CDDSTP_Ver_RegSlope 0 //tbd - NVM LWR configuration!
  #define CDDSTP_Hor_RegSlope 1 //tbd - NVM KL  configuration!
  #define CDDSTP_Sht_RegSlope 0 //tbd - NVM GLW configuration!

  // definition of regulation slope (only in combination with position sensor) // StpExt
  // this is the slope that is calibrated at headlamp production
  // 1 = regulation slope if target position is incremented
  // (only as init values, load by biRegelflanke of NVM StpExt)
  #define CDDSTP_Hor0_RegSlope 1
  #define CDDSTP_Hor1_RegSlope 1
  #define CDDSTP_Hor2_RegSlope 1
  #define CDDSTP_Hor3_RegSlope 1


  //  -----------------------------------------------------------------------------------------------
  //  local system behaviour
  //  -----------------------------------------------------------------------------------------------

  #define CDDSTP_Ver_NewRefLoVoltType    eCddStp_NewRefAlways

  // behaviour in case of low volt events (driver switched off while motor in motion) to trigger new referencing
  #define CDDSTP_Hor0_NewRefLoVoltType   eCddStp_NewRefAlways
  #define CDDSTP_Hor1_NewRefLoVoltType   eCddStp_NewRefAlways
  #define CDDSTP_Hor2_NewRefLoVoltType   eCddStp_NewRefAlways
  #define CDDSTP_Hor3_NewRefLoVoltType   eCddStp_NewRefAlways

#endif // __CDDSTPCFG_H__
