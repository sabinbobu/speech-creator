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
/// \file  CddMlc_Cfg.h
///
/// \brief Project specific configuration for Mlc module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_MLC_CFG_2021_09_02_H_
#define CDD_MLC_CFG_2021_09_02_H_

//==============================================================================
//  Includes
//==============================================================================
#include <AL_Helper.h>
#include <IoHwAbUser.h>

//==============================================================================
//  User Defines
//==============================================================================
#define CDDMLC_SUPPORTED_MLCs                 (sizeof(CddMlcGen_sCodingDataValue.ucMlcCanUartAddress)/sizeof(CddMlcGen_sCodingDataValue.ucMlcCanUartAddress[0]))
#ifndef UNIT_TEST
#define CDD_MLC_CHIPS                         (CddMlcGen_sCodingDataValue.ucMlcMatrixCount)
#endif
#define CFG_MAX_NO_OF_MLC                      7U
#define CFG_MAX_NO_OF_ADDRS_MLC                8U

#define CDDMLC_POWER_ON()                                                    \
IoHwAb_User_SetVccxEn(STD_HIGH)


#define CDDMLC_POWER_OFF()                                                   \
Dio_WriteChannel(IOHWABUSER_DIO_CHANNEL_MAP_VCCX_EN, STD_LOW)

#define CDDMLC_IS_POWERED()                                             \
( Dio_ReadChannel(IOHWABUSER_DIO_CHANNEL_MAP_VCCX_EN) == (Dio_LevelType)STD_HIGH ? TRUE : FALSE)



//wrapper
#define CDDMLC_CODING_GET_MLC_CAN_UART_ADDRESS(pADDRS)    {                                                                                     \
                                                            for (uint8 ucDevice=0U; ucDevice < CFG_MAX_NO_OF_MLC; ucDevice++)         \
                                                              {   \
                                                                    *pADDRS.ucMlcCanUartAddress[ucDevice] =*(&CddMlcGen_sCodingParameters.psCodingParameters_Blocks->LmmConfig.LMM_Config_Diagnosis.ucLMM__UART_CAN_ADDRESSES[ucDevice]);\
                                                              }\
                                                           }

#define CDDMLC_CODING_GET_MLC_CAN_UART_INTERFACE(pInt)              (*pInt.ucMlcCanUartInterface = CDDMLC_GEN_CODING_MATRIX_INTERFACE_PRIVATE_CAN )
#define CDDMLC_CODING_GET_MLC_TYPE(pType)                           (*pType.ucMlcMatrixType = CddMlcGen_sCodingParameters.psCodingParameters_Blocks->LmmConfig.LMM_Config_Diagnosis.ucLMM_CHIP_TYPE )
#define CDDMLC_CODING_GET_MLC_EEPROM_ADDRESS(pADDRS)                (*pADDRS.ucMlcEepromAddress = *(&CddMlcGen_sCodingParameters.psCodingParameters_Blocks->LmmConfig.LMM_Config_Diagnosis.ucEEPROM_ADDRESS))

#define CDDMLC_RTE_READ_CODING_DATA_STATUS(pStatus)                 (*pStatus = CddMlcGen_sCodingParameters.eCodingState)   //(void)Rte_Read_CodM_CddMlc_Para(pTarget)                      //from CodM
#define CDDMLC_RTE_READ_CODING_PARAMETERS(pTarget)                  (void)Rte_Read_CodM_CddMlc_Para(pTarget)


#define CDD_MLC_CODING_DATA_CONNECTED_DEVICES                       (CddMlcGen_sCodingDataValue.ucMlcMatrixCount)
#define CDD_MLC_CODING_DATA_ACTIVE_CAN_BUS                          (CddMlcGen_sCodingDataValue.ucMlcCanUartInterface)
#define CDD_MLC_PHY_CHIP_ID                                         ((uint8*)&(CddMlcGen_sCodingDataValue.ucMlcCanUartAddress[0U]))


#endif // CDD_MLC_CFG_2021_09_02_H_
