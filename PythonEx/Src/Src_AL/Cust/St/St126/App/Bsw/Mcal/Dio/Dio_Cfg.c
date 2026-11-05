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
/// \file  Dio_Cfg.c
///
/// \brief
///
//-----------------------------------------------------------------------------

#include <Dio.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#include <Cfg/Cfg.h>
#include <AL_Helper.h>

// MISRA / QAC
//  warning - QAC(Prio5) Msg: 306([I] Cast between a pointer to object and an integral type.) Depth: 0 Ref: MISRA C:2012 Rule-11.4, Rule-11.6; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
// dirct memory access to uC peripherics
//PRQA S 306 EOF //

CONST_AL ChannelIdMap_t Dio_ChannelMap[] =
{
  /* channel id, port,       pin */
#ifdef LDMO_A0_SAMPLE
  #ifdef SAMPLE_FULL
  { 0U,  PTB,  2U }, // Boost Enable
  { 1U,  PTD,  6U }, // HSS_EN_1
  { 2U,  PTC,  9U }, // HSS_EN_2
  { 3U,  PTC, 12U }, // HSS_EN_3  //TO DO : CHECK IF THIS IS A PWM 
  { 4U,  PTD,  14U }, // HSS_ERROR
  { 5U,  PTB, 11U }, // HSS_SEL_1
  { 6U,  PTD,  7U }, // HSS_SEL_2
  { 7U,  PTE,  7U }, // HSS_SEN
  { 8U,  PTA, 17U }, // DIR_LWR
  { 9U,  PTD, 13U }, // ST_SLEEP
  {10U,  PTE, 14U }, // ST_DRVOFF
  {11U,  PTB, 10U }, // VCCX_EN
  {12U,  PTC, 13U }, // DIR_AHL
  {13U,  PTD, 14U }, // ST_ERROR
  {14U,  PTE, 13U }, // IN_FCT_2_UC // TO DO: CHECK IF THIS IS A PWM
  {15U,  PTE, 15U }, // IMU_ALARMB
  {16U,  PTE, 16U }, // IMU_RESTN

  #elif defined(SAMPLE_ECO)
  { 0U,  PTB,  2U }, // Boost Enable
  { 1U,  PTD,  6U }, // HSS_EN_1
  { 2U,  PTC,  9U }, // DC_EN
  { 3U,  PTE,  7U }, // HSS_SEN
  #endif
#elif defined(LDMO_B0_SAMPLE) 
    #if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  { 0U,  PTE,  9U }, // Boost Enable
  { 1U,  PTD,  6U }, // HSS_EN_1
  { 2U,  PTC,  9U }, // HSS_EN_2
  { 3U,  PTD, 14U }, // HWID_0         NEW NEW NEW
  { 4U,  PTE,  7U }, // HSS_ERROR
  { 5U,  PTB, 11U }, // HSS_SEL_1
  { 6U,  PTD,  7U }, // HSS_SEL_2
  { 7U,  PTA, 12U }, // HSS_SEN
  { 8U,  PTA, 17U }, // DIR_LWR
  { 9U,  PTD,  8U }, // ST_SLEEP
  {10U,  PTE, 14U }, // ST_DRVOFF
  {11U,  PTC, 10U }, // VCCX_EN
  {12U,  PTA, 14U }, // VCCX2_PG        NEW NEW NEW
 // {12U,  PTC, 13U }, // DIR_AHL // UPDATE - DO NOT EXIST ANYMORE !!!
  {13U,  PTD, 10U }, // ST_ERROR
  {14U,  PTE,  3U }, // IN_FCT_2_UC // TO DO: CHECK IF THIS IS A PWM // UPDATE - MAYBE IT's PWM!!!
  {15U,  PTE, 15U }, // IMU_ALARMB
  {16U,  PTE, 16U }, // IMU_RESTN
  {17U,  PTD, 13U }, // HWID_1          NEW NEW NEW
  {18U,  PTC, 12U }, // HSS_EN_3  //TO DO : CHECK IF THIS IS A PWM // UPDATE - IT's PWM!!!

  #elif defined(SAMPLE_ECO) || defined (UNIT_TEST)
  { 0U,  PTE,  9U }, // Boost Enable
  { 1U,  PTD,  6U }, // HSS_EN_1
  { 2U,  PTC,  9U }, // DC_EN
  { 3U,  PTA, 12U }, // HSS_SEN
  #endif
#endif
};
