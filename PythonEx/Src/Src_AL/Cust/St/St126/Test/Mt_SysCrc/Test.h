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

// Headers of the Module
#include <SysCrc_TargetTypes.h>
#include <SysCrc_Cfg.h>
#include <SysCrc.h>
#include <SysCrc_reg_stubs.h>
#include <Util/UtilUtility.h>
#include <CddDma.h>
#include <RteCommonTypes.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern STATIC_AL boolean SysCrc_RomSegs_boCrcStatus[eSegmentsCount];
extern STATIC_AL uint8   SysCrc_ucRomSegmentIdx;

extern STATIC_AL uint32  SysCrc_RomSegs_ulRegCalcCRC[eSegmentsCount];
extern STATIC_AL boolean SysCrc_ucProbablyElfFile;

extern STATIC_AL CONST_AL tsSysCrc_SegmentConfig SysCrc_RomSegs_RomSegs[eSegmentsCount];

extern STATIC_AL boolean SysCrc_boCRCCalcStarted;
extern STATIC_AL boolean SysCrc_boCRCCalcFinished;
extern STATIC_AL uint32  SysCrc_ulRomAddress;
extern STATIC_AL uint32  SysCrc_ulRomLength;
extern STATIC_AL boolean SysCrc_boCalibCrcStatus;
extern STATIC_AL boolean SysCrc_boCalibCrcCheckInit;

//=============================================================================
// Module function declarations
//=============================================================================

extern boolean           SysCrc_RomSegs_GetCalibCrcStatus(void);
extern STATIC_AL void    SysCrc_RomSegs_CallbackFunction(tSysCrc_pFnct pFct);
extern void              SysCrc_RomSegs_Init(const SysCrc_ConfigType* ConfigPtr);
extern STATIC_AL void    SysCrc_RomSegs_InitCRC(void);
extern void              SysCrc_RomSegs_DoCRC(void);
extern STATIC_AL boolean SysCrc_RomSegs_DoCRCSegment(uint8 ucSegment);
extern void              SysCrc_RomSegs_SegmentCrcCheck(teSysCrc_SegmentId eSegId);
extern STATIC_AL void    SysCrc_RomSegs_CheckCrc(void);
extern STATIC_AL uint32  SysCrc_RomSegs_CatchCrc(void);
extern STATIC_AL boolean SysCrc_RomSegs_Crc32_Vector_AUTOSAR(const uint32 ulCrc_StartAddressVal, const uint32 ulLength, uint32 * pulResult);
extern STATIC_AL void    SysCrc_Dma_Transfer(uint32* pulSourceAdress, uint32* pulTargetAdress, uint16 unLen);
extern void              riSysCrc_Init(void);
extern void              rpSysCrc_Cycle0(void);
extern void              SysCrc_RomSegs_GetCalibState(tsSysCrc_CalibGetStatus *psCalibState);

//=============================================================================
// Module function parameter stubs
//=============================================================================

tSysCrc_pFnct      SysCrc_RomSegs_CallbackFunction_Param1;
SysCrc_ConfigType* SysCrc_RomSegs_Init_Param1;
teSysCrc_SegmentId SysCrc_RomSegs_SegmentCrcCheck_Param1;
uint32             SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1;
uint32             SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2;
uint32*            SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3;
uint8              SysCrc_RomSegs_CalculateCrc32_Param1[20];
uint16             SysCrc_RomSegs_CalculateCrc32_Param2;
uint32             SysCrc_RomSegs_CalculateCrc32_Param3;
uint8              SysCrc_RomSegs_DoCRCSegment_Param1;
uint32*            SysCrc_Dma_Transfer_Param1;
uint32*            SysCrc_Dma_Transfer_Param2;
uint16             SysCrc_Dma_Transfer_Param3;
tsSysCrc_CalibGetStatus SysCrc_RomSegs_GetCalibState_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean SysCrc_RomSegs_GetCalibCrcStatus_RetVal;
boolean SysCrc_RomSegs_GetPavCrcStatus_RetVal;
uint32  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal;
uint32  SysCrc_RomSegs_CalculateCrc32_RetVal;
uint32  SysCrc_RomSegs_CatchCrc_RetVal;
boolean SysCrc_RomSegs_DoCRCSegment_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================


//=============================================================================
// Module global variable stubs
//=============================================================================
uint32  SysCrc_ulRomCalcCRC_Var1;
uint32* pSysCrc_ulRomCalcCRC = &SysCrc_ulRomCalcCRC_Var1;

uint32 SysCrc_RomSegs_SegmentCrcCheck_Var1[518];
uint32 SysCrc_RomSegs_DoCRCSegment_Var1[520];
uint8  PC_MemBlock[64];


#endif // TEST_2023_08_25_H_