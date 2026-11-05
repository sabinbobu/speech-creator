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
/// \file  ErrCust.h
///
/// \brief  DTC handling
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __ERRCUST_H__
#define __ERRCUST_H__

//=============================================================================
// Includes
//=============================================================================
#include <Dem.h>
#include <ErrCust_Types.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <../App/Rte/RteCommonTypes.h>
#endif

//=============================================================================
// Definitions
//=============================================================================
// ERRCUST status flags
#define ERRCUST_STATUS_TEST_FAILED                      (uint8)0x01u
#define ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE           (uint8)0x02u
#define ERRCUST_STATUS_PENDING_DTC                      (uint8)0x04u
#define ERRCUST_STATUS_CONFIRMED_DTC                    (uint8)0x08u
#define ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR   (uint8)0x10u
#define ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR          (uint8)0x20u
#define ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE    (uint8)0x40u
#define ERRCUST_STATUS_TEST_PASSED                      (uint8)0x80u

// BSI (JDD) status flags
#define ERRCUST_BSI_TEST_FAILED                         0x01u
#define ERRCUST_BSI_TEST_PASSED                         0x02u
#define ERRCUST_BSI_REPORTED                            0x04u

// Number of bytes from a Dtc code
#define ERRCUST_DTC_CODE_SIZE                     3u

// Max number of DTCs
#define ERRCUST_NUMBER_OF_DTCS                          (uint8)ERRCUST_IxPsErrorMax
// Maximum number of freeze frame data
#define ERRCUST_FREEZE_FRAME_DATA_ENTRIES               10u
// Min age for which is allowed to store snapshot data for the current freeze frame data index
#define ERRCUST_MIN_AGE                                 0u
// Maximum allowed age for the current freeze frame data; it has the same value with maximum number of entries
#define ERRCUST_MAX_AGE                                 ERRCUST_FREEZE_FRAME_DATA_ENTRIES
// Value which indicate that for the current DTC Freeze Frame data were not stored
#define ERRCUST_DTC_AVAILABLE_FOR_FFD                   0xFFu

// Macro for taking the high byte from Dtc code
#define ERRCUST_GET_DTC_HIGH_BYTE(IxPsError) \
    (UTIL_LOBYTE(UTIL_HIWORD(ErrCust_aPsDtcs[IxPsError].ulDtc)))
// Macro for taking the middle byte from Dtc code
#define ERRCUST_GET_DTC_MIDDLE_BYTE(IxPsError) \
    (UTIL_HIBYTE(UTIL_LOWORD(ErrCust_aPsDtcs[IxPsError].ulDtc)))
// Macro for taking the low byte from Dtc code
#define ERRCUST_GET_DTC_LOW_BYTE(IxPsError) \
    (UTIL_LOBYTE(UTIL_LOWORD(ErrCust_aPsDtcs[IxPsError].ulDtc)))


// build the teErrCust_IxPsError type
//lint -e451 Header file 'xxx.h' repeatedly included but does not have a standard include guard
#define ERRCUST_CONFIG_DECL
#include <ErrCust_Cfg.h>
#undef  ERRCUST_CONFIG_DECL
//lint +e451 Header file 'xxx.h' repeatedly included but does not have a standard include guard

//=============================================================================
// Externs
//=============================================================================
extern CONST_AL  tNvmPara_CodingArea* ErrCust_pCodingArea;

//=============================================================================
// Function Prototypes
//=============================================================================
// Initialization of the ErrCust module
void ErrCust_Init(void);
// ErrCust Cyclic function
void ErrCust_Cycle0(void);
// Dtc handling
void ErrCust_ErrHandling(uint16 unAlecId, uint8 ucAlecStatus);
// Trigger  clear memory
boolean ErrCust_ClearMemory(uint8* pucDtcCode);
// Read the status of the given Dtc
uint8 ErrCust_ucGetStatusOfDTC(uint8 ucDtcIndex);
// Fill up the buffer pucBuf with DTCs which match with ucDTCStatusMask
void ErrCust_SetAvailableDtc(uint8* pucBuf, uint8 ucDTCStatusMask);
// Get the actual error count
uint8 ErrCust_ucGetErrorCount(uint8 ucDTCStatusMask);
// Convert internal error to customer error
uint32 ErrCust_ulGetDtcCode(uint8 ucDtcIndex);
// Store RBIN/NTC failure per light function ECU data
void ErrCust_CaptureAftermarketRbinNtcFailureEcuData(tsErrCust_AftermarketRbinNtcFailureData* psOutputData);
// Store RBIN EEPROM LMM Diagnosis ECU data
void ErrCust_CaptureAftermarketRbinEepromLmmEcuData(tsErrCust_AftermarketRbinEepromLmmData* psOutputData);
// Store LED Channel Output Failure ECU data
void ErrCust_CaptureAftermarketLedOutputFailEcuData(tsErrCust_AftermarketLedChnlOutData* psOutputData);
// Stores aftermarket ATTITUDE ECU data
void ErrCust_CaptureAftermarketAttitudeEcuData(tsErrCust_AftermarketAttitudeEcuData* psOutputData);
// Stores aftermarket LVL ECU data
void ErrCust_CaptureAftermarketLvlEcuData(tsErrCust_AftermarketLvlEcuData* psOutputData);
// Stores aftermarket CONTEXT ECU data
void ErrCust_CaptureAftermarketContextEcuData(tsErrCust_AftermarketContextEcuData* psOutputData);
// Get actual Error index based on Alec Id input
uint8 ErrCust_GetActualErrorIndex(uint16 unAlecId);
// Get actual status of a DTC code
uint8 ErrCust_GetStatusOfDtc(uint8 ucDtcIndex);
// Reset a global Dtc Index
void ErrCust_ResetDtcIndex(void);
// Convert sint to uint
uint32 ErrCust_ConvertValueSint2Int(sint32 slInValue, uint8 ucbitLength);
sint32 ErrCust_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength);

#endif  // __ERRCUST_H__

//EOF
