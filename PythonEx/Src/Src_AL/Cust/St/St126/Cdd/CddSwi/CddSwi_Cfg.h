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
/// \file  CddSwi_Cfg.h
///
/// \brief  Configuration of CddSwi module
///
/// \author CRETU Vladut (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_SWI_CFG_2021_03_01_H_
#define CDD_SWI_CFG_2021_03_01_H_

#include <Std_Types.h>
//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define CDDSWI_CFG_SWI_CNT             (4u)  // Number of Switch
#elif defined(SAMPLE_ECO)
#define CDDSWI_CFG_SWI_CNT             (1u)  // Number of Switch
#endif 
#define CDDSWI_CFG_VND7140_CNT         (1u)  // Number of Switch
#define CDDSWI_CFG_VN7140_CNT          (1u)  // Number of Switch
#define CDDSWI_CFG_TLE9471_CNT         (1u)  // Number of Switch

#define CDDSWI_CFG_HSS_OUTPUT1     (0u)
#define CDDSWI_CFG_HSS_OUTPUT2     (1u)
#define CDDSWI_CFG_HSS_OUTPUT3     (2u)

#define CDDSWI_CFG_MAX_TGT_VAL     (0x8000u)
#define CDDSWI_CFG_MIN_TGT_VAL     (0u)

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define CDDSWI_CFG_ROUTE_LIST           \
    {                                  \
    /*  eDrvTyp        DrvIdx, ucOutIdx          */ \
      { eDrvVnd7140,    0u,     0u   },   /*  0 Hss CH1*/ \
      { eDrvVnd7140,    0u,     1u   },   /*  1 Hss CH2*/ \
      { eDrvVn7140,     0u,     2u   },   /*  2 Hss CH3*/ \
      { eDrvTle94x1,    0u,     4u   },   /*  3 Sbc GPIO*/ \
    }
#elif defined(SAMPLE_ECO)
#define CDDSWI_CFG_ROUTE_LIST           \
    {                                  \
    /*  eDrvTyp        DrvIdx, ucOutIdx          */ \
      { eDrvVn7140,     0u,     0u   },   /*  0 Hss CH1*/  \
    }
#endif 

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define CDDSWI_CFG_OUTPUTS_CNT             (4u)  // Number of Switch outputs
#elif defined(SAMPLE_ECO)
#define CDDSWI_CFG_OUTPUTS_CNT             (1u)  // Number of Switch outputs
#endif

#endif // CDD_SWI_CFG_2021_03_01_H_
