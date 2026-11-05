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
/// \file  RSens_Data.c
///
/// \brief Thermo profiles for NTCs and LMM
///
//-----------------------------------------------------------------------------

#include <Al_Helper.h>
#include <RSens_Types.h>
#include <RSens.h>

#define RSENS_THERMO_PROFILE_NTC_B4000        0u
#define RSENS_THERMO_PROFILE_NTC_B3650        1u
#define RSENS_THERMO_PROFILE_NTC_B3380        2u
#define RSENS_THERMO_NR_PROFILE_NTC           3u
#define RSENS_THERMO_PROFILE_LMM              0u

NtcTables RSens_Data_asnNTCB4000 =
{
  {-40, 3883, 3775},
  {  0, 3540, 3375},
  { 25, 2872, 2819},
  { 60, 1573, 1353},
  { 80,  993,  831},
  {100,  612,  502},
  {120,  379,  307},
  {150,  194,  156}
};

NtcTables RSens_Data_asnNTCB3650 =
{
  {-40, 3870, 3760},
  {  0, 3501, 3332},
  { 25, 2872, 2804},
  { 60, 1690, 1463},
  { 80, 1135,  955},
  {100,  744,  614},
  {120,  488,  399},
  {150,  269,  217}
};

NtcTables RSens_Data_asnNTCB3380 =
{
  {-40, 3857, 3744},
  {  0, 3470, 3296},
  { 25, 2872, 2792},
  { 60, 1782, 1550},
  { 80, 1252, 1060},
  {100,  860,  714},
  {120,  590,  484},
  {150,  344,  279}
};

NtcTables RSens_Data_asnLMM =
{                  // ADC LMM Values
  {-40, 4941, 4941 /*252*/},
  {  0, 4412, 4412 /*225*/},
  { 25, 3412, 3412 /*174*/},
  { 60, 1725, 1725 /*88 */},
  { 80, 1059, 1059 /*54 */},
  {100, 627 , 627  /*32 */},
  {120, 392 , 392  /*20 */},
  {150, 196 , 196  /*10 */}
};  // temperature curve from coding

NtcTables *RSens_Data_apsnNTC[] = { &RSens_Data_asnNTCB4000, &RSens_Data_asnNTCB3650, &RSens_Data_asnNTCB3380, &RSens_Data_asnLMM };
