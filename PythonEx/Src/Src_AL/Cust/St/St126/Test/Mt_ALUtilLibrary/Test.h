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
#include <AL_Helper.h>

//=============================================================================
// Module function declarations
//=============================================================================
extern void UtilMemClr(uint8* pucBuffer, uint16_least unLength);
extern void UtilMemSet(uint8* pucBuffer, const uint8 ucData, uint16_least unLength);
extern void UtilMemCopy(uint8* pucDest, const uint8* pucSource, uint16_least unLength);
extern sint16 UtilMemCmp(const uint8* pucDest, const uint8* pucSource, uint16_least unLength);
extern void UtilDebounce(tUtilDebounceControl* const pCtrl, boolean boVal);
extern void UtilDebounceReset(tUtilDebounceControl* const pCtrl, tieDigState eStateInit);
extern void UtilDebounceInit(tUtilDebounceControl* const pCtrl, tieDigState eStateInit, TIMER tOnDelay, TIMER tOffDelay);
extern sint32 Order1Filter32(ORDER1_Filter32* pFilter, uint32 ulBeta, sint32 lValue);
extern sint32 LowPass1Filter32(ORDER1_Filter32* pFilter, uint32 ulBeta, sint32 lValue);
extern STATIC_AL void LowPass1FilterInit32(ORDER1_Filter32* pFilter, sint32 lValue);
extern sint32 Order1TrackingFilter32(ORDER1_Filter32* pFilter, uint32 ulBeta, sint32 lValue, uint32 ulDeviation);
extern sint32 FirFilter32(sint32 alFirFilter[], sint32 lFilterSize, sint32 lValue);
extern uint16 UtilMath_LinearInterpolateU16(const uint16* punX, const uint16* punY, sint32 lLinPairs, uint16 unX);
extern sint32 UtilMath_LinearInterpolate(const tLinearPoint* pPoints, sint32 nLinPairs, sint32 lX);
extern uint32 UtilMath_Log2(uint32 ulArg);
extern uint32 UtilMath_Log2Core(uint32 ulX);
extern void Order1Filter(ORDER1_Filter* const pFilter, const sint16 nValue, const uint16 unBeta);
extern void Order1FilterInit(ORDER1_Filter* const pFilter, const sint16 nValue);
extern sint16 Order1FilterValue(const ORDER1_Filter* const pFilter);
extern uint16 Order1FilterGetCoef(const uint16 unSamplimgTime, const uint16 unFilterTime);
extern void LinEquSolver(tPoint Point1, tPoint Point2, tLinEqu* pLinEquPar);
extern sint16 LinEquCalculator(const sint16 nX, const tLinEqu *const pLinEquPar);
extern void UtilMath_FastIir_u(tFiltIir_u* const pY, const uint16 unInput, const uint8 ucFilt);
extern void UtilMath_FastIir_u_Init(tFiltIir_u* const pY, const uint16 unInputInit);
extern uint16 UtilMath_FastIir_u_GetResult(const tFiltIir_u* pY);
extern uint32 Crc_CalculateCRC32P4(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint32 StartValue32);
extern uint32 Crc_CalculateCRC32(CONST_AL uint8* pucCrc_DataPtr, uint32_least ulCrc_Length, uint32 ulCrc_StartValue32);
extern uint16 Crc_CalculateCRC16(CONST_AL uint8* pucCrc_DataPtr, uint16_least unCrc_Length, uint16 unCrc_StartValue16);
extern uint8 Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8);
extern uint8 Crc_CalculateCRC8H1D(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8);
extern uint32 Crc_CalculateCRC32_4C11DB7(CONST_AL uint8*  pucCrc_DataPtr, uint32  ulCrc_Length, uint32  ulCrc_StartValue32);
extern sint32 ASHRI32(const sint32 x, const uint32_least n);
extern void UtilClearVarBitAtomicU8_(uint32 ulBitPos, volatile uint8* pVariable);

//=============================================================================
// Module function parameter stubs
//=============================================================================
uint8        UtilMemClr_Param1;
uint16_least UtilMemClr_Param2;

uint8        UtilMemSet_Param1[10];
uint8        UtilMemSet_Param2;
uint16_least UtilMemSet_Param3;

uint8        UtilMemCopy_Param1[10];
uint8        UtilMemCopy_Param2[10];
uint16_least UtilMemCopy_Param3;

uint8        UtilMemCmp_Param1;
uint8        UtilMemCmp_Param2;
uint16_least UtilMemCmp_Param3;

tUtilDebounceControl UtilDebounce_Param1;
boolean              UtilDebounce_Param2;

tUtilDebounceControl UtilDebounceReset_Param1;
tieDigState          UtilDebounceReset_Param2;

tUtilDebounceControl UtilDebounceInit_Param1;
tieDigState          UtilDebounceInit_Param2;
TIMER                UtilDebounceInit_Param3;
TIMER                UtilDebounceInit_Param4;

ORDER1_Filter32     Order1Filter32_Param1;
uint32              Order1Filter32_Param2;
sint32              Order1Filter32_Param3;

ORDER1_Filter32     LowPass1Filter32_Param1;
uint32              LowPass1Filter32_Param2;
sint32              LowPass1Filter32_Param3;

ORDER1_Filter32    LowPass1FilterInit32_Param1;
sint32             LowPass1FilterInit32_Param2;

ORDER1_Filter32    Order1TrackingFilter32_Param1;
uint32             Order1TrackingFilter32_Param2;
sint32             Order1TrackingFilter32_Param3;
uint32             Order1TrackingFilter32_Param4;

sint32            FirFilter32_Param1[10];
sint32            FirFilter32_Param2;
sint32            FirFilter32_Param3;

