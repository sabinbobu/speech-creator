/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_Cb.h
* Description:
*   AUTOSAR SPI module callback integration for CDD.
*   The SPI module invokes this sequence-end notification when an
*   asynchronous sensor transfer completes.
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_CB_2026_07_07_H_
#define CDD_ASM330LHH_CB_2026_07_07_H_

#include <Std_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ctadCddAsm330lhh_START_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

/*
*****************************************************************************
* Function: CddAsm330lhh_SequenceEndNotification
* Purpose : Latch completion of the configured ASM330LHH SPI sequence.
*           Called directly by the SPI MCAL sequence-end notification.
*****************************************************************************
*/
void CddAsm330lhh_SequenceEndNotification(void);

#define ctadCddAsm330lhh_STOP_SEC_CODE
#include <../Cfg/CddAsm330lhh_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif /* CDD_ASM330LHH_CB_2026_07_07_H_ */
