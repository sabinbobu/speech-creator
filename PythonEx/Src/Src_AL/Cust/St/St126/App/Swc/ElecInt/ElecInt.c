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
/// \file   ElecInt.c
///
/// \brief  Electronic Integration Mode handling
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <ElecInt.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif // UNIT_TEST
#include <AL_Helper.h>
#include <LgmEIMMainAPI.h>
#include <LgmDEHMainAPI.h>
#include <_NM_Types.h>
//#include <SysMonRx.h>
//#include <SysMonTx.h>
#include <SigPrepRx.h>
#include <SigPrepTx.h>

//extern void EcuM_RequestRUN(uint8 ucUser);
//extern void EcuM_ReleasePOST_RUN(uint8 ucUser);

//-----------------------------------------------------------------------------
// Local defines
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
/// \brief  ElecInt_Init
///
/// \descr  Electronic Integration init function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void ElecInt_Init(void)
{
  TE_Bool boElecInt_SafetyConditionsCheck = E_TRUE;

  // Init EI module
  EAPI_InitModule();

  // Inform the EI module of the safety conditions state
  EAPI_SetSafetyConditions(boElecInt_SafetyConditionsCheck);
}


//-----------------------------------------------------------------------------
/// \brief  ElecInt_Cycle
///
/// \descr  Electronic Integration cyclic function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void ElecInt_Cycle(void)
{
  LEIM_TE_ActionRequest E_RetReqAction;

  E_RetReqAction = EAPI_MainFunction();

  if (LEIM_E_AR_ENTEREIM == E_RetReqAction)
  {
    // Enter EIM
    ElecInt_EnterEIMMode();
  }
  else if (LEIM_E_AR_EXITEIM == E_RetReqAction)
  {
    // Exit EIM
    ElecInt_ExitEIMMode();
  }
  else
  {
    // nothing to do
  }
}



//-----------------------------------------------------------------------------
/// \brief  ElecInt_EnterEIMMode
///
/// \descr  Enter Electronic Integration Mode function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void  ElecInt_EnterEIMMode(void)
{
  // Stop memorizing the defects
  NM_ProhibitDefectMemorization(LGM_TRUE);

  // Do not allow to store the defects
  DAPI_PermFifoStorage(LDEH_E_FIFO_NOTPERM);

  // Stop transmission
  (void)NM_CommunicationControl(ENABLE_RX_AND_DISABLE_TX);
}



//-----------------------------------------------------------------------------
/// \brief  Com_Loss_Callback
///
/// \descr  LGM callback for Loss of Communication
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void  Com_Loss_Callback(void)
{
  LEIM_TE_CurrentEIMode E_Ret;
  boolean boEnable = TRUE;
  DAPI_SetPermToSend(LDEH_E_SEND_NOTPERM);

  E_Ret = EAPI_GetCurrentEIMode();

  if (LEIM_E_ACTIVE == E_Ret)
  {
    // Stop transmission
    (void)NM_CommunicationControl(ENABLE_RX_AND_DISABLE_TX);
  }
  else
  {
    NM_ProhibitDefectMemorization(LGM_FALSE);
  }

  // Re-enable SysMonRx and SigPrepRx in case of LIMP HOME mode
  //SysMonRx_ComM_EnableCallbacks();

  (void)Rte_Write_ElecInt_EnableCallbacks(boEnable);
  SigPrepRx_ComM_EnableCallbacks();
}



//-----------------------------------------------------------------------------
/// \brief  ElecInt_EnterEIMMode
///
/// \descr  Enter Electronic Integration Mode function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void  ElecInt_ExitEIMMode(void)
{
  NM_ModeType NMMode;

  // Start memorizing the defects
  NM_ProhibitDefectMemorization(LGM_FALSE);

  // Allow to store the defects
  DAPI_PermFifoStorage(LDEH_E_FIFO_PERM);

  // Get life phasis from the NM
  (void)NM_GetMode(&NMMode);

  if ((LIMP_HOME_MODE == NMMode) || (NM_NORMAL == NMMode))
  {
    // Restart transmission
    (void)NM_CommunicationControl(ENABLE_RX_AND_TX);
  }
  else
  {
    // nothing to do
  }
}





