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
/// \file  CddUart_Types.h
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_UART_TYPES_2023_09_01_H
#define CDD_UART_TYPES_2023_09_01_H

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

//=============================================================================
// Public preprocessor definitions
//=============================================================================

// uart clock configuration
#define CDDUART_S32K_14X_UART_REF_FREQ                                  16000000u   // 16Mhz
#define CDDUART_S32K_14X_PERI_SCB_DIVIDER_NUMBER                        22u

#define CDDUART_S32K_14X_DIVIDER_VALUE                                  (CDDUART_S32K_14X_PERI_CLK_UART_FREQ/CDDUART_S32K_14X_UART_REF_FREQ)
#define CDDUART_S32K_14X_DIVIDER_VALUE_REGISTER_VAL(divider)            ((divider) - 1u)

#define CDDUART_S32K_14X_PERI_DIV_CMD_TYPE_SEL_8DIV_INTEGER             0u
#define CDDUART_S32K_14X_PERI_DIV_CMD_PA_TYPE_SEL_DEFAULT_VAL           3u
#define CDDUART_S32K_14X_PERI_DIV_CMD_PA_DIV_SEL_DEFAULT_VAL            0xFFu
#define CDDUART_S32K_14X_PERI_DIV_CMD_CLK_DIVIDER_ENABLE_CMD            1u

#define CDDUART_S32K_14X_PERI_CLK_IDX(n)                                (30u + (n))

#define CDDUART_S32K_14X_CTRL_DEFAULT_VAL                               0u
#define CDDUART_S32K_14X_CTRL_8_BIT_FIFO_DATA                           0u


/* ---------------------------------------------------------
    S32K Baud rate = baud clock / ((OSR+1) × SBR)

    (OSR+1) × SBR = Baud Clock / Baud Rate
    Take SBR = 1 => OSR  = (Baud Clock / Baud Rate) - 1 
   ---------------------------------------------------------  */
#define CDDUART_S32K_14X_BAUD_RATE_OVS_REGISTER_VAL(baudrate)           (CDDUART_S32K_14X_UART_REF_FREQ/(baudrate)) 
#define CDDUART_S32K_14X_OVERSAMPLING_FACTOR(baudrate)                  (CDDUART_S32K_14X_BAUD_RATE_OVS_REGISTER_VAL(baudrate) - 1u)
#define CDDUART_S32K_14X_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(baudrate)    1u        


/*  */
#define CDDUART_S32K_14X_STOPBIT_SELECT(val)                            ((val) - 1U)
#define CDDUART_S32K_14X_PARITY_SELECT(val)                             (val)
#define CDDUART_S32K_14X_BIT_ORDER_SELECT(val)                          (val)

/* ---------------------------------------------------------
    DRIVER SETTINGS based on Microcontroller type
   ---------------------------------------------------------  */
#define CDDUART_PERI_CLOCK_FREQ                                         CDDUART_S32K_14X_UART_REF_FREQ
#define CDDUART_BAUDRATE_OVS_REGISTER_VAL(baudrate)                     CDDUART_S32K_14X_OVERSAMPLING_FACTOR(baudrate)
#define CDDUART_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(baudrate)             CDDUART_S32K_14X_BAUDRATE_SBR_DIVISOR_REGISTER_VAL(baudrate)
#define CDDUART_STOPBIT_SELECT(val)                                     CDDUART_S32K_14X_STOPBIT_SELECT(val)
#define CDDUART_PARITY_SELECT(val)                                      CDDUART_S32K_14X_PARITY_SELECT(val)
#define CDDUART_BIT_ORDER_SELECT(val)                                   CDDUART_S32K_14X_BIT_ORDER_SELECT(val)


#define CDDUART_DISABLE_INTERRUPT                                       0u
#define CDDUART_ENABLE_INTERRUPT                                        1u

#define CDDUART_DISABLE_VAL_SET                                         0u
#define CDDUART_ENABLE_VAL_SET                                          1u





//=============================================================================
// Public type definitions
//=============================================================================

 //create interface enum
#define CDDUART_MAC_DECL_IFC_ENUM
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef CDDUART_MAC_DECL_IFC_ENUM


typedef struct tsCddUartDevCfg
{
  uint8  ucUartIfc;      // Uart interface that the device is attached to
  uint8  ucDataLen;      // data length (normally 8 bits)
  uint32 ulBaudRate;     // baud rate
  uint8  ucDataDir;      // Data direction : MSB or LSB
  uint8  ucParity;       // parity enabled/disabled
  uint8  ucStopBits;     // number of stop bits
}tsCddUartDevCfg;

typedef struct tsCddUartTransferData
{
  uint32 ulTCR_data;
  uint32 ulTDR_data;
} tsCddUartTransferData;

typedef struct
{
  uint8*        pucTxData;
  uint8         ucTxDataLength;
  uint8*        pucRxData;
  uint8         ucRxDataLength;
  boolean       boToBeProcessed;
}tsCddUart_MessageEntryType;


#endif // CDD_UART_TYPES_2023_09_01_H
