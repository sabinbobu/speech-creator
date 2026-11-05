/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_Com.h
* Description:
* Internal non-blocking communication API for register-level SPI access.
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_COM_2026_07_07_H_
#define CDD_ASM330LHH_COM_2026_07_07_H_

#include <Std_Types.h>
#include <../Api/CddAsm330lhh.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ctadCddAsm330lhh_START_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

/*
*****************************************************************************
* Function: CddAsm330lhh_Com_Init
* Purpose : Store communication configuration for subsequent SPI access.
*****************************************************************************
*/
void CddAsm330lhh_Com_Init(const CddAsm330lhh_ConfigType* CfgPtr);

/*
*****************************************************************************
* Function: CddAsm330lhh_Com_DeInit
* Purpose : Clear communication configuration.
*****************************************************************************
*/
void CddAsm330lhh_Com_DeInit(void);

/*
*****************************************************************************
* Function: CddAsm330lhh_Com_StartReadReg
* Purpose : Start one register read without waiting for completion.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_Com_StartReadReg(uint8 RegAddr);

/*
*****************************************************************************
* Function: CddAsm330lhh_Com_StartWriteReg
* Purpose : Start one register write without waiting for completion.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_Com_StartWriteReg(uint8 RegAddr, uint8 Data);

/*
*****************************************************************************
* Function: CddAsm330lhh_Com_StartReadBurst
* Purpose : Start a contiguous register read without waiting for completion.
*****************************************************************************
*/
Std_ReturnType CddAsm330lhh_Com_StartReadBurst(uint8 StartRegAddr, uint8 Length);

/*
*****************************************************************************
* Function: CddAsm330lhh_Com_GetRxBuffer
* Purpose : Retrieve pointer to SPI receive buffer after async transfer.
*****************************************************************************
*/
const uint8* CddAsm330lhh_Com_GetRxBuffer(void);

#define ctadCddAsm330lhh_STOP_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif /* CDD_ASM330LHH_COM_2026_07_07_H_ */
