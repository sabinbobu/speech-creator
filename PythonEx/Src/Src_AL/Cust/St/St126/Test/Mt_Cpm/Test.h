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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
// Headers of the Module
#include <../App/Swc/Cpm/Api/Cpm_Adapter.h>
#include <../App/Swc/Cpm/Gen/FanM/FanM_Gen.h>
#include <../App/Swc/Cpm/Gen/FanM/FanM_GenTypes.h>
#include <Nvm.h>

//=============================================================================
// Defines
//=============================================================================
#define CPM_PERCENT_VAL                                            1
#define BINCUR2CURMA(cur)                        (uint16)(cur) /** 2u*/)
#define BINDUCY2PER1328(per)                     uint16)(((uint32)(per) << 15u) / 200u)
#define DUCY2PER1328(per)                        uint16)(((uint32)(per) << 15u) / 100u)
#define PER13282DUCY(per)                        uint16)(((uint32)(per) * 100u) >> 15u)
#define MULTDUTYCYCLE(x,y)                       uint16)(((uint32)(x)*(uint32)(y))>> 15u)
#define CODTEMP2MTEMP(deg)                       (((sint32)(deg)) - 40) * 1000)
#define MTEMP2CODTEMP(deg)                       uint8)(((sint32)(deg) / 1000) + 40)
#define DEG2MDEG(deg)                            ((sint32)(deg)) * 1000)
#define CODRED2DUCY2PER1328(per)                 uint16)(((uint32)((uint32)(per) * 4u) << 15u) / 1000u)
#define CPM_RSENS2CPMRES(deg)                    ((sint32)(deg)) * 100) //Cpm module has resolution 0.001
#define BINCUR2CURMA(cur)                        (uint16)(cur) /** 2u*/)
#define BINDUCY2PER1328(per)                     uint16)(((uint32)(per) << 15u) / 200u)
#define DUCY2PER1328(per)                        uint16)(((uint32)(per) << 15u) / 100u)
#define PER13282DUCY(per)                        uint16)(((uint32)(per) * 100u) >> 15u)
#define MULTDUTYCYCLE(x,y)                       uint16)(((uint32)(x)*(uint32)(y))>> 15u)
#define CODTEMP2MTEMP(deg)                       (((sint32)(deg)) - 40) * 1000)
#define MTEMP2CODTEMP(deg)                       uint8)(((sint32)(deg) / 1000) + 40)
#define DEG2MDEG(deg)                            ((sint32)(deg)) * 1000)
#define CODRED2DUCY2PER1328(per)                 uint16)(((uint32)((uint32)(per) * 4u) << 15u) / 1000u)
#define CPM_RSENS2CPMRES(deg)                    ((sint32)(deg)) * 100) //Cpm module has resolution 0.001

