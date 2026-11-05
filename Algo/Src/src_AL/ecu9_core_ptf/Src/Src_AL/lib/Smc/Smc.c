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
/// \file  Smc.c
///
/// \brief  State Machine Controller - Implementation
///
/// \descr  Generic State Machine Controller (SMC) library used to implement finite state machines through a configurable
///         state table. Each state may define Entry, Run and Exit callbacks. The module provides initialization, 
///         consistency checks, controlled state transitions and execution of the currently active state.
///
/// \author Luca Bortolotti, Andrea Locatelli
///
//----------------------------------------------------------------------------------------------------------------------

//======================================================================================================================
// Includes
//======================================================================================================================
#include "Smc.h"

//======================================================================================================================
// Private constants
//======================================================================================================================
#define SMC_START_SEC_CONST
#include "Smc_MemMap.h"

#define SMC_STOP_SEC_CONST
#include "Smc_MemMap.h"

//======================================================================================================================
// Private variables
//======================================================================================================================
#define SMC_START_SEC_VAR_INIT
#include "Smc_MemMap.h"

#define SMC_STOP_SEC_VAR_INIT
#include "Smc_MemMap.h"

//======================================================================================================================
// Private functions prototypes
//======================================================================================================================

STATIC FUNC(Smc_ReturnType, SMC_CODE) Smc_IsHandlerConsistent
(
   CONSTP2CONST(Smc_HandlerType, AUTOMATIC, SMC_APPL_CONST)pSmcHandler,
   VAR(Smc_InitStatusType, AUTOMATIC) requiredInitStatus
);


//======================================================================================================================
// Public functions implementation
//======================================================================================================================
#define SMC_START_SEC_CODE
#include "Smc_MemMap.h"

/** @brief Function to initialize a SMC 
*   @param[in] pSmcHandler The SMC handler.
*   @returns A value of @ref Smc_ReturnType
*/
FUNC(Smc_ReturnType, SMC_CODE) Smc_Init
(
   CONSTP2VAR(Smc_HandlerType, AUTOMATIC, SMC_APPL_DATA) pSmcHandler
)
{
   /* Init res value while checking input parameters to check the initialization status consistency */
   Smc_ReturnType res = Smc_IsHandlerConsistent(pSmcHandler, SMC_INIT_STATUS_NOT_INITIALIZED);

   if(SMC_RETURN_OK == res)
   {
      /* Execute the Entry function of the Current State if necessary */
      if(NULL_PTR != pSmcHandler->pStatesList[pSmcHandler->currStateId].pEntry)
      {
         pSmcHandler->pStatesList[pSmcHandler->currStateId].pEntry();
      }

      /* Set initialization status ok */
      pSmcHandler->initStatus = SMC_INIT_STATUS_INITIALIZATION_OK;
   }
  
   return res;
}

/** @brief Function to request a state transition of a specified SMC 
*   @param[in] pSmcHandler The SMC handler
*   @param[in] toStateId The ID of the next state of the SMC (it's the position in the array pStatesList
*                        provided at SMC init call)
*   @returns A value of @ref Smc_ReturnType
*/
FUNC(Smc_ReturnType, SMC_CODE) Smc_StateTransition
(
   CONSTP2VAR(Smc_HandlerType, AUTOMATIC, SMC_APPL_DATA) pSmcHandler,
   VAR(uint8, AUTOMATIC) toStateId
)
{
   /* Init res value while checking input parameters */
   Smc_ReturnType res = Smc_IsHandlerConsistent(pSmcHandler, SMC_INIT_STATUS_INITIALIZATION_OK);
   
   /* Check if the state target of the transition is valid:
   *     - in the range 
   *     - different from the current
   */
   if((toStateId >= pSmcHandler->statesListLen) || (toStateId == pSmcHandler->currStateId))
   {
      res = SMC_RETURN_ERR_IN_PARAM;
   }

   /* Perform the transition */
   if(SMC_RETURN_OK == res)
   {
      /* Execute Exit of previous State if necessary */
      if(NULL_PTR != pSmcHandler->pStatesList[pSmcHandler->currStateId].pExit)
      {
         pSmcHandler->pStatesList[pSmcHandler->currStateId].pExit();
      }

      /* Switch to the new State */
      pSmcHandler->currStateId = toStateId;

      /* Execute Entry of current State if necessary */
      if(NULL_PTR != pSmcHandler->pStatesList[pSmcHandler->currStateId].pEntry)
      {
         pSmcHandler->pStatesList[pSmcHandler->currStateId].pEntry();
      }
   }

   return res;
}

/** @brief Function to run the SMC 
*   @param[in] pSmcHandler The SMC handler
*   @returns A value of @ref Smc_ReturnType
*
*   @note Each time it's called, it performs a step of the SMC. Usually shall be called periodically.
*/
FUNC(Smc_ReturnType, SMC_CODE) Smc_StateRun
(
   CONSTP2CONST(Smc_HandlerType, AUTOMATIC, SMC_APPL_CONST)pSmcHandler
)
{
   /* Init res value while checking input parameters */
   Smc_ReturnType res = Smc_IsHandlerConsistent(pSmcHandler, SMC_INIT_STATUS_INITIALIZATION_OK);
   
   if((SMC_RETURN_OK == res))
   {
      /* Execute the current status, null pointer checked previously in Smc_IsHandlerConsistent() */
      pSmcHandler->pStatesList[pSmcHandler->currStateId].pRun();
   }

   return res;
}

//======================================================================================================================
// Private functions implementation
//======================================================================================================================

/** @brief Function to check the validity of a SMC handler 
*   @param[in] pSmcHandler The SMC handler to check
*   @param[in] requiredInitStatus The SMC initialization status required for the phase
*   @returns A value of @ref Smc_ReturnType
*/
STATIC FUNC(Smc_ReturnType, SMC_CODE) Smc_IsHandlerConsistent
(
   CONSTP2CONST(Smc_HandlerType, AUTOMATIC, SMC_APPL_CONST)pSmcHandler,
   VAR(Smc_InitStatusType, AUTOMATIC) requiredInitStatus
)
{
   /* Return value init */
   Smc_ReturnType res = SMC_RETURN_OK;
   
   /* Check input parameters to check the initialization status consistency:
   *     - pSmcHandler provided not null
   *     - States list array not null and its length is at least 1
   *     - The initial status is included in the possible states array
   */
   if((NULL_PTR == pSmcHandler) ||
      (NULL_PTR == pSmcHandler->pStatesList) || (pSmcHandler->statesListLen < 1u) ||
      (pSmcHandler->currStateId >= pSmcHandler->statesListLen))
   {
      res = SMC_RETURN_ERR_IN_PARAM;
   }

   /* Check the initialization status required for the phase */
   if(requiredInitStatus != pSmcHandler->initStatus)
   {
      res = SMC_RETURN_ERR_INIT_STATUS;
   }

   if(SMC_RETURN_OK == res)
   {
      /* Check if all status are valid */
      for(uint8 i = 0u; i < pSmcHandler->statesListLen; i++)
      {
         if(NULL_PTR == pSmcHandler->pStatesList[i].pRun)
         {
            /* Set Input parameters error and break as one NULL status is enough to validate an error */
            res = SMC_RETURN_ERR_IN_PARAM;
            break;
         }
      }
   }

   return res;
}

#define SMC_STOP_SEC_CODE
#include "Smc_MemMap.h"

//======================================================================================================================
// End of file
//======================================================================================================================
