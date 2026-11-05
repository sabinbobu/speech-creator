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
/// \file  CddDma.c
///
/// \brief
///
//-----------------------------------------------------------------------------

/*============================================================================ */
/* Includes */
/*============================================================================ */


#include <CddDma_Types.h>
#include <AL_Helper.h>

// PRQA S 1503 EOF // Unused Functions are possible due to platform architecture.
// PRQA S 303 EOF // this module uses direct memory access

// PRQA S 310, 3305 2 // Casting is OK, as we need access Registers
STATIC_AL volatile  tsCddDma_S32K_146_Registers*           CddDma_psRegister = CDDDMA;                       // PRQA S 303  //the cast is allowed since we are accessing hardware registers
STATIC_AL volatile  tsCddDmaMux_S32K_146_Register*          CddDma_DmaMux_psRegister = CDDDMA_DMAMUX;         // PRQA S 303  //the cast is allowed since we are accessing hardware registers
//PRIVATE CddDma_InterruptRegister_StructType*  CddDma_vpst__InterruptRegister = (CddDma_InterruptRegister_StructType*)&ICDMA0;



typedef struct tsCddDmaConfig
{
  teCddDma_Source_Trigger                     eDmaSourceTriggerName;
  teCddDma_InterruptRequestChannel            eDmaIrqNumber;
  teCddDma_TransferSize                       eTransferSize;
  teCddDma_AddressOperations                  eSourceIncrement;
  teCddDma_AddressOperations                  eTargetIncrement;
  teCddDma_LoopMode                           eLoopMode;
} tsCddDmaConfig;

// need +1 in case VIRTUAL_TRIGGER_NAMES_COUNT==0
//#pragma ghs nowarning 550 // Disable: "warning #550-D: Not used pfn__DmaCallbacks are possible depending on configuration
//#pragma ghs nowarning 177 // Disable: "warning #177-D: Not used pfn__DmaCallbacks are possible depending on configuration
//lint -e528 Symbol 'pfn__DmaCallbacks' not referenced
//lint -e551 Not used pfn__DmaCallbacks are possible depending on configuration
// PRQA S 3229, 3207 1 // Not used afpDmaCallbacks are possible depending on configuration

STATIC_AL CddDma_tfpCallback                           afpDmaCallbacks[(uint8)VIRTUAL_TRIGGER_NAMES_COUNT + 1U];



//lint -e451 repeated file inclusion is desired in this case
//lint -e545 Suspicious use of & is in this case allowed
//lint -e485 Duplicate initialization of object element is ok (C99 usage)
#define CDDDMA_MAC_EXPAND

#define  CDDDMA_MAC_STEP2_CREATE_CONST_ARRAY
#include <CddDma_Cfg.h>
#undef   CDDDMA_MAC_STEP2_CREATE_CONST_ARRAY


#ifdef   CDDDMA_USE_CAT2_INTERRUPTS
#else
#define  CDDDMA_MAC_STEP3_CREATE_INTERRUPT_DEFINES
#include <CddDma_Cfg.h>
#undef   CDDDMA_MAC_STEP3_CREATE_INTERRUPT_DEFINES
#endif

#undef CDDDMA_MAC_EXPAND

//lint +e451
//lint +e485
//lint +e545

//-----------------------------------------------------------------------------
/// \brief  Returns true if Dma Transfer Job is completed.
///
/// \descr  This function can be used for polling dma status.
///
/// \param  eDmaChannelName  The Dma Name defined in CddDma_Cfg.h
///
/// \return boolean      TRUE - JOB is finished
///                      FALSE  JOB still running
//-----------------------------------------------------------------------------
boolean CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName)
{
  boolean boRet = FALSE;
  if (CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.sBit.u1DONE == 1U)
  {
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.sBit.u1DONE = 0U;
    boRet = TRUE;
  }
  return boRet;
}

