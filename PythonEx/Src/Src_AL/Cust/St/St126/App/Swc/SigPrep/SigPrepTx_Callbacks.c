
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
/// \file   SigPrepTx_Callbacks.c
///
/// \brief  Output Frame Tx Callbacks
///
/// \descr  Output Frame Tx Callbacks
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SigPrepTx_Callbacks.h>
#include <SigPrepRx.h>
#include <p_NM.h>
#include <Cfg/CfgId.h>
#include <Nvm.h>

//-----------------------------------------------------------------------------
// definitions
//-----------------------------------------------------------------------------

//Concatenate logzone date by entry index
#define APPDESC_CONCATENATE_DATE_BY_INDEX(x)     (APPDESC_CONCATENATE_DATE(C_BOOT_ZI_Area[x].uData.sLogZoneInfo.ucDownloadedYear,  \
                                                                           C_BOOT_ZI_Area[x].uData.sLogZoneInfo.ucDownloadedMonth, \
                                                                           C_BOOT_ZI_Area[x].uData.sLogZoneInfo.ucDownloadedDay))

//PRQA S 3447 1 // C_BOOT_ZI_Area' is being declared with external linkage but this declaration is not in a header file.
extern tsSigprepTx_LogZoneEntry C_BOOT_ZI_Area[SIGPREPTX_LOGZONE_ENTRIES_NR]; //identification zone

