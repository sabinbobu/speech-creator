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
/// \file  Test_Adapter.h
///
/// \brief Additional test cases for adapter
///        These test must be customized according to the adapter implementation
///
//-----------------------------------------------------------------------------
#ifndef TEST_ADAPTER_2024_08_06_H
#define TEST_ADAPTER_2024_08_06_H


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#include <string.h>

// Headers of the Module
#include <../../CddMlc/Cfg/CddMlc_Cfg.h>
#include <CddMlc_Cod.h>
#include <CddMlc.h>

//-----------------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private type definitions
//-----------------------------------------------------------------------------
typedef void (*pMlcDevInitFunc)(void);
typedef void (*pMlDevCyclicFunc)(void);

typedef struct
{
  pMlcDevInitFunc init;
  pMlcDevInitFunc cyclic;
}tsCddMlc_DeviceAPIs;

//=============================================================================
// Private variables
//=============================================================================

// Device enum
#define CDDMLC_DECL_DEV_ENUM
#include <CddMlc_Cfg.h>

// Interface Configuration
#define CDDMLC_DECL_IFCCFG
#include <CddMlc_Cfg.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Module global variables
//-----------------------------------------------------------------------------
extern tNvmPara_CodingArea*  CddMlc_pCodingArea;
extern tsCddMlc_CodingData   CddMlc_sCodingData;
extern teCddMlc_DeviceType   CddMlc_eConnectedDevice;
extern boolean               CddMlc_boExecuteOperation;
extern boolean               CddMlc_boActionToExecuteAfterNewConfig;
extern tsCddMlcStatus        CddMlc_sStatus;

//-----------------------------------------------------------------------------
// Module function declarations
//-----------------------------------------------------------------------------
extern teCddMlc_DeviceType  CddMlc_DeviceCfg            (void);
extern void                 CddMlc_DevInit              (teCddMlc_DeviceType eDeviceId);
extern void                 CddMlc_DevCyclic            (teCddMlc_DeviceType eDeviceId);
extern void                 reCddMlc_NewTarget          (void);
extern void                 CddMlc_UpdateRTE            (tsCddMlcStatus sMlcComStatus);
extern void                 CddMlc_Read_CodingPara      (tsCddMlc_CodingParam * sCodingParam);
extern boolean              CddMlc_ParaFct0             (tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea * CONST_AL pData);
extern void                 CddMlc_EvaluateCoding       (void);
extern boolean              CddMlc_CodingDataValidation (void);
extern void                 CddMlc_Data_LmmConfig       (void);
extern void                 CddMlc_CheckReinitMatrix    (void);
extern void                 riCddMlc_Init               (void);
extern void                 rpCddMlc_Cycle0             (void);

//-----------------------------------------------------------------------------
// Adapter unit test suit function declaration
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests_Adapter(void);

//-----------------------------------------------------------------------------
// Module function parameter stubs
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Module function return value stubs
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Module static variables inside functions 
//-----------------------------------------------------------------------------
boolean boCodingPrevStatus;
uint8   ucDev_Bit;

//-----------------------------------------------------------------------------
// Global stubs variables
//-----------------------------------------------------------------------------
static tsPara_LmmConfig_Diagnosis Test_Drv_CodingConfig_Variants[] = CDDMLC_CODINGCONFIG;


#endif // TEST_ADAPTER_2024_08_06_H
