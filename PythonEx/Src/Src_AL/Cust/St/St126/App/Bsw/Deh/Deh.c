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
/// \file   Deh.c
///
/// \brief  DEH handling
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <LgmDEHMainAPI.h>
#include <Deh.h>
#include <AL_Helper.h>
#include <ErrCust.h>
#include <_IL_types.h>
#include <p_IL_messages.h>
#include <p_NM.h>
#include <LgmDEHConfig_Cfg.h>
#include <Nvm.h>

#ifndef UNIT_TEST
#include <Rte.h>
#endif // UNIT_TEST


//-----------------------------------------------------------------------------
// Local defines
//-----------------------------------------------------------------------------
// ECU_CODE for Left LDM
#define DEH_L_ECU_CODE       0xA8u
// ECU_CODE for Right LDM
#define DEH_R_ECU_CODE       0xA9u

// DTC FORMAT ID
#define DEH_DTC_FORMAT_ID    0x00u

 // VITESSE_VEHICULE_ROUES 5 km/h value
#define DEH_5KMH_THRESHOLD   (uint16)500u        

//number of log entries for DEH Table
#define DEH_TABLE_LOG_LENGTH 20u

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
  // ECU_Code for left/right LDM
STATIC_AL uint8  ucEcuCode;

STATIC_AL LDEH_TS_DECtxt S_DE[DEH_TABLE_LOG_LENGTH];

STATIC_AL boolean Deh_TableFullStatus = FALSE;
STATIC_AL tsDeh_EventLog Deh_asDehLogTab[DEH_TABLE_LOG_LENGTH];

const tisNmBackupCounters  NvmInit_NmBackupCountersDefault = NmBackupCountersINIT;

//-----------------------------------------------------------------------------
// funtion prototypes
//-----------------------------------------------------------------------------
STATIC_AL void Deh_CheckSafetyConditions(void);

//-----------------------------------------------------------------------------
/// \brief  Deh_Init
///
/// \descr  Deh init function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void Deh_Init(void)
{
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Variable for safety conditions check
  TE_Bool eSafetyConditionsCheck = E_FALSE;

  // Read MountingSide RTE port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  // Get correct ECU_Code
  ucEcuCode = (eMountingSide != eMountedLeft) ? DEH_R_ECU_CODE : DEH_L_ECU_CODE;

  // Init LDEH module
  DAPI_InitModule(E_TRUE, (Tu8_Int)ucEcuCode);

  // Authorize to store in DEH Fifo
  DAPI_PermFifoStorage(LDEH_E_FIFO_PERM);

  // Authorize to send DEH frames
  DAPI_SetPermToSend(LDEH_E_SEND_PERM);

  // Inform the DEH module of the safety conditions state
  DAPI_SetSafetyConditions(eSafetyConditionsCheck);

  //TBD-  Should sent the contact State to LGM until they will change the implementation [LDMO-2182]
  DAPI_SetMainStatus(DAPI_E_MS_IGNITION);

  //Init values for DehLogTab
  Deh_ClearAndInitDehLogTab();
}

//-----------------------------------------------------------------------------
/// \brief  Deh_ClearAndInitDehLogTab
///
/// \descr  Assign with init values each parameter of
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void Deh_ClearAndInitDehLogTab(void)
{
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].unDemEvent = 0u;
    Deh_asDehLogTab[ucIndx].ulDTCCode = 0u;
    Deh_asDehLogTab[ucIndx].eEventState = eDeh_Init;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared = 0u;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared = 0u;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Deh_Cycle0
