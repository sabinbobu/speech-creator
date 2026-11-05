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
/// \file  CddVn7140_Cfg.h
///
/// \brief  Configuration of CddVn7140 module
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_VN140_CFG_2021_03_01_H_
#define CDD_VN140_CFG_2021_03_01_H_

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define CDDVN7140_CFG_OUTPUTS_CNT         (1u)  // Number of Switch
#define CDDVN7140_CFG_OUTPUT1             (0u)  // HSS Output 1 index

#define CDDVN7140_CFG_HSS_EN_LOW  0u      // HSS disable value
#define CDDVN7140_CFG_HSS_EN_HIGH 0x8000u // HSS enable value

#ifndef CDDVN7140_CFG_ERR_SNA
#define CDDVN7140_CFG_ERR_SNA 0U
#endif /*CDDVN7140_CFG_ERR_SNA*/

#ifndef CDDVN7140_CFG_ERR_NO
#define CDDVN7140_CFG_ERR_NO 2U
#endif /*CDDVN7140_CFG_ERR_NO*/

#ifndef CDDVN7140_CFG_ERR_YES
#define CDDVN7140_CFG_ERR_YES 1U
#endif /*CDDVN7140_CFG_ERR_YES*/

#ifndef CDDVN7140_CFG_HSS_SNA
#define CDDVN7140_CFG_HSS_SNA 0U
#endif /*CDDVN7140_CFG_HSS_SNA*/

#ifndef CDDVN7140_CFG_HSS_NOEFT
#define CDDVN7140_CFG_HSS_NOEFT 1U
#endif /*CDDVN7140_CFG_HSS_NOEFT*/

#ifndef CDDVN7140_CFG_HSS_SUPPORT
#define CDDVN7140_CFG_HSS_SUPPORT 2U
#endif /*CDDVN7140_CFG_HSS_SUPPORT*/

#ifndef CDDVN7140_CFG_HSS_NOSUPPORT
#define CDDVN7140_CFG_HSS_NOSUPPORT 3U
#endif /*CDDVN7140_CFG_HSS_NOSUPPORT*/

#define CDDVN7140_CFG_SHORT2GND_THRESHOLD                      3610u

#define CDDVN7140_CFG_SHORT2VBAT_THRESHOLD                     4860u

#define CDDVN7140_CFG_OPENLOAD_THRESHOLD                         68u

#define CDDVN7140_CFG_CURRENT_RSENES                           1300u   // RSense  =1300Ohm
#define CDDVN7140_CFG_CURRENT_FACTOR_HSS3                       500u

#define CDDVN7140_HSS_SM                                          8u
#define CDDVN7140_HSS_RGB                                         9u
#define CDDVN7140_HSS_DRL                                         4u

#endif // CDD_VN7140_CFG_2021_03_01_H_

// EOF
