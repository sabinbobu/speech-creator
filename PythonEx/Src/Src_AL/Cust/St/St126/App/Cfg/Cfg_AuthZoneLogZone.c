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
/// \file  Cfg.h
///
/// \brief  
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

#ifndef CFG_2021_05_15_H_
#define CFG_2021_05_15_H_

#include <Std_Types.h>
#include <Cfg/CfgId.h>
#include <UtilUtility.h>
#include <Diag_Callbacks.h>
#include <SigPrepTx_Callbacks.h>


/* -------------------------- START of customer defined values -------------------------- */

#define SUPPLIER_IDENT_MANUFACT_DATE_0	(uint8)0x01
#define SUPPLIER_IDENT_MANUFACT_DATE_1	(uint8)0x01
#define SUPPLIER_IDENT_MANUFACT_DATE_2	(uint8)0x01

#define SUPPLIER_IDENT_SITE_CODE_0		  (uint8)0xFE

#define SUPPLIER_IDENT_SIGNATURE_CODE_0	(uint8)0x00
#define SUPPLIER_IDENT_SIGNATURE_CODE_1	(uint8)0x00
#define SUPPLIER_IDENT_SIGNATURE_CODE_2	(uint8)0x00

#define SUPPLIER_IDENT_NUMBER_CODE_0	  (uint8)0xFE
#define SUPPLIER_IDENT_MARKING_0		    (uint8)0x5C

#ifdef SAMPLE_ECO
#define SUPPLIER_IDENT_CRC_0			      (uint8)0x01
#define SUPPLIER_IDENT_CRC_1			      (uint8)0xB8
#else
#define SUPPLIER_IDENT_CRC_0            (uint8)0x51
#define SUPPLIER_IDENT_CRC_1            (uint8)0x8A
#endif 

#define ZI_TOTAL_SIZE_IN_BYTES          (uint8)48


/***********************************************/
/* Reading of the authentication parameters    */
/* This values must be changed by the customer */
/***********************************************/
#define AUTHENTICATION_DID_F080_SIZE        (uint8)22

/* Supplier Code */
#define SUPPLIER_CODE_0							        (uint8)0x00
#define SUPPLIER_CODE_1							        CFG_ULP_CAL_SUPPLIER

#define NUMBER_OF_ASSOCIATED_PARAMETERS_0		(uint8)0x00

