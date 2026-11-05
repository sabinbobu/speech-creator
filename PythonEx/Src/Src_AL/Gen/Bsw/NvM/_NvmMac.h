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
/// \file  _NvmMac.h
///
/// \brief  X- Macros Header file 
///
/// \descr  Macros for building the NvM config tables
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// includes
// ----------------------------------------------------------------------------

#include <Std_Types.h>

// ----------------------------------------------------------------------------
// typedefs and defines, macros 
// ----------------------------------------------------------------------------
#ifdef BEGIN_NVM_MAP
  #undef BEGIN_NVM_MAP
  #undef END_NVM_MAP
  #undef NVM_BLOCK

#endif

#if defined(_MAC_EEL_DESCRIPTOR)
//  #define BEGIN_NVM_MAP()      const r_eel_ds_cfg_t IDLTab_astr[] = { 
//  #define END_NVM_MAP()         }; 
//  #define NVM_BLOCK( name,type,block_id, init_rom,prio,flags,cbfunc)  { (uint16)(block_id),sizeof(type) + NVM_CRC_SIZE},
    #define BEGIN_NVM_MAP()    
    #define END_NVM_MAP()
    #define NVM_BLOCK( name,type,block_id, init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblockid)

// creates an enum with the Ids to identify the NvM Blocks
// for example, if there where two blocks A and B, the the enum would look like
// typedef enum {
//                 NvmBlockAId,
//                 NvmBlockBId,
//                 NvmBlockCount
//              }
// NvmBlockCount is obtained automatically
#elif defined(_MAC_ENUM)
  #define BEGIN_NVM_MAP()  typedef enum { 
  #define END_NVM_MAP()      NvMBlockCount } tNvmBlockIndex;
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblockid) NvmBlock##name##Id,   

// creates the external definitions for the used variables
#elif defined(_MAC_EXTERN)
// create the MemIfBlockTable
  #define BEGIN_NVM_MAP()
#ifndef UNIT_TEST
                                                       extern uint8 *  MemIfBlockTable[NvMBlockCount];         \
                                                       extern tNvMBlockDescriptor NvMBlockTable[NvMBlockCount];
  #else
                                                              uint8 *  MemIfBlockTable[NvMBlockCount];         \
                                                              tNvMBlockDescriptor NvMBlockTable[NvMBlockCount];
  #endif
  #define END_NVM_MAP()                             
#ifndef UNIT_TEST
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock)  extern type NvmBlock##name;
#else
#define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock)    type NvmBlock##name;
#endif
// creates the global variables to store the NvM Blocks
// for example, if there where two blocks A and B with typeA and TypeB , the expanded code would look like this
//  typeA NvmBlockA, RAM mirror for block A
//  typeB NvmBlockB, RAM mirror for block B
//  
//  
//              }
#elif defined(_MAC_DECLARATION)
  #define BEGIN_NVM_MAP()
  #define END_NVM_MAP()   
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock) type NvmBlock##name;

//  Creates a union, which is capable to store any NvM block
//  this union is used to calculate the maximum size of a NvM Block including CrC
// the data type should never be used
// for example, if there where two blocks A and B with typeA and TypeB , the expanded code would look like this
// typedef union {
//                  uint8 NvmBlockA[sizeof(typeA) + NVM_CRC_SIZE];
//                  uint8 NvmBlockA[sizeof(typeB) + NVM_CRC_SIZE];
//               } memif_io_buffer_t;
#elif defined (_MAC_MEMIF_BUFFER)
  #define BEGIN_NVM_MAP() typedef union { 
  #define END_NVM_MAP()   } memif_io_buffer_t;
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock) uint8 NvmBlock##name[sizeof(type) + NVM_CRC_SIZE];

#elif defined(_MAC_MEMIF_BLOCK_DECLARATION)
  #define BEGIN_NVM_MAP()
  #define END_NVM_MAP()   
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock) uint8 MemIfBlock##name[sizeof(type) + NVM_CRC_SIZE];


#elif defined(_MAC_NVM_BLOCKS)
  #define BEGIN_NVM_MAP()  tNvMBlockDescriptor NvMBlockTable[NvMBlockCount] = { 
  #define END_NVM_MAP()  };   
#ifdef NVM_API_V2
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock) {NVM_BLOCK_STATUS_INIT,       \
                                                                                             (uint8 *) &NvmBlock##name,   \
                                                                                             memif_device,                \
                                                                                             memifblock##Id,              \
                                                                                             sizeof(type) ,               \
                                                                                             flags,                       \
                                                                                             init_rom,                    \
                                                                                             init_callback,               \
                                                                                             cbfunc},
#else
  #define NVM_BLOCK( name,type,block_id,init_rom,init_callback,prio,flags,cbfunc,memif_device,memifblock) {NVM_BLOCK_STATUS_INIT,       \
                                                                                             (uint8 *) &NvmBlock##name,   \
                                                                                             memif_device,                \
                                                                                             memifblock##Id,              \
                                                                                             sizeof(type) ,               \
                                                                                             flags,                       \
                                                                                             init_rom,                    \
                                                                                             init_callback},
#endif
#else
  #error Definition error, reason for including this file is not defined, must be an error.
#endif

#ifndef BEGIN_NVM_MAP
  #error NVM Map not definded !!
#endif


