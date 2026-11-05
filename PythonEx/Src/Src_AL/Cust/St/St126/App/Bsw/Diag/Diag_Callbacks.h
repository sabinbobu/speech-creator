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
/// \file  Diag_Callbacks.h
///
/// \brief  Configuration macros used in Diag module
///
/// \descr  
///
/// \author Emanuel Baba (F48828C)
///         mailTo:emanuel.baba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __DIAG_CALLBACKS_H__
#define __DIAG_CALLBACKS_H__

//=============================================================================
// includes
//=============================================================================
#include <Cfg/Cfg.h>
#include <Cfg/CfgId.h>
#include <_DIAG_types.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#endif

//=============================================================================
// defines
//=============================================================================

#define DIAG_BUFFER_MAXSIZE 4095u
#define DIAG_8_BIT_MASK     0xFFU

//Length of Authentification zone
#define DIAG_AUTH_ZONE_LENGTH                     (sizeof(tsDiag_AuthZoneInfo))
//Length of ECU identification zone valid data
#define DIAG_LOGZONE_LENGTH                       (sizeof(tsDiag_LogZoneInfo))
//ECU identification zone - nr of entries
#define DIAG_LOGZONE_ENTRIES_NR                   (48u)

//Bits shift macros
#define DIAG_1BIT_SHIFT                   1u
#define DIAG_2BIT_SHIFT                   2u
#define DIAG_3BIT_SHIFT                   3u
#define DIAG_4BIT_SHIFT                   4u
#define DIAG_5BIT_SHIFT                   5u
#define DIAG_6BIT_SHIFT                   6u
#define DIAG_7BIT_SHIFT                   7u
#define DIAG_8BIT_SHIFT                   8u
#define DIAG_9BIT_SHIFT                   9u
#define DIAG_15BIT_SHIFT                 15u


#define DIAG_LD_CTRL_MAX_RANGE_BYTE0    3U
#define DIAG_LD_CTRL_MIN_RANGE_BYTE0    1U
#define DIAG_LD_CTRL_MAX_RANGE_BYTE1    0x20U
#define DIAG_LD_CTRL_MIN_RANGE_BYTE1    0x01U
#define DIAG_LD_CTRL_ACTIVATION         1U
#define DIAG_LD_CTRL_DEACTIVATION       2U
#define DIAG_LD_CTRL_RESERVED           3U

#define DIAG_CALLBACKS_LU_NR            103U

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
#define DIAG_AFS_CONTROL_START        0x1u
#define DIAG_AFS_CONTROL_STOP         0x2u
#define DIAG_AFS_CONTROL_RESULT       0x3u
#define DIAG_AFS_CONTROL_RES_LENGTH     4u
#define DIAG_AFS_CONTROL_RESULT_ONGOING 1u
#define DIAG_AFS_CONTROL_RESULT_DONE    0u
#define DIAG_AFS_CONTROL_RES_BYTE_1  0xDFu
#define DIAG_AFS_CONTROL_RES_BYTE_2  0x17u
#define DIAG_AFS_STATES_NR_ALLOWED      9u
#define DIAG_CALLBACKS_ROUTINE_NA       0x00u
#define DIAG_CALLBACKS_ROUTINE_START    0x01u
#define DIAG_CALLBACKS_ROUTINE_STOP     0x02u
#define DIAG_CALLBACKS_ROUTINE_RESULT   0x03u
#endif

#define DIAG_LENGTH_STP_POS             16u    // Stepper Position length for DD05

#define DIAG_REF_VOLTAGE                2560u
#define DIAG_MAX_ADC_VAL                255u //8 bits

// Conv formula for the mlc reg values
#define DIAG_ROWADC8BIT_TO_MV(x) ((x) * DIAG_REF_VOLTAGE) / DIAG_MAX_ADC_VAL