///
/// \descr  Deh cyclic function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void Deh_Cycle0(void)
{
  //check safety conditions
  Deh_CheckSafetyConditions();

  uint8 ucIndx = 0u;

  for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    if((Deh_asDehLogTab[ucIndx].eEventState == eDeh_Undef) && (Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared != 0u))
    {
      // Build and get DE context
      Deh_asDehLogTab[ucIndx].eEventState = (DAPI_BuildDECtxt(&S_DE[ucIndx], LDEH_E_APPEAR, Deh_asDehLogTab[ucIndx].ulDTCCode, DEH_DTC_FORMAT_ID, ucEcuCode)
        == LDEH_E_SUCCESS) ? eDeh_Apeared : eDeh_Undef;
    }
    else if (Deh_asDehLogTab[ucIndx].eEventState == eDeh_ApearedConf_DirectSent)
    {
      // Build and get DE context
      Deh_asDehLogTab[ucIndx].eEventState = (DAPI_BuildDECtxt(&S_DE[ucIndx], LDEH_E_APPEAR, Deh_asDehLogTab[ucIndx].ulDTCCode, DEH_DTC_FORMAT_ID, ucEcuCode)
        == LDEH_E_SUCCESS) ? eDeh_Apeared : eDeh_Undef;

      if (Deh_asDehLogTab[ucIndx].eEventState == eDeh_Apeared)
      {
        // In normal mode, add DE in DEH send process
        (void)DAPI_AddDE(&S_DE[ucIndx], E_TRUE);
      }
      else 
      {
        //do nothing
      }
    }
    else
    {
      //do nothing
    }

    if ((Deh_asDehLogTab[ucIndx].eEventState == eDeh_Undef) && (Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared != 0u))
    {

      // Build and get DE context
      Deh_asDehLogTab[ucIndx].eEventState = (DAPI_BuildDECtxt(&S_DE[ucIndx], LDEH_E_DISAPPEAR, Deh_asDehLogTab[ucIndx].ulDTCCode, DEH_DTC_FORMAT_ID, ucEcuCode)
        == LDEH_E_SUCCESS) ? eDeh_DisapearedConf_LGM : eDeh_Undef;
    }
  }


  (void)DAPI_ScheduleMainFunction();
}

//-----------------------------------------------------------------------------
/// \brief  Deh_CheckSafetyConditions
///
/// \descr  Check safety conditions for 'request of global clearing of vehicle faults'
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void Deh_CheckSafetyConditions(void)
{
	tsRte_SysMon_LifePhases    sLifePhases = { 0 };
	tsRte_SysMon_VehicleSpeed  sVehSpeed   = { 0 };
	// Variable for safety conditions check
	TE_Bool eSafetyConditionsCheck = E_FALSE;

	(void)Rte_Read_SysMon_LifePhases(&sLifePhases);
	(void)Rte_Read_SysMon_VehicleSpeed(&sVehSpeed);

	if ((sLifePhases.ePhaseVie == eNormalMode) &&
		(((sVehSpeed.eVehicleSpeed.unVehicleSpeed <= DEH_5KMH_THRESHOLD) && (sVehSpeed.eSigQty == SIG_VALID)) ||
		((sVehSpeed.eSigQty == SIG_INVALID) && (sVehSpeed.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable))))
	{
		eSafetyConditionsCheck = E_TRUE;
	}
	else
	{
		//do nothing
	}

	DAPI_SetSafetyConditions(eSafetyConditionsCheck);
}


