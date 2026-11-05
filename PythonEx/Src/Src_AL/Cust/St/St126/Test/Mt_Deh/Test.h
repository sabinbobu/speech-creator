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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <Deh.h>

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================
// ECU_CODE for Left LDM
#define DEH_L_ECU_CODE        0xA8u
// ECU_CODE for Right LDM
#define DEH_R_ECU_CODE        0xA9u

#define DEH_DTC_FORMAT_ID     0x00u
#define DEH_5KMH_THRESHOLD    (uint16)500u

#define DEH_TABLE_LOG_LENGTH  20u


//=============================================================================
// Module global variables
//=============================================================================
 // ECU_Code for left/right LDM
extern                 uint8  ucEcuCode;
extern                 LDEH_TS_DECtxt S_DE[DEM_CONFIG_ENTRY_MAX];
extern                 boolean Deh_TableFullStatus;
extern                 tsDeh_EventLog Deh_asDehLogTab[DEH_TABLE_LOG_LENGTH];


//=============================================================================
// Module function declarations
//=============================================================================
// ctaaDeh.c
extern void            riDeh_Init(void);
extern void            rpDeh_Cycle0(void);

// Deh.c
extern void            Deh_Init(void);
extern void            Deh_Cycle0(void);
extern LDEH_TE_ErrVal  APPLI_Send_Defaut(const Tu8P_Int PIu8P_ByteToSend);

// Callback functions for Detection/Confirmation of DEH Appearance/Disappearance
extern void            Deh_AppearanceDetected(uint16 unEventId);
extern void            Deh_AppearanceConfirmed(uint16 unEventId);
extern void            Deh_DisappearanceDetected(uint16 unEventId);
extern void            Deh_DisappearanceConfirmed(uint16 unEventId);


//=============================================================================
// Module function parameter stubs
//=============================================================================
uint16                 Deh_AppearanceDetected_Param1;
uint16                 Deh_AppearanceConfirmed_Param1;
uint16                 Deh_DisappearanceDetected_Param1;
uint16                 Deh_DisappearanceConfirmed_Param1;
uint8                  APPLI_Send_Defaut_Param1[8];
uint8                  *Recover_UCE_ABS_RL_F_1_HDC_Param1;
uint8                  Backup_UCE_ABS_RL_F_1_HDC_Param1;
uint8                  *Recover_C_Mute_Param1;
uint8                  Backup_C_Mute_Param1;
uint8                  *Recover_C_BusOff_Param1;
uint8                  Backup_C_BusOff_Param1;
uint8                  *Recover_C_ABS_BSI_Param1;
uint8                  Backup_C_ABS_BSI_Param1;


//=============================================================================
// Module function return value stubs
//=============================================================================
LDEH_TE_ErrVal        APPLI_Send_Defaut_RetVal;


#endif // TEST_2023_08_25_H_