//Maximum index of longzone entries
#define APPDESC_LOGZONE_ENTRY_MAX_INDEX         (DIAG_LOGZONE_ENTRIES_NR - 1u)
//Max uint8 value
#define APPDESC_MAX_UINT8_VALUE                 (255u)
//Empty logzone area
#define APPDESC_EMPTY_ZONE                      (0xFFU)
//Concatenate date like "YYMMDD"
#define APPDESC_CONCATENATE_DATE(x, y, z)       (uint32)(((uint32)(x) * 10000u) + ((uint32)(y) * 100u) + (uint32)(z))

#define DIAG_PWM_RESOLUTION                         0x8000u    // max PWM resolution 
#define DIAG_DO_SCALLING_FOR_MLC(pwm)               ((pwm))     //MLC WIDTH register = 10-bit
#define DIAG_FIND_PERCENTAGE_PWM(pwm_raw)           (uint8)(((uint32)(pwm_raw) * 100u ) / DIAG_PWM_RESOLUTION)
#define DIAG_MLC_DEV_ADDR_NOT_CONNECTED             (uint8)(0xFFU)
#define DIAG_EXTERNAL_EEPROM_SIZE                   CFG_MATRIX_EEPROM_SIZE  //external matrix EEPROM size


// Defines used for DID D401 and D402 (FAN1 and FAN2 status)
#define FAN_1                                       0u
#define FAN_2                                       1u
#define ON                                          1u
#define OFF                                         2u
#define DIAG_FAN_ON                              0x00U
#define DIAG_FAN_OFF                             0x01U
#define DIAG_FAN_UNKOWN                          0x02U



#define LOWBEAM_TOWN_LIGHT                         1u
#define LOWBEAM_FOGGY_WEATHER                      9u
#define TURNINDICATOR_TI                          30u
#define TURNINDICATOR_TI_BLINK                    32u

#define DIAG_DCM_MIN_LEVEL                       (20u)
#define DIAG_DCM_MAX_LEVEL                       (80u)

#define min(a,b)  (((a)<(b)) ? (a) : (b))
#define max(a,b)  (((a)>(b)) ? (a) : (b))

// Convertion factor from hex to ascii
#define HEX_TO_ASCII_FACTOR                    (0x30u)

// Converts day, month year from hex to dec                
#define ECU_EFT_DATE_ASCII_TO_DEC(x, y)    ((uint8)(((x) - HEX_TO_ASCII_FACTOR) * 10u) + (uint8)((y) - HEX_TO_ASCII_FACTOR))
#define ECU_EFT_DATE_ASCII_TO_BCD(x, y)    ((uint8)((uint8)(((x) - HEX_TO_ASCII_FACTOR) << 4u) & 0xF0u) | (uint8)((uint8)((y) - HEX_TO_ASCII_FACTOR) & 0x0Fu))

// Get manufacturing day in BCD format
#define ECU_EFT_DAY_BCD                    ECU_EFT_DATE_ASCII_TO_BCD(EFT_MANUFACTURING_DATE_DAY(0), EFT_MANUFACTURING_DATE_DAY(1));
// Get manufacturing month in BCD format
#define ECU_EFT_MONTH_BCD                  ECU_EFT_DATE_ASCII_TO_BCD(EFT_MANUFACTURING_DATE_MONTH(0), EFT_MANUFACTURING_DATE_MONTH(1));
// Get manufacturing year in BCD format
#define ECU_EFT_YEAR_BCD                   ECU_EFT_DATE_ASCII_TO_BCD(EFT_MANUFACTURING_DATE_YEAR(2), EFT_MANUFACTURING_DATE_YEAR(3));

// Get manufacturing day in DEC format
#define ECU_EFT_DAY_DEC                    ECU_EFT_DATE_ASCII_TO_DEC(EFT_MANUFACTURING_DATE_DAY(0), EFT_MANUFACTURING_DATE_DAY(1));
// Get manufacturing month in DEC format
#define ECU_EFT_MONTH_DEC                  ECU_EFT_DATE_ASCII_TO_DEC(EFT_MANUFACTURING_DATE_MONTH(0), EFT_MANUFACTURING_DATE_MONTH(1));
// Get manufacturing year in DEC format
#define ECU_EFT_YEAR_DEC                   ECU_EFT_DATE_ASCII_TO_DEC(EFT_MANUFACTURING_DATE_YEAR(2), EFT_MANUFACTURING_DATE_YEAR(3));


