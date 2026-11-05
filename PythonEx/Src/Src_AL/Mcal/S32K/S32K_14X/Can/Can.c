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
/// \file  Can.c
///
/// \brief Can functions APIs implementation.
///
/// \descr 
///
/// \author Ramona-Andreea Bolboaca (f33613c)
///         mailTo:ramona-andreea.bolboaca(at)magnetimarelli.com
//-----------------------------------------------------------------------------


//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <Bsw/Com/ComStack_Types.h>
#include <Can.h>
#include <Bsw/Com/ISO15765/CanTp.h>
#include <Cfg/Cfg.h>
#include <stddef.h>
#include <string.h>
#include <can_pal.h>
#include <UtilUtility.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//=============================================================================
// Private Variables
//=============================================================================

  static volatile can_message_t recvMsg;
  static const can_buff_config_t buffCfg = {
  /* enableFD, enableBRS, fdPadding,        idType,         isRemote*/
     FALSE,     TRUE,      PADDING_BYTE,     CAN_MSG_ID_STD, FALSE
  };

////=============================================================================
//// Private functions declaration
////=============================================================================
static void Can_GetMsgRxBuff(void);
//
//=============================================================================
// Public functions definition
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rx callback for CAN0 used in Can_Cfg.h
///
/// \descr  Take the received message and put it into the CAN transport protocol stack 
///
/// \param  *data - the received data
/// \param  dlc - the length of the received data
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros
void Can_RxBptCallback1(const uint8* data, uint8 dlc)
{
  PduInfoType pduinfo;
  // PRQA S 3112 2 // parameters not used at the moment
  (void) dlc;

  // Copy data into pduinfo structure
  // PRQA S 311 1 // cast intended
  pduinfo.SduDataPtr = (SduDataPtrType)(data);
  pduinfo.SduLength = dlc;

  //CanTp_RxIndication(0U, &pduinfo);
}

// void Can_RxBptCallback2(cddcan_handle_type rx_handle, const uint8* data, uint8 dlc)
// {
// 
// }

// void Can_RxBptCallback3(cddcan_handle_type rx_handle, const uint8* data, uint8 dlc)
// {
// 
// }

//-----------------------------------------------------------------------------
/// \brief  Initialization of Can Cycle Task
///
/// \descr  
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros
void TaskCan_Cycle_Init(void)
{
  Can_Init(&Can_Config);
}

//-----------------------------------------------------------------------------
/// \brief  Can Cyclic Execution Task
///
/// \descr  
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros
void TaskCan_Cycle_Func(void)
{ 
  static uint8 state;
  static uint32 status;
  
  if (state == 0U)
  {
    // Handle reception if necessary
    Can_GetMsgRxBuff(); // CAN_receive
    state = 1U;
  }
  else
  {
    status = CAN_GetTransferStatus((const can_instance_t*)Can_Config.Can_Cfg_atyCharacteristics[0].ptyInstType,
                                   CAN_RX_MAILBOX); 
    // Handle transmission if necessary
    if (status != STATUS_BUSY)
    {
      state = 0U;
      if (recvMsg.id == CAN_RX_MSG_ID)
      {
        Can_RxBptCallback1((const uint8 *)recvMsg.data, recvMsg.length);
        recvMsg.id = 0U;
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  Can_Init
///
/// \descr   This function initializes the Can module using the maps from 
///          Can_Cfg.h This function does not use the configuration structure 
///          given as parameter.
/// \param   *ConfigPtr  configuration structure pointer (not used)
///
/// \return  void 
//-----------------------------------------------------------------------------
void Can_Init(const Can_SpecificType* Can_Config)
{
  CAN_Init((const can_instance_t*)Can_Config->Can_Cfg_atyCharacteristics[0].ptyInstType, 
           (const can_user_config_t*)Can_Config->Can_Cfg_atyCharacteristics[0].ptyUsrCfgType);
   
  CAN_ConfigRxBuff((const can_instance_t*)Can_Config->Can_Cfg_atyCharacteristics[0].ptyInstType,
                   CAN_RX_MAILBOX,
                   &buffCfg,
                   CAN_RX_MSG_ID);
  CAN_ConfigTxBuff((const can_instance_t*)Can_Config->Can_Cfg_atyCharacteristics[0].ptyInstType,
                   CAN_TX_MAILBOX,
                   &buffCfg);
}

//-----------------------------------------------------------------------------
/// \brief   Can_Enable
///
/// \descr   This function enables the given Can channel.
/// \param   channel - the  channel to be enabled
///
/// \return  void 
//-----------------------------------------------------------------------------
void Can_Enable(uint8 channel)
{
  (void)channel;

}

//-----------------------------------------------------------------------------
/// \brief  Send a CAN message
///
/// \descr   This function sends a message over CAN
/// \param   handle  the handle of the CAN message that was configured in 
///          Can_Cfg.h
/// \param  * data  the data to be sent over CAN
///
/// \return  true: message sent
/// \return  false: message not sent
//-----------------------------------------------------------------------------
boolean Can_SendMsg(const uint8* data, uint32 size)
{
  boolean retVal = TRUE;
  can_message_t message;
  message.cs= 0U;
  message.id = CAN_TX_MSG_ID;
  memset(message.data, PADDING_BYTE, 8U);
  memcpy(&message.data[0], data, size);
  message.length = size % 8U == 0U ? size : size + (8U - size % 8U);

  //CAN_ConfigTxBuff((const can_instance_t*)Can_Config.Can_Cfg_atyCharacteristics[0].ptyInstType, 
  //                 CAN_TX_MAILBOX, 
  //                 &buffCfg);  

  CAN_Send((const can_instance_t*)Can_Config.Can_Cfg_atyCharacteristics[0].ptyInstType,
           CAN_TX_MAILBOX, 
           &message);
  return retVal;
}


//=============================================================================
// Private functions definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief   Can_GetMsgRxBuff
///
/// \descr   This function stores the received data from hardware buffers
///          to software buffers and calls the according callback function
///          if new data has been received.
///
/// \param   void
///
/// \return  -
//-----------------------------------------------------------------------------
static void Can_GetMsgRxBuff(void)
{
  CAN_Receive((const can_instance_t*)Can_Config.Can_Cfg_atyCharacteristics[0].ptyInstType,
              CAN_RX_MAILBOX, 
              (can_message_t*)&recvMsg);
}

void Can_Cycle_SetDownloadIsInProgress(boolean value)
{
  (void) value;
//  Can_CycleDownloadIsInProgress = value;
}
