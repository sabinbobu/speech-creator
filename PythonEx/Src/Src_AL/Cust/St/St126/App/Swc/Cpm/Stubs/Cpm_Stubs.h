//This file is the interface between AppM and RTE.

#define RTE_ALLOW_CROSS_HEADER_INCLUSION
#include <AL_Helper.h>
#include <Rte_ctaaAppM.h>
#include <Rte_ctasCtrlHss.h>
#include <Swc/Cpm/Api/Cpm_Adapter.h>
#include <Swc/Cpm/Gen/Cpm/CPM_GenTypes.h>


extern tieDataStatus                      ieDataStatus;
extern tisHssStatusError                  isHssStatusError;
extern uint8                              int1;
extern tiu32LsChannel                     iu32LsChannel[APPM_CFG_MAX_NO_OF_MLC][APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC+4];
extern tiu32Thermozone                    iu32ExtSwThermozone[APPM_CFG_MAX_NO_OF_MLC][APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC];
extern tunPercent_1_328                   iu16Percent_1_328[APPM_CFG_MAX_NO_OF_MLC][APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC];
extern tisLsTarget_perc                   isLsTarget_perc[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS];
extern uint8                              ctrlLedTargetEnable[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS];
extern tiu32Thermozone                    iu32LsThermozone[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS];
extern tiu32Voltage_mV                    iu32Voltage_mV;
extern tiu32Voltage_mV                    iu32Voltage_mV2;
extern tis32Temperature_mCelsius          is32Temperature_mCelsius;
extern tisBinningResistor                 isBinning[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS + APPM_CFG_MAX_NO_OF_MLC];
extern tisTemperature_mCelsius            isTemperature_mCelsius[20];
extern tieHssState                        ieHssState_read;
extern uint8                              int3;
extern tiu16Percent_1_328                 iu16Percent_1_328_2[APPM_CFG_MAX_NO_OF_MLC][APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC];
extern tieHssState                        ieHssState[APPM_CFG_HSS_MAX_NO_OF_HSS_CHANNELS];
extern tisLsTarget                        isLsTarget[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS];
extern sint8                              ieTLsRedLevel[APPM_CFG_MAX_NO_OF_THERMOZONES];
extern tisLsTarget_perc                   isLsTarget_perc2[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS];
extern tiu8Temperature_Celsius            iu8Temperature_Celsius[20];
extern uint8                              int4;
extern tiu8TempGradient_mKelvinPerSecond  iu8TempGradient_mKelvinPerSecond;
extern tiu32LsErrorBitMask                iu32LsErrorBitMask;
extern tisTemperature_mCelsius            tempRSensMLsTemperature0[APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS + APPM_CFG_MAX_NO_OF_MLC];



#define Rte_Read_ctaaAppM_ppareCodMCodingDataStatus0_sVal(X)               memcpy(X, &ieDataStatus, sizeof(tieDataStatus))
#define Rte_Read_ctaaAppM_ppareCtrlHssStatusError0_sVal(X)                 memcpy(X, &isHssStatusError, sizeof(tisHssStatusError))
#define Rte_Read_ctaaAppM_ppareCtrlLedExtSwitchTarget0_aucEnable(X)        memcpy(X, &int1, sizeof(uint8))
#define Rte_Read_ctaaAppM_ppareCtrlLedExtSwitchTarget0_aulDrvChannel(X)    memcpy(X, &iu32LsChannel, sizeof(tiu32LsChannel)*APPM_CFG_MAX_NO_OF_MLC*(APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC+4))
#define Rte_Read_ctaaAppM_ppareCtrlLedExtSwitchTarget0_aulThermozone(X)    memcpy(X, &iu32ExtSwThermozone, sizeof(tiu32Thermozone)*APPM_CFG_MAX_NO_OF_MLC*APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC)
#define Rte_Read_ctaaAppM_ppareCtrlLedExtSwitchTarget0_aunDutyCycle(X)     memcpy(X, &iu16Percent_1_328, sizeof(tunPercent_1_328)*APPM_CFG_MAX_NO_OF_MLC*APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC)
#define Rte_Read_ctaaAppM_ppareCtrlLedLsTarget0_asSetting(X)               memcpy(X, &isLsTarget_perc, sizeof(tisLsTarget_perc)*APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS)
#define Rte_Read_ctaaAppM_ppareCtrlLedLsTarget0_aucEnable(X)               memcpy(X, &ctrlLedTargetEnable, sizeof(uint8)*APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS)
#define Rte_Read_ctaaAppM_ppareCtrlLedLsTarget0_aulThermozone(X)           memcpy(X, &iu32LsThermozone, sizeof(tiu32Thermozone)*APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS)
#define Rte_Read_ctaaAppM_ppareIoHwAbUserEcuSupply0_ulActualMean(X)        memcpy(X, &iu32Voltage_mV, sizeof(tiu32Voltage_mV))
#define Rte_Read_ctaaAppM_ppareIoHwAbUserEcuSupply0_ulActualMin(X)         memcpy(X, &iu32Voltage_mV2, sizeof(tiu32Voltage_mV))
#define Rte_Read_ctaaAppM_ppareRSensPcbTemperature0_lActual(X)             memcpy(X, &is32Temperature_mCelsius, sizeof(tis32Temperature_mCelsius))
#define Rte_Read_ctaaCPM_ppareRSensBinning0_asAct(X)                       memcpy(X, &isBinning, sizeof(tisBinningResistor)*(APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS+APPM_CFG_MAX_NO_OF_MLC))
#define Rte_Read_ctaaAppM_ppareSensMLsTemperature0_asAct(X)                memcpy(X, &isTemperature_mCelsius, sizeof(tisTemperature_mCelsius))
#define Rte_Read_ctaaAppM_ppareAppMHssTarget0_aeSetting(X)                 memcpy(X, &ieHssState_read, sizeof(tieHssState))
#define Rte_Read_ctaaCPM_ppareRSensExtTemperature0_asAct(X)                memcpy(X, &tempRSensMLsTemperature0, sizeof(tisTemperature_mCelsius)*(APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS + APPM_CFG_MAX_NO_OF_MLC))