// Diagnostic response length check and buffers
#define DIAG_RESP_0BYTE            (0u)
#define DIAG_RESP_1BYTE            (1u)
#define DIAG_RESP_2BYTES           (2u)
#define DIAG_RESP_3BYTES           (3u)
#define DIAG_RESP_4BYTES           (4u)
#define DIAG_RESP_5BYTES           (5u)
#define DIAG_RESP_7BYTES           (7u)
#define DIAG_RESP_10BYTES         (10u)
#define DIAG_RESP_14BYTES         (14U)
#define DIAG_RESP_103BYTES       (103u)

#define DIAG_BUFFER_1BYTE          (1u)
#define DIAG_BUFFER_2BYTES         (2u)
#define DIAG_BUFFER_3BYTES         (3u)
#define DIAG_BUFFER_4BYTES         (4u)
#define DIAG_BUFFER_5BYTES         (5u)
#define DIAG_BUFFER_6BYTES         (6u)
#define DIAG_BUFFER_7BYTES         (7u)
#define DIAG_BUFFER_10BYTES       (10u)
#define DIAG_BUFFER_17BYTES       (17u)
#define DIAG_BUFFER_19BYTES       (19u)
#define DIAG_BUFFER_21BYTES       (21u)
#define DIAG_BUFFER_22BYTES       (22u)
#define DIAG_BUFFER_24BYTES       (24u)
#define DIAG_BUFFER_25BYTES       (25u)
#define DIAG_BUFFER_26BYTES       (26u)
#define DIAG_BUFFER_27BYTES       (27u)
#define DIAG_BUFFER_29BYTES       (29u)
#define DIAG_BUFFER_32BYTES       (32u)
#define DIAG_BUFFER_38BYTES       (38U)
#define DIAG_BUFFER_41BYTES       (41U)
#define DIAG_BUFFER_60BYTES       (60U)
#define DIAG_BUFFER_62BYTES       (62U)
#define DIAG_BUFFER_208BYTES     (208u)
#define DIAG_BUFFER_512BYTES     (512u)

// Diagnostic Sessionss
#define DIAG_01_DEFAULT_SESSION                             (0x01u)
#define DIAG_02_PROGRAMMING_SESSION                         (0x02u)
#define DIAG_03_EXTENDED_SESSION                            (0x03u)
#define DIAG_50_SUPPLIER_SESSION                            (0x50u)
#define DIAG_60_AL_SESSION                                  (0x60u)

// EcuM users
#define DIAG_01_EcuMUser                                    (0x00u)
#define DIAG_02_EcuMUser                                    (0x01u)

// Diagnostic Sub Services for Read DTC Information
#define DIAG_01_READ_NR_OF_DTC_BY_MASK                      (0x01u)
#define DIAG_02_READ_DTC_BY_MASK                            (0x02u)
#define DIAG_04_READ_DTC_SNAPSHOT_DATA                      (0x04u)

// Diagnostic Sub Functions for Control DTC Setting
#define DIAG_01_CONTROL_DTC_SETTING_ON                      (0x01u)
#define DIAG_01_CONTROL_DTC_SETTING_OFF                     (0x02u)

