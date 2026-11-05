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
/// \file  CddVnd7140_Cfg.h
///
/// \brief  Configuration of CddVnd7140 module
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_VND7140_CFG_2021_03_01_H_
#define CDD_VND7140_CFG_2021_03_01_H_

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define CDDVND7140_CFG_OUTPUTS_CNT         (2u)  // Number of Switch
#define CDDVND7140_CFG_OUTPUT1             (0u)  // HSS Output 1 index
#define CDDVND7140_CFG_OUTPUT2             (1u)  // HSS Output 2 index

#define CDDVND7140_CFG_HSS_EN_LOW  0u      // HSS disable value
#define CDDVND7140_CFG_HSS_EN_HIGH 0x8000u // HSS enable value

#ifndef CDDVND7140_CFG_ERR_SNA
#define CDDVND7140_CFG_ERR_SNA 0U
#endif /*CDDVND7140_CFG_ERR_SNA*/

#ifndef CDDVND7140_CFG_ERR_NO
#define CDDVND7140_CFG_ERR_NO 2U
#endif /*CDDVND7140_CFG_ERR_NO*/

#ifndef CDDVND7140_CFG_ERR_YES
#define CDDVND7140_CFG_ERR_YES 1U
#endif /*CDDVND7140_CFG_ERR_YES*/

#ifndef CDDVND7140_CFG_HSS_SNA
#define CDDVND7140_CFG_HSS_SNA 0U
#endif /*CDDVND7140_CFG_HSS_SNA*/

#ifndef CDDVND7140_CFG_HSS_NOEFT
#define CDDVND7140_CFG_HSS_NOEFT 1U
#endif /*CDDVND7140_CFG_HSS_NOEFT*/

#ifndef CDDVND7140_CFG_HSS_SUPPORT
#define CDDVND7140_CFG_HSS_SUPPORT 2U
#endif /*CDDVND7140_CFG_HSS_SUPPORT*/

#ifndef CDDVND7140_CFG_HSS_NOSUPPORT
#define CDDVND7140_CFG_HSS_NOSUPPORT 3U
#endif /*CDDVND7140_CFG_HSS_NOSUPPORT*/


#define CDDVND7140_CFG_CH1_SHORT2GND_THRESHOLD                  3610u
#define CDDVND7140_CFG_CH2_SHORT2GND_THRESHOLD                  3610u

#define CDDVND7140_CFG_CH1_SHORT2VBAT_THRESHOLD                 4860u
#define CDDVND7140_CFG_CH2_SHORT2VBAT_THRESHOLD                 4860u

#define CDDVND7140_CFG_CH1_OPENLOAD_THRESHOLD                     68u
#define CDDVND7140_CFG_CH2_OPENLOAD_THRESHOLD                     68u

#define CDDVND7140_CFG_DIAGNOSE_CYCLE_60ms                         6u

#define CDDVND7140_CFG_CURRENT_RSENES                           1300u   // RSense  =1300Ohm
#define CDDVND7140_CFG_CURRENT_FACTOR_HSS1_2                     500u

#endif // CDD_VND7140_CFG_2021_03_01_H_

// EOF
