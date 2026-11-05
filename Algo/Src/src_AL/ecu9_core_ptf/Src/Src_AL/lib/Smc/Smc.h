//**********************************************************************************************************************
// (C) Automotive Lighting Tolmezzo
//     <Site Address>
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Tolmezzo.
//**********************************************************************************************************************

//----------------------------------------------------------------------------------------------------------------------
/// \file  Smc.h
///
/// \brief  State Machine Controller - Header File
///
/// \author Luca Bortolotti, Andrea Locatelli
///
//----------------------------------------------------------------------------------------------------------------------

#ifndef SMC_H
#define SMC_H

//======================================================================================================================
// Includes
//======================================================================================================================
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Rte_Compiler_Cfg.h"

//======================================================================================================================
// Public preprocessor definitions
//======================================================================================================================

//======================================================================================================================
// Public typedefs
//======================================================================================================================

/** @brief Module return possible values */
typedef enum
{
   SMC_RETURN_OK,                       /**< Return NoError generic */
   SMC_RETURN_ERR_IN_PARAM,             /**< Return Error specific: Worong Init Parameters */
   SMC_RETURN_ERR_INIT_STATUS,          /**< Return Error specific: Wrong Initialization Status */
   SMC_RETURN_ERR_GENERIC               /**< Return Error generic */
}Smc_ReturnType;

/** @brief Initialization status of a SMC */
typedef enum
{
   SMC_INIT_STATUS_NOT_INITIALIZED,     /**< Value of the init status of a SMC when it has not been initialized */
   SMC_INIT_STATUS_INITIALIZATION_OK    /**< Value of the init status of a SMC when it has been initialized */
}Smc_InitStatusType;

/** @brief State function pointer type definition */
typedef void (*Smc_StateFuncPtr_t)(void);

/** @brief Module Sate Representation
*   @details Entry and Exit Pointer can be NULL, but Run shall not.
*            At startup, and every time a status change is required, Exit function of the current active status and
*            Entry function of the next active satus are called just before execute the next active status Run function
*/
typedef struct
{
   Smc_StateFuncPtr_t const pEntry;        /**< Pointer to the Entry function of the state */
   Smc_StateFuncPtr_t const pRun;          /**< Pointer to the Run function of the state */
   Smc_StateFuncPtr_t const pExit;         /**< Pointer to the Exit function of the state */
}Smc_StateType;

/** @brief SMC handler */
typedef struct
{
   Smc_InitStatusType initStatus;             /**< The variable to keep track of the init status of the SMC */
   Smc_StateType const *const pStatesList;    /**< List of the possible States */
   uint8 const statesListLen;                 /**< List of the possible Staus Lenght */
   uint8 currStateId;                         /**< Current Active States */
}Smc_HandlerType;

//======================================================================================================================
// Public constants
//======================================================================================================================

//======================================================================================================================
// Public variables
//======================================================================================================================

//======================================================================================================================
// Public functions prototypes
//======================================================================================================================

FUNC(Smc_ReturnType, SMC_CODE) Smc_Init
(
   CONSTP2VAR(Smc_HandlerType, AUTOMATIC, SMC_APPL_DATA) pSmcHandler
);

FUNC(Smc_ReturnType, SMC_CODE) Smc_StateTransition
(
   CONSTP2VAR(Smc_HandlerType, AUTOMATIC, SMC_APPL_DATA) pSmcHandler,
   VAR(uint8, AUTOMATIC) toStateId
);

FUNC(Smc_ReturnType, SMC_CODE) Smc_StateRun
(
   CONSTP2CONST(Smc_HandlerType, AUTOMATIC, SMC_APPL_CONST)pSmcHandler
);


#endif  /* SMC_H */

//======================================================================================================================
// End of file
//======================================================================================================================
