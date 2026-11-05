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
/// \file  CddBVnd7140_Router.h
///
/// \brief  Configuration of Cdd Switch router
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_VND7140_ROUTER_2021_03_01_H_
#define CDD_VND7140_ROUTER_2021_03_01_H_

// standard includes
#include <Std_Types.h>

// module API (include path)
#ifndef UNIT_TEST
#include <CddEft.h>
#endif // !UNIT_TEST

#include <IoHwAbUser.h>

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Configuration
//=============================================================================

#ifndef UNIT_TEST
#define CDDVND7140_ECUVARCFG_aHSS_Type(Ch)  EFT_ECUVARCFG_Vnd7140[Ch].ucType
#endif

#define DrvVnd7140SetTgt_FuncRouteList           \
{                                  \
/*  IoHwAbUSerFunc   */ \
  { IoHwAbUser_SetHss_En1  },   /*  0 Hss CH1*/ \
  { IoHwAbUser_SetHss_En2  },   /*  1 Hss CH2*/ \
}

#define DrvVnd7140GetDiagVal_FuncRouteList           \
{                                  \
/*  IoHwAbUSerFunc   */ \
  { IoHwAbUser_GetHss0Sense  },   /*  0 Hss CH1*/ \
  { IoHwAbUser_GetHss1Sense  },   /*  1 Hss CH2*/ \
}

#define DrvVnd7140EnableHssSense  IoHwAbUser_SetHss_Sen   // Set HSS SEN
#define DrvVnd7140SetHssERROR     IoHwAbUser_SetHss_Error // Set HSS ERROR
#define DrvVnd7140SetEn1          IoHwAbUser_SetHss_En1   // Set HSS EN 1
#define DrvVnd7140SetEn2          IoHwAbUser_SetHss_En2   // Set HSS EN 2

//=============================================================================
// Prototypes
//=============================================================================

#endif // CDD_VND7140_ROUTER_2021_08_26_H_

// EOF
