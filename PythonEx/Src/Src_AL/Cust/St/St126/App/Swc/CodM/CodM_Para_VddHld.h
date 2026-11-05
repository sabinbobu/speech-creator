#ifndef __CODM_PARA_VDDHLD_H__
#define __CODM_PARA_VDDHLD_H__

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
/// \file  NvM_Para_AfsDbl.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author VORNICU Tony - EEG-PM4 (F63906B)
///         mailTo:tony.vornicu@al-lighting.com
//-----------------------------------------------------------------------------


//****************************************************************************
// typedefs
//****************************************************************************

// -----------------------------------------------------------------------------
// AFS VddHldFilterCur3
//   filter configuration for _VddFilterIIR_SWA3
//   Module: VddHldBasic.c
// -----------------------------------------------------------------------------
typedef struct
{
  uint8   ucFilterTrackingTau;           //               PT1 Tracking Filter Tau
  uint8   ucFilterTrackingRange;         //  [0.000025/m] PT1 Tracking Filter Range
  uint8   ucFilterTau;                   //               PT1 Filter Tau
  uint8   ucDummy;                       // 
}tAfsVddHldFilterCur3Struct;

// -----------------------------------------------------------------------------
// AFS VddHld2Parameter
// -----------------------------------------------------------------------------
typedef struct
{         
  uint8   ucMixerV0;                 // [Km/h] V0                             
  uint8   ucCurFilterSize;           // Curvature filter size, input filter size
  uint8   ucCurFilterSizeOpt;        // Curvature filter size, input filter size
  uint8   ucCurFilterTracking;       // Tracking Filter SWA 
  uint8   ucCurFilterTrackingOpt;    // Tracking Filter YR
  uint8   ucCurFilterTrackingTau;    // Tracking Filter TAU
  uint8   ucInvalid;                 // invalid flag
  uint8   ucSteerBackFilter;         // Filter used in case of steering back event detected
  uint8   ucStraightAheadFilter;     // Filter used in case of straight ahead driving 
  uint8   ucHighSpeedFilter;         // Filter used in case of high speed driving situation detected

}tAFSVddHld2ParameterStruct;


typedef struct
{
	tAfsVddHldFilterCur3Struct  VddHldFilterConfig;
	tAFSVddHld2ParameterStruct  VddHldParamConfig;

} tNvmPara_VddHldDataBlock;



#endif // __CODM_PARA_VDDHLD_H__
