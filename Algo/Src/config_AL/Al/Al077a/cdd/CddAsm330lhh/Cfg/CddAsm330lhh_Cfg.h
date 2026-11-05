/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_Cfg.h
* Description:
*   AUTOSAR-oriented module constants, service IDs and DET error IDs.
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_CFG_2026_07_07_H_
#define CDD_ASM330LHH_CFG_2026_07_07_H_

#include <Std_Types.h>

/*
*****************************************************************************
* Basic module identity and compile-time safety switches
*****************************************************************************
*/
#define CDDASM330LHH_MODULE_ID              (0xB2u)
#define CDDASM330LHH_INSTANCE_ID            (0u)
#define CDDASM330LHH_VENDOR_ID              (0u)
#define CDDASM330LHH_EXPECTED_WHO_AM_I      (0x6Bu)
#define CDDASM330LHH_DEV_ERROR_DETECT       (STD_ON)

/*
*****************************************************************************
* Service IDs
*****************************************************************************
*/
#define CDDASM330LHH_SID_INIT               (0x00u)
#define CDDASM330LHH_SID_DEINIT             (0x01u)
#define CDDASM330LHH_SID_MAINFUNCTION       (0x02u)
#define CDDASM330LHH_SID_GETDEVICEID        (0x03u)
#define CDDASM330LHH_SID_SETPOWERMODE       (0x04u)
#define CDDASM330LHH_SID_CONFIGACCEL        (0x05u)
#define CDDASM330LHH_SID_CONFIGGYRO         (0x06u)
#define CDDASM330LHH_SID_READRAWDATA        (0x07u)
#define CDDASM330LHH_SID_READSCALEDDATA     (0x08u)
#define CDDASM330LHH_SID_SELFTEST           (0x09u)

/*
*****************************************************************************
* Development error IDs
*****************************************************************************
*/
#define CDDASM330LHH_E_UNINIT               (0x10u)
#define CDDASM330LHH_E_PARAM_POINTER        (0x11u)
#define CDDASM330LHH_E_PARAM_CONFIG         (0x12u)
#define CDDASM330LHH_E_COMM                 (0x13u)
#define CDDASM330LHH_E_HW                   (0x14u)

#endif /* CDD_ASM330LHH_CFG_2026_07_07_H_ */