// Diagnostic DIDs
#define DIAG_0D00_FACTORY_DATA                              (0x0D00u)
#define DIAG_0D01_SIZE_ECU_SERIAL_NUMBER_IDENTIFIER         (0x0D01u)
#define DIAG_1100_CPU_LOAD_DEVICE                           (0X1100u)
#define DIAG_C002_SIZE_FOR_MULTI_DID                        (0xC002u)
#define DIAG_D400_PIXEL_LED_STATUS                          (0XD400U)
#define DIAG_D401_FAN1_STATUS                               (0xD401u)
#define DIAG_D402_FAN2_STATUS                               (0xD402u)
#define DIAG_D404_SCROLLING_CTRL_OUTPUT_STATE               (0xD404u)
#define DIAG_D405_LED_CHANNEL_OUTPUT_STATE                  (0xD405u)
#define DIAG_D406_LIGHT_DIST_STATUS                         (0XD406U)
#define DIAG_D407_NTC_RBIN_DATA                             (0xD407u)
#define DIAG_D408_DERATING_FACTOR_AND_TEMP                  (0xD408u)
#define DIAG_D409_CURRENT_BINNING_CLASS                     (0XD409U)
#define DIAG_D410_DIAG_SCROLLING_INPUT_STATE                (0XD410U)
#define DIAG_D411_INSTRUMENTATED_FRAMES                     (0xD411u)
#define DIAG_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION      (0xD420u)
#define DIAG_D421_RBIN_EEPROM_LMM_DIAGNOSIS                 (0xD421u)
#define DIAG_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS              (0xD422u)
#define DIAG_D4C5_LIGHTING_ENG_DATA                         (0xD4C5u)
#define DIAG_D4C6_SIGNALLING_ENG_DATA                       (0xD4C6u)
#define DIAG_D4C7_TURN_IND_ENG_DATA                         (0xD4C7u)
#define DIAG_D4C8_BODY_HIGH_SENSOR_ENG_DATA                 (0xD4C8u)
#define DIAG_D4C9_ATTITUDE_ENG_DATA                         (0xD4C9u)
#define DIAG_D4CB_LEVELLING_ENG_DATA                        (0xD4CBu)
#define DIAG_D4CD_RGB_LED                                   (0xD4CDu)
#define DIAG_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES    (0xE888u)
#define DIAG_F080_AUTHENTIFICATION_ZONE                     (0xF080u)
#define DIAG_F08F_EMC_STANDARDIZATION_LABEL                 (0XF08FU)
#define DIAG_F0FE_IDENTIFICATION_ZONE                       (0xF0FEu)
#define DIAG_F186_ACTIVE_DIAG_SESSION_IDENTIFIER            (0xF186u)
#define DIAG_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER    (0xF18Bu)
#define DIAG_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER         (0xF18Cu)
#define DIAG_FD00_STATISTICS_DATA_IDENTIFIER                (0xFD00u)
#define DIAG_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS           (0xFD01u)
#define DIAG_FD02_ECU_SERIAL_NUMBER_DATA_IDENTIFIER         (0xFD02u)
#define DIAG_FD03_READ_ACTIVE_ALECS                         (0xFD03u)
#define DIAG_FD04_INTERNAL_SOFTWARE_LABEL                   (0xFD04u)

// Diagnostic RCs
#define DIAG_0301_RESET_CPU_LOAD                            (0x0301u)
#define DIAG_DD00_LD_ACTIVATION                             (0xDD00u)
#define DIAG_DD01_PIXEL_ACTIVATION                          (0xDD01u)
#define DIAG_DD03_FAN1_ACTIVATION                           (0xDD03u)
#define DIAG_DD04_FAN2_ACTIVATION                           (0xDD04u)
#define DIAG_DD05_STEPPER_POSITION                          (0xDD05u)
#define DIAG_DD06_DCMOTOR_POSITION                          (0xDD06u)
#define DIAG_DD07_SET_SCROLLING_CTRL_OUTPUT                 (0xDD07u)
#define DIAG_DF10_REFERENCING_RUN                           (0xDF10u)
#define DIAG_DF11_STEPPER_CONTROL                           (0xDF11u)
#define DIAG_DF12_STEPPER_CONTROL                           (0xDF12u)
#define DIAG_DF13_STEPPER_CONTROL                           (0xDF13u)
#define DIAG_DF17_AFS_CONTROL                               (0xDF17u)
#define DIAG_DFB5_INIT_AUTOMATIC_LEVELING                   (0xDFB5u)
#define DIAG_F001_AL_RDM                                    (0xF001u)
#define DIAG_FF00_ERASE_MEMORY                              (0xFF00u)
#define DIAG_FF04_CHECK_MEMORY                              (0xFF04u)

// Identifiers for DFB5 routine
#define DIAG_DFB5_ID_1                    0xDFU
#define DIAG_DFB5_ID_2                    0xB5U

