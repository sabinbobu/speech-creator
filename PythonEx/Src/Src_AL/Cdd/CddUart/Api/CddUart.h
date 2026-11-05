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
/// \file  CddUart.h
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_UART_2023_09_01_H
#define CDD_UART_2023_09_01_H

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>

//=============================================================================
// Public preprocessor definitions
//=============================================================================

#define CDDUART_DEVICE(dev)  (CddUart_eDev_##dev)

//CddSpi States
#define CDDUART_STATE_RESET                             0x00U
#define CDDUART_STATE_INITIALIZED                       0x01U
#define CDDUART_STATE_CYCLIC_OPERATION                  0x02U
#define CDDUART_STATE_SINGLE_OPERATION                  0x03U

//CddUart Status Fault
#define CDDUART_STATUS_FAULT_SA_MSK                     0x80U  //Signal Available
#define CDDUART_STATUS_FAULT_SA_POS                     7U
#define CDDUART_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK   0x40U  //Dynamic Configuration Error
#define CDDUART_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_POS   6U

//=============================================================================
// Public type definitions
//=============================================================================

//Device enum
#define CDDUART_MAC_DECL_DEV_ENUM
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_DEV_ENUM

//=============================================================================
// Public function declarations
//=============================================================================

  //Module APIS
void    CddUart_Init(void);
void    CddUart_DeInit(void);
void    CddUart_Cycle(void);
void    CddUart_SendReceived_Irq0(void);

//RTE-Runnables
void    riCddUartInit(void);
void    rpCddUart_Cycle(void);

#endif // CDD_UART_2023_09_01_H
