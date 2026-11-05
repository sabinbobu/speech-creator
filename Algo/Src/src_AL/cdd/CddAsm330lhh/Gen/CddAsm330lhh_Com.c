/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_Com.c
* Description:
*   Non-blocking SPI frame preparation for ASM330LHH register access.
*****************************************************************************
*/

#include <Std_Types.h>
#include <Spi.h>
#include <../Gen/CddAsm330lhh_Com.h>
#include <../Gen/CddAsm330lhh_Types.h>
#include <../Cfg/CddAsm330lhh_RoutCfg.h>

#define CDDASM330LHH_SPI_SINGLE_FRAME_LEN  (2u)
#define CDDASM330LHH_SPI_MAX_FRAME_LEN     (17u)

#define ctadCddAsm330lhh_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddAsm330lhh_MemMap.h>

static uint8 CddAsm330lhh_Com_TxBuf[CDDASM330LHH_SPI_MAX_FRAME_LEN];
static uint8 CddAsm330lhh_Com_RxBuf[CDDASM330LHH_SPI_MAX_FRAME_LEN];

#define ctadCddAsm330lhh_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddAsm330lhh_MemMap.h>

#define ctadCddAsm330lhh_START_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

static Std_ReturnType CddAsm330lhh_Com_StartTransfer(uint16 Length)
{
  if ((Spi_SetupEB(CDDASM330LHH_SPI_CHANNEL_ID,
                   CddAsm330lhh_Com_TxBuf,
                   CddAsm330lhh_Com_RxBuf,
                   Length) != E_OK) ||
      (Spi_AsyncTransmit(CDDASM330LHH_SPI_SEQUENCE_ID) != E_OK))
  {
    return E_NOT_OK;
  }

  return E_OK;
}

void CddAsm330lhh_Com_Init(const CddAsm330lhh_ConfigType* CfgPtr)
{
  (void)CfgPtr;
}

void CddAsm330lhh_Com_DeInit(void)
{
}

Std_ReturnType CddAsm330lhh_Com_StartReadReg(uint8 RegAddr)
{
  CddAsm330lhh_Com_TxBuf[0] = (uint8)(RegAddr | CDDASM330LHH_SPI_READ_MASK);
  CddAsm330lhh_Com_TxBuf[1] = 0u;
  CddAsm330lhh_Com_RxBuf[0] = 0u;
  CddAsm330lhh_Com_RxBuf[1] = 0u;

  return CddAsm330lhh_Com_StartTransfer(CDDASM330LHH_SPI_SINGLE_FRAME_LEN);
}

Std_ReturnType CddAsm330lhh_Com_StartWriteReg(uint8 RegAddr, uint8 Data)
{
  CddAsm330lhh_Com_TxBuf[0] = (uint8)(RegAddr & (uint8)(~CDDASM330LHH_SPI_READ_MASK));
  CddAsm330lhh_Com_TxBuf[1] = Data;
  CddAsm330lhh_Com_RxBuf[0] = 0u;
  CddAsm330lhh_Com_RxBuf[1] = 0u;

  return CddAsm330lhh_Com_StartTransfer(CDDASM330LHH_SPI_SINGLE_FRAME_LEN);
}

Std_ReturnType CddAsm330lhh_Com_StartReadBurst(uint8 StartRegAddr, uint8 Length)
{
  uint8 Index = 0u;

  if ((Length == 0u) || ((uint16)Length >= CDDASM330LHH_SPI_MAX_FRAME_LEN))
  {
    return E_NOT_OK;
  }

  CddAsm330lhh_Com_TxBuf[0] = (uint8)(StartRegAddr | CDDASM330LHH_SPI_READ_MASK);
  CddAsm330lhh_Com_RxBuf[0] = 0u;

  for (Index = 1u; Index <= Length; Index++)
  {
    CddAsm330lhh_Com_TxBuf[Index] = 0u;
    CddAsm330lhh_Com_RxBuf[Index] = 0u;
  }

  return CddAsm330lhh_Com_StartTransfer((uint16)Length + 1u);
}

const uint8* CddAsm330lhh_Com_GetRxBuffer(void)
{
  return CddAsm330lhh_Com_RxBuf;
}

#define ctadCddAsm330lhh_STOP_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>