// Identifiers for DD05 routine
#define DIAG_DD05_ID_1                    0xDDU
#define DIAG_DD05_ID_2                    0x05U

// Identifiers for DD06 routine
#define DIAG_DD06_ID_1                    0xDDU
#define DIAG_DD06_ID_2                    0x06U

// Identifiers for DD07 routine
#define DIAG_DD07_ID_1                    0xDDU
#define DIAG_DD07_ID_2                    0x07U

// Identifiers for DF10 routine
#define DIAG_DF10_ID_1                    0xDFU
#define DIAG_DF10_ID_2                    0x10U

// Identifiers for DF11 routine
#define DIAG_DF11_ID_1                    0xDFU
#define DIAG_DF11_ID_2                    0x11U

// Identifiers for DF12 routine
#define DIAG_DF12_ID_1                    0xDFU
#define DIAG_DF12_ID_2                    0x12U

// Identifiers for DF13 routine
#define DIAG_DF13_ID_1                    0xDFU
#define DIAG_DF13_ID_2                    0x13U

// Identifiers for DD03 routine
#define DIAG_DD03_ID_1                    0xDDU
#define DIAG_DD03_ID_2                    0x03U

// Identifiers for DD04 routine
#define DIAG_DD04_ID_1                    0xDDU
#define DIAG_DD04_ID_2                    0x04U

// Identifiers for DD00 routine
#define DIAG_DD00_ID_1                    0xDDU
#define DIAG_DD00_ID_2                    0x00U

// Identifiers for DD01 routine
#define DIAG_DD01_ID_1                    0xDDU
#define DIAG_DD01_ID_2                    0x01U

// Identifiers for DD01 routine
#define DIAG_0301_ID_1                    0x03U
#define DIAG_0301_ID_2                    0x01U

// Identifiers for D411 DID
#define DIAG_D411_DID_1                   0xD4U
#define DIAG_D411_DID_2                   0x11U

// Identifiers for FD00 DID
#define DIAG_FD00_DID_1                   0xFDU
#define DIAG_FD00_DID_2                   0x00U

// Identifiers for 0D00 DID
#define DIAG_0D00_DID_1                   0x0DU
#define DIAG_0D00_DID_2                   0x00U

#define DIAG_LENGTH_ASSIETTE_VEHICULE     10u    // ASSIETTE_VEHICULE signal length
#define DIAG_LENGTH_8BIT     8u

// Routine Control Types
#define DIAG_ROUTINE_CONTROL_TYPE_START   0x01U
#define DIAG_ROUTINE_CONTROL_TYPE_STOP    0x02U
#define DIAG_ROUTINE_CONTROL_TYPE_RESULTS 0x03U

// Length of the diag answer in case snapshot was not stored for the current DTC
#define DIAG_LENGTH_SNAPSHOT_NOT_AVAILABLE (5u)
#define DIAG_ADJ_ANGLE_DEGREE              52428 //  80° = 52428
#define DIAG_PWM_BALANCING_ANGLE           32768 //  50° = 32768
#define DIAG_MAX_STATIC_SPEED              1500u //  15 km/h

// Value of Pixel Max PWM
#define DIAG_MAX_PWM_100                 0x0064U //  0x64 = 100%

// Id for reading ALL AfterMarket Data's
#define DIAG_ALL_DATA_RECORD_NUMBER        (uint8)0xFFu

// Constant byte for 19 04 did
#define DIAG_LAST_BYTE_DTC_SPNASHOT        (0xFFu)

// Max value for factory data
#define DIAG_MAX_FACTORY_DATA              (99u)

// Max value for factory data
#ifndef UNIT_TEST
#define DIAG_NR_LD                         (32u)
#else
//needed to cover for UT the case when index exceeds maximum
#define DIAG_NR_LD                         (31u)
#endif

//Max number of ext NTCs
#define DIAG_MAX_NO_OF_EXT_NTCS     14u

//Defines for Activation/Deactivation of FANs
#define DIAG_FAN1             1u
#define DIAG_FAN2             2u

//Defines for CddEft datas
#define DIAG_CALLBACKS_ECRNUMBER_BYTE_NR 13u 

