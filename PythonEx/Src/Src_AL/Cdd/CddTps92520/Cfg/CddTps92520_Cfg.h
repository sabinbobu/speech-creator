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
/// \file  CddTps92520_Cfg.h
///
/// \brief  Configuration of CddTps92520 module
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_CFG_2021_01_21_H_
#define CDD_TPS92520_CFG_2021_01_21_H_


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Cfg/Cfg.h>


//-----------------------------------------------------------------------------
// Basic Configuration
//-----------------------------------------------------------------------------

// number of TPS92520 devices
#define CDDTPS92520_Cfg_NbOfDevices 6u


// values needed for projects without calibration data
#define CDDTPS92520_Eft_Calib_Default              \
{                                                  \
  { 0xFFFFFFFFu, { {  3875u, 0 },     /* Chn  1 */ \
                   {  5813u, 0 } } }, /* Chn  2 */ \
  { 0xFFFFFFFFu, { {  3875u, 0 },     /* Chn  3 */ \
                   {  5813u, 0 } } }, /* Chn  4 */ \
  { 0xFFFFFFFFu, { {  3875u, 0 },     /* Chn  5 */ \
                   {  5813u, 0 } } }, /* Chn  6 */ \
  { 0xFFFFFFFFu, { {  3875u, 0 },     /* Chn  7 */ \
                   {  5813u, 0 } } }, /* Chn  8 */ \
  { 0xFFFFFFFFu, { {  5813u, 0 },     /* Chn  9 */ \
                   {  5813u, 0 } } }, /* Chn 10 */ \
  { 0xFFFFFFFFu, { {  5813u, 0 },     /* Chn 11 */ \
                   {  5813u, 0 } } }  /* Chn 12 */ \
}


#if defined (CFG_VARIANT_ECO)

  #define CDDTPS92520_Eft_EcuVarCfg_Default                                     \
  {                                                                             \
  /* Driver                      Output  Pmax   Imax    Imin                 */ \
  {    1u,  255u, 255u, 255u, { {  1u,    20u,  1500u,  200u, 255u, 255u },     \
                                {  2u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    1u,  255u, 255u, 255u, { {  3u,    20u,  1500u,  200u, 255u, 255u },     \
                                {  4u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    0u,  255u, 255u, 255u, { {  0u,     0u,     0u,    0u, 255u, 255u },     \
                                {  0u,     0u,     0u,    0u, 255u, 255u } } }, \
  {    0u,  255u, 255u, 255u, { {  0u,     0u,     0u,    0u, 255u, 255u },     \
                                {  0u,     0u,     0u,    0u, 255u, 255u } } }, \
  {    0u,  255u, 255u, 255u, { {  0u,     0u,     0u,    0u, 255u, 255u },     \
                                {  0u,     0u,     0u,    0u, 255u, 255u } } }, \
  {    0u,  255u, 255u, 255u, { {  0u,     0u,     0u,    0u, 255u, 255u },     \
                                {  0u,     0u,     0u,    0u, 255u, 255u } } }  \
  }

#else // CFG_VARIANT_FULL

  #define CDDTPS92520_Eft_EcuVarCfg_Default                                     \
  {                                                                             \
  /* Driver                      Output  Pmax   Imax    Imin                 */ \
  {    1u,  255u, 255u, 255u, { {  1u,    40u,  1500u,  200u, 255u, 255u },     \
                                {  2u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    1u,  255u, 255u, 255u, { {  3u,    40u,  1500u,  200u, 255u, 255u },     \
                                {  4u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    1u,  255u, 255u, 255u, { {  5u,    40u,  1500u,  200u, 255u, 255u },     \
                                {  6u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    1u,  255u, 255u, 255u, { {  7u,    40u,  1500u,  200u, 255u, 255u },     \
                                {  8u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    1u,  255u, 255u, 255u, { {  9u,    20u,  1000u,  100u, 255u, 255u },     \
                                { 10u,    20u,  1000u,  100u, 255u, 255u } } }, \
  {    1u,  255u, 255u, 255u, { { 11u,    20u,  1000u,  100u, 255u, 255u },     \
                                { 12u,    20u,  1000u,  100u, 255u, 255u } } }  \
  }

#endif


//-----------------------------------------------------------------------------
// Advanced Configuration
//-----------------------------------------------------------------------------
// PWM duty cycle thresholds
#define CDDTPS92520_MinDutyVledOn     1638u  //  5.0% of 32768, minimum PWM for VLED_ON  measurement
#define CDDTPS92520_MaxDutyVledOff   31130u  // 95.0% of 32768, minimum PWM for VLED_OFF measurement
#define CDDTPS92520_ContHiThresh     32735u  // 99.9% of 32768, threshold to interpret PWM signal as continous high

// open load diagnosis
#define CDDTPS92520_OpenLoadDiff      2154u  // [mV] voltage according to 8.5LSB (to switch between 8 and 9 LSBs)

// short to GND diagnosis
#define CDDTPS92520_ShortGndThresh    1647u  // [mV] voltage according to 6.5LSB (to switch between 6 and 7 LSBs)

// detection of low voltage LED chains
#define CDDTPS92520_VoltSingleLed     4750u  // [mV] voltage indicating chain with single LED



#endif // CDD_TPS92520_CFG_2021_01_21_H_