//-----------------------------------------------------------------------------
/// \brief  Normal_Request_Callback
///
/// \descr  LGM callback for Normal request
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void  Normal_Request_Callback(void)
{
  LEIM_TE_CurrentEIMode E_Ret;
  boolean boEnable = TRUE;
  uint8 ucReq = 0u;

  DAPI_SetPermToSend(LDEH_E_SEND_PERM);

  E_Ret = EAPI_GetCurrentEIMode();

  if (LEIM_E_ACTIVE == E_Ret)
  {
    // Stop transmission
    (void)NM_CommunicationControl(ENABLE_RX_AND_DISABLE_TX);
  }
  else
  {
    NM_ProhibitDefectMemorization(LGM_FALSE);
  }

  // Enable SysMon and SigPrep Rx/Tx
  //SysMonRx_ComM_EnableCallbacks();
  (void)Rte_Write_ElecInt_EnableCallbacks(boEnable);
  //SysMonTx_ComM_ActivateTxBufer();
  (void)Rte_Write_ElecInt_ActivateTxBufer(boEnable);
  SigPrepRx_ComM_EnableCallbacks();
  SigPrepTx_ComM_ActivateTxBufer();


  //EcuM_RequestRUN(0u);
  (void)Rte_Write_ElecInt_RequestRUN(&ucReq);

  //EcuM_ReleasePOST_RUN(0u);
  (void)Rte_Write_ElecInt_ReleasePOST_RUN(&ucReq);
} // PRQA S 5324 1 // Software Architecture

  


//-----------------------------------------------------------------------------
/// \brief Wake_Up_Request_Callback
///
/// \descr NM callback for wake up network
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Wake_Up_Request_Callback(void)
{
    boolean boEnable = FALSE;
    // Disable SysMon and SigPrep Rx/Tx
    //SysMonRx_ComM_DisableCallbacks();
    (void)Rte_Write_ElecInt_EnableCallbacks(boEnable);
    //SysMonTx_ComM_DeactivateTxBuffer();
    (void)Rte_Write_ElecInt_ActivateTxBufer(boEnable);
    SigPrepRx_ComM_DisableCallbacks();
    SigPrepTx_ComM_DeactivateTxBuffer();
}

//-----------------------------------------------------------------------------
/// \brief Sleep_Callback
///
/// \descr NM callback for sleep network
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Sleep_Callback(void)
{
    boolean boEnable = FALSE;
    // Disable SysMon and SigPrep Rx/Tx
    //SysMonRx_ComM_DisableCallbacks();
    (void)Rte_Write_ElecInt_EnableCallbacks(boEnable);
    //SysMonTx_ComM_DeactivateTxBuffer();
    (void)Rte_Write_ElecInt_ActivateTxBufer(boEnable);
    SigPrepRx_ComM_DisableCallbacks();
    SigPrepTx_ComM_DeactivateTxBuffer();
}

//-----------------------------------------------------------------------------
/// \brief Sleep_Request_Callback
///
/// \descr NM callback for preparing to sleep network
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Sleep_Request_Callback(void)
{
    // Run release by NM user
    //EcuM_ReleaseRUN(ECUM_LIFEPHASE_NM_USER);
    uint8 ucReq = 0u;
    boolean boEnable = FALSE;
    (void)Rte_Write_ElecInt_ReleaseRUN(&ucReq);

    // Disable SysMon and SigPrep Rx/Tx
    //SysMonRx_ComM_DisableCallbacks();
    (void)Rte_Write_ElecInt_EnableCallbacks(boEnable);
    //SysMonTx_ComM_DeactivateTxBuffer();
    (void)Rte_Write_ElecInt_ActivateTxBufer(boEnable);
    SigPrepRx_ComM_DisableCallbacks();
    SigPrepTx_ComM_DeactivateTxBuffer(); 
}

//-----------------------------------------------------------------------------
/// \brief Com_Off_Request_Callback
///
/// \descr NM callback for COM OFF network
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Com_Off_Request_Callback(void)
{
    boolean boEnable = FALSE;
    // Disable SysMon and SigPrep Rx/Tx
    //SysMonRx_ComM_DisableCallbacks();
    (void)Rte_Write_ElecInt_EnableCallbacks(boEnable);
    //SysMonTx_ComM_DeactivateTxBuffer();
    (void)Rte_Write_ElecInt_ActivateTxBufer(boEnable);
    SigPrepRx_ComM_DisableCallbacks();
    SigPrepTx_ComM_DeactivateTxBuffer();
}


//-----------------------------------------------------------------------------
/// \brief Connected_Callback
///
/// \descr NM network on (connected) callback
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Connected_Callback(void)
{
    // NM Run Request
    //EcuM_RequestRUN(ECUM_LIFEPHASE_NM_USER);
    uint8 ucReq = 0u;
    (void)Rte_Write_ElecInt_RequestRUN(&ucReq);
}


// EOF