//Number of ext NTCs
#define DIAG_NO_OF_EXT_NTCS            12u
#define DIAG_LENGTH_TEMP_THERMO        16u    //

//Number of Thermo Zones 
#define DIAG_NO_OF_THERMO_ZONES        12u

//Length of SW Label
#define DIAG_SOFTWARE_LABEL_LENGTH     27u

#if defined (CFG_VARIANT_FULL ) || (UNIT_TEST) 
//Number of LED Channels
#define DIAG_NO_OF_LED_CHANNELS        12u

#define DIAG_D4C5_LIGHTING_ENG_DATA                        (0xD4C5u)
#define DIAG_D4C5_MB_PRESENT_DEFECT                         0x02u
#define DIAG_D4C5_MB_NO_DEFECT                              0x01u
#define DIAG_D4C5_HB_STATUS                                 0x00u

#elif defined (CFG_VARIANT_ECO)
#define DIAG_NO_OF_LED_CHANNELS      4u
#define DIAG_D4C5_MB_NOT_USED                               0x03u
#endif

// Starting index from the second element
#define DIAG_START_INDEX_2            2u
// Starting index from the third element
#define DIAG_START_INDEX_3            3u
// Starting index from the fourth element
#define DIAG_START_INDEX_4            4u
// Starting index from the fifth element
#define DIAG_START_INDEX_5            5u
// Starting index from the sixth element
#define DIAG_START_INDEX_6            6u

// Reserved byte
#define DIAG_RESERVED_BYTE      (uint8)0xFF

// Light functions
#define DIAG_LIGHT_FUNCTION_LB              0u
#define DIAG_LIGHT_FUNCTION_HB              1u
#define DIAG_LIGHT_FUNCTION_DRL_POS         2u
#define DIAG_LIGHT_FUNCTION_TI              3u
#define DIAG_LIGHT_FUNCTION_SM              4u
#define DIAG_LIGHT_FUNCTION_RGB             5u
#define DIAG_LIGHT_FUNCTION_FOG             6u
#define DIAG_LIGHT_FUNCTION_CORNERING       7u

#define DIAG_LF_LB                    (uint8) 1u
#define DIAG_LF_LB_FuSa               (uint8) 2u
#define DIAG_LF_HB                    (uint8) 3u
#define DIAG_LF_DRL_POS               (uint8) 4u
#define DIAG_LF_DRL_POS_SCRL          (uint8) 5u
#define DIAG_LF_TI                    (uint8) 6u
#define DIAG_LF_TI_SCRL               (uint8) 7u
#define DIAG_LF_SM                    (uint8) 8u
#define DIAG_LF_RGB                   (uint8) 9u
#define DIAG_LF_FOG                   (uint8)10u
#define DIAG_LF_LB_BOOST              (uint8)11u
#define DIAG_LF_HB_BOOST              (uint8)12u
#define DIAG_LF_CL                    (uint8)13u
#define DIAG_LF_PXL                   (uint8)14u
#define DIAG_LF_MXB                   (uint8)15u

// Reserved bits for D421
#define DIAG_RESERVED_D421               (uint8)0x7F
#define DIAG_D421_EXT_NTCBIN_START       (uint8)0u
#define DIAG_D421_LMM_NTCBIN_START       (uint8)14u
#define DIAG_D421_EEPROM_NTCBIN_START    (uint8)21u
#define DIAG_D421_MAX_NTCBIN_INPUTS      (uint8)33u

// Reserved bits for D422
#define DIAG_RESERVED_D422      (uint8)0x0F

// Reserved bits for D4CD
#define DIAG_RESERVED_D4CD      (uint8)0x3F

// Mask for RGB LED
#define DIAG_RGB_LED_MASK       (uint8)0x01u

// Index offset for 2'nd element
#define DIAG_OFFSET_INDEX_2           2u

// Index offset for 3'rd element
#define DIAG_OFFSET_INDEX_3           3u

// Index offset for 6'th element
#define DIAG_OFFSET_INDEX_6           6u

// Index offset for 10'th element
#define DIAG_OFFSET_INDEX_10         10u

