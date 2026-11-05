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
/// \file  CddSpi_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------

//==============================================================================
//  Includes
//==============================================================================
#include <CddSpi_Mac.h>
#include <CddSpi_CallOuts.h>
#include <AL_Helper.h>
#include <CddTps92520_Cb.h>

//==============================================================================
//  Preprocessor definitions
//==============================================================================
//Interfaces enumeration
#define CDDSPI_IFC0                             0
#define CDDSPI_IFC1                             1
#define CDDSPI_IFC2                             2
#define CDDSPI_IFC3                             3
#define CDDSPI_IFC4                             4
#define CDDSPI_IFC5                             5
#define CDDSPI_IFC6                             6
#define CDDSPI_IFC7                             7

//Device transmission parameters
#define CDDSPI_BRS_500K                         0U
#define CDDSPI_BRS_1M                           1U

#define CDDSPI_CPOL_0                           0U
#define CDDSPI_CPOL_1                           1U
#define CDDSPI_CPHA_0                           0U
#define CDDSPI_CPHA_1                           1U

#define CDDSPI_LSB_FIRST                        0U
#define CDDSPI_MSB_FIRST                        1U

#define CDDSPI_PARITY_NO                        0U
#define CDDSPI_PARITY_0                         1U
#define CDDSPI_PARITY_ODD                       2U
#define CDDSPI_PARITY_EVEN                      3U

//Hw mechanism used for the transmission in Single Operation mode
#define CDDSPI_SINGLE_POLLING                   0U
#define CDDSPI_SINGLE_INTERRUPT                 1U  //Not supported yet
#define CDDSPI_SINGLE_DMA                       2U  //Not supported yet

//Hw mechanism used for the transmission in Cyclic Operation mode
#define CDDSPI_CYCLIC_POLLING                   0U
#define CDDSPI_CYCLIC_INTERRUPT                 1U //Not supported yet
#define CDDSPI_CYCLIC_DMA                       2U

//==============================================================================
//  User Configuration: Operation options
//==============================================================================
//Enable operation modes
#define CDDSPI_SINGLE_OPERATION                 STD_ON
#define CDDSPI_CYCLIC_OPERATION                 STD_ON

//==============================================================================
//  User Configuration: Dynamic configuration
//==============================================================================
//Enable dynamic configuration (Change number of elements of one device)
#define CDDSPI_DYNAMIC_CFG                      STD_ON

//==============================================================================
//  User Configuration: StatusFault CallOut
//==============================================================================
//Enable Cyclic CallOut to provide Project Defined functionality
//If enabled, function void CddSpi_StatusFault(uint8 ucData) must be provided
#define CDDSPI_STATUS_FAULT                     STD_OFF // Spi Fault not implemented in LDM at CddSpi level

//==============================================================================
//  User Configuration: Debug
//==============================================================================
//Enable debug options
#define CDDSPI_DEBUG                            STD_OFF
#define CDDSPI_DEBUG_PROFILE                    STD_OFF
#define CDDSPI_DEBUG_ITM_RUNNABLE               STD_OFF
#define CDDSPI_DEBUG_ITM_INTERRUPT              STD_OFF
#define CDDSPI_DEBUG_ITM                        ITM_TRACE_D8
#define CDDSPI_DEBUG_SEQ_BUFF_SIZE              10U
#define CDDSPI_DEBUG_ELEMENT_BUFF_SIZE          10U
#define CDDSPI_DEBUG_CYCLIC_RECORD_SIZE         10U

//==============================================================================
//  User Configuration: Time Out 
//==============================================================================
#define CDDSPI_TIMEOUT_VAL                      0xFFFFUL

//==============================================================================
//  User Configuration:  Assertion
//==============================================================================
#define CDDSPI_STATIC_ASSERT(cond, msg)        //static_assert(cond, msg)

//==============================================================================
//  User Configuration:  Critical Section
//==============================================================================
#define CddSpi_EnterCriticalSection()          //SuspendAllInterrupts()
#define CddSpi_ExitCriticalSection()           //ResumeAllInterrupts()

