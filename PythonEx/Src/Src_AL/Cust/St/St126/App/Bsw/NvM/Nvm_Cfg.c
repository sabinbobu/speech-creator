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
/// \file   NvmCfg.c
///
/// \brief  Configuration of the NvM module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//#include <Types/Types.h>
//#include <Cfg/Cfg.h>

#include <Std_Types.h>
#include <Nvm.h>

#define _MAC_EEL_DESCRIPTOR           //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard
//#include <Bsw/Nvm/NvmCfg.h>         //do not include as EEL desciptor is no longer present
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  _MAC_EEL_DESCRIPTOR





#define _MAC_DECLARATION              //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Bsw/Nvm/Nvm_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  _MAC_DECLARATION

#define _MAC_NVM_BLOCKS               //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Bsw/Nvm/Nvm_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef _MAC_NVM_BLOCKS



#define _MAC_MEMIF_BLOCK_DECLARATION    //PRQA S 602  //correct reserved ifentifier
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Bsw/Nvm/Nvm_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef _MAC_MEMIF_BLOCK_DECLARATION