// Index offset for 13'th element
#define DIAG_OFFSET_INDEX_13         13u

// Index offset for 14'th element
#define DIAG_OFFSET_INDEX_14         14u

// Index offset for 15'th element
#define DIAG_OFFSET_INDEX_15         15u

// Index offset for 17'th element
#define DIAG_OFFSET_INDEX_17         17u

// Index offset for 19'th element
#define DIAG_OFFSET_INDEX_19         19u

// Index offset for 21'st element
#define DIAG_OFFSET_INDEX_21         21u

// Index offset for 22'th element
#define DIAG_OFFSET_INDEX_22         22u

// Index offset for 23'th element
#define DIAG_OFFSET_INDEX_23         23u

// Index offset for 2'th element
#define DIAG_OFFSET_INDEX_24         24u

// DTCSnapshotRecordNumber for AfterMarket Data's CTX_ECU
#define DIAG_CTX_DTCSNAPSHOT_RECORD_NUMBER (uint8)(DIAG_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES>>8u)

// DID SIZE Macro List 
#define DIAG_SERIAL_NUMBER_DID_F18C_SIZE          (UINT8)15
#define DIAG_SIZE_SERIAL_NUMBER_DID_0D01_SIZE     (UINT8)1
#define DIAG_ASCII_DEFAULT                        (UINT8)0x3F
#define DIAG_ASCII_LOWER_LIMIT                    (UINT8)0x20
#define DIAG_ASCII_UPPER_LIMIT                    (UINT8)0x7E
#define DIAG_ASCII_NOT_SUPPORTED_CHARACTER_1      (UINT8)0x22
#define DIAG_ASCII_NOT_SUPPORTED_CHARACTER_2      (UINT8)0x26
#define DIAG_ASCII_NOT_SUPPORTED_CHARACTER_3      (UINT8)0x3C
#define DIAG_ASCII_NOT_SUPPORTED_CHARACTER_4      (UINT8)0x3E
#define DIAG_ASCII_NOT_SUPPORTED_CHARACTER_5      (UINT8)0x7C

//DID
#define DIAG_DID_D4XX_HIGH_BYTE        (uint8)0xD4U
#define DIAG_DID_D420_LOW_BYTE         (uint8)0x20U
#define DIAG_DID_D421_LOW_BYTE         (uint8)0x21U
#define DIAG_DID_D422_LOW_BYTE         (uint8)0x22U
#define DIAG_DID_D4C9_LOW_BYTE         (uint8)0xC9U
#define DIAG_DID_D4CB_LOW_BYTE         (uint8)0xCBU
#define DIAG_DID_E888_HIGH_BYTE        (uint8)0xE8U
#define DIAG_DID_E888_LOW_BYTE         (uint8)0x88U

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
//Aftermarket Data - number of identifiers for FULL
#define DIAG_AFTERMARKET_DATA_IDS_NR   (uint8)6u
// Length DTC Snapshot FULL
#define DIAG_DTC_SNAPSHOT_LENGTH       (uint8)41u
#else
//Aftermarket Data - number of identifiers for ECO
#define DIAG_AFTERMARKET_DATA_IDS_NR   (uint8)4u
// Length DTC Snapshot ECO
#define DIAG_DTC_SNAPSHOT_LENGTH       (uint8)32u
#endif

// Instantaneous value of front/rear left or front/rear body high sensor
#define DIAG_MAX_VALUE_DID_D4C8            (250u)
#define DIAG_RESOLUTION_DID_D4C8           (65536u)

// Identifiers for F080 routine
#define DIAG_F080_ID_1 0xF0U
#define DIAG_F080_ID_2 0x80U

//Vehicle moving
#define DIAG_VEHICLE_MOVING 500u // 5km/h
#define CTRLSWI_CFG_ERR_SNA   0U
#define CTRLSWI_CFG_ERR_NO    2U
#define CTRLSWI_CFG_ERR_YES   1U

// Zero value
#define DIAG_OPTION_DISABLED     0u
#define DIAG_OPTION_ENABLED      1u

