#ifndef __AVAC_DATA_H__
#define __AVAC_DATA_H__

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
/// \file  AvacData.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen@al-lighting.com
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h>
//#include <Bsw/Nvm/Nvm.h> TO DO
#include <Swc/AfsMaster/Avac/AvacTypes.h>

#ifdef UNIT_TEST

#define bool	_Bool

#endif

// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------
//extern const tNvmPara_CodingArea*   AvacData_pCodingArea;
extern boolean                      AvacData_boCodingValid; 
extern boolean                      AvacData_boPitchConfigValid;
extern uint8                        AvacData_ucFilterStatic;
extern uint8                        AvacData_ucGradientLimiterUp;
extern uint8                        AvacData_ucGradientLimiterDown;
extern tNvmPara_AvacStpBlock        AvacData_CodingData;

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void AvacData_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData);
void AvacData_Init(void);
boolean AvacData_GetLowBeamOn(void);
boolean AvacData_GetAvacD_Ok(void);
boolean AvacData_GetAvacD_En(void);
boolean AvacData_GetAvacS_Ok(void);
boolean AvacData_GetAvacS_En(void);

void AvacData_ReadPitch(tAvac_Pitch* pPitch);
void AvacData_ReadSpeed(tAvac_Speed* pSpeed);
void AvacData_ReadAccelPreDetect(tAvac_AccelPreDetect* pAccelPreDetect);
void AvacData_ReadBrakePreDetect(tAvac_BrakePreDetect* pBrakePreDetect);
void AvacData_WriteAvacOut(const tAvac_Out* pAvacOut);

extern Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
extern Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1);
extern Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
// ----------------------------------------------------------------------------
// AvacCodingData
// ----------------------------------------------------------------------------


INLINE boolean  AvacData_GetCodingValid(void)           {return AvacData_boCodingValid;}
INLINE boolean  AvacData_GetPitchConfigValid(void)      {return AvacData_boPitchConfigValid;}

INLINE uint8 Cod_AvacStpEnable(void)                    {return  AvacData_CodingData.Modus.ucAvacStp_Enable;}

INLINE uint8 Cod_AvacFilterUpMax(void)                  {return  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMax;}
INLINE uint8 Cod_AvacFilterUpMid(void)                  {return  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMid;}
INLINE uint8 Cod_AvacFilterUpMin(void)                  {return  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMin;}

INLINE uint8 Cod_AvacFilterDownMax(void)                {return  AvacData_CodingData.AvacFilter.AvacStp_FilterDownMax;}
INLINE uint8 Cod_AvacFilterDownMid(void)                {return  AvacData_CodingData.AvacFilter.AvacStp_FilterDownMid;}
INLINE uint8 Cod_AvacFilterDownMin(void)                {return  AvacData_CodingData.AvacFilter.AvacStp_FilterDownMin;}

INLINE uint8 Cod_AvacBadStreetTolerance()               {return  4/*NvmBlockDavacPara.BadStreetTolerance*/;}
INLINE uint8 Cod_AvacHighDynamicLimit()                 {return  AvacData_CodingData.AvacFilter.AvacStp_HighDynamicLimit;}

INLINE sint8 Cod_AvacAccelPreDetectThresholdUp(void)    {return    5/*NvmBlockDavacPara.AccelPreDetectThresholdUp*/  ;}
INLINE sint8 Cod_AvacAccelPreDetectThresholdDown(void)  {return  -10/*NvmBlockDavacPara.AccelPreDetectThresholdDown*/;}
INLINE sint8 Cod_AvacBrakePreDetectThresholdUp(void)    {return    1/*NvmBlockDavacPara.BrakePreDetectThresholdUp*/  ;}
INLINE sint8 Cod_AvacBrakePreDetectThresholdDown(void)  {return   -1/*NvmBlockDavacPara.BrakePreDetectThresholdDown*/;}

INLINE uint8 Cod_AvacFilterStatic(void)                 { return AvacData_ucFilterStatic;        }
INLINE uint8 Cod_AvacGradientLimiterUp(void)            { return AvacData_ucGradientLimiterUp;   }
INLINE uint8 Cod_AvacGradietnLimiterDown(void)          { return AvacData_ucGradientLimiterDown; }

#endif // __AVAC_DATA_H__
