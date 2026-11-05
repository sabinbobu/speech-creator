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
/// \file   FeeCfg.c
///
/// \brief  COnfiguration of Flash EEPROM EMULATION
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


//#include <Types/Types.h>
//#include <Cfg/Cfg.h>

#include <Std_Types.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Fee.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#define _MAC_EEL_DESCRIPTOR         //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard
//#include <Bsw/MCal/Fee/FeeCfg.h>    //do not include anything, as EEL descriptor is not used
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  _MAC_EEL_DESCRIPTOR




#define _MAC_FEE_BLOCKS             //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Bsw/Mcal/Fee/Fee_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef _MAC_FEE_BLOCKS


#define _MAC_MEMIF_BLOCK_DECLARATION  //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard\
#pragma __attribute__((section(".FlexRAM"))) 
#include <Bsw/Mcal/Fee/Fee_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef _MAC_MEMIF_BLOCK_DECLARATION

