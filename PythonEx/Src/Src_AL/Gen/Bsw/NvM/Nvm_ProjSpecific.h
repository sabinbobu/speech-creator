#ifndef __NVM_PROJSPECIFIC_M_H__
#define __NVM_PROJSPECIFIC_M_H__

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
/// \file  NvM_ProjSpecific.h
///
/// \brief Generic structure definition of NvM CustProj, fix 64 bytes
///                                 and of NvM ProjIdentifier
///
/// \descr NvM ProjIdentifier is a general NvM block.
///        NvM CustProj in split into 2 parts:
///        - general part (32 bytes): data definiton can be added during Alx1
///            history, can be used none, partly or fully in different projects
///        - specific part (32 bytes): used completely individually (in
///            different projects)
///
///         Additional information can be found in the design description (Link:
///         <a /a
///
/// \author 
///
//-----------------------------------------------------------------------------

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include <Bsw/Nvm/NvM_ProjSpecificInit.h>


/*******************************************************************************
* Version
*******************************************************************************/


/*******************************************************************************
* Defintions
*******************************************************************************/
  enum ProjectIdentifier
  {
    PrjID_Al51 = 0x01,
    PrjID_Fd04 = 0x02,
    PrjID_Ps14 = 0x03,
    PrjID_Ps15 = 0x04,
    PrjID_Gm11 = 0x05,
    PrjID_Gm16 = 0x06,
    PrjID_Fa39 = 0x07,
    PrjID_Fa47 = 0x08,
    PrjID_Ps31 = 0x09,
    PrjID_Cr02 = 0x0A,
    PrjID_Ts01 = 0x0B,
    PrjID_Ne01 = 0x0C,
    PrjID_Cr03 = 0x0D,
    PrjID_Cr05 = 0x0E,
    PrjID_Cr06 = 0x0F,
    PrjID_Fd05 = 0x10,
    PrjID_Tp50 = 0x11,
    PrjID_Gm19 = 0x12,
    PrjID_Ne05 = 0x13,
    PrjID_Gm21 = 0x14,
    PrjID_Ne02 = 0x15,
    PrjID_An04 = 0x16
  };


#ifndef NVM_CUST_INIT
//NvM CustProj parameter initialisation: default values
#define SW_ID_HI_INIT   0xFF // Version ID initialized with 1..1bin as default
#define SW_ID_LO_INIT   0xFF
#define NVM_CUST_INIT \
            { \
              /* general part */ \
              SW_ID_HI_INIT, SW_ID_LO_INIT, \
              {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, \
              {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, \
              /* project specific part - default */ \
              {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, \
               0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u} \
            }
#endif

#ifndef NVM_CUST_SPECIFIC_STRUCT_64B
#define NVM_CUST_SPECIFIC_STRUCT_64B  uint8 aucCustData_Specific[64]
#endif

/*******************************************************************************
* types
*******************************************************************************/
  typedef struct
  {
    uint16 ucProjId;
    uint16 unProjectCfgNo;
  } tNvMPara_ProjIdentifier;


  typedef struct
  {
    // size is fix: 96 bytes

    /* general part (general definition, prj-specific use case): 32 bytes */
    // byte 0..1
    uint8   ucVersionId_High;               // default init: 0xFF (see above)
    uint8   ucVersionId_Low;                // default init: 0xFF (see above)
    uint16  aunBinningFactorPromille[8];    // default init: 0xFFFF as invalid (see above)
    // byte 18..31 - not yet defined ("Undef")
    uint8   aucCustData_CommonUndef[14];    // default init: 0x00 (see above)
    /* project specific part (prj-specific definitiuon and use case): 64 bytes */
    // byte 32..95
    NVM_CUST_SPECIFIC_STRUCT_64B;           // default init: 0x00 (see above)
  } tNvMPara_CustProj;
// ----------------------------------------------------------------------------
// external vars
// ----------------------------------------------------------------------------


#endif // __NVM_PROJSPECIFIC_M_H__
