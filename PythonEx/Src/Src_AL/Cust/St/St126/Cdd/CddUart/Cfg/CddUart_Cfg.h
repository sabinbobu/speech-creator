//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddUart_Cfg.h
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------

//=============================================================================
//  !!! ATTENTION : DO NOT create include guard for this file ! 
//=============================================================================


//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <CddUart_Mac.h>

#include <CddMlc.h>

//=============================================================================
// Public preprocessor definitions
//=============================================================================

//=============================================================================
// Preprocessor definitions - Microcontroller specific
//=============================================================================

//Interfaces enumeration
#define CDDUART_IFC0                               0     // LDM : LPUART0
#define CDDUART_IFC1                               1     // LDM : CAN1 over LPUART1
#define CDDUART_IFC2                               2     // LDM : LPUART2 ; NIO : CAN2 over UART2
#define CDDUART_IFC3                               3     // only available on cypress NIO : CAN3 over UART3
#define CDDUART_IFC4                               4     // only available on cypress
#define CDDUART_IFC5                               5     // only available on cypress
#define CDDUART_IFC6                               6     // only available on cypress
#define CDDUART_IFC7                               7     // only available on cypress
                                                   
//Device transmission parameters                   
#define CDDUART_BAUDRATE_500K                      500000u
#define CDDUART_BAUDRATE_1M                        1000000u

#define CDDUART_LSB_FIRST                          0u
#define CDDUART_MSB_FIRST                          1u

#define CDDUART_8BIT_DATALEN                       8u

#define CDDUART_PARITY_DISABLE                     0u // No hardware parity generation or checking.
#define CDDUART_PARITY_ENABLE                      1u

#define CDDUART_1_STOPBIT                          1u
#define CDDUART_2_STOPBITS                         2u

#define CDDUART_MAX_CMD_BYTES                      40u


//mechanism used for the transfer message mode
#define CDDUART_TRANSFER_USING_POLLING             0u
#define CDDUART_TRANSFER_USING_INTERRUPT           1u
#define CDDUART_TRANSFER_USING_DMA                 2u

//mechanism used for the transmission in Cyclic Operation mode
#define CDDUART_CYCLIC_POLLING                     0u
#define CDDUART_CYCLIC_INTERRUPT                   1u
#define CDDUART_CYCLIC_DMA                         2u

#define CDDUART_MAX_RX_DATA                        50u//bytes

//==============================================================================
//  User Configuration: Operation options
//==============================================================================


//==============================================================================
//  User Configuration: Mechanism options
//==============================================================================
#define CDDUART_POLLINGMODE                      STD_OFF //not implemented
#define CDDUART_IRQMODE                          STD_OFF //not implemented

//==============================================================================
//  User Configuration: Dynamic configuration
//==============================================================================

//==============================================================================
//  User Configuration: StatusFault CallOut
//==============================================================================
//Enable Cyclic CallOut to provide Project Defined functionality
//If enabled, function void CddSpi_StatusFault(uint8 ucData) must be provided
#define CDDUART_STATUS_FAULT                     STD_OFF 

//==============================================================================
//  User Configuration: Debug
//==============================================================================

//==============================================================================
//  User Configuration: Time Out 
//==============================================================================
#define CDDUART_TIMEOUT_VAL                      0xFFFFUL

//==============================================================================
//  User Configuration:  Assertion
//==============================================================================
#define CDDUART_STATIC_ASSERT(cond, msg)        //static_assert(cond, msg)