//==============================================================================
//  User Configuration: Driver map
//==============================================================================
BEGIN_CDDSPI_MAP

 //Spi interfaces enabled
 BEGIN_CDDSPI_IFC
 //CDDSPI_IFC(Ifc, Hw mechanism for Syngle Mode, Hw mechanism for Cyclic Mode)
 CDDSPI_IFC(CDDSPI_IFC0, CDDSPI_SINGLE_POLLING, CDDSPI_CYCLIC_DMA)
 CDDSPI_IFC(CDDSPI_IFC1, CDDSPI_SINGLE_POLLING, CDDSPI_CYCLIC_DMA)
 END_CDDSPI_IFC

 //Slave configuration
 BEGIN_CDDSPI_DEV
 //CDDSPI_DEV_CFG(Device      ,Ifc          ,CS  ,len ,Elements, Brs               , Cpol         ,CPha          , Msb|Lsb         , Parity          , Callout for dynamic configuration)
 CDDSPI_DEV_CFG(SBC, CDDSPI_IFC0, 0, 16, 1, CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_1, CDDSPI_LSB_FIRST, CDDSPI_PARITY_NO, NULL_PTR)
 CDDSPI_DEV_CFG(BOOST, CDDSPI_IFC0, 1, 16, 1, CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST, CDDSPI_PARITY_NO, NULL_PTR)
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
 CDDSPI_DEV_CFG(STP, CDDSPI_IFC0, 3, 16, 1, CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_1, CDDSPI_MSB_FIRST, CDDSPI_PARITY_NO, NULL_PTR)
 CDDSPI_DEV_CFG(BUCK_0_5, CDDSPI_IFC1, 0, 16, 6, CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST, CDDSPI_PARITY_NO, CddTps92520_SpiGetConfig)
#elif defined (CFG_VARIANT_ECO)
 CDDSPI_DEV_CFG(BUCK_0_1, CDDSPI_IFC1, 0, 16, 2, CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST, CDDSPI_PARITY_NO, CddTps92520_SpiGetConfig)
#endif
 END_CDDSPI_DEV

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
 //BEGIN_CDDSPI_SEQ(Ifc , cycle offset, cycle prescaler, max cycles to wait for a transfer to be completed)
 BEGIN_CDDSPI_SEQ(CDDSPI_IFC0, 0, 0, 3)
 //BEGIN_CDDSPI_DEVCYC(devNAME)
 BEGIN_CDDSPI_DEVCYC(SBC)
 //CDDSPI_DEVCB_CFG(cbid, Tx Callback, Rx Callback, CRC Error bit Pos)
 CDDSPI_DEVCB_CFG(0, CddTle94x1_SpiTx, CddTle94x1_SpiRx)
 END_CDDSPI_DEVCYC
 BEGIN_CDDSPI_DEVCYC(BOOST)
 CDDSPI_DEVCB_CFG(0, CddNcv78702_SpiTx, CddNcv78702_SpiRx)
 END_CDDSPI_DEVCYC
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
 BEGIN_CDDSPI_DEVCYC(STP)
 CDDSPI_DEVCB_CFG(0, CddStp_SpiTx, CddStp_SpiRx)
 END_CDDSPI_DEVCYC
#endif
 END_CDDSPI_SEQ
 BEGIN_CDDSPI_SEQ(CDDSPI_IFC1, 0, 0, 3)
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
 BEGIN_CDDSPI_DEVCYC(BUCK_0_5)
 CDDSPI_DEVCB_CFG(0, CddTps92520_SpiTx, CddTps92520_SpiRx)
 CDDSPI_DEVCB_CFG(1, CddTps92520_SpiTx, CddTps92520_SpiRx)
 CDDSPI_DEVCB_CFG(2, CddTps92520_SpiTx, CddTps92520_SpiRx)
 CDDSPI_DEVCB_CFG(3, CddTps92520_SpiTx, CddTps92520_SpiRx)
 CDDSPI_DEVCB_CFG(4, CddTps92520_SpiTx, CddTps92520_SpiRx)
 CDDSPI_DEVCB_CFG(5, CddTps92520_SpiTx, CddTps92520_SpiRx)
 END_CDDSPI_DEVCYC
#elif defined (CFG_VARIANT_ECO)
 BEGIN_CDDSPI_DEVCYC(BUCK_0_1)
 CDDSPI_DEVCB_CFG(0, CddTps92520_SpiTx, CddTps92520_SpiRx)
 CDDSPI_DEVCB_CFG(1, CddTps92520_SpiTx, CddTps92520_SpiRx)
 END_CDDSPI_DEVCYC
#endif
 END_CDDSPI_SEQ
#endif
END_CDDSPI_MAP

//==============================================================================
//  Option guards
//==============================================================================
#if ((CDDSPI_SINGLE_OPERATION != STD_ON) && (CDDSPI_CYCLIC_OPERATION != STD_ON))
#error "At least one OPERATION mode must be enabled"
#endif