//-----------------------------------------------------------------------------
/// \brief  Deh_AppearanceDetected
///
/// \descr Callback from Dem module. It is called at first detection of a fault
///        (transition from confirmed absent to present).
///        In this momment the enviromental parameters needed for DEH reporting are freezed
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
void Deh_AppearanceDetected(uint16 unEventId)
{
  uint8   ucActualPsError = 0u;
  uint32  ulDtcCode = 0u;
  uint16  newEventId = 0u;
  uint8   ucIndx = 0u;
  boolean boEventFound = FALSE;

  newEventId = unEventId + 1u;
  // Get DTC index
  ucActualPsError = ErrCust_GetActualErrorIndex(newEventId);

  // Get 3 byte DTC code
  ulDtcCode = ErrCust_ulGetDtcCode(ucActualPsError);
  
  //go through all elements of the DehLogTable o see if the DTC Code is already logged with correct state
  for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    if ((Deh_asDehLogTab[ucIndx].ulDTCCode == ulDtcCode) && ((Deh_asDehLogTab[ucIndx].eEventState == eDeh_Apeared) || (Deh_asDehLogTab[ucIndx].eEventState == eDeh_ApearedConf)))
    {
      //Increment DEH frame for Apeared
      Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared++;
      boEventFound = TRUE;
      break;
    }
  }
  //If no element found, save the info for the logged one
  if (boEventFound == FALSE)
  {
    for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
    {
      if ((Deh_asDehLogTab[ucIndx].eEventState == eDeh_DisapearedConf_LGM) 
        || (Deh_asDehLogTab[ucIndx].eEventState == eDeh_Init))
      {
        Deh_asDehLogTab[ucIndx].unDemEvent              = unEventId;
        Deh_asDehLogTab[ucIndx].ulDTCCode               = ulDtcCode;
        Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared    = 1u;
        Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared = 0u;
        Deh_TableFullStatus = FALSE;
        break;
      }
    }
    //Write DEH frames if the DTC was found with correct state and the list is not full
    if (ucIndx == DEH_TABLE_LOG_LENGTH)
    {
      //All 20 entrys is full
      Deh_TableFullStatus = TRUE;
    }
    else
    {
      // Build and get DE context
      Deh_asDehLogTab[ucIndx].eEventState = (DAPI_BuildDECtxt(&S_DE[ucIndx], LDEH_E_APPEAR, Deh_asDehLogTab[ucIndx].ulDTCCode, DEH_DTC_FORMAT_ID, ucEcuCode) 
                                                == LDEH_E_SUCCESS) ? eDeh_Apeared : eDeh_Undef;
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  Deh_AppearanceConfirmed
///
/// \descr  Callback from Dem module. It is called at first detection of a fault confirmed present
///        (transition from present to confirmed present).
///        In this momment the DEH frames shall be sent.
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
void Deh_AppearanceConfirmed(uint16 unEventId)
{
	uint8  ucActualPsError = 0u;
	uint16 newEventId = 0u;
	uint8  ucStatusOfDtc = 0u;
  uint8  ucIndx = 0u;
  uint32 ulDtcCode = 0u;

	newEventId = unEventId + 1u;
	// Get DTC index
	ucActualPsError = ErrCust_GetActualErrorIndex(newEventId);

  // Get 3 byte DTC code
  ulDtcCode = ErrCust_ulGetDtcCode(ucActualPsError);

	// Get status of a DTC based on given EventId
	ucStatusOfDtc = ErrCust_GetStatusOfDtc(ucActualPsError);

  //go through all elements and found the one with State eDeh_Apeared, change it into eDeh_ApearedConf
  for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    if((Deh_asDehLogTab[ucIndx].ulDTCCode == ulDtcCode) && (Deh_asDehLogTab[ucIndx].unDemEvent == unEventId) &&
      (Deh_asDehLogTab[ucIndx].eEventState == eDeh_Apeared))
    {
      Deh_asDehLogTab[ucIndx].eEventState = eDeh_ApearedConf;
      Deh_TableFullStatus                 = FALSE;
      break;
    }
    else if ((Deh_asDehLogTab[ucIndx].ulDTCCode == ulDtcCode) && (Deh_asDehLogTab[ucIndx].unDemEvent == unEventId) &&
              (Deh_asDehLogTab[ucIndx].eEventState == eDeh_Undef))
    {
      Deh_asDehLogTab[ucIndx].eEventState = eDeh_ApearedConf_DirectSent;
      //PRQA S 2469 1 // This loop control is intendeed in order to assure the functionality
      ucIndx = DEH_TABLE_LOG_LENGTH;
      Deh_TableFullStatus = FALSE;
      break;
    }
    else {

    }
  }

  //Send DEH frame if the DTC was found with correct state and the list is not full
  if (ucIndx == DEH_TABLE_LOG_LENGTH)
  {
    Deh_TableFullStatus = TRUE;
  }
  else
  {
    // In normal mode, add DE in DEH send process
    (void)DAPI_AddDE(&S_DE[ucIndx], E_TRUE);
  }	
}


//-----------------------------------------------------------------------------
/// \brief  Deh_DisappearanceDetected
///
/// \descr Callback from Dem module. It is called at first detection of a fault present
///        (transition from confirmed present to absent).
///        In this momment the DEH frames shall be Nvm stored
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
void Deh_DisappearanceDetected(uint16 unEventId)
{
  uint8   ucActualPsError = 0u;
  uint32  ulDtcCode = 0u;
  uint16  newEventId = 0u;
  uint8   ucIndx = 0u;
  uint8   ucDeh_ErrCustStatusOfDTC = 0u;
  boolean boEventFound = FALSE;

  newEventId = unEventId + 1u;
   // Get DTC index
  ucActualPsError = ErrCust_GetActualErrorIndex(newEventId);

  // Get 3 byte DTC code
  ulDtcCode = ErrCust_ulGetDtcCode(ucActualPsError);

  //Get Status of DTC
  ucDeh_ErrCustStatusOfDTC = ErrCust_ucGetStatusOfDTC(ucActualPsError);
 
  for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    if ((Deh_asDehLogTab[ucIndx].ulDTCCode == ulDtcCode) && ((Deh_asDehLogTab[ucIndx].eEventState == eDeh_Apeared) ||
      (Deh_asDehLogTab[ucIndx].eEventState == eDeh_ApearedConf)))
    {
      //Increment DEH frame for Disapeared
      Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared++;
      boEventFound = TRUE;
      break;
    }
  }

  //If no element found, save the info for the logged one
  if (boEventFound == FALSE)
  {
    for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
    {
      if ((Deh_asDehLogTab[ucIndx].eEventState == eDeh_Init) && ((ucDeh_ErrCustStatusOfDTC & ERRCUST_STATUS_CONFIRMED_DTC) != 0u))
      {
        Deh_asDehLogTab[ucIndx].ulDTCCode = ulDtcCode;
        Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared++;

        break;
      }
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  Deh_DisappearanceConfirmed
///
/// \descr Callback from Dem module. It is called at first detection of a fault confirmed absent
///        (transition from absent to confirmed absent).
///        In this momment the DEH frames shall be Nvm stored and sent
///
/// \param  unEventId: Alec Id
///
/// \return void
//-----------------------------------------------------------------------------
void Deh_DisappearanceConfirmed(uint16 unEventId)
{
  uint8   ucActualPsError = 0u;
  uint32  ulDtcCode = 0u;
  uint16  newEventId = 0u;
  boolean boStatusOfDTC = FALSE;
  uint8   ucIndx = 0u;
  uint8   ucCnt = 0u;

	newEventId = unEventId + 1u;
	// Get DTC index
	ucActualPsError = ErrCust_GetActualErrorIndex(newEventId);

	// Get 3 byte DTC code
	ulDtcCode = ErrCust_ulGetDtcCode(ucActualPsError);

  for (ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    if ((Deh_asDehLogTab[ucIndx].ulDTCCode == ulDtcCode) &&
      (Deh_asDehLogTab[ucIndx].eEventState == eDeh_ApearedConf))
    {
      //in case of multiple frame, this counter is saving the number of DEH frames remained with the same DTC code 
      ucCnt = (Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared - Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared) > 0u ? Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared - Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared : 0u;

      //when the last event occured, do break and send DEH frames
      if (ucCnt == 0u)
      {
        Deh_TableFullStatus = FALSE;
        //check if the DEH frame is Builded and get DE context
        Deh_asDehLogTab[ucIndx].eEventState = (DAPI_BuildDECtxt(&S_DE[ucIndx], LDEH_E_DISAPPEAR, Deh_asDehLogTab[ucIndx].ulDTCCode, DEH_DTC_FORMAT_ID, ucEcuCode) == LDEH_E_SUCCESS)
          ? eDeh_DisapearedConf_LGM : eDeh_Undef;

        //if the frames are correctly BUILD, send the DEH frames
        if (Deh_asDehLogTab[ucIndx].eEventState == eDeh_DisapearedConf_LGM)
        {
          (void)DAPI_AddDE(&S_DE[ucIndx], E_TRUE);
        }
        break;
      }
      else
      {
        //do nothing
      }
    }
    else if ((Deh_asDehLogTab[ucIndx].ulDTCCode == ulDtcCode) &&
      (Deh_asDehLogTab[ucIndx].eEventState == eDeh_Init))
    {
      //check if the DEH frame is Builded and get DE context
      Deh_asDehLogTab[ucIndx].eEventState = (DAPI_BuildDECtxt(&S_DE[ucIndx], LDEH_E_DISAPPEAR, Deh_asDehLogTab[ucIndx].ulDTCCode, DEH_DTC_FORMAT_ID, ucEcuCode) == LDEH_E_SUCCESS)
        ? eDeh_DisapearedConf_LGM : eDeh_Undef;

      //if the frames are correctly BUILD, send the DEH frames
      if (Deh_asDehLogTab[ucIndx].eEventState == eDeh_DisapearedConf_LGM)
      {
        (void)DAPI_AddDE(&S_DE[ucIndx], E_TRUE);
      }
      else
      {
        //do nothing
      }
    }
    else
    {
      //do nothing
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  APPLI_Send_Defaut
///
/// \descr  Callback from LGM DEH Module to send the faults
///
/// \param  PIu8P_ByteToSend: 
///
/// \return LDEH_TE_ErrVal
//-----------------------------------------------------------------------------
LDEH_TE_ErrVal APPLI_Send_Defaut(const Tu8P_Int PIu8P_ByteToSend)
{
  LDEH_TE_ErrVal  E_Ret = LDEH_E_SUCCESS;
  IL_StatusType   E_RetSend = IL_E_NOK;

  uint8 DEH_Frame[7];
  uint8 i;

  // We need to invert the data (Motorola)
  for (i = (uint8)0; i < (uint8)7; i++)
  {
    DEH_Frame[i] = PIu8P_ByteToSend[(uint8)7 - (uint8)i];
  }

  // Initialize the signals with the right values
  (void)LGM_InitMessage(DATA_JDD, &(DEH_Frame[0]));
  (void)LGM_InitMessage(HEADER_JDD, &(PIu8P_ByteToSend[0]));

  // Send the DEH frame
  E_RetSend = IL_EnvoyerIpdu((uint8)EVT_DEFAUT_FRAME_ID);

  if (E_RetSend != IL_E_OK)
  {
    // Error case
    E_Ret = LDEH_E_ERR_FATAL;
  }
  else
  {
    // Frame sent successfully
    E_Ret = LDEH_E_SUCCESS;
  }
  return E_Ret;
}


//-----------------------------------------------------------------------------
/// \brief  APPLI_DENotAck
///
/// \descr Callback from LGM module. It is called when Ack was not done.
///
/// \param  PISP_DE => Pointer to the DE to send
///
/// \return void
//-----------------------------------------------------------------------------
void APPLI_DENotAck(LDEH_TS_DECtxt const * const PISP_DE)
{
	Rte_Call_DemPrj_ReportErrorStatus((uint16)MED_NOT_ACK, DEM_EVENT_STATUS_FAILED);
	(void)PISP_DE;
}


//-----------------------------------------------------------------------------
/// \brief  APPLI_DEAck
///
/// \descr Callback from LGM module. It is called when Ack was done.
///
/// \param  PISP_DE => Pointer to the DE to send
///
/// \return void
//-----------------------------------------------------------------------------
void APPLI_DEAck(LDEH_TS_DECtxt const * const PISP_DE)
{
	Rte_Call_DemPrj_ReportErrorStatus((uint16)MED_NOT_ACK, DEM_EVENT_STATUS_PASSED);
	(void)PISP_DE;
}


//-----------------------------------------------------------------------------
/// \brief  Default_BSI_AppearedDetected
///
/// \descr  Appearance confirmed of 0x036 frame callback
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BSI_AppearedDetected(void)
{
	Deh_AppearanceDetected((uint16)HS6_COMMANDES_VSM_036_ID);
}


//-----------------------------------------------------------------------------
/// \brief  Default_BSI_AppearedConfirmed
///
/// \descr  Appearance confirmed of 0x036 frame callback
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BSI_AppearedConfirmed(void)
{
	Deh_AppearanceConfirmed((uint16)HS6_COMMANDES_VSM_036_ID);
	// Reset DTC U014087 - frame lost
	Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_COMMANDES_VSM_036_ID, DEM_EVENT_STATUS_FAILED);
}


//-----------------------------------------------------------------------------
/// \brief  Default_BSI_DisappearedDetected
///
/// \descr  Disappearance detected of 0x036 frame callback
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BSI_DisappearedDetected(void)
{
  Deh_DisappearanceDetected((uint16)HS6_COMMANDES_VSM_036_ID);
}


//-----------------------------------------------------------------------------
/// \brief  Default_BSI_DisappearedConfirmed
///
/// \descr  Disappearance confirmed of 0x036 frame callback
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BSI_DisappearedConfirmed(void)
{
  Deh_DisappearanceConfirmed((uint16)HS6_COMMANDES_VSM_036_ID);
  // Reset DTC U014087 - frame lost
  Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_COMMANDES_VSM_036_ID, DEM_EVENT_STATUS_PASSED);
}


//-----------------------------------------------------------------------------
/// \brief  Backup_C_ABS_BSI
///
/// \descr  LGM callback for backup in NvM of C_ABS_BSI counter
///
/// \param  ui8_Counter - C_ABS_BSI counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Backup_C_ABS_BSI(UINT8 ui8_Counter)
{
  NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter = ui8_Counter;
}


//-----------------------------------------------------------------------------
/// \brief  Recover_C_ABS_BSI
///
/// \descr  LGM callback for recovery from NvM of C_ABS_BSI counter
///
/// \param  p_ui8_Counter - pointer to C_ABS_BSI counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Recover_C_ABS_BSI(UINT8* p_ui8_Counter)
{
  *p_ui8_Counter = NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter;
}


//-----------------------------------------------------------------------------
/// \brief  Default_BusOff_AppearedDetected
///
/// \descr  LGM callback for Bus Off default appearance detected
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BusOff_AppearedDetected(void)
{
  Deh_AppearanceDetected((uint16)SUBCAN_BUSOFF);
}


//-----------------------------------------------------------------------------
/// \brief  Default_BusOff_AppearedConfirmed
///
/// \descr  LGM callback for Bus Off default appearance confirmed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BusOff_AppearedConfirmed(void)
{
  Deh_AppearanceConfirmed((uint16)SUBCAN_BUSOFF);
  // Fixed based on issue - LDMO-3635
  Rte_Call_DemPrj_Set_DiagWindow(TRUE);
  // Reset DTC U1FC488 - Bus Off
  Rte_Call_DemPrj_ReportErrorStatus((uint16)SUBCAN_BUSOFF, DEM_EVENT_STATUS_FAILED);
}


//-----------------------------------------------------------------------------
/// \brief  Default_BusOff_DisappearedDetected
///
/// \descr  LGM callback for Bus Off default dissapearance detected
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BusOff_DisappearedDetected(void)
{
  Deh_DisappearanceDetected((uint16)SUBCAN_BUSOFF);
}


//-----------------------------------------------------------------------------
/// \brief  Default_BusOff_DisappearedConfirmed
///
/// \descr  LGM callback for Bus Off default dissapearance confirmed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_BusOff_DisappearedConfirmed(void)
{
  Deh_DisappearanceConfirmed((uint16)SUBCAN_BUSOFF);
  // Reset DTC U1FC488 - Bus Off
  Rte_Call_DemPrj_ReportErrorStatus((uint16)SUBCAN_BUSOFF, DEM_EVENT_STATUS_PASSED);
  // Fixed based on issue - LDMO-3635
  Rte_Call_DemPrj_Set_DiagWindow(FALSE);
}


//-----------------------------------------------------------------------------
/// \brief  Backup_C_BusOff
///
/// \descr  LGM callback for backup in NvM of C_BussOff counter
///
/// \param  ui8_Counter - C_BussOff counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Backup_C_BusOff(UINT8 ui8_Counter)
{
  NvmBlockNmBackupCounters.ucC_BusOff_Counter = ui8_Counter;
}


//-----------------------------------------------------------------------------
/// \brief  Recover_C_BusOff
///
/// \descr  LGM callback for recovery from NvM of C_BussOff counter
///
/// \param  p_ui8_Counter - pointer to C_BussOff counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Recover_C_BusOff(UINT8* p_ui8_Counter)
{
  *p_ui8_Counter = NvmBlockNmBackupCounters.ucC_BusOff_Counter;
}


//-----------------------------------------------------------------------------
/// \brief  Bus_Off_Callback
///
/// \descr  LGM callback for Buss Off detection
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Bus_Off_Callback(void)
{
  // Perform NvM write on NM Backup Counters Block
  (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockNmBackupCountersId, (void*)&NvmBlockNmBackupCounters);
}


//-----------------------------------------------------------------------------
/// \brief  Default_Mute_AppearedDetected
///
/// \descr  LGM callback for CAN Mute default appearance detected
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_Mute_AppearedDetected(void)
{
  Deh_AppearanceDetected((uint16)Mute_ECU);
}


//-----------------------------------------------------------------------------
/// \brief  Default_Mute_AppearedConfirmed
///
/// \descr  LGM callback for CAN Mute default appearance confirmed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_Mute_AppearedConfirmed(void)
{
  Deh_AppearanceConfirmed((uint16)Mute_ECU);
  // Reset DTC U1FC313 - CAN Mute
  Rte_Call_DemPrj_ReportErrorStatus((uint16)Mute_ECU, DEM_EVENT_STATUS_FAILED);
}


//-----------------------------------------------------------------------------
/// \brief  Default_Mute_DisappearedDetected
///
/// \descr  LGM callback for CAN Mute default disappearance detected
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_Mute_DisappearedDetected(void)
{
  Deh_DisappearanceDetected((uint16)Mute_ECU);
}


//-----------------------------------------------------------------------------
/// \brief  Default_Mute_DisappearedConfirmed
///
/// \descr  LGM callback for CAN Mute default disappearance confirmed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Default_Mute_DisappearedConfirmed(void)
{
  Deh_DisappearanceConfirmed((uint16)Mute_ECU);
  // Reset DTC U1FC313 - CAN Mute
  Rte_Call_DemPrj_ReportErrorStatus((uint16)Mute_ECU, DEM_EVENT_STATUS_PASSED);
}


//-----------------------------------------------------------------------------
/// \brief  Backup_C_Mute
///
/// \descr  LGM callback for backup in NvM of C_Mute counter
///
/// \param  ui8_Counter - C_Mute counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Backup_C_Mute(UINT8 ui8_Counter)
{
  NvmBlockNmBackupCounters.ucC_Mute_Counter = ui8_Counter;
}


//-----------------------------------------------------------------------------
/// \brief  Recover_C_Mute
///
/// \descr  LGM callback for recovery from NvM of C_Mute counter
///
/// \param  p_ui8_Counter - pointer to C_Mute counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Recover_C_Mute(UINT8* p_ui8_Counter)
{
  *p_ui8_Counter = NvmBlockNmBackupCounters.ucC_Mute_Counter;
}


//-----------------------------------------------------------------------------
/// \brief  Backup_UCE_ABS_RL_F_1_HDC
///
/// \descr  LGM callback for backup in NvM of UCE_ABS_RL_F_1_HDC counter
///
/// \param  ui8_Counter - UCE_ABS_RL_F_1_HDC counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Backup_UCE_ABS_RL_F_1_HDC(UINT8 ui8_Abs)
{
  NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter = ui8_Abs;
}


//-----------------------------------------------------------------------------
/// \brief  Recover_UCE_ABS_RL_F_1_HDC
///
/// \descr  LGM callback for recovery from NvM of UCE_ABS_RL_F_1_HDC counter
///
/// \param  p_ui8_Abs - pointer to UCE_ABS_RL_F_1_HDC counter value
///
/// \return void
//-----------------------------------------------------------------------------
void Recover_UCE_ABS_RL_F_1_HDC(UINT8* p_ui8_Abs)
{
  *p_ui8_Abs = NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter;
}


// EOF
