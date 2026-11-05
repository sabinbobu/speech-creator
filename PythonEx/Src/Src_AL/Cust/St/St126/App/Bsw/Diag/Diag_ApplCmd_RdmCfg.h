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
/// \file  ApplCmd_Rdm.c
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Heusel Johannes ALDE-RT/EEG-PM2 (F89037A)
///         mailTo:johannes.heusel@al-lighting.com
//-----------------------------------------------------------------------------
#include <Diag_ApplCmd_RdmTypes.h>
#include <Cfg/Cfg.h>

//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Diag_ApplCmd_RdmMac.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard

//#include <Cfg/CfgPrj.h>

#define SUPPORT_RDM_SERVICES

#define RDM_BITPOS_VIRT_ID  12U
#define RDM_ADDROFFSET_MASK 0x00000FFFU //(2^RDM_BITPOS_VIRT_ID - 1)

#define RDM_VIRT_ID_BITS    5U
#define RDM_VIRT_ID_MASK    0x0000001FU  //(2^RDM_VIRT_ID_BITS - 1)

#if defined (SAMPLE_FULL) 

#define RDM_ROM_BEGIN       0x00000000U
#define RDM_ROM_END         0x000FFFFFU

#define RDM_RAM_BEGIN       0x1FFF0000U
#define RDM_RAM_END         0x2000EFFFU

#define RDM_REG_BEGIN       0x400FF000U
#define RDM_REG_END         0x400FF000U


#elif  defined(SAMPLE_ECO)

#define RDM_ROM_BEGIN       0x00000000U
#define RDM_ROM_END         0x0007FFFFU

#define RDM_RAM_BEGIN       0x1FFF8000U
#define RDM_RAM_END         0x20006FFFU

#define RDM_REG_BEGIN       0x400FF000U
#define RDM_REG_END         0x400FF000U


#elif defined  (UNIT_TEST)
#define RDM_ROM_BEGIN       0x00000000U
#define RDM_ROM_END         0xFFFFFFF0U

#define RDM_RAM_BEGIN       0x00000000U
#define RDM_RAM_END         0xFFFFFFF0U

#define RDM_REG_BEGIN       0x00000000U
#define RDM_REG_END         0xFFFFFFF8U

#endif

#define RDM_VIRT_ID_BEGIN   0x00FC0000U
#define RDM_VIRT_ID_END     (RDM_VIRT_ID_BEGIN + (uint32)((uint32)((uint32)RDM_VIRT_ID_MASK + 1U) << RDM_BITPOS_VIRT_ID))


#ifdef SUPPORT_RDM_SERVICES
  BEGIN_APPLCMD_RDM_LIST_MAP
    APPLCMD_RDM_CFG(Diag_GetVirtData_OsSystemCounter)
    //APPLCMD_RDM_CFG( DiagR_GetVirtData_Led_FanOn           )
    //APPLCMD_RDM_CFG( DiagR_GetVirtData_LedInit_CtrlTx      )

  END_APPLCMD_RDM_LIST_MAP
#endif

