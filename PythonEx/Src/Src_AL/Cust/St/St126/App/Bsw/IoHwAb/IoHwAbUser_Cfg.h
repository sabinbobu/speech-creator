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
/// \file  IoHwAbUser_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------
//=============================================================================
//  includes
//=============================================================================


#include <Cfg/Cfg.h>

//=============================================================================
//  Definitions
//=============================================================================

#if defined(UNIT_TEST)
void  Mt_IoHwAbuser_GetMountingSideMemoryValue(uint32* Mt_IoHwAbuser_MountingSideMemoryValue);
void Mt_IoHwAbuser_GetSupervisorFlashMemValue(uint32* Mt_IoHwAbuser_SupervisorFlashMemValue);
void Mt_IoHwAbuser_GetFTM0RegisterValues(uint32* Mt_IoHwAbuser_FTM0);
void Mt_IoHwAbuser_GetFTM4RegisterValues(uint32* Mt_IoHwAbuser_FTM4);
#else


// The following symbols deal with hard-coded 32-bit numerical addresses
// of the entities MEM_ADR_LR_DET and MEM_ADR_LR_DET_INV.
// These are the physical addresses of the codinginformation
// such as 0x20000004 and 0x20000006. The proper address de-referencing
// is performed in the code of IoHwAbUser.c.
#define IOHWABUSER_MEM_ADR_LR_DET                          (uint32)0x20002F04
#define IOHWABUSER_MEM_ADR_LR_DET_INV                      (uint32)0x20002F06
#endif

#define IOHWABUSER_MAX_VAL_DUTY_RANGE                                 58982  //90 %
#define IOHWABUSER_MIN_VAL_DUTY_RANGE                                  6554  //10 %
#define IOHWABSUSER_5_PERCENT_PWM                                    0xCCCu
#define IOHWABSUSER_95_PERCENT_PWM                                  0xF332u
#define IOHWABUSER_ADJ_DUTY_PERCENT                                   52428  //80 %
#define IOHWABUSER_HSS_ADC_WAIT_TIME_30MS                               29u  // waiting time before calculation of mean value of HSS sensor

#define IOHWABUSER_LEFT_ECU                                 ((uint16)0x0101u)
#define IOHWABUSER_LEFT_ECU_INV                             ((uint16)0xFEFEu)
#define IOHWABUSER_RIGHT_ECU                                ((uint16)0x0202u)
#define IOHWABUSER_RIGHT_ECU_INV                            ((uint16)0xFDFDu)
#define IOHWABUSER_UNKNOWN_ECU                              ((uint16)0x0303u)
#define IOHWABUSER_UNKNOWN_ECU_INV                          ((uint16)0xFCFCu)

#define IOHWABUSER_ECU_HIGH_VAR                                ((uint8)0x01u)
#define IOHWABUSER_ECU_LOW_VAR                                 ((uint8)0x02u)

#define IOHWABUSER_RESOLUTION_12BIT                                   4095u

#define IOHWABUSER_FACTOR_VBAT                                       24642u

#define IOHWABUSER_SUBCYCLE_5MS                                          5u
#define IOHWABUSER_SUBCYCLE_10MS                                        10u
#define IOHWABUSER_SUBCYCLE_100MS                                      100u

#define IOHWABUSER_USAMPLIMGTIME_5                                       5u
#define IOHWABUSER_USAMPLIMGTIME_100                                   100u
#define IOHWABUSER_USAMPLIMGTIME_1                                       1u
#define IOHWABUSER_USAMPLIMGTIME_80                                     80u

#define IOHWABUSER_UFILTERTIME_HSS                                      5u
#define IOHWABUSER_UFILTERTIME_HSS3                                  2000u
#define IOHWABUSER_UFILTERTIME_TEMP                                   300u
#define IOHWABUSER_UFILTERTIME_VCCX1                                    5u

#define IOHWABUSER_INTERNAL_COM_ERR_DEBOUNCE_LIMIT           ((sint16)10u)  // 10 to reach the 200ms debounce time error states, because IoHwAbUser_SetLsDuty() is triggered by CddLed_Cycle20ms().
#define IOHWABUSER_COM_ERR_DEBOUNCE_LIMIT                    ((sint16)20u)  // 20 to reach the 200ms debounce time error states, because this is done by IoHwAbUser_Cycle10ms() runnable.
#define IOHWABUSER_INTERNAL_COM_ERR_FREE_DEBOUNCE_LIMIT       ((sint16)-1)   //Debounce value to reach error free state of internal communication err

#define IOHWABUSER_NR_PWMTARGET                                         2
#define IOHWABUSER_NR_HSSSENSOR                                         3
#define IOHWABUSER_HSSSENSE_0                                           0
#define IOHWABUSER_HSSSENSE_1                                           1
#define IOHWABUSER_HSSSENSE_2                                           2
#define IOHWABUSER_MAX_PWM                                          0xFFFFU
#define IOHWABUSER_PWMTARGET_OFFSET                                 32768

#define IOHWABUSER_RINGBUFFER_SIZE                                    10u  // This ring buffer define is used only for UBat measurement buffer which sample every 1ms and calculate every 10ms

#define IOHWABUSER_MOUNTINGSIDERAW_LEFT                                1u
#define IOHWABUSER_MOUNTINGSIDERAW_UNKNOW                            255u
#define IOHWABUSER_MOUNTINGSIDERAW_RIGHT                               2u
#define IOHWABUSER_MOUNTINGSIDE_RIGHT                                170u
#define IOHWABUSER_MOUNTINGSIDE_LEFT                                  85u