//PRQA S 3408 1 // C_BOOT_ZI_Area' has external linkage and is being defined without any previous declaration.
tsDiag_LogZoneEntry C_BOOT_ZI_Area[DIAG_LOGZONE_ENTRIES_NR] __attribute__((section(".LOG_ZONE"), used)) =
{ //PRQA S 693 2 // special memory mapping mechanism
  /* Initialization of the first ZI record */
  /* 00 */		(uint8)0xFF, /* Reserved */       
  /* 01 */		(uint8)0xFF, /* Reserved */
  /* 02 */		(uint8)0x00, /* Reserved */
  /* 03 */		(uint8)0x00, /* Reserved */
  /* 04 */		(uint8)CFG_ULP_CAL_SUPPLIER, /* Supplier */
  /* 05 */		(uint8)CFG_ULP_CAL_SYSTEM, /* System */
  /* 06 */		(uint8)SUPPLIER_IDENT_MANUFACT_DATE_0, /* Manufacturing date0 */
  /* 07 */		(uint8)SUPPLIER_IDENT_MANUFACT_DATE_1, /*Manufacturing date1*/
  /* 08 */		(uint8)SUPPLIER_IDENT_MANUFACT_DATE_2, /*Manufacturing date2 */
  /* 09 */		(uint8)CFG_ULP_CAL_APPLICATION, /* Application */
  /* 10 */		(uint8)CFG_ULP_CAL_SOFTWARE_VERSION, /* Version */
  /* 11 */		HIBYTE(CFG_ULP_CAL_SOFTWARE_EDITION), /* Edition0 */
  /* 12 */		LOBYTE(CFG_ULP_CAL_SOFTWARE_EDITION), /* Edition1 */
  /* 13 */		(uint8)JENKINS_BUILD_DAY, /* Programming date0 */
  /* 14 */		(uint8)JENKINS_BUILD_MONTH, /* Programming date1 */
  /* 15 */		(uint8)JENKINS_BUILD_YEAR, /* Programming date2 */
  /* 16 */		(uint8)SUPPLIER_IDENT_SITE_CODE_0, /* Site */
  /* 17 */		(uint8)SUPPLIER_IDENT_SIGNATURE_CODE_0, /* Signature0 */
  /* 18 */		(uint8)SUPPLIER_IDENT_SIGNATURE_CODE_1, /* Signature1 */
  /* 19 */		(uint8)SUPPLIER_IDENT_SIGNATURE_CODE_2, /* Signature2 */
  /* 20 */		(uint8)SUPPLIER_IDENT_NUMBER_CODE_0, /* Number */
  /* 21 */		(uint8)CFG_ULP_CAL_FILE_NUMBER_1, /* ref: Software0 */
  /* 22 */		(uint8)CFG_ULP_CAL_FILE_NUMBER_2, /* ref: Software1 */
  /* 23 */		(uint8)CFG_ULP_CAL_FILE_NUMBER_3, /* ref: Software2 */
  /* 24 */		(uint8)0xFF, /* reserved 21 bytes : 0 */
  /* 25 */		(uint8)0xFF,
  /* 26 */		(uint8)0xFF,
  /* 27 */		(uint8)0xFF,
  /* 28 */		(uint8)0xFF,
  /* 29 */		(uint8)0xFF,
  /* 30 */		(uint8)0xFF,
  /* 31 */		(uint8)0xFF,
  /* 32 */		(uint8)0xFF,
  /* 33 */		(uint8)0xFF,
  /* 34 */		(uint8)0xFF,
  /* 35 */		(uint8)0xFF,
  /* 36 */		(uint8)0xFF,
  /* 37 */		(uint8)0xFF,
  /* 38 */		(uint8)0xFF,
  /* 39 */		(uint8)0xFF,
  /* 40 */		(uint8)0xFF,
  /* 41 */		(uint8)0xFF,
  /* 42 */		(uint8)0xFF,
  /* 43 */		(uint8)0xFF,
  /* 44 */		(uint8)0xFF, /* reserved 21 bytes : 20 */
  /* 45 */		(uint8)SUPPLIER_IDENT_MARKING_0, /* Marking of the recording */
  /* 46 */		(uint8)SUPPLIER_IDENT_CRC_0, /* CRC HISTO0 */
  /* 47 */		(uint8)SUPPLIER_IDENT_CRC_1, /* CRC HISTO1 */
}; // PRQA S 686 1 // only first 48 bytes are of interes

/* BootLoader authentication zone */
//PRQA S 3408 1 // AppDesc_AuthZone' has external linkage and is being defined without any previous declaration.
volatile const tuDiag_AuthZoneInfo AppDesc_AuthZone __attribute__((section(".AuthZone"),used)) = 
{
 .sAuthZoneInfo.aucFunctPlanNb            = CFG_FUNCTPLANNB,
 .sAuthZoneInfo.aucPsaSupplierCode        = {SUPPLIER_CODE_0, SUPPLIER_CODE_1},
 .sAuthZoneInfo.aucFunctProdNb            = CFG_FUNCTPRODNB,
 .sAuthZoneInfo.ucSwEvolutionIndex_MSB    = CFG_SOFT_VERSION,
 .sAuthZoneInfo.ucSwEvolutionIndex_LSB    = CFG_SOFT_EDITION,
 .sAuthZoneInfo.aucReserved               = {0xFF, 0xFF},
 .sAuthZoneInfo.ucDiagFrameEvolutionIndex = CFG_SOFT_EVOLUTION_INDEX,
 .sAuthZoneInfo.ucFaultsParamNr           = NUMBER_OF_ASSOCIATED_PARAMETERS_0,
 .sAuthZoneInfo.aucReserved2              = CFG_APPLI_TYPE
};
#endif // CFG_2021_05_15_H_