#define CPM_Rte_Read_ppareRSensExtTemperature0_asAct(X)                    memcpy(X, &tempRSensMLsTemperature0, sizeof(tisTemperature_mCelsius)*(APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS + APPM_CFG_MAX_NO_OF_MLC))
#define CPM_Rte_Read_ppareRSensBinning0_asAct(X)                           memcpy(X, &isBinning, sizeof(tisBinningResistor)*(APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS+APPM_CFG_MAX_NO_OF_MLC))


#define Rte_Write_ctaaAppM_ppaseAppDataTemp_Temperature(X)                 memcpy(int3, X, sizeof(uint8))
#define Rte_Write_ctaaAppM_ppaseAppMExtSwitchTarget0_aunDutyCycle(X)       memcpy(iu16Percent_1_328_2, X, sizeof(tiu16Percent_1_328)*APPM_CFG_MAX_NO_OF_MLC*APPM_CFG_MAX_NO_OF_SWITCHES_ON_MLC)
#define Rte_Write_ctaaAppM_ppaseAppMHssTarget0_sSetting(X)                memcpy(ieHssState, X, sizeof(tieHssState)*APPM_CFG_HSS_MAX_NO_OF_HSS_CHANNELS)
#define Rte_Write_ctaaAppM_ppaseAppMLsTarget0_asSetting(X)                 memcpy(isLsTarget, X, sizeof(tisLsTarget)*APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS)
#define Rte_Write_ctaaAppM_ppaseAppMStatusError0_aeStatTLsRedLevel(X)      memcpy(ieTLsRedLevel, X, sizeof(sint8)*APPM_CFG_MAX_NO_OF_THERMOZONES)
#define Rte_Write_ctaaAppM_ppaseAppMStatusError0_asStatTargetDerated(X)    memcpy(isLsTarget_perc2, X, sizeof(tisLsTarget_perc)*APPM_CFG_LED_MAX_NO_OF_LS_CHANNELS)
#define Rte_Write_ctaaAppM_ppaseAppMStatusError1_ucDrvTemperature(X)       memcpy(iu8Temperature_Celsius, X, sizeof(tiu8Temperature_Celsius)*20)
#define Rte_Write_ctaaAppM_ppaseAppMStatusError1_ucRootCause(X)            memcpy(int4, X, sizeof(uint8))
#define Rte_Write_ctaaAppM_ppaseAppMStatusError1_ucTempGradient(X)         memcpy(iu8TempGradient_mKelvinPerSecond, X, sizeof(tiu8TempGradient_mKelvinPerSecond))
#define Rte_Write_ctaaAppM_ppaseAppMStatusError1_ulErrorBitMask_Thermal(X) memcpy(iu32LsErrorBitMask, X, sizeof(tiu32LsErrorBitMask))
#define Rte_Write_ctaaCPM_ppaseCPMFanRequest_sSetting(X)                   memcpy(ieHssState, X, sizeof(tieHssState)*APPM_CFG_HSS_MAX_NO_OF_HSS_CHANNELS)