#define IOHWABUSER_MAX_TARGET_VALUE                                32768u

/* these values correspond to the limits in SWR LDM.SYRS.32298 & LDM.SYRS.32300 */
//Short to Ground voltage limit in mV
#define IOHWABUSER_VCCX_SHORTTOGND_A_U_VCCX_MV                       400u

//Short to VBat voltage limit in mV
#define IOHWABUSER_VCCX_SHORTTOVBAT_A_U_VCCX_MV                     5500u

#define IOHWAB_MAX_TARGET_VALUE                                       32768u
#define IOHWAB_DIO_CHANNEL_MAP_HSS_EN_1                               0u
#define IOHWAB_DIO_CHANNEL_MAP_HSS_EN_2                               1u
#define IOHWAB_DIO_CHANNEL_MAP_HSS_EN_3                               2u
#define IOHWAB_OUTPUT_HSS_1                                           0u
#define IOHWAB_OUTPUT_HSS_2                                           1u
#define IOHWAB_OUTPUT_HSS_3                                           2u

#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_PCB_TEMP                       0u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_1                          1u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_2                          2u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_3                          3u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_4                          4u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_5                          5u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_6                          6u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_7                          7u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_8                          8u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_9                          9u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_10                         10u

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)

#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_11                         11u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_12                         12u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_13                         13u
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_EXT_14                         14u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VBAT                     15u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_LR_DETECTION             16u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VCCX1                    17u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VCCX2                    18u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_1_2            19u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_3              20u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_OUT_FCT                  21u

#elif defined(SAMPLE_ECO) || defined(UNIT_TEST)

#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_DC_OUT_1                       11u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VBAT                     12u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_LR_DETECTION             13u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_VCCX1                    14u
#define IOHWABUSER_ADC_GROUP_CHANNEL_MAP_ADC_HSS_SENSE_1_2            15u

#endif

#if defined (UNIT_TEST)
#define IOHWABUSER_ADC_CHANNEL_MAP_ADC_DC_OUT_1                       11u
#endif

#if defined(SAMPLE_FULL) || UNIT_TEST

#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_1                          0u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_2                          1u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_3                          2u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_4                          3u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_5                          4u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_6                          5u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_7                          6u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_8                          7u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_9                          8u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_10                         9u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_11                         10u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_12                         11u
#define IOHWABUSER_PWM_CHANNEL_MAP_ST_STEP_LWR                         12u
#define IOHWABUSER_PWM_CHANNEL_MAP_HSS_EN_3                            13u

#elif defined(SAMPLE_ECO) || defined(UNIT_TEST)

#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_1                          0u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_2                          1u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_3                          2u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_4                          3u
#define IOHWABUSER_PWM_CHANNEL_MAP_LEDCNTRL_5                          4u
#define IOHWABUSER_PWM_CHANNEL_MAP_DC_MOTOR                            5u
#endif

#define IOHWABUSER_DIO_CHANNEL_MAP_BOOST_EN                            0u
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_1                            1u

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)

#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_2                            2u
#define IOHWABUSER_DIO_CHANNEL_MAP_HWID_0                              3u  // NEW NEW
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_ERROR                           4u
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_1                           5u
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEL_2                           6u
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEN                             7u
#define IOHWABUSER_DIO_CHANNEL_MAP_DIR_LWR                             8u
#define IOHWABUSER_DIO_CHANNEL_MAP_ST_SLEEP                            9u
#define IOHWABUSER_DIO_CHANNEL_MAP_ST_DRVOFF                           10u
#define IOHWABUSER_DIO_CHANNEL_MAP_VCCX_EN                             11u
#define IOHWABUSER_DIO_CHANNEL_MAP_VCCX2_PG                            12u  // NEW NEW
#define IOHWABUSER_DIO_CHANNEL_MAP_ST_ERROR                            13u
#define IOHWABUSER_DIO_CHANNEL_MAP_IN_FCT_2_UC                         14u  // TO DO: CHECK IF THIS IS A PWM
#define IOHWABUSER_DIO_CHANNEL_MAP_IMU_ALARMB                          15u
#define IOHWABUSER_DIO_CHANNEL_MAP_IMU_RESTN                           16u
#define IOHWABUSER_DIO_CHANNEL_MAP_HWID_1                              17u  // NEW NEW
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_EN_3                            18u  // NEW NEW
#elif defined(SAMPLE_ECO) || defined(UNIT_TEST)

#define IOHWABUSER_DIO_CHANNEL_MAP_DC_EN                               2u
#define IOHWABUSER_DIO_CHANNEL_MAP_HSS_SEN                             3u
#endif

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define IOHWABUSER_CFG_MAX_NO_OF_LS_CHANNELS                           13u
#define IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS                              14u
#elif defined(SAMPLE_ECO) || defined(UNIT_TEST)
#define IOHWABUSER_CFG_MAX_NO_OF_LS_CHANNELS                            5u
#define IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS                              10u
#endif

#define IOHWABUSER_MEAS_MODE_PERIOD                                     0U
#define IOHWABUSER_MEAS_MODE_DUTY                                       1U
#define IOHWABUSER_DEFAULT_ERR_PERIOD                                   5520u
#define IOHWABUSER_ERR_PERIOD_OFFSET                                    20u

#define IOHWABUSER_FTM0_CHOV                                            0x4003800C
#define IOHWABUSER_FTM4_CHOV                                            0x4003802C
#define IOHWABUSER_CHOV_BITSTATUS                                       0x00000200u

#define IOHWABUSER_FLTDCOUT                                             UTIL_Tau2   // 2 *  1ms = 2ms  --> 3T =  6ms

// EOF
