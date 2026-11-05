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
/// \file  _FeeMac.h
///
/// \brief  X- Macros Header file 
///
/// \descr  Macros for building the Fee config tables
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
// open issues
//
// information about CRC siz needed
// first workaround : Add additional 4 bytes to size to reserve space for CRC

// ----------------------------------------------------------------------------
// includes
// ----------------------------------------------------------------------------
#include <Std_Types.h>

// ----------------------------------------------------------------------------
// typedefs and defines, macros 
// ----------------------------------------------------------------------------
#ifdef BEGIN_FEE_MAP
  #undef BEGIN_FEE_MAP
  #undef END_FEE_MAP
  #undef FEE_BLOCK
  // workaround
  #undef FEE_CRC_SIZE
#endif

#define FEE_CRC_SIZE 4

#if defined(_MAC_EEL_DESCRIPTOR)
  #define BEGIN_FEE_MAP()      const r_eel_ds_cfg_t IDLTab_astr[] = { 
  #define END_FEE_MAP()         }; 
  #define FEE_BLOCK( name,type,block_id,immediate,cbfunc)  { (uint16)(block_id),sizeof(type) + FEE_CRC_SIZE },

#elif defined(_MAC_ENUM)
  #define BEGIN_FEE_MAP()  typedef enum { 
  #define END_FEE_MAP()      FeeBlockCount } tFeeBlockIndex;
  #define FEE_BLOCK( name,type,block_id,immediate,cbfunc) FeeBlock##name##Id,   


#elif defined(_MAC_EXTERN)
  #define BEGIN_FEE_MAP()                              
#ifndef UNIT_TEST
              extern tFeeBlockDescriptor  FeeBlockTable[FeeBlockCount];
#else
              tFeeBlockDescriptor  FeeBlockTable[FeeBlockCount];
#endif
  #define END_FEE_MAP()
#ifndef UNIT_TEST
  #define FEE_BLOCK( name,type,block_id,immediate,cbfunc)  extern  /*__attribute__((section(".bss.FlexRAM"), used))*/ uint8 FeeBlock##name[sizeof(type) + FEE_CRC_SIZE];
#else
  #define FEE_BLOCK( name,type,block_id,immediate,cbfunc)   /*__attribute__((section(".bss.FlexRAM"), used))*/ uint8 FeeBlock##name[sizeof(type) + FEE_CRC_SIZE];
#endif

#elif defined(_MAC_MEMIF_BLOCK_DECLARATION)
  #define BEGIN_FEE_MAP()
  #define END_FEE_MAP()   
  #define FEE_BLOCK( name,type,block_id,immediate,cbfunc) __attribute__((section(".bss.FlexRAM"), used)) uint8 FeeBlock##name[sizeof(type) + FEE_CRC_SIZE ];


#elif defined(_MAC_FEE_BLOCKS)
  #define BEGIN_FEE_MAP()  tFeeBlockDescriptor FeeBlockTable[FeeBlockCount] = { 
  #define END_FEE_MAP()  };   
  #define FEE_BLOCK( name,type,block_id,immediate,cbfunc) {block_id,sizeof(type) + FEE_CRC_SIZE,immediate},

#else
  #error Definition error, reason for including this file is not defined, must be an error.
#endif

#ifndef BEGIN_FEE_MAP
  #error FEE Map not definded !!
#endif