//-----------------------------------------------------------------------------
/// \brief  Creates a software trigger for the chosen DMA Channel.
///
/// \descr  This function can be used for software triggering.
///
/// \param  eDmaChannelName  The Dma Name defined in CddDma_Cfg.h
///
/// \return -
//-----------------------------------------------------------------------------
void CddDma_GenerateTriggerSignal(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName)
{
  // Software Start DMA Transfer
  CddDma_psRegister->Reg_SSRT.ucData = (uint8)eDmaChannelName;
}

//-----------------------------------------------------------------------------
/// \brief  Setup a Dma Job.
///
/// \descr  Configure Channel Name, Source Address, Target Address and 
///         Amount of Repetitions.
///         When <afpCallback> is used, CddDma will use Interrupts to call 
///         these functions. Otherwise it will also execute but not use any
///         interrupts.
///
///         Note:
///         The Main Configuration see CddDma_Cfg for this channel remains 
///         unchanged (like transfer size, used dma interrupt, 
///         source increment, target increment, hw_trigger)
///
/// \param  eDmaChannelName  The Dma Name defined in CddDma_Cfg.h
/// \param  psParameter      source address, target address, repetitions
/// \param  afpCallback       The callback function, if not needed (void* null)
///
/// \return -
//-----------------------------------------------------------------------------
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback)
{
  if (fpCallback != NULL_PTR)
  {
#ifndef   CDDDMA_USE_CAT2_INTERRUPTS
    afpDmaCallbacks[eDmaChannelName] = fpCallback;
#endif
    //config channel interrupt 
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR = 1U;  //generates an interrupt request when current major interation reaches zero
  }
  else
  {
    // do not need to set pfn__DmaCallbacks because it will not be called  - disable all interrupt
    //config channel interrupt 
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR = 0U;
  }

  CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.unData &= (uint16)0xFFFFFFFFU ^ CDDDMA_TCD_CSR_DONE_MASK; // 0x80u is CSR_DONE_MASK

   // DMA Source Address Register
  CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_SADDR.ulData = (uint32)psParameter->pulSourceAddress;  //Source Address       // PRQA S 306  // correct cast - working with actual address

  //DMA Destination Address Register
  CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_DADDR.ulData = (uint32)psParameter->pulTargetAddress;  //Target Address       // PRQA S 306  // correct cast - working with actual address


  if (CDDDMA_CHECK_ADDRESS(psParameter->pulSourceAddress) && CDDDMA_CHECK_ADDRESS(psParameter->pulTargetAddress))                   // PRQA S 306  // correct cast - working with actual address
  {
    //set channel minor link - enable minor link and set the channel number to be linked
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK = 1U;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK = 1U;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = (uint8)eDmaChannelName;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = (uint8)eDmaChannelName;

    //set number of repetitions - BITER must be equal with CITER at the beginning of a transmission
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER = psParameter->unRepetitions;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER = psParameter->unRepetitions;

    //trigger channel transfer   -> it is sufficient to do it once as we enabled minor link and channel link
    CddDma_psRegister->Reg_SSRT.ucData = (uint8)eDmaChannelName;
  }
  else
  {
    boolean boHasRequestSource = CddDma_cast__DynConfig_Triggers[eDmaChannelName].eDmaSourceTriggerName != CDDDMA_REQ_DISABLED ? TRUE : FALSE;
    if (boHasRequestSource != FALSE)
    {
      //set channel minor link - disable minor link 
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK = 0U;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK = 0U;

      //set number of repetitions - BITER must be equal with CITER at the beginning of a transmission
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u15BITER = psParameter->unRepetitions;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u15CITER = psParameter->unRepetitions;
    }
    else
    {
      //set channel minor link - enable minor link and set the channel number to be linked
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK = 1U;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK = 1U;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = (uint8)eDmaChannelName;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = (uint8)eDmaChannelName;

      //set number of repetitions - BITER must be equal with CITER at the beginning of a transmission
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER = psParameter->unRepetitions;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER = psParameter->unRepetitions;
    }

    //PRQA S 3101 1  // operand needed so that the final source address is adjusted to return to its beginning value
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_SLAST.ulData = -(psParameter->unRepetitions * (uint32)((uint32)1U << (uint8)CddDma_cast__DynConfig_Triggers[eDmaChannelName].eTransferSize));
    
    //PRQA S 3101 1  // operand needed so that the final destination address is adjusted to return to its beginning value
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_DLASTSGA.ulData = -(psParameter->unRepetitions * (uint32)((uint32)1U << (uint8)CddDma_cast__DynConfig_Triggers[eDmaChannelName].eTransferSize));

    if (boHasRequestSource != FALSE)
    {
      //enable HW request
      CddDma_psRegister->Reg_SERQ.ucData = (uint8)eDmaChannelName;
    }
    else
    {
      //trigger channel transfer   -> it is sufficient to do it once as we enabled minor link and channel link
     // CddDma_psRegister->Reg_SSRT.ucData = (uint8)eDmaChannelName;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.sBit.u1START = 1u;
    }
  }


}