uint16 UtilMath_LinearInterpolateU16_Param1[10];
uint16 UtilMath_LinearInterpolateU16_Param2[10];
sint32 UtilMath_LinearInterpolateU16_Param3;
uint16 UtilMath_LinearInterpolateU16_Param4;

tLinearPoint UtilMath_LinearInterpolate_Param1[10];
sint32       UtilMath_LinearInterpolate_Param2;
sint32       UtilMath_LinearInterpolate_Param3;


uint32 UtilMath_Log2_Param1;

uint32 UtilMath_Log2Core_Param1;

ORDER1_Filter Order1Filter_Param1;
sint16        Order1Filter_Param2;
uint16        Order1Filter_Param3;

ORDER1_Filter Order1FilterInit_Param1;
sint16        Order1FilterInit_Param2;

ORDER1_Filter Order1FilterValue_Param1;

uint16        Order1FilterGetCoef_Param1;
uint16        Order1FilterGetCoef_Param2;

tFiltIir_u    UtilMath_FastIir_u_Param1;
uint16        UtilMath_FastIir_u_Param2;
uint8         UtilMath_FastIir_u_Param3;

tFiltIir_u    UtilMath_FastIir_u_Init_Param1;
uint16        UtilMath_FastIir_u_Init_Param2;

tFiltIir_u    UtilMath_FastIir_u_GetResult_Param1;

tPoint        LinEquSolver_Param1;
tPoint        LinEquSolver_Param2;
tLinEqu       LinEquSolver_Param3;

sint16        LinEquCalculator_Param1;
tLinEqu       LinEquCalculator_Param2;

uint16        ShiftValue_Param1;

uint8         Crc_CalculateCRC32P4_Param1[9];
uint32        Crc_CalculateCRC32P4_Param2;
uint32        Crc_CalculateCRC32P4_Param3;

uint8         Crc_CalculateCRC32_Param1[9];
uint32_least  Crc_CalculateCRC32_Param2;
uint32        Crc_CalculateCRC32_Param3;

uint8         Crc_CalculateCRC16_Param1[9];
uint16_least  Crc_CalculateCRC16_Param2;
uint16        Crc_CalculateCRC16_Param3;

uint8         Crc_CalculateCRC8H2F_Param1[9];
uint32        Crc_CalculateCRC8H2F_Param2;
uint8         Crc_CalculateCRC8H2F_Param3;


uint8         Crc_CalculateCRC8H1D_Param1[9];
uint32        Crc_CalculateCRC8H1D_Param2;
uint8         Crc_CalculateCRC8H1D_Param3;

uint8*        Crc_CalculateCRC32_4C11DB7_Param1;
uint32        Crc_CalculateCRC32_4C11DB7_Param2;
uint32        Crc_CalculateCRC32_4C11DB7_Param3;

uint32        UTILTIME_USEC_Param1;

uint32        UTILTIME_MSEC_Param1;

uint32        UTILTIME_SEC_Param1;

uint32        TimerShortStart_Param1;

uint32        TimerShortTimeout_Param1;

uint32        TimerShortTimeoutOfCustomTick_Param1;
uint32        TimerShortTimeoutOfCustomTick_Param2;

uint32        TimerShortGetTimeSince_Param1;

uint32        TimerStart_Param1;

uint32        TimerTimeout_Param1;

uint32        TimerTimeoutOfCustomTick_Param1;
uint32        TimerTimeoutOfCustomTick_Param2;

uint32        TimerGetTimeSince_Param1;

uint32        TimerGetTimeSinceMs_Param1;

sint32        ASHRI32_Param1;
uint32_least  ASHRI32_Param2;

uint32        UtilClearVarBitAtomicU8__Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
sint16  UtilMemCmp_RetVal;
sint32  Order1Filter32_RetVal;
sint32  LowPass1Filter32_RetVal;
sint32  Order1TrackingFilter32_RetVal;
sint32  FirFilter32_RetVal;
uint16  UtilMath_LinearInterpolateU16_RetVal;
sint32  UtilMath_LinearInterpolate_RetVal;
uint32  UtilMath_Log2_RetVal;
uint32  UtilMath_Log2Core_RetVal;
sint16  Order1FilterValue_RetVal;
uint16  Order1FilterGetCoef_RetVal;
sint16  LinEquCalculator_RetVal;
uint16  ShiftValue_RetVal;
uint16  UtilMath_FastIir_u_GetResult_RetVal;
uint32  Crc_CalculateCRC32P4_RetVal;
uint32  Crc_CalculateCRC32_RetVal;
uint16  Crc_CalculateCRC16_RetVal;
uint8   Crc_CalculateCRC8H2F_RetVal;
uint8   Crc_CalculateCRC8H1D_RetVal;
uint32  Crc_CalculateCRC32_4C11DB7_RetVal;
TIMER   UTILTIME_USEC_RetVal;
TIMER   UTILTIME_MSEC_RetVal;
TIMER   UTILTIME_SEC_RetVal;
STIMER  TimerShortStart_RetVal;
boolean TimerShortTimeout_RetVal;
boolean TimerShortTimeoutOfCustomTick_RetVal;
STIMER  TimerShortGetTimeSince_RetVal;
STIMER  TimerShortGetTick_RetVal;
TIMER   TimerStart_RetVal;
boolean TimerTimeout_RetVal;
boolean TimerTimeoutOfCustomTick_RetVal;
TIMER   TimerGetTimeSince_RetVal;
TIMER   TimerGetTick_RetVal;
TIMER   TimerGetTimeSinceMs_RetVal;
sint32  ASHRI32_RetVal;

#endif // TEST_2023_08_25_H_
