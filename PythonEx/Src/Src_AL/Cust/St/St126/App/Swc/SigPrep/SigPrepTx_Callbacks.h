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
/// \file   SigPrepTx_Callbacks.h
///
/// \brief  
///
/// \descr  Output Frame Tx Callbacks Header file
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_TX_CALLBACKS_H__
#define __SIG_PREP_TX_CALLBACKS_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SigPrep_Types.h>
#include <CddEft.h>
#include <Cfg/Cfg.h>

//-----------------------------------------------------------------------------
// callbacks prototypes
//-----------------------------------------------------------------------------
void SigPrep_TxCallbacks_CyclicFrame_5x7(void);
void SigPrep_TxCallbacks_ToFrame_5x7(void);
void SigPrep_TxCallbacks_CyclicFrame_2B7(void);
void SigPrep_TxCallbacks_ToFrame_2B7(void);
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
void SigPrep_TxCallbacks_CyclicFrame_297(void);
void SigPrep_TxCallbacks_CyclicFrame_4D7(void);
void SigPrep_TxCallbacks_ToFrame_297(void);
void SigPrep_TxCallbacks_ToFrame_4D7(void);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


#endif // __SIG_PREP_TX_CALLBACKS_H__

//=============================================================================
// Defines
//=============================================================================
// Convertion factor from hex to ascii
#define HEX_TO_ASCII_FACTOR                    (0x30u)

// Converts day, month year from hex to dec                
#define ECUTRACECFG_DATE_HEX_TO_DEC(x, y)      ((uint8)(((x) - HEX_TO_ASCII_FACTOR) * 10u) + (uint8)((y) - HEX_TO_ASCII_FACTOR))


//Length of ECU identification zone valid data
#define SIGPREPTX_LOGZONE_LENGTH                       (sizeof(tsSigprepTx_LogZoneInfo))
//ECU identification zone - nr of entries
#define SIGPREPTX_LOGZONE_ENTRIES_NR                   (48u)

//Maximum index of longzone entries
#define SIGPREPTX_LOGZONE_ENTRY_MAX_INDEX         (SIGPREPTX_LOGZONE_ENTRIES_NR - 1u)
//Max uint8 value
#define APPDESC_MAX_UINT8_VALUE                 (255u)
//Empty logzone area
#define APPDESC_EMPTY_ZONE                      (0xFFU)
//Concatenate date like "YYMMDD"
#define APPDESC_CONCATENATE_DATE(x, y, z)       (uint32)(((uint32)(x) * 10000u) + ((uint32)(y) * 100u) + (uint32)(z))


// Get manufacturing day in decimal format
#define ECUTRACECFG_DAY_DEC                    ECUTRACECFG_DATE_HEX_TO_DEC(EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucDay[0], EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucDay[1]);
// Get manufacturing month in decimal format
#define ECUTRACECFG_MONTH_DEC                  ECUTRACECFG_DATE_HEX_TO_DEC(EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucMonth[0], EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucMonth[1]);
// Get manufacturing year in decimal format
#define ECUTRACECFG_YEAR_DEC                   ECUTRACECFG_DATE_HEX_TO_DEC(EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucYear[2], EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucYear[3]);

// ECU_CODE for Left LDM
#define SIGPREPTX_CALLBACKS_L_ECU_CODE              0xA8u
// ECU_CODE for Right LDM                           
#define SIGPREPTX_CALLBACKS_R_ECU_CODE              0xA9u

// Max allowed software types
#define SIGPREPTX_CALLBACKS_MAX_ALLOWED_SW_TYPE     15u


//ECU identification zone info
typedef struct
{
  uint8 aucReserved[4];
  uint8 ucSupplierCode;
  uint8 ucSystemCode;
  uint8 ucEcuManufacturingDay;
  uint8 ucEcuManufacturingMonth;
  uint8 ucEcuManufacturingYear;
  uint8 ucApplicationType;
  uint8 ucSoftwareVersion;
  uint8 aucSoftwareEdition[2];
  uint8 ucDownloadedDay;
  uint8 ucDownloadedMonth;
  uint8 ucDownloadedYear;
  uint8 ucDownloadingSite;
  uint8 aucDownloadingToolSignature[3];
  uint8 ucDownloadingNumber;
  uint8 aucSoftwareReference[3];
}tsSigprepTx_LogZoneInfo;

typedef union
{
  tsSigprepTx_LogZoneInfo sLogZoneInfo;
  uint8              aucInfo[SIGPREPTX_LOGZONE_LENGTH];
}tuSigprepTx_LogZoneInfo;

//ECU identification zone entry structure
typedef struct
{
  tuSigprepTx_LogZoneInfo uData;
  uint8              aucReserved[24 + 208]; // 24 bytes reprog + 208 Padd for mapping 256 bytes page
}tsSigprepTx_LogZoneEntry;

// EOF