//-----------------------------------------------------------------------------
/// \brief  Setup a Dma Job
///
/// \descr  Configure Channel Name, Source Address, Target Address and 
///         Amount of Repetitions.
///
///         This method like CddDma_StartJob, just without explizit assignment of, 
///         Callbacks to save some runtime.
///
/// \param  eDmaChannelName  The Dma Name defined in CddDma_Cfg.h
/// \param  psParameter      source address, target address, repetitions
///
/// \return -
//-----------------------------------------------------------------------------
void CddDma_StartJob_ForInterrupt(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter)
{
  //clear channel Done flag
  CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.unData &= (uint16)0xFFFFFFFFU ^ CDDDMA_TCD_CSR_DONE_MASK; // 0x80u is CSR_DONE_MASK
  //CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CSR.sBit.u1INTMAJOR = 1U;
  CddDma_psRegister->Reg_CERQ.ucData = (uint8)eDmaChannelName;

  // DMA Source Address Register
  CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_SADDR.ulData = (uint32)psParameter->pulSourceAddress;           //Source Address          // PRQA S 306  // correct cast - working with actual address

  //DMA Destination Address Register
  CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_DADDR.ulData = (uint32)psParameter->pulTargetAddress;           //Target Address          // PRQA S 306  // correct cast - working with actual address


  if (CDDDMA_CHECK_ADDRESS(psParameter->pulSourceAddress) && CDDDMA_CHECK_ADDRESS(psParameter->pulTargetAddress))                               // PRQA S 306  // correct cast - working with actual address
  {
    //set channel minor link - enable minor link and set the channel number to be linked
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK   = 1U;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK   = 1U;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH  = (uint8)eDmaChannelName;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH  = (uint8)eDmaChannelName;

    //set number of repetitions - BITER must be equal with CITER at the beginning of a transmission
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER = (uint8)psParameter->unRepetitions;
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER = (uint8)psParameter->unRepetitions;

    //trigger channel transfer   -> it is sufficient to do it once as we enabled minor link and channel link
    CddDma_psRegister->Reg_SSRT.ucData = (uint8)eDmaChannelName;
  }
  else
  {
    boolean boHasRequestSource = CddDma_cast__DynConfig_Triggers[eDmaChannelName].eDmaSourceTriggerName != CDDDMA_REQ_DISABLED ? TRUE : FALSE;
    if (boHasRequestSource != FALSE)
    {
      //set channel minor link - disable minor link 
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK = 0U;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK = 0U;

      //set number of repetitions - BITER must be equal with CITER at the beginning of a transmission
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKNO.sBit.u15BITER = psParameter->unRepetitions;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKNO.sBit.u15CITER = psParameter->unRepetitions;
    }
    else
    {
      //set channel minor link - enable minor link and set the channel number to be linked
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u1ELINK = 1U;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u1ELINK = 1U;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u4LINKCH = (uint8)eDmaChannelName;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u4LINKCH = (uint8)eDmaChannelName;

      //set number of repetitions - BITER must be equal with CITER at the beginning of a transmission
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_BITER.tuELINKYES.sBit.u9BITER = psParameter->unRepetitions;
      CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_CITER.tuELINKYES.sBit.u9CITER = psParameter->unRepetitions;
    }

    //PRQA S 3101 1  // operand needed so that the final source address is adjusted to return to its beginning value
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_SLAST.ulData = -(psParameter->unRepetitions * (uint32)((uint32)1U << (uint8)CddDma_cast__DynConfig_Triggers[eDmaChannelName].eTransferSize));

    //PRQA S 3101 1  // operand needed so that the final destination address is adjusted to return to its beginning value
    CddDma_psRegister->Reg_TCDn[eDmaChannelName].tuTCDn_DLASTSGA.ulData = -(psParameter->unRepetitions * (uint32)((uint32)1U << (uint8)CddDma_cast__DynConfig_Triggers[eDmaChannelName].eTransferSize));

    if (boHasRequestSource != FALSE)
    {
      //enable HW request
      CddDma_psRegister->Reg_SERQ.ucData = (uint8)eDmaChannelName;
    }
    else
    {
      //trigger channel transfer   -> it is sufficient to do it once as we enabled minor link and channel link
      CddDma_psRegister->Reg_SSRT.ucData = (uint8)eDmaChannelName;
    }
  }

  }