//-----------------------------------------------------------------------------
// functions prototypes
//-----------------------------------------------------------------------------
STATIC_AL uint8 SigPrepTx_Callbacks_LogZoneLastDataSearch(void);


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_CyclicFrame_5x7
///
/// \descr  Cyclic callback for 5D7/5F7 message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_CyclicFrame_5x7(void)
{
  // LDMO-3552 // Buss OFF and Perte Com is already implemented in the LGM stack, no need for this code.
  //uint8 ucCDefautBussOff[1] = { 0u };
  //uint8 ucCDefautPerteCom[1] = { 0u };
  
  //ucCDefautBussOff[0] = NvmBlockNmBackupCounters.ucC_BusOff_Counter;
  //ucCDefautPerteCom[0] = NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter;
  
  //(void)LGM_SendMessage(C_DEFAUT_BUSOFF, ucCDefautBussOff);
  //(void)LGM_SendMessage(C_DEFAUT_PERTE_COM, ucCDefautPerteCom);
  return;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_ToFrame_5x7
///
/// \descr  Time-Out callback for 5D7/5F7 cylic message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_ToFrame_5x7(void)
{
  return;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_CyclicFrame_2B7
///
/// \descr  Cyclic callback for 2B7 message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_CyclicFrame_2B7(void)
{
  tsRte_LevellingTgtPos  data = { 0 };
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  tsRte_BendingBeamFault_OtherHL sBendingBeamFaultL = { 0 };
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  uint8  ucCmdSignLvlTx[1] = { 0u };
  uint8  ucCmdRefLvlTx[1] = { 0u };
  uint8  ucCmdPosLvlTx[2] = { 0u };
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  uint8  ucDynBendingBeamFaultTx[1] = { 0u };
  (void)Rte_Read_CtrlStp_MasterCommand(&data);

  (void)Rte_Read_Dbl_SigPrepTx_LeftStatus(&sBendingBeamFaultL);

  // Inhibit LVL HMI if ADL option is not available in coding
  boolean boAdl_Enable = Cod_AvacStp_Enable();

  if (boAdl_Enable != FALSE)
  {
    ucCmdSignLvlTx[0]  = (uint8)data.eRCmdSignLvl;
    ucCmdRefLvlTx[0]   = (uint8)data.eRCmdRefLvl;
    ucCmdPosLvlTx[0]   = (uint8)data.eRCmdPosLvl.unRCmdPosLvl;
    ucCmdPosLvlTx[1]   = (uint8)(data.eRCmdPosLvl.unRCmdPosLvl >> 8u);
  }
  else
  {
    ucCmdSignLvlTx[0]  = 0u;
    ucCmdRefLvlTx[0]   = 0u;
    ucCmdPosLvlTx[0]   = 0u;
    ucCmdPosLvlTx[1]   = 0u;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)Rte_Read_CtrlDcm_MasterCommand(&data);

  // Inhibit LVL HMI if ASL option is not available in coding
  boolean boAsl_Enable = Cod_Asl_Enable();

  if (boAsl_Enable != FALSE)
  {
    ucCmdSignLvlTx[0]  = (uint8)data.eRCmdSignLvl;
    ucCmdRefLvlTx[0]   = (uint8)data.eRCmdRefLvl;
    ucCmdPosLvlTx[0]   = (uint8)data.eRCmdPosLvl.unRCmdPosLvl;
    ucCmdPosLvlTx[1]   = (uint8)(data.eRCmdPosLvl.unRCmdPosLvl >> 8u);
  }
  else
  {
    ucCmdSignLvlTx[0]  = 0u;
    ucCmdRefLvlTx[0]   = 0u;
    ucCmdPosLvlTx[0]   = 0u;
    ucCmdPosLvlTx[1]   = 0u;
  }
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Inhibit DBL HMI if DBL option is not available in coding
  boolean boDbl_Enable = Cod_Dbl_Enable();

  ucDynBendingBeamFaultTx[0] = (boDbl_Enable != FALSE) ? (uint8)sBendingBeamFaultL.eDynBendingBeamFault : 0u;

  (void)LGM_SendMessage(DYN_BENDING_BEAM_FAULT_L_TX, ucDynBendingBeamFaultTx);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  (void)LGM_SendMessage(SIGNE_CONSIGNE_SITE_D_TX, ucCmdSignLvlTx);
  (void)LGM_SendMessage(CMD_REF_SITE_D_TX, ucCmdRefLvlTx);
  (void)LGM_SendMessage(CONSIGNE_SITE_D_TX, ucCmdPosLvlTx);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_ToFrame_2B7
///
/// \descr  Time-Out callback for 2B7 cylic message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_ToFrame_2B7(void)
{
  return;
}



//-----------------------------------------------------------------------------
/// \brief  Version_Frame_Callback
///
/// \descr  LGM callback to send Version Frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void Version_Frame_Callback(void)
{
  uint8 ucNumUCE[1]            = { 0u };
  uint8 ucVerLogJour[1]        = { 0u };
  uint8 ucVerLogMois[1]        = { 0u };
  uint8 ucVerLogAnnee[1]       = { 0u };
  uint8 ucIdentLogic[2]        = { 0u };
  uint8 ucDigit_1[1]           = { 0u };
  uint8 ucDigit_2[1]           = { 0u };
  uint8 ucNumEdition[1]        = { 0u };
  uint8 ucLastDLIndexData      = 0u;
  uint8 ucEcuCode              = 0u;
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Read MountingSide RTE port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  // Get correct ECU_Code
  ucEcuCode = (eMountingSide != eMountedLeft) ? SIGPREPTX_CALLBACKS_R_ECU_CODE : SIGPREPTX_CALLBACKS_L_ECU_CODE;

  for (uint8 ucIndex = SIGPREPTX_LOGZONE_ENTRY_MAX_INDEX; ucIndex < APPDESC_MAX_UINT8_VALUE; ucIndex--)
  {
    // Check if PSA Supplier Code is valid
    //PRQA S 1863 1 // The operands of this equality operator are of different 'essential signedness' but will both be promoted to 'signed int' for comparison.
    if (C_BOOT_ZI_Area[ucIndex].uData.sLogZoneInfo.ucSupplierCode != APPDESC_EMPTY_ZONE)
    {
      // Valid data found

      // If LogZone is full, check if data from the begining of LogZone area has been overwritten
      if (ucIndex == SIGPREPTX_LOGZONE_ENTRY_MAX_INDEX)
      {
        // Search for last downloaded data by date
        ucLastDLIndexData = SigPrepTx_Callbacks_LogZoneLastDataSearch();
      }
      else
      {
        // Last downloaded data found
        ucLastDLIndexData = ucIndex;
      }

      break;
    }
    else
    {
      // Continue searching for valid data
    }
  }
  
  //Side of the software
  ucNumUCE[0]           = ucEcuCode;
  //SW version day
  ucVerLogJour[0]       = ECUTRACECFG_DAY_DEC;
  //SW version month
  ucVerLogMois[0]       = ECUTRACECFG_MONTH_DEC; 
  //SW version year
  ucVerLogAnnee[0]      = ECUTRACECFG_YEAR_DEC;
  //SW edition from ZI
  ucIdentLogic[0]       = C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.aucSoftwareEdition[1];
  ucIdentLogic[1]       = C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.aucSoftwareEdition[0];
  //Application Type from ZI
  ucDigit_1[0] = (C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.ucApplicationType > SIGPREPTX_CALLBACKS_MAX_ALLOWED_SW_TYPE) ? 
    SIGPREPTX_CALLBACKS_MAX_ALLOWED_SW_TYPE : C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.ucApplicationType;
  //SW Version from ZI
  ucDigit_2[0] = (C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.ucSoftwareVersion > SIGPREPTX_CALLBACKS_MAX_ALLOWED_SW_TYPE) ?
    SIGPREPTX_CALLBACKS_MAX_ALLOWED_SW_TYPE : C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.ucSoftwareVersion;
  //System code from ZI
  ucNumEdition[0]       = C_BOOT_ZI_Area[ucLastDLIndexData].uData.sLogZoneInfo.ucSystemCode;

  (void)LGM_SendMessage(NUM_UCE, ucNumUCE);
  (void)LGM_SendMessage(VER_LOG_JOUR, ucVerLogJour);
  (void)LGM_SendMessage(VER_LOG_MOIS, ucVerLogMois);
  (void)LGM_SendMessage(VER_LOG_ANNEE, ucVerLogAnnee);
  (void)LGM_SendMessage(IDENT_LOGIC, ucIdentLogic);
  (void)LGM_SendMessage(DIGIT_1, ucDigit_1);
  (void)LGM_SendMessage(DIGIT_2, ucDigit_2);
  (void)LGM_SendMessage(NUM_EDITION, ucNumEdition);
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_Callbacks_LogZoneLastDataSearch
///
/// \descr  Search in LogZone for last downloaded data by date
///
/// \param  void
///
/// \return Last downloaded data index
//-----------------------------------------------------------------------------
STATIC_AL uint8 SigPrepTx_Callbacks_LogZoneLastDataSearch(void)
{
  uint8 ucIndex;
  uint8 ucLastDownloadedDataIndex;
  uint32 ulCurrentIndexDate, ulLastStoredIndexDate;

  ucLastDownloadedDataIndex = SIGPREPTX_LOGZONE_ENTRY_MAX_INDEX;

  // Search for last downloaded data by date
  for (ucIndex = 0; ucIndex <= SIGPREPTX_LOGZONE_ENTRY_MAX_INDEX; ucIndex++)
  {
    // Concatenate date from last stored index
    //PRQA S 4434 3 // A non-constant expression of 'essentially signed' type (signed int) is being converted to unsigned type, 'unsigned long' on assignment.
      //PRQA S 1850 2 // The right-hand operand is 'essentially unsigned' (unsigned char) but will be implicitly converted to a signed type (signed int) in this arithmetic operation.
    //PRQA S 1860 1 // The operands of this arithmetic operator are of different 'essential signedness' but will generate a result of type 'signed int'.
    ulLastStoredIndexDate = APPDESC_CONCATENATE_DATE_BY_INDEX(ucLastDownloadedDataIndex);

    // Concatenate date from current index
    //PRQA S 1850 4 // The right-hand operand is 'essentially unsigned' (unsigned char) but will be implicitly converted to a signed type (signed int) in this arithmetic operation.
      //PRQA S 4434 3 // A non-constant expression of 'essentially signed' type (signed int) is being converted to unsigned type, 'unsigned long' on assignment.
    //PRQA S 1850 2 // The right-hand operand is 'essentially unsigned' (unsigned char) but will be implicitly converted to a signed type (signed int) in this arithmetic operation.
     //PRQA S 1860 1 // The operands of this arithmetic operator are of different 'essential signedness' but will generate a result of type 'signed int'.
    ulCurrentIndexDate = APPDESC_CONCATENATE_DATE_BY_INDEX(ucIndex);

    if (ulLastStoredIndexDate > ulCurrentIndexDate)
    {
      // Last downloaded data found
      break;
    }
    else
    {
      // Continue searching with the next element
      ucLastDownloadedDataIndex = ucIndex;
    }
  }

  return ucLastDownloadedDataIndex;
}



#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_CyclicFrame_297
///
/// \descr  Cyclic callback for 297 message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_CyclicFrame_297(void)
{
  tsRte_LevellingFeedback  data = { 0 };
  tsRte_BendingBeamFault_OtherHL sBendingBeamFaultR = { 0 };

  uint8  ucCmdSignLvlTx[1]          = { 0u };
  uint8  ucDynBendingBeamFaultTx[1] = { 0u };
  uint8  ucCmdPosLvlTx[2]           = { 0u };

  (void)Rte_Read_CtrlStp_SlaveFeedback(&data);

  (void)Rte_Read_Dbl_SigPrepTx_RightStatus(&sBendingBeamFaultR);

  // Inhibit DBL HMI if DBL option is not available in coding
  boolean boDbl_Enable = Cod_Dbl_Enable();

  ucDynBendingBeamFaultTx[0] = (boDbl_Enable != FALSE) ? (uint8)sBendingBeamFaultR.eDynBendingBeamFault : 0u;

  // Inhibit LVL HMI if ADL option is not available in coding
  boolean boAdl_Enable = Cod_AvacStp_Enable();

  if (boAdl_Enable != FALSE)
  {
    ucCmdSignLvlTx[0]  = (uint8)data.eRPosSignLvl;
    ucCmdPosLvlTx[0]   = (uint8)data.ePositionSiteD.unRPosLvl;
    ucCmdPosLvlTx[1]   = (uint8)(data.ePositionSiteD.unRPosLvl >> 8u);
  }
  else
  {
    ucCmdSignLvlTx[0]  = 0u;
    ucCmdPosLvlTx[0]   = 0u;
    ucCmdPosLvlTx[1]   = 0u;
  }

  (void)LGM_SendMessage(SIGN_POS_LVL_R_TX, ucCmdSignLvlTx);
  (void)LGM_SendMessage(DYN_BENDING_BEAM_FAULT_R_TX, ucDynBendingBeamFaultTx);
  (void)LGM_SendMessage(POSITION_SITE_D_TX, ucCmdPosLvlTx);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_CyclicFrame_4D7
///
/// \descr  Cyclic callback for 4D7 message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_CyclicFrame_4D7(void)
{
  tsRte_LevellingDiagStatus  data = { 0 };

  uint8  ucLvlElecR[1]        = { 5u };
  uint8  ucLvlTemperatureR[1] = { 5u };
  uint8  ucLvlSteplossR[1]    = { 5u };
  uint8  ucLvlRefStateR[1]    = { 5u };
  uint8  ucLvlVoltR[1]        = { 5u };

  // Inhibit LVL HMI if ADL option is not available in coding
  boolean boAdl_Enable = Cod_AvacStp_Enable();

  if (boAdl_Enable != FALSE)
  {
    (void)Rte_Read_CtrlStp_SlaveDiagStatus(&data);
    
    ucLvlElecR[0]        = (uint8)data.eLvlElecR;
    ucLvlTemperatureR[0] = (uint8)data.eLvlTemperatureR;
    ucLvlSteplossR[0]    = (uint8)data.eLvlSteplossR;
    ucLvlRefStateR[0]    = (uint8)data.eLvlRefStateR;
    ucLvlVoltR[0]        = (uint8)data.eLvlVoltR;
  }
  else
  {
    ucLvlElecR[0]        = (uint8)0u;
    ucLvlTemperatureR[0] = (uint8)0u;
    ucLvlSteplossR[0]    = (uint8)0u;
    ucLvlRefStateR[0]    = (uint8)0u;
    ucLvlVoltR[0]        = (uint8)0u;
  }


  (void)LGM_SendMessage(LVL_ELEC_R_TX, ucLvlElecR);
  (void)LGM_SendMessage(LVL_TEMPERATURE_R_TX, ucLvlTemperatureR);
  (void)LGM_SendMessage(LVL_STEPLOSS_R_TX, ucLvlSteplossR);
  (void)LGM_SendMessage(LVL_REF_STATE_R_TX, ucLvlRefStateR);
  (void)LGM_SendMessage(LVL_VOLT_R_TX, ucLvlVoltR);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_ToFrame_297
///
/// \descr  Time-Out callback for 297 cylic message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_ToFrame_297(void)
{
  return;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_TxCallbacks_ToFrame_4D7
///
/// \descr  Time-Out callback for 4D7 cylic message frame
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_ToFrame_4D7(void)
{
  return;
}


#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)



// EOF
