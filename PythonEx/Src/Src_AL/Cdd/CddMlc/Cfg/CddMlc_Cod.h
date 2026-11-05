//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file   CddMlc_Cod.h
///
/// \brief  Header file - Declares generic functions to access coding data
///
//-----------------------------------------------------------------------------
#ifndef CDD_MLC_COD_2024_04_01_H
#define CDD_MLC_COD_2024_04_01_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#ifndef UNIT_TEST
#include <Rte/Rte.h>
#endif

#include <CodM.h>
#include <CddMlc_Types.h>


//-----------------------------------------------------------------------------
// External variables
//-----------------------------------------------------------------------------
extern CONST_AL tNvmPara_CodingArea* CddMlc_pCodingArea;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

/* !!!!!!!!!! MLC TYPE -  keep as in coding IFD file !!!!!!!!!!!!!  */
#define CDDMLC_COD_MATRIX_TYPE_DISABLED       0U
#define CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A   1U
#define CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A   2U
#define CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664    3U
#define CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665    4U
#define CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667    5U
#define CDDMLC_COD_MATRIX_TYPE_TPSGENx_1      6U
#define CDDMLC_COD_MATRIX_TYPE_TPSGENx_2      7U
#define CDDMLC_COD_MATRIX_TYPE_NXP            8U    /* not supported */


//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd        eCodingState;
}tsCddMlc_CodingParam;


typedef struct
{
  uint8   ucMlcCanUartInterface;                        //Values: 0.. 1 ~0= CAN2(PriV-CAN) ; 1= CAN3(SAT-CANFD) ~1 Bit für jeden MLC (0…7) ~ Origin: FLK
  uint8   ucMlcBaudRate;
  uint8   aucMlcCanUartDeviceID[CDDMLC_CFG_MAX_CHIPS];  //Values: TPS92662A&TPS92663A (TI) Addr. 0…7 are allowed; TPS92664&TPS92665&TPS92667 (TI) Addr. 0..15 are allowed + 32 added as offset 
  uint8   ucMlcEepromDeviceID;                          //Values: 0.. 7;255 ~255= no EEPROM ~ EEPROM connected to LMM address
  uint8   ucMlcMatrixType;                              //Values: 0..15 ~ which MLC controller is used; 0: Matrix disabled;1:TPS92662A-Q1(TI);2:TPS92663A-Q1(TI);3: ASL5115SHN(NXP) Origin: FLK
  uint8   ucMlcConnectedDevs;
  uint8   ucMlcConnectedDevGEN2;
  uint8   ucMlcConnectedDevGEN3;
  uint8   ucMlcSwitchsSupported;
  boolean boCodingValid;
}tsCddMlc_CodingData;

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Definition of functions 
//-----------------------------------------------------------------------------

/* Access to CodM*/
#define CDDMLC_RTE_RE_GET_CODING_DATA(pTarget)        CddMlc_Read_CodingPara(pTarget);


/* Lmm_Config file from Coding IFD */
LOCAL_INLINE uint8  CddMlc_Cod_Get_MlcChipType(void)                    { return CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis.ucLMM_CHIP_TYPE;   }

LOCAL_INLINE uint8  CddMlc_Cod_Get_MlcBaudRate(void)                    { return CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis.unLMM_UART_COMM_SPEED;   }

LOCAL_INLINE uint8* CddMlc_Cod_Get_ChipID(void)                         { return (uint8*)&CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis.ucLMM__UART_CAN_ADDRESSES; }

LOCAL_INLINE uint8  CddMlc_Cod_Get_EepromAddrID(void)                   { return CddMlc_pCodingArea->LmmConfig.LMM_Config_Diagnosis.ucEEPROM_ADDRESS; }


tsCddMlc_CodingData* CddMlc_pfGetCodingData(void);
boolean              CddMlc_IsDevGEN2(uint8 ucDevId);
boolean              CddMlc_IsDevGEN3(uint8 ucDevId);


//-----------------------------------------------------------------------------
// Parameter access
//-----------------------------------------------------------------------------

#define CDDMLC_Para_IS_CODING_VALID         CddMlc_pfGetCodingData()->boCodingValid     
#define CDDMLC_Para_CHIP_TYPE               CddMlc_pfGetCodingData()->ucMlcMatrixType     
#define CDDMLC_Para_SUPPORTED_SWITCHES      CddMlc_pfGetCodingData()->ucMlcSwitchsSupported
#define CDDMLC_Para_CHIP_ID(ucIdx)          CddMlc_pfGetCodingData()->aucMlcCanUartDeviceID[ucIdx]
#define CDDMLC_Para_CHIP_EEPROM_ID          CddMlc_pfGetCodingData()->ucMlcEepromDeviceID
#define CDDMLC_Para_GEN2_CNT_DEVS           CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN2
#define CDDMLC_Para_GEN3_CNT_DEVS           CddMlc_pfGetCodingData()->ucMlcConnectedDevGEN3
#define CDDMLC_Para_BAUDRATE                CddMlc_pfGetCodingData()->ucMlcBaudRate


#endif // CDD_MLC_COD_2024_04_01_H