//LED_DRV_13 NAME
#define DIAG_HSS_SM              8u
#define DIAG_HSS_DRL             4u

// Defines used for DID F18C
#define DIAG_DATE_MONTHS_MIN                (uint8)1
#define DIAG_DATE_MONTHS_MAX                (uint8)12
#define DIAG_DATE_FEBRUARY                  (uint8)2
#define DIAG_DATE_LEAP_YEAR                 (uint8)4 
#define DIAG_DATE_INVALID_NUMBER_OF_DAYS    (uint16)999


//=============================================================================
// Externs
//=============================================================================
extern CONST_AL  tNvmPara_CodingArea*  Diag_pCodingArea;

//=============================================================================
// Data Types
//=============================================================================

//ECU identification zone info
typedef struct
{
  uint8 aucReserved[4];
  uint8 ucSupplierCode;
  uint8 ucSystemCode;
  uint8 ucEcuManufacturingDay;
  uint8 ucEcuManufacturingMonth;
  uint8 ucEcuManufacturingYear;
  uint8 ucApplicationType;
  uint8 ucSoftwareVersion;
  uint8 aucSoftwareEdition[2];
  uint8 ucDownloadedDay;
  uint8 ucDownloadedMonth;
  uint8 ucDownloadedYear;
  uint8 ucDownloadingSite;
  uint8 aucDownloadingToolSignature[3];
  uint8 ucDownloadingNumber;
  uint8 aucSoftwareReference[3];
}tsDiag_LogZoneInfo;

//Authentification zone info
typedef struct
{
  uint8 aucFunctPlanNb[5];
  uint8 aucPsaSupplierCode[2];
  uint8 aucFunctProdNb[5];
  uint8 ucSwEvolutionIndex_MSB;
  uint8 ucSwEvolutionIndex_LSB;
  uint8 aucReserved[2];
  uint8 ucDiagFrameEvolutionIndex;
  uint8 ucFaultsParamNr;
  uint8 aucReserved2[4];
}tsDiag_AuthZoneInfo;

typedef union
{
  tsDiag_AuthZoneInfo sAuthZoneInfo;
  uint8               aucInfo[DIAG_AUTH_ZONE_LENGTH];
}tuDiag_AuthZoneInfo;

typedef union
{
  tsDiag_LogZoneInfo sLogZoneInfo;
  uint8              aucInfo[DIAG_LOGZONE_LENGTH];
}tuDiag_LogZoneInfo;

//ECU identification zone entry structure
typedef struct
{
  tuDiag_LogZoneInfo uData;
  uint8              aucReserved[24 + 208]; // 24 bytes reprog + 208 Padd for mapping 256 bytes page
}tsDiag_LogZoneEntry;

// Structure for Coding used by Diag_Callbacks
typedef struct
{
  tNvmPara_CodingArea* psCodingParameters;
  tParaFct0_Cmd        eCodingState;
}tsDiag_CodingParameters;


// Structure for RBIN failure per light function
typedef struct
{
  uint8  aucChannelName[DIAG_NO_OF_LED_CHANNELS];
  uint8  aucRbinError[DIAG_NO_OF_LED_CHANNELS];
  uint8  aucNtcError[DIAG_NO_OF_LED_CHANNELS];
}tsDiag_RbinFailLightFunc;

// Structure for DID F18C month/days checking
typedef struct
{
  uint8 ucMonth;
  uint8 ucNbOfDays;
}tsDiag_MonthHandle;


//-----------------------------------------------------------------------------
// funtion prototypes
//-----------------------------------------------------------------------------
void     roDiag_Callbacks_ProgramingSessionAccepted(void);
void     roDiag_Callbacks_NRC_Response(uint8 ucCode);
boolean  roDiag_IntegrationMode(void);
// TODO VS: Uncomment once AL_SESSION is removed DIAG_status APPLI_ReadMemoryByAddress(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
// TODO VS: Uncomment once AL_SESSION is removed DIAG_status APPLI_WriteMemoryByAddress(UINT8 const* p_ui8_Data, Diag_Length_Type Length);


#endif // __DIAG_CALLBACKS_H__


// EOF