//=============================================================================
// Module global variables
//=============================================================================
extern boolean                                          Cpm_aboFanCtrl[2];
extern tsCPM_LifePhases                                 Cpm_eEcuOpMode;
extern tNvmPara_CodingArea                              Coding_Dummy = { 0u };
extern tParaFct0_Cmd                                    Coding_State = eParaFct0_CodingDataInvalid;
CodingDataVariableClass uint16                          FANM_PARA_unFanOffDelay;
CodingDataVariableClass uint16                          FANM_PARA_unFanOnDelay;
CodingDataVariableClass boolean                         FANM_PARA_abFan1FS[12];
CodingDataVariableClass boolean                         FANM_PARA_abFan2FS[12];
CodingDataVariableClass uint8                           FANM_PARA_aucExtSwitch2Tz[8][12];
CodingDataVariableClass uint8                           FANM_PARA_aucLsTarget2Tz[12];
CodingDataVariableClass uint8                           FANM_PARA_aucTz2Temp[12];
CodingDataVariableClass tlTemperature_mCelsius          FANM_PARA_alFan1TempOff[12];
CodingDataVariableClass tlTemperature_mCelsius          FANM_PARA_alFan1TempOn[12];
CodingDataVariableClass tlTemperature_mCelsius          FANM_PARA_alFan2TempOff[12];
CodingDataVariableClass tlTemperature_mCelsius          FANM_PARA_alFan2TempOn[12];
CodingDataVariableClass uint8                           CPM_PARA_ucLedUBatDeratingDelay;
CodingDataVariableClass uint8                           CPM_PARA_ucLedUBatDeratingFilter;
CodingDataVariableClass tunPercent_1_328                CPM_PARA_aunTzFS[13];
CodingDataVariableClass tunPercent_1_328                CPM_PARA_aunTzPwrFct[5][13];
CodingDataVariableClass boolean                         CPM_PARA_abTzFctGrp[4][12];
CodingDataVariableClass tlTemperature_mCelsius          CPM_PARA_alTzTemp[5][13];
CodingDataVariableClass sint16                          CPM_PARA_aunTzLmtFal;
CodingDataVariableClass sint16                          CPM_PARA_aunTzLmtRis;
CodingDataVariableClass boolean                         CPM_PARA_abTzFctGrp[4][12];
CodingDataVariableClass tulVoltage_mV                   CPM_PARA_aulLedDeratingV[2];
CodingDataVariableClass tunPercent_1_328                CPM_PARA_aunLedDeratingPwm[2];
CodingDataVariableClass uint8                           CPM_PARA_aucTz2Temp[12];
CodingDataVariableClass uint8                           CPM_PARA_aucLsTarget2Tz[12];
CodingDataVariableClass uint8                           CPM_PARA_aucExtSwitch2Tz[8][16];
CodingDataVariableClass tunPercent_1_328                CPM_DISP_aunTzPowerLimiter[13];

//=============================================================================
// Module function declarations
//=============================================================================
extern void                                      Cpm_Init(void);
extern void                                      Cpm_Cycle10ms(void);
extern void                                      Cpm_CodingValidCycle(void);
extern boolean                                   Cpm_MapParams(void);
extern boolean                                   Cpm_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern void                                      CpmThermo_SetPara(void);
extern uint8                                     Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT(void);
extern tiu32Voltage_mV                           Cpm_RteAccess_Read_Vbat(void);
extern tiu32Voltage_mV                           Cpm_RteAccess_Read_Vbat(void);
extern void                                      Cpm_RteAccess_Write_PwFact_Temp(tsCPM_PowFactTemp* sParam1);
extern Std_ReturnType                            Cpm_Read_PhaseVie(tsCPM_LifePhases* eEcuOpMode);
extern Std_ReturnType                            Cpm_Rte_Read_PcbTemperature(const tsRte_PcbTemperatureMsg *pdata);
extern tAppMThermo_CodHelper*                    CPM_Data_DriverMap(uint8 ucEcuSide);
extern uint8                                     Cpm_RteAccess_Get_ECU_Side(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
tiu32Voltage_mV	                                 Cpm_RteAccess_Read_Vbat_Param1;
tsCPM_LifePhases*                                Cpm_Read_PhaseVie_Param1;
tParaFct0_Cmd		                                 Cpm_ParaFct0_Param1;
tNvmPara_CodingArea*                             Cpm_ParaFct0_Param2;
tsCPM_PowFactTemp*                               Cpm_RteAccess_Write_PwFact_Temp_Param1;
uint8                                            CPM_Data_DriverMap_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
uint8                                            Cpm_RteAccess_Read_Vbat_RetVal;
uint8                                            Cpm_RteAccess_Get_ECU_Side_RetVal;
uint8                                            CPM_Data_DriverMap_RetVal;
teRte_EtatFeuxStationnement                      Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal;
uint8                                            Cpm_Read_PhaseVie_RetVal;
boolean                                          Cpm_MapParams_RetVal;
boolean                                          Cpm_ParaFct0_RetVal;
//=============================================================================
// Module static variables inside functions 
//=============================================================================
#endif // TEST_2023_08_25_H_

// EOF
