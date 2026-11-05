//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

//----------------------------------------------------------------------------
// \file   Dem_EventListId.h GENERATED
//
// \brief  
// \descr  This files include all ALEC IDs
//
// \project St126
// \version 0.1
// \date    7/1/2025
//
// \path tool    D:\ALGitRepo\DPEMCA\Tools\DTCConfiguration\DTCConfigurator_St126.xlsm
//
// \author  Vlad Sarghe (F09695C)
//          mailto:adrian-vlad.sarghe[at]marelli.com
//
//----------------------------------------------------------------------------


#ifndef __DEM_LIST_ID__
  #define __DEM_LIST_ID__

typedef enum
{
  MED_NOT_ACK =   1,   //MED_NOT_ACK, Deh frames has never been acknowledged, left side
  FR_BHS_PLAUS_FAIL =   3,   //FR_BHS_PLAUS_FAIL, front signal plausibility failure, left side
  FR_BHS_CSG =   5,   //FR_BHS_CSG, front circuit short to ground, left side
  FR_BHS_OC =   7,   //FR_BHS_OC, front circuit short to battery or open circuit, left side
  RR_BHS_PLAUS_FAIL =   9,   //RR_BHS_PLAUS_FAIL, rear signal plausibility failure, left side
  RR_BHS_CSG =  11,   //RR_BHS_CSG, rear circuit short to ground, left side
  RR_BHS_OC =  13,   //RR_BHS_OC, rear circuit short to battery or open circuit, left side
  FR_BHS_SUPPLY_LOW =  15,   //FR_BHS_SUPPLY_LOW, front leveling sensor signal low, left side
  FR_BHS_SUPPLY_HIGH =  17,   //FR_BHS_SUPPLY_HIGH, front leveling sensor signal high, left side
  RR_BHS_SUPPLY_LOW =  19,   //RR_BHS_SUPPLY_LOW, rear leveling sensor signal low, left side
  RR_BHS_SUPPLY_HIGH =  21,   //RR_BHS_SUPPLY_HIGH, rear leveling sensor signal high, left side
  DCMotor_SC_GND =  23,   //DCMotor_SC_GND, short to ground, left side
  DCMotor_SC_BAT =  25,   //DCMotor_SC_BAT, short to battery, left side
  Vehicle_attitude_ID =  27,   //Vehicle_attitude_ID, invalid parameter, left side
  ZERO_LVL_PROG =  29,   //ZERO_LVL_PROG, attitude initialisation not valid, left side
  ETAT_FEE_INVALID_DATA =  31,   //ETAT_FEE_INVALID_DATA, Etat Fee invalid data, left side
  HS6_DAT_VSM_2AE_ID =  33,   //HS6_DAT_VSM_2AE_ID, frame lost, left side
  HS6_DAT_VSM_34E_ID =  35,   //HS6_DAT_VSM_34E_ID, frame lost, left side
  HS6_DAT_VSM_36E_ID =  37,   //HS6_DAT_VSM_36E_ID, frame lost, left side
  HS6_COMMANDES_VSM_036_ID =  39,   //HS6_COMMANDES_VSM_036_ID, frame lost, left side
  HS6_DAT_VSM_3AE_ID =  41,   //HS6_DAT_VSM_3AE_ID, frame lost, left side
  HS6_DAT_BSI_432_ID =  43,   //HS6_DAT_BSI_432_ID, frame lost, left side
  HS6_DYN_ABR_38D_ID =  45,   //HS6_DYN_ABR_38D_ID, frame lost, left side
  INVALID_DATA_2B7 =  47,   //INVALID_DATA_2B7, invalid data, left side
  HS6_38D_PROC_COUNTER_ID =  49,   //HS6_38D_PROC_COUNTER_ID, calculated process counter not corresponding, left side
  HS6_38D_CALC_CHKSUM_ID =  51,   //HS6_38D_CALC_CHKSUM_ID, calculated checksum not corresponding, left side
  HS6_DYN3_CMM_468_ID =  53,   //HS6_DYN3_CMM_468_ID, CMM frame lost, left side
  Wheel_vehicle_speed_ID =  55,   //Wheel_vehicle_speed_ID, invalid parameter, left side
  PHASEVIE_INVALID_DATA_036 =  57,   //PHASEVIE_INVALID_DATA_036, phase vie invalid data, left side
  ANIMA_INVALID_DATA_36E =  59,   //ANIMA_INVALID_DATA_36E, welcome goodbye invalid data, left side
  LOCATION_INVALID_DATA_3AE =  61,   //LOCATION_INVALID_DATA_3AE, loc showroom invalid data, left side
  Unavailable_speed_ID =  63,   //Unavailable_speed_ID, invalid parameter, left side
  HS6_DYN_VSM_257_ID =  65,   //HS6_DYN_VSM_257_ID, frame lost, left side
  OV_D =  67,   //OV_D, Over voltage defect, +CAN > +16V;  left side
  UV_D =  69,   //UV_D, Under voltage defect, +CAN < +8V;  left side
  HS6_DYN_BEMP_2B7_ID =  71,   //HS6_DYN_BEMP_2B7_ID, frame lost, left side
  HS6_DAT_DRVLED_R_297_ID =  73,   //HS6_DAT_DRVLED_R_297_ID, frame lost, left side
  HS6_34E_PROC_COUNTER_ID =  75,   //HS6_34E_PROC_COUNTER_ID, calculated process counter not corresponding, left side
  HS6_34E_CALC_CHKSUM_ID =  77,   //HS6_34E_CALC_CHKSUM_ID, calculated checksum not corresponding, left side
  TI_INVALID_DATA_2AE =  79,   //TI_INVALID_DATA_2AE, TI invalid data, left side
  Mute_ECU =  81,   //Mute_ECU, CAN BUS mute detected, left side
  IGNITION_INVALID_DATA_432 =  83,   //IGNITION_INVALID_DATA_432, ignition state invalid data, left side
  ACCELERATION_INVALID_DATA_257 =  85,   //ACCELERATION_INVALID_DATA_257, acceleration invalid data, left side
  CPT_TEMPOREL_INVALID_DATA_552 =  87,   //CPT_TEMPOREL_INVALID_DATA_552, cpt temporel invalid data, left side
  SM_CVBT =  89,   //SM_CVBT,SM LED String circuit voltage below threshold, left side
  Fan1_E_SC_GND =  91,   //Fan1_E_SC_GND, CircuitShortToGND, left side
  Fan1_E_OC =  93,   //Fan1_E_OC, OpenCircuit, left side
  Fan1_E_SC_BAT =  95,   //Fan1_E_SC_BAT, CircuitShortToBAT, left side
  SM_SC_GND =  97,   //SM_SC_GND,SM LED String Circuit short to ground, left side
  SM_SC_BAT =  99,   //SM_SC_BAT,SM LED String Circuit short to battery, left side
  SM_OL = 101,   //SM_OL,SM LED String Circuit Open, left side
  HS6_DAT4_V2_BSI_552 = 103,   //HS6_DAT4_V2_BSI_552, frame lost , left side
  SUBCAN_BUSOFF = 105,   //SUBCAN_BUSOFF, control unit Bus off, left side
  Lb_E_SC_GND = 107,   //Lb_E_SC_GND, CircuitShortToGround, left side
  Lb_E_SC_BAT = 109,   //Lb_E_SC_BAT, CircuitShortToBattery, left side
  Lb_Strang_E_OC = 111,   //Lb_Strang_E_OC, CircuitOpen, left side
  HS6_DAT_VSM_54D_ID = 113,   //HS6_DAT_VSM_54D_ID, frame lost, left side
  INVALID_DATA_54D = 115,   //INVALID_DATA_54D, KM Total invalid data, left side
  Drl_E_SC_GND = 117,   //Drl_E_SC_GND, CircuitShortToGround, left side
  Drl_E_SC_BAT = 119,   //Drl_E_SC_BAT, CircuitShortToBattery, left side
  Drl_E_OC = 121,   //Drl_E_OC, CircuitOpen, left side
  Drl_E_OVTEMP_OFF = 123,   //Drl_E_OVTEMP_OFF, ThermalShutdown, left side
  Drl_E_OV_CURRENT = 125,   //Drl_E_OV_CURRENT, OverCurrent (From LED Chip), left side
  Drl_E_UN_VOLT = 127,   //Drl_E_UN_VOLT, CircuitVoltageBelowThreshold, left side
  Ti_E_SC_GND = 129,   //Ti_E_SC_GND, CircuitShortToGround, left side
  Ti_E_SC_BAT = 131,   //Ti_E_SC_BAT, CircuitShortToBattery, left side
  Ti_Strang_E_OC = 133,   //Ti_Strang_E_OC, CircuitOpen, left side
  FEE_Ecu_Error = 135,   //FEE_Ecu_Error, left side
  MPU_Error = 137,   //MPU_Error, left side
  SBC_DEFECT = 139,   //SBC_DEFECT, left side
  SPI_Bus1_E_DEFECT = 141,   //SPI_Bus1_E_DEFECT, left side
  SPI_Bus2_E_DEFECT = 143,   //SPI_Bus2_E_DEFECT, left side
  Booster_E_DEFECT = 145,   //Booster_E_DEFECT, left side
  WATCHDOG_DEFECT = 147,   //WATCHDOG_DEFECT, left side
  CRC_APP_INIT_DEFECT = 149,   //CRC_APP_INIT_DEFECT, left side
  CRC_APP_DEFECT = 151,   //CRC_APP_DEFECT, left side
  CRC_CALIB_DEFECT = 153,   //CRC_CALIB_DEFECT, left side
  CRC_PAV_DEFECT = 155,   //CRC_PAV_DEFECT, left side
  NTC_PCB_E_SC_BAT = 157,   //NTC_PCB_E_SC_BAT, left side [N/A]
  NTC_PCB_E_SC_GND = 159,   //NTC_PCB_E_SC_GND, left side
  NTC_PCB_E_OPENLOAD = 161,   //NTC_PCB_E_OPENLOAD, left side
  OS_WRONG_CONFIGURED = 163,   //OS_WRONG_CONFIGURED, left side
  CALIB_ERR_MISSING_CALIB = 165,   //CALIB_ERR_MISSING_CALIB, missing calibration error, left side
  CALIB_OV_UV_FLASH = 167,   //CALIB_OV_UV_FLASH, overvoltage/undervoltage while flashing, left side
  CALIB_PARAM_CALIB_DEFECT = 169,   //CALIB_PARAM_CALIB_DEFECT, parameter set calibration defect, left side
  RGB_HSS_DRIVER_SCB = 171,   //RGB_HSS_DRIVER_SCB, RGB driver short circuit to battery, left side
  RGB_HSS_DRIVER_SCG = 173,   //RGB_HSS_DRIVER_SCG, RGB driver short circuit to ground, left side
  RGB_HSS_DRIVER_OL = 175,   //RGB_HSS_DRIVER_OL, RGB driver driver circuit open, left side
  RGB_LED_SCB = 177,   //RGB_LED_SCB, LED channel circuit short to battery, left side
  RGB_LED_SCG = 179,   //RGB_LED_SCG, LED channel circuit short to ground, left side
  RGB_LED_OL = 181,   //RGB_LED_OL, LED channel circuit open load, left side
  RGB_LED_OT = 183,   //RGB_LED_OT, LED channel over temperature, left side
  RGB_LED_OC = 185,   //RGB_LED_OC, LED Channel Over current from LED chip, left side
  RGB_LED_CVBT = 187,   //RGB_LED_CVBT, LED Channel circuit voltage below threshold, left side
  LR_Detect = 189,   //LR_Detect, Right Side short to Vbatt, left side
  RCOD_IMP_PLAUS_RANGE = 191,   //RCOD_IMP_PLAUS_RANGE, impedance out of plausibile ranges, left side
  NTC_IMP_OUT_RANGE = 193,   //NTC_IMP_OUT_RANGE, impedance out range, left side
  HB_E_SC_GND = 195,   //HB_E_SC_GND, CircuitShortToGround, left side
  HB_E_SC_BAT = 197,   //HB_E_SC_BAT, CircuitShortToBattery, left side
  HB_E_OC = 199,   //HB_E_OC, CircuitOpen, left side
  VCCX2_SC_GND = 201,   //VCCX2_SC_GND, circuit short to ground, left side
  VCCX2_SC_BAT = 203,   //VCCX2_SC_BAT, circuit short to battery, left side
  NTCs_SC_BAT = 205,   //NTCs_SC_BAT, short to battery, left side
  NTCs_SC_GND = 207,   //NTCs_SC_GND, short to ground, left side
  NTCs_OL = 209,   //NTCs_OL, open load, left side
  RCODs_SC_BAT = 211,   //RCODs_SC_BAT, short to battery, left side
  RCODs_SC_GND = 213,   //RCODs_SC_GND, short to ground, left side
  RCODs_OL = 215,   //RCODs_OL, open load, left side
  LBSafety_SC_BAT = 217,   //LBSafety_SC_BAT, led channel short to battery, left side
  LBSafety_SC_GND = 219,   //LBSafety_SC_GND, led channel short to ground, left side
  LBSafety_OL = 221,   //LBSafety_OL, led channel open load, left side
  LBSafety_OT = 223,   //LBSafety_OT, led channel over temperature, left side
  LBSafety_OC = 225,   //LBSafety_OC, led channel over current from LED Chip, left side
  LBSafety_CVBT = 227,   //LBSafety_CVBT, led channel circuit voltage below threshold, left side
  LB_OT = 229,   //LB_OT, led channel over temperature, left side
  LB_OC = 231,   //LB_OC, led channel over current from LED Chip, left side
  LB_CVBT = 233,   //LB_CVBT, led channel circuit voltage below threshold, left side
  HB_OT = 235,   //HB_OT, led channel over temperature, left side
  HB_OC = 237,   //HB_OC, led channel over current from LED Chip, left side
  HB_CVBT = 239,   //HB_CVBT, led channel circuit voltage below threshold, left side
  TI_OT = 241,   //TI_OT, led channel over temperature, left side
  TI_OC = 243,   //TI_OC, led channel over current from LED Chip, left side
  TI_CVBT = 245,   //TI_CVBT, led channel circuit voltage below threshold, left side
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  VSM_FRAME_LOST_0E3_ID = 247,   //VSM_FRAME_LOST_0E3_ID, VSM frame lost, left side
  VSM_FRAME_LOST_0EB_ID = 249,   //VSM_FRAME_LOST_0EB_ID, VSM frame lost, left side
  VSM_FRAME_LOST_103_ID = 251,   //VSM_FRAME_LOST_103_ID, VSM frame lost, left side
  VSM_FRAME_LOST_10B_ID = 253,   //VSM_FRAME_LOST_10B_ID, VSM frame lost, left side
  VSM_FRAME_LOST_123_ID = 255,   //VSM_FRAME_LOST_123_ID, VSM frame lost, left side
  VSM_FRAME_LOST_163_ID = 257,   //VSM_FRAME_LOST_163_ID, VSM frame lost, left side
  VSM_FRAME_LOST_16B_ID = 259,   //VSM_FRAME_LOST_16B_ID, VSM frame lost, left side
  VSM_FRAME_LOST_183_ID = 261,   //VSM_FRAME_LOST_183_ID, VSM frame lost, left side
  VSM_FRAME_LOST_18B_ID = 263,   //VSM_FRAME_LOST_18B_ID, VSM frame lost, left side
  VSM_FRAME_LOST_1AB_ID = 265,   //VSM_FRAME_LOST_1AB_ID, VSM frame lost, left side
  VSM_INVALID_DATA_0E3_ID = 267,   //VSM_INVALID_DATA_0E3_ID, VSM invalid data, left side
  VSM_INVALID_DATA_0EB_ID = 269,   //VSM_INVALID_DATA_0EB_ID, VSM invalid data, left side
  VSM_INVALID_DATA_103_ID = 271,   //VSM_INVALID_DATA_103_ID, VSM invalid data, left side
  VSM_INVALID_DATA_10B_ID = 273,   //VSM_INVALID_DATA_10B_ID, VSM invalid data, left side
  VSM_INVALID_DATA_123_ID = 275,   //VSM_INVALID_DATA_123_ID, VSM invalid data, left side
  VSM_INVALID_DATA_163_ID = 277,   //VSM_INVALID_DATA_163_ID, VSM invalid data, left side
  VSM_INVALID_DATA_16B_ID = 279,   //VSM_INVALID_DATA_16B_ID, VSM invalid data, left side
  VSM_INVALID_DATA_183_ID = 281,   //VSM_INVALID_DATA_183_ID, VSM invalid data, left side
  VSM_INVALID_DATA_18B_ID = 283,   //VSM_INVALID_DATA_18B_ID, VSM invalid data, left side
  VSM_INVALID_DATA_1AB_ID = 285,   //VSM_INVALID_DATA_1AB_ID, VSM invalid data, left side
  GFHB_SC_BAT = 287,   //GFHB_SC_BAT, led channel LMMx short to battery, left side
  GFHB_OL = 289,   //GFHB_OL, led channel LMMx open load, left side
  GFHB_OT = 291,   //GFHB_OT, led channel LMMx over temperature, left side
  GFHB_OC = 293,   //GFHB_OC, led channel LMMx over current from LED chip, left side
  GFHB_1ROW = 295,   //GFHB_1ROW,LMM 1 Row HB short or open, left side
  GFHB_2ROW = 297,   //GFHB_2ROW,LMM 2 Row LB+HB short or open, left side
  StpV0_E_SC = 299,   //StpV0_E_SC, CircuitShortToGND/BAT, Electrical defect of levelling actuator, left side
  StpV0_E_OC = 301,   //StpV0_E_OC, CircuitOpen, Electrical defect of levelling actuator, left side
  StpV0_E_OVTEMP_OFF = 303,   //StpV0_E_OVTEMP_OFF, Thermical shutdown of levelling actuator, left side
  HS6_DAT7_BSI_612_ID = 305,   //HS6_DAT7_BSI_612_ID, frame lost, left side
  HS6_DAT_CSS_350_ID = 307,   //HS6_DAT_CSS_350_ID, frame lost, left side
  LMM_LB_LOS_COM = 309,   //LMM_LB_LOS_COM, loss of communication, left side
  LMM_LB_CRPT_COM = 311,   //LMM_LB_CRPT_COM, corrupt communication, left side
  LMM_HB_LOS_COM = 313,   //LMM_HB_LOS_COM, loss of communication, left side
  LMM_HB_CRPT_COM = 315,   //LMM_HB_CRPT_COM, corrupt communication, left side
  LMM_GFHB_LOS_COM = 317,   //LMM_GFHB_LOS_COM, loss of communication, left side
  LMM_GFHB_CRPT_COM = 319,   //LMM_GFHB_CRPT_COM, corrupt communication, left side
  HS6_DAT_VSM_32E_ID = 321,   //HS6_DAT_VSM_32E_ID, frame lost, left side
  HS6_DAT_DRVLED_R_4D7_ID = 323,   //HS6_DAT_DRVLED_R_4D7_ID, frame lost, left side
  INVALID_DATA_4D7 = 325,   //INVALID_DATA_4D7, invalid data, left side
  LMM_SatEEPROM_WRNG_CHKSUM = 327,   //LMM_SatEEPROM_WRNG_CHKSUM, wrong checksum, left side
  LMM_SatEEPROM_NO_ACC = 329,   //LMM_SatEEPROM_NO_ACC, no acces, left side
  LB_SC_BAT_LMMx = 331,   //LB_SC_BAT_LMMx, led channel LMMx short to battery, left side
  LB_OL_LMMx = 333,   //LB_OL_LMMx, led channel LMMx open load, left side
  LB_OT_LMMx = 335,   //LB_OT_LMMx, led channel LMMx over temperature, left side
  LB_OC_LMMx = 337,   //LB_OC_LMMx, led channel LMMx over current from LED chip, left side
  LB_2ROW = 339,   //LB_2ROW,LMM 2 Row LB+HB short or open, left side
  LB_3ROW = 341,   //LB_3ROW,LMM 3 Row LB short or open, left side
  HB_SC_BAT = 343,   //HB_SC_BAT, led channel LMMx short to battery, left side
  HB_OL_LMMx = 345,   //HB_OL_LMMx, led channel LMMx open load, left side
  HB_OT_LMMx = 347,   //HB_OT_LMMx, led channel LMMx over temperature, left side
  HB_OC_LMMx = 349,   //HB_OC_LMMx, led channel LMMx over current from LED chip, left side
  HB_1ROW = 351,   //HB_1ROW,LMM 1 Row HB short or open, left side
  HB_2ROW = 353,   //HB_2ROW,LMM 2 Row LB+HB short or open, left side
  STP_LOSS = 355,   //STP_LOSS,Step Loss, left side
  STP_E_UV = 357,   //STP_E_UV,Stepper under-voltage< 9V, left side
  STP_E_OV = 359,   //STP_E_OV,Stepper over-voltage> 17V, left side
  STP_OTW = 361,   //STP_OTW,Stepper Thermal Warning, left side
  CL_SBL_SC_GND = 363,   //CL_SBL_SC_GND,CL_SBL LED String Circuit short to ground, left side
  CL_SBL_SC_BAT = 365,   //CL_SBL_SC_BAT,CL_SBL LED String Circuit short to battery, left side
  CL_SBL_OL = 367,   //CL_SBL_OL,CL_SBL LED String Circuit Open, left side
  CL_SBL_OT = 369,   //CL_SBL_OT,CL_SBL LED String over temperature, left side
  CL_SBL_OC = 371,   //CL_SBL_OC,CL_SBL LED String over current, left side
  CL_SBL_CVBT = 373,   //CL_SBL_CVBT,CL_SBL LED String circuit voltage below threshold, left side
  SM_OT = 375,   //SM_OT,SM LED String over temperature, left side
  SM_OC = 377,   //SM_OC,SM LED String over current, left side
  FF_SC_GND = 379,   //FF_SC_GND,FF LED String Circuit short to ground, left side
  FF_SC_BAT = 381,   //FF_SC_BAT,FF LED String Circuit short to battery, left side
  FF_OL = 383,   //FF_OL,FF LED String Circuit Open, left side
  FF_OT = 385,   //FF_OT,FF LED String over temperature, left side
  FF_OC = 387,   //FF_OC,FF LED String over current, left side
  FF_CVBT = 389,   //FF_CVBT,FF LED String circuit voltage below threshold, left side
  HS6_DYN_VSM_28E_ID = 391,   //HS6_DYN_VSM_28E_ID, frame lost, left side
  DBL_28E_INVALID_DATA = 393,   //DBL_28E_INVALID_DATA, invalid data for DBl Curvature frame 28E, left side
  VacPos_DBLErr_INVALID_DATA = 395,   //VacPos_DBLErr_INVALID_DATA, invalid data for VacPos/DblErr frame 297, left side
  VSM_FRAME_LOST_12B_ID = 397,   //VSM_FRAME_LOST_12B_ID, VSM frame lost, left side
  VSM_INVALID_DATA_12B_ID = 399,   //VSM_INVALID_DATA_12B_ID, VSM invalid data, left side
  VSM_FRAME_LOST_143_ID = 401,   //VSM_FRAME_LOST_143_ID, VSM frame lost, left side
  VSM_INVALID_DATA_143_ID = 403,   //VSM_INVALID_DATA_143_ID, VSM invalid data, left side
  VSM_FRAME_LOST_14B_ID = 405,   //VSM_FRAME_LOST_14B_ID, VSM frame lost, left side
  VSM_INVALID_DATA_14B_ID = 407,   //VSM_INVALID_DATA_14B_ID, VSM invalid data, left side
  STP_DRIVER_SPI = 409,   //STP_DRIVER_SPI, No communication-internal(SPI bus), left side
  VSM_FRAME_LOST_0AB_ID = 411,   //VSM_FRAME_LOST_0AB_ID, VSM frame lost, left side
  VSM_INVALID_DATA_0AB_ID = 413,   //VSM_INVALID_DATA_0AB_ID, VSM invalid data, left side
  VSM_FRAME_LOST_0C3_ID = 415,   //VSM_FRAME_LOST_0C3_ID, VSM frame lost, left side
  VSM_INVALID_DATA_0C3_ID = 417,   //VSM_INVALID_DATA_0C3_ID, VSM invalid data, left side
  VSM_FRAME_LOST_0CB_ID = 419,   //VSM_FRAME_LOST_0CB_ID, VSM frame lost, left side
  VSM_INVALID_DATA_0CB_ID = 421,   //VSM_INVALID_DATA_0CB_ID, VSM invalid data, left side
  BUSSOFF_UART = 423,   //BUSSOFF_UART, buss off uart, left side
  OUTFCT_GPIO_TI_SCGND = 425,   //OUTFCT_GPIO_TI_SCGND, CircuitShortToGround, left side
  OUTFCT_GPIO_TI_SC_BAT = 427,   //OUTFCT_GPIO_TI_SC_BAT, CircuitShortToBattery, left side
  OUTFCT_GPIO_DRLPOS_SCGND = 429,   //OUTFCT_GPIO_DRLPOS_SCGND, CircuitShortToGround, left side
  OUTFCT_GPIO_DRLPOS_SC_BAT = 431,   //OUTFCT_GPIO_DRLPOS_SC_BAT, CircuitShortToBattery, left side
  INVALID_DATA_34E = 433,   //INVALID_DATA_34E,invalid data from frame 34E, left side
  STEER_WHEEL_ANGLE_INVALID_DATA_257 = 435   //STEER_WHEEL_ANGLE_INVALID_DATA_257, steering wheel angle invalid data, left side
#endif
}Dem_EventListId_EnumType;

#endif

//End file
