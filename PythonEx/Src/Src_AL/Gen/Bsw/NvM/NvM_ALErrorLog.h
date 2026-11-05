#ifndef __NVM_AL_ERROR_LOG_H__
#define __NVM_AL_ERROR_LOG_H__

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
/// \file  NvM_ALErrorLog.h
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a /a
///
/// \author Vu, Tuan
///
//-----------------------------------------------------------------------------



/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <AL_Helper.h>

/*******************************************************************************
* Defintions
*******************************************************************************/
#define CFG_MAX_SUPPORTED_ERROR_ENTRIES (20u)

/*******************************************************************************
* types
*******************************************************************************/
typedef struct
{
  uint16 u16Idx;    // Index
  uint16 u16Cnt;    // Counter
} tAL_Error;

typedef struct
{
  tAL_Error ALErrorTable[CFG_MAX_SUPPORTED_ERROR_ENTRIES]; //
  uint32    ulDummy;          // force the compiler to allocate 
                              // the size for this structure / union a multiple of 4 
} tALErrorLog;

#define NVM_AL_ERROR_LOG_INIT \
{                             \
  {                           \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0},                    \
   {0, 0}                     \
  },                          \
  (uint32)0u                  \
}

extern tALErrorLog   NvM_ErrorBlock;

#endif // __NVM_AL_ERROR_LOG_H__