//-----------------------------------------------------------------------------
/// \brief  Enables / Disables the HW Trigger.
///
/// \descr  -
///
/// \param  eDmaChannelName  The Dma Name defined in CddDma_Cfg.h
/// \param  boEnabled         When True HW Trigger Signals Can Be Received
///
/// \return -
//-----------------------------------------------------------------------------
void CddDma_EnableHwTrigger(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, boolean boEnabled)
{
  if (boEnabled == 0U)
  {
    CddDma_psRegister->Reg_CERQ.ucData = (uint8)eDmaChannelName;
  }
  else
  {
    CddDma_psRegister->Reg_SERQ.ucData = (uint8)eDmaChannelName;
  }
}


//-----------------------------------------------------------------------------
/// \brief  Initialize CddDma with a set of Virtual Channels, 
///         Scan Groups, Triggers and HW Sampling, based on en__DmaConfiguration.
///
/// \descr  
///
/// \return -
//-----------------------------------------------------------------------------
void CddDma_Init(void)
{
  volatile  tsCddDma_S32K_146_Registers*           local_CddDma_psRegister = CDDDMA;          // PRQA S 303  //the cast is allowed since we are accessing hardware registers

  //set Control Register
  CddDma_psRegister->Reg_CR.sBit = (tsCddDma_S32K_146_CR) {
                                                            .u1EDBG = 0U,
                                                            .u1ERCA = 0U, //set channel arbitration mode(RR/Fixed priority)
                                                            .u1HOE  = 0U, //set halt on error
                                                            .u1HALT = 0U,
                                                            .u1CLM  = 0U,
                                                            .u1EMLM = 1U, //set minor looping command
                                                            .u1ECX  = 0U,
                                                            .u1CX   = 0U,
  };

  //init DmaMux
  for (uint8 ucDmaMuxChannel = 0; ucDmaMuxChannel < FEATURE_DMAMUX_CHANNELS; ucDmaMuxChannel++)
  {
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucDmaMuxChannel].ucData = 0;
  }

  for (uint8 ucVirtualDmaNumber = 0; ucVirtualDmaNumber < (uint8)VIRTUAL_TRIGGER_NAMES_COUNT; ucVirtualDmaNumber++)
  {
    uint8 ucTransferSize = (uint8)CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eTransferSize;
    uint8 ucTransferSizeLimited = ucTransferSize < 3U ? ucTransferSize : (uint8)DMA_TRANSFER_SIZE_32;

    //reset transmit command register
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLNO.ulData     = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_SADDR.ulData             = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_SOFF.unData              = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_ATTR.unData              = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_SLAST.ulData             = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_DADDR.ulData             = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_DOFF.unData              = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_CITER.tuELINKNO.unData   = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_DLASTSGA.ulData          = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_CSR.unData               = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_BITER.tuELINKNO.unData   = 0U;


    //set channel request and trigger
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucVirtualDmaNumber].sBit.u1ENBL = 0U;
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucVirtualDmaNumber].sBit.u6SOURCE = (uint8)CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eDmaSourceTriggerName;
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucVirtualDmaNumber].sBit.u1TRIG = 0U;
    CddDma_DmaMux_psRegister->Reg_CHCFGn[ucVirtualDmaNumber].sBit.u1ENBL = 1U;

    //DMA Transfer Attribute - set transfer size
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_ATTR.sBit.u3SSIZE = ucTransferSizeLimited;                //srcTransferSize
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_ATTR.sBit.u3DSIZE = ucTransferSizeLimited;                //destTransferSize

   
    //Set source/destination offset - 
    boolean boIsDma_Address_Fixed = (CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eSourceIncrement == DMA_ADDRESS_FIXED ? TRUE : FALSE);
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_SOFF.unData = (boIsDma_Address_Fixed == 1U) && (ucTransferSize < 3U) ? 0U : (uint16)((uint16)1U << ucTransferSizeLimited);
    boIsDma_Address_Fixed = (CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eTargetIncrement == DMA_ADDRESS_FIXED ? TRUE : FALSE);
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_DOFF.unData = (boIsDma_Address_Fixed == 1U) && (ucTransferSize < 3U) ? 0U : (uint16)((uint16)1U << ucTransferSizeLimited);

    //Set last adjustment(=Adjustment value added to the source address at the completion of the major iteration count)
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_SLAST.ulData         = 0U;

    //scatter gather disable
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_CSR.sBit.u1ESG        = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_CSR.sBit.u1MAJORELINK = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_DLASTSGA.ulData       = 0U;

    /*Set SMLOE - Source Minor Loop Offset Enable and DMLOE - Destination Minor Loop Offset Enable*/
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1SMLOE = (CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eSourceIncrement == DMA_ADDRESS_FIXED && ucTransferSize >= 3U) ? 1U : 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1DMLOE = (CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eTargetIncrement == DMA_ADDRESS_FIXED && ucTransferSize >= 3U) ? 1U : 0U;


    if((CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1SMLOE == 1U) || (CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFNO.sBit.u1DMLOE == 1U))
    {
      //TODO: improve the maths used - number of bytes and offset
      /* Set the total number of bytes to be transfered */
      CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFYES.sBit.u10NBYTES = (uint32)(((uint32)1U) << ucTransferSize);
      //Set minor loop offset
      //PRQA S 3101 1 // operand needed so that the minor loop offset value shall return to its beginning value after minor loop completion
      CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFYES.sBit.u20MLOFF  = -((uint32)(((uint32)1U) << ucTransferSize)); 
    }
    else
    {
      /* Set the total number of bytes to be transfered */
      CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_NBYTES.tuMLOFFNO.sBit.u30NBYTES = (uint32)(((uint32)1U) << ucTransferSize);
    }

    //set channel minor link - disable minor link
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_BITER.tuELINKNO.sBit.u1ELINK = 0U;
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_CITER.tuELINKNO.sBit.u1ELINK = 0U;

    //enable HW request
    CddDma_psRegister->Reg_SERQ.ucData = ucVirtualDmaNumber;

    //enable DREW bit that will disable HW request when a tranmission is done
    //endless = 1, none = 0
    CddDma_psRegister->Reg_TCDn[ucVirtualDmaNumber].tuTCDn_CSR.sBit.u1DREQ = ((uint8)CddDma_cast__DynConfig_Triggers[ucVirtualDmaNumber].eLoopMode == 1U) ? 0U : 1U;
  }
}

//EOF