//==============================================================================
//  User Configuration: Driver map
//==============================================================================
#ifndef UNIT_TEST
BEGIN_CDDUART_MAP

  //Uart interfaces enabled 
  BEGIN_CDDUART_IFC
    CDDUART_IFC(CDDUART_IFC1, CDDUART_TRANSFER_USING_INTERRUPT, CDDUART_CYCLIC_DMA)
    //CDDUART_IFC(CDDUART_IFC2, CDDUART_TRANSFER_USING_INTERRUPT, CDDUART_CYCLIC_INTERRUPT)     /* NIO */
    //CDDUART_IFC(CDDUART_IFC3, CDDUART_TRANSFER_USING_INTERRUPT, CDDUART_CYCLIC_INTERRUPT)     /* NIO */
  END_CDDUART_IFC
 
  BEGIN_CDDUART_DEV
    // CDDUART_DEV_CFG(  name,        ifc,              datalen,                 brs,               msb,               par,               stopbit,               ddcb         )
       CDDUART_DEV_CFG(MATRIX_GEN2, CDDUART_IFC1,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_1M,   CDDUART_LSB_FIRST, CDDUART_PARITY_DISABLE, CDDUART_1_STOPBIT, CddMlc_Cod_UartGetConfig)
       CDDUART_DEV_CFG(MATRIX_GEN3, CDDUART_IFC1,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_1M,   CDDUART_LSB_FIRST, CDDUART_PARITY_DISABLE, CDDUART_1_STOPBIT, CddMlc_Cod_UartGetConfig)
  END_CDDUART_DEV

  BEGIN_CDDUART_SEQ(CDDUART_IFC1, 0, 0, 3)
    BEGIN_CDDUART_DEVCYC(MATRIX_GEN2)
       CDDUART_DEVCB_CFG( 0, CddTpsGen2_UartTx, CddTpsGen2_UartRx)/*this is called every 2ms from Cycle*/
       CDDUART_DEVCB_CFG( 1, CddTpsGen2_UartTx, CddTpsGen2_UartRx)/*this is called every 2ms from Cycle*/
       CDDUART_DEVCB_CFG( 2, CddTpsGen2_UartTx, CddTpsGen2_UartRx)/*this is called every 2ms from Cycle*/
    END_CDDUART_DEVCYC
    BEGIN_CDDUART_DEVCYC(MATRIX_GEN3)
       CDDUART_DEVCB_CFG( 0, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
       CDDUART_DEVCB_CFG( 1, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
       CDDUART_DEVCB_CFG( 2, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
    /*this is called every 2ms from Cycle*/
     END_CDDUART_DEVCYC
  END_CDDUART_SEQ
END_CDDUART_MAP

#else

BEGIN_CDDUART_MAP

  //Uart interfaces enabled 
  BEGIN_CDDUART_IFC                                                                                                                                                                      // CddUart_asIfcCfg
    CDDUART_IFC(CDDUART_IFC1, CDDUART_TRANSFER_USING_INTERRUPT, CDDUART_CYCLIC_DMA        )
    CDDUART_IFC(CDDUART_IFC3, CDDUART_TRANSFER_USING_POLLING,   CDDUART_CYCLIC_POLLING    )
    CDDUART_IFC(CDDUART_IFC2, CDDUART_TRANSFER_USING_DMA,       CDDUART_CYCLIC_INTERRUPT  )
  END_CDDUART_IFC
 
  BEGIN_CDDUART_DEV                                                                                                                                                                      //tsCddUartDevCfg CddUart_asDeviceCfg[]
    // CDDUART_DEV_CFG(  name,        ifc,              datalen,                 brs,               msb,               par,               stopbit,               ddcb         )
       CDDUART_DEV_CFG(MATRIX_GEN2, CDDUART_IFC1,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_1M,   CDDUART_LSB_FIRST, CDDUART_PARITY_DISABLE,   CDDUART_1_STOPBIT,  CddMlc_Cod_UartGetConfig)
       CDDUART_DEV_CFG(MATRIX_GEN3, CDDUART_IFC1,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_1M,   CDDUART_LSB_FIRST, CDDUART_PARITY_DISABLE,   CDDUART_1_STOPBIT,  CddMlc_Cod_UartGetConfig)
       CDDUART_DEV_CFG(UT1,         CDDUART_IFC2,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_500K, CDDUART_MSB_FIRST, CDDUART_PARITY_ENABLE,    CDDUART_2_STOPBITS, CddMlc_Cod_UartGetConfig)
       CDDUART_DEV_CFG(UT2,         CDDUART_IFC2,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_500K, CDDUART_MSB_FIRST, CDDUART_PARITY_ENABLE,    CDDUART_2_STOPBITS, NULL_PTR                )
       CDDUART_DEV_CFG(UT3,         CDDUART_IFC3,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_500K, CDDUART_MSB_FIRST, CDDUART_PARITY_ENABLE,    CDDUART_2_STOPBITS, CddMlc_Cod_UartGetConfig)
       CDDUART_DEV_CFG(UT4,         CDDUART_IFC3,   CDDUART_8BIT_DATALEN , CDDUART_BAUDRATE_500K, CDDUART_MSB_FIRST, CDDUART_PARITY_ENABLE,    CDDUART_2_STOPBITS, CddMlc_Cod_UartGetConfig)
  END_CDDUART_DEV
                 //(IFC,          CycleCnt      Prescaler     waitcyclmax)
  BEGIN_CDDUART_SEQ(CDDUART_IFC1, 0 ,           0,            3)                                                //tsCddUartSeqHandler  CddUart_asSeqHandler[]
    BEGIN_CDDUART_DEVCYC(MATRIX_GEN2)
       CDDUART_DEVCB_CFG( 0, CddTpsGen2_UartTx, CddTpsGen2_UartRx)
       CDDUART_DEVCB_CFG( 1, CddTpsGen2_UartTx, CddTpsGen2_UartRx)
    END_CDDUART_DEVCYC
    BEGIN_CDDUART_DEVCYC(MATRIX_GEN3)
       CDDUART_DEVCB_CFG( 0, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
       CDDUART_DEVCB_CFG( 1, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
       CDDUART_DEVCB_CFG( 2, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
       CDDUART_DEVCB_CFG( 3, CddTpsGen3_UartTx, CddTpsGen3_UartRx)
     END_CDDUART_DEVCYC
  END_CDDUART_SEQ

  //(IFC,          CycleCnt      Prescaler     waitcyclmax)
  BEGIN_CDDUART_SEQ(CDDUART_IFC2, 0, 0, 3)
    BEGIN_CDDUART_DEVCYC(UT1)
       CDDUART_DEVCB_CFG( 0, CddTps_UartTxDummyIFC2, CddTps_UartRxDummyIFC2)
       CDDUART_DEVCB_CFG( 1, CddTps_UartTxDummyIFC2, CddTps_UartRxDummyIFC2)
       CDDUART_DEVCB_CFG( 2, CddTps_UartTxDummyIFC2, CddTps_UartRxDummyIFC2)
    END_CDDUART_DEVCYC
    BEGIN_CDDUART_DEVCYC(UT2)
       CDDUART_DEVCB_CFG( 0, CddTps_UartTxDummyIFC2, CddTps_UartRxDummyIFC2)
       CDDUART_DEVCB_CFG( 1, CddTps_UartTxDummyIFC2, CddTps_UartRxDummyIFC2)
       CDDUART_DEVCB_CFG( 2, CddTps_UartTxDummyIFC2, CddTps_UartRxDummyIFC2)
     END_CDDUART_DEVCYC
  END_CDDUART_SEQ

  //(IFC,          CycleCnt      Prescaler     waitcyclmax)
  BEGIN_CDDUART_SEQ(CDDUART_IFC3, 0, 0, 3)
    BEGIN_CDDUART_DEVCYC(UT3)
       CDDUART_DEVCB_CFG( 0, CddTps_UartTxDummyIFC3, CddTps_UartRxDummyIFC3)
       CDDUART_DEVCB_CFG( 1, CddTps_UartTxDummyIFC3, CddTps_UartRxDummyIFC3)
       CDDUART_DEVCB_CFG( 2, CddTps_UartTxDummyIFC3, CddTps_UartRxDummyIFC3)
    END_CDDUART_DEVCYC
    BEGIN_CDDUART_DEVCYC(UT4)
       CDDUART_DEVCB_CFG( 0, CddTps_UartTxDummyIFC3, CddTps_UartRxDummyIFC3)
       CDDUART_DEVCB_CFG( 1, CddTps_UartTxDummyIFC3, CddTps_UartRxDummyIFC3)
       CDDUART_DEVCB_CFG( 2, CddTps_UartTxDummyIFC3, CddTps_UartRxDummyIFC3)
    END_CDDUART_DEVCYC
  END_CDDUART_SEQ


END_CDDUART_MAP

#endif
//=============================================================================
// Public type definitions
//=============================================================================

//=============================================================================
// Public function declarations
//=============================================================================


