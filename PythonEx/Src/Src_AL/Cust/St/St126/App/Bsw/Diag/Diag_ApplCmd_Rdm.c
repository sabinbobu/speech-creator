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
/// \file  Diag_ApplCmd_Rdm.c
///
/// \brief
///
/// \descr 
///
///
/// \author Emanuel Baba (F31202D)
///         mailTo: emanuel.baba[at]marelli.com
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <Diag_ApplCmd_Rdm.h>
#include <AL_Helper.h>

typedef void* (*tpfnGetVirtData)(uint32* pulSize);
//PRQA S 602 1 // special definition used with X macro generator
#define _MAC_APPLCMD_RDM_ENUM
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Diag_ApplCmd_RdmCfg.h> 
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  _MAC_APPLCMD_RDM_ENUM

#define APPLCMD_RDM_MAC_DECL_FCT
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Diag_ApplCmd_RdmCfg.h> 
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  APPLCMD_RDM_MAC_DECL_FCT

//PRQA S 602 1 // special definition used with X macro generator
#define _MAC_APPLCMD_RDM_LIST_CALLBACK
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Diag_ApplCmd_RdmCfg.h> 
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  _MAC_APPLCMD_RDM_LIST_CALLBACK


#ifndef APPLCMD_RDM_MESSAGE_OFFSET
  #define APPLCMD_RDM_MESSAGE_OFFSET             (0U)
#endif

//extern uint32 Gpt_tySystemTick;


#ifdef SUPPORT_RDM_SERVICES

STATIC_AL uint8 DiagR_CalcSrcAddressForVirtID(uint8**          ppSrc,
                                     const tpfnGetVirtData* pfnGetVirtData,
                                           uint32           ulAdr,
                                           uint32           ulNumOfBytes,
                                           uint8            ucMaxTableEntries);

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

volatile uint32 ApplCmd_Rdm_ulMcuPrivStatus = 0u;

#endif


//-----------------------------------------------------------------------------
/// \brief  ApplCmd_Rdm_ReadMemByAddr
///
/// \descr  This function reads data of a specific size from a specific address
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return -ResponseCode: it returns a response code 
//-----------------------------------------------------------------------------
uint8  ApplCmd_Rdm_ReadMemByAddr(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  uint8  ResponseCode = 0u;
  const uint8  *pucReqData      = p_ui8_Data;
  const uint16 unReqDataLen     = Length;
  uint16 unDataLength = 0u;

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

  boolean boIsMcuPrivilege = TRUE;

  ApplCmd_Rdm_GetMcuPrivilegeStatus();

  if(ApplCmd_Rdm_ulMcuPrivStatus == 0u)
  {
    ApplCmd_Rdm_PrivilegeSwitch();
    boIsMcuPrivilege = FALSE;
  }
  else
  {
    // MCU is in Privilege already
  }

#endif

   //Evt. hier auch noch mit CallBack Technik arbeiten, fur den Fall das die Ausfuhrung langer dauert.  
   //Read Memory by Address mit Lange null wird ebenfalls positive Acknowledged.

  uint8 ucNumberOfBytesForAdr = pucReqData[0u + APPLCMD_RDM_MESSAGE_OFFSET] & 0x0fu;
  const uint8 ucNumberOfBytesForLen = (pucReqData[0U + APPLCMD_RDM_MESSAGE_OFFSET] >> 4U);
  const uint8 *const pucLenInfo     = &pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] + ucNumberOfBytesForAdr;
  uint32 ulNumOfBytes, ulAdr;
  uint8* pReadAddress = (uint8*) 0u;
  
  ulAdr = (ucNumberOfBytesForAdr == 1U) ? ((uint32)pucReqData[1] << 0U) :
    (ucNumberOfBytesForAdr == 2U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] <<  8U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET] <<  0U) :
    (ucNumberOfBytesForAdr == 3U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] << 16U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET] <<  8U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET] << 0U) :
    (ucNumberOfBytesForAdr == 4U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] << 24U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET] << 16U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET] << 8U) | ((uint32)pucReqData[4U + APPLCMD_RDM_MESSAGE_OFFSET] << 0U) :
    (uint32)0xffffffffu;

  ulNumOfBytes = (ucNumberOfBytesForLen == 1U) ? ((uint32)pucLenInfo[0] << 0U) :
    (ucNumberOfBytesForLen == 2U) ? ((uint32)pucLenInfo[0] <<  8U) | ((uint32)pucLenInfo[1] <<  0U) :
    (ucNumberOfBytesForLen == 3U) ? ((uint32)pucLenInfo[0] << 16U) | ((uint32)pucLenInfo[1] <<  8U) | ((uint32)pucLenInfo[2] << 0U) :
    (ucNumberOfBytesForLen == 4U) ? ((uint32)pucLenInfo[0] << 24U) | ((uint32)pucLenInfo[1] << 16U) | ((uint32)pucLenInfo[2] << 8U) | ((uint32)pucLenInfo[3] << 0U) :
    (uint32)0xffffffffu;

  if ( (ulAdr == (uint32)0xffffffffu) || (ulNumOfBytes == (uint32)0xffffffffu) )
  {
    ResponseCode = 0x31u; //DCM_E_REQUESTOUTOFRANGE;
  }
  else if (unReqDataLen != (uint16)(1U + (uint16)ucNumberOfBytesForAdr + (uint16)ucNumberOfBytesForLen))
  {
    ResponseCode = 0x13u; //DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    //nothing to do
  }

  if (ResponseCode == 0u /*DCM_E_OK*/)
  {
    const boolean boAddressIsInRam = (boolean) ((( RDM_RAM_BEGIN <= ulAdr ) && ( ulAdr < RDM_RAM_END )) ? TRUE : FALSE);
    const boolean boAddressIsInReg = (boolean) ((( RDM_REG_BEGIN <= ulAdr ) && ( ulAdr < RDM_REG_END )) ? TRUE : FALSE);

    #if(RDM_ROM_BEGIN > 0U)
    const boolean boAddressIsInRom = (boolean) ((( RDM_ROM_BEGIN <= ulAdr ) && ( ulAdr < RDM_ROM_END )) ? TRUE : FALSE);
    #else
    const boolean boAddressIsInRom = (boolean) ((ulAdr < RDM_ROM_END ) ? TRUE : FALSE);
    #endif

    if ( ( boAddressIsInRam == TRUE )   // RAM area
      || ( boAddressIsInRom == TRUE )   // ROM area
      || ( boAddressIsInReg == TRUE ))  // Register area
    {
      pReadAddress = (uint8*)(ulAdr); //PRQA S 306 1 // direct memory access
    }
    else
    {
#if 0
      /* User Data? */
      if ( ( RDM_VIRT_ID_BEGIN <= ulAdr ) && ( ulAdr < RDM_VIRT_ID_END ))
      {
        ResponseCode = DiagR_CalcSrcAddressForVirtID(&pReadAddress, apfnGetVirtDataUserStructs, ulAdr, ulNumOfBytes, (uint8)eMaxCmdRdmList);
      }
      else
      {
        ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT;
      }
#endif
      ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT;
    }

    /* Address is OK? */
    if (pReadAddress != (uint8*) 0)
    {
      unDataLength = (uint16)ulNumOfBytes;
      uint8 aucResData[63];
      uint8 *pucResData = aucResData;
      while (ulNumOfBytes-- > 0U)
      {
         *pucResData = *pReadAddress;
          pucResData++;  pReadAddress++;
      }

     (void)DIAG_Send_Diag_Response(aucResData, unDataLength);

    }
    else
    {
      ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  else
  {
    // Keep last ResponseCode (DCM_E_REQUESTOUTOFRANGE || DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT)
  }

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

  // Switch back to user mode
  if (boIsMcuPrivilege == FALSE)
  {
    ApplCmd_Rdm_UserSwitch();
  }

#endif

  return ResponseCode;
  // PRQA S 5310 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  ApplCmd_Rdm_WriteMemByAddr
///
/// \descr  This function writes data of a specific size to a specific address
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return -ResponseCode: it returns a response code
//-----------------------------------------------------------------------------
uint8 ApplCmd_Rdm_WriteMemByAddr(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  uint8 ResponseCode = 0U;
  const uint8  *pucReqData      = p_ui8_Data;
  const uint16 unReqDataLen     = Length;
  uint16 unResponseLength = 0U;
  // Evt. hier auch noch mit CallBack Technik arbeiten, fur den Fall das die Ausfuhrung langer dauert.
  // Write Memory by Address mit Lange 0 wird ebenfalls aktzeptiert, aber 0 Bytes geschrieben.

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

  boolean boIsMcuPrivilege = TRUE;

  ApplCmd_Rdm_GetMcuPrivilegeStatus();

  if(ApplCmd_Rdm_ulMcuPrivStatus == 0u)
  {
    ApplCmd_Rdm_PrivilegeSwitch();
    boIsMcuPrivilege = FALSE;
  }
  else
  {
    // MCU is in Privilege already
  }

#endif

  {
    const uint8 ucNumberOfBytesForLen = pucReqData[0U + APPLCMD_RDM_MESSAGE_OFFSET] >> 4U;
    const uint8 ucNumberOfBytesForAdr = pucReqData[0U + APPLCMD_RDM_MESSAGE_OFFSET] & 0x0fU;
    const uint8 *const pucLenInfo     = &pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] + ucNumberOfBytesForAdr;
    uint32 ulNumOfBytes, ulAdr;

    ulAdr = (ucNumberOfBytesForAdr == 1U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] <<  0U) :
            (ucNumberOfBytesForAdr == 2U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] <<  8U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET] <<  0U) :
            (ucNumberOfBytesForAdr == 3U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] << 16U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET] <<  8U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET] << 0U) :
            (ucNumberOfBytesForAdr == 4U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] << 24U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET] << 16U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET] << 8U) | ((uint32)pucReqData[4U + APPLCMD_RDM_MESSAGE_OFFSET] << 0U) :
            (uint32)0xffffffffu;

    ulNumOfBytes = (ucNumberOfBytesForLen == 1U) ? ((uint32)pucLenInfo[0] <<  0U) :
                   (ucNumberOfBytesForLen == 2U) ? ((uint32)pucLenInfo[0] <<  8U) | ((uint32)pucLenInfo[1] <<  0U) :
                   (ucNumberOfBytesForLen == 3U) ? ((uint32)pucLenInfo[0] << 16U) | ((uint32)pucLenInfo[1] <<  8U) | ((uint32)pucLenInfo[2] << 0U) :
                   (ucNumberOfBytesForLen == 4U) ? ((uint32)pucLenInfo[0] << 24U) | ((uint32)pucLenInfo[1] << 16U) | ((uint32)pucLenInfo[2] << 8U) | ((uint32)pucLenInfo[3] << 0U) :
                   (uint32)0xffffffffu;

    if ( (ulAdr == (uint32)0xffffffffu) || (ulNumOfBytes == (uint32)0xffffffffu) )
    {
      ResponseCode = 0x31u /*DCM_E_REQUESTOUTOFRANGE*/;
    }
    else if (unReqDataLen != (uint16)(1U + (uint32)ucNumberOfBytesForAdr + (uint32)ucNumberOfBytesForLen + ulNumOfBytes))
    {
      ResponseCode = 0x13u /*DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT*/;
    }
    else
    {
      //nothing to do
    }

    if (ResponseCode == 0U)
    {
      const uint8 *pSrc = &pucReqData[1] + ucNumberOfBytesForLen + ucNumberOfBytesForAdr;
      uint8 *pDest = NULL_PTR;

      if( ( RDM_RAM_BEGIN <= ulAdr ) && ( ulAdr < RDM_RAM_END ) )  // RAM area
      {
        pDest = (uint8*)(ulAdr); // PRQA S 306 1 // direct memory access
      }
      else
      { 
#if 0
        if ( ( RDM_VIRT_ID_BEGIN <= ulAdr ) && ( ulAdr < RDM_VIRT_ID_END ))
        {

          // PRQA S 4424 1 // enumeration type used to automatically generate maximum size of entries during X macro generator
          ResponseCode = DiagR_CalcSrcAddressForVirtID(&pDest, apfnGetVirtDataUserStructs, ulAdr, ulNumOfBytes, (uint8)eMaxCmdRdmList); 
        }
        else
        {
          ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT;
        }
#endif
        ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT
      }

      if (pDest != NULL_PTR)
      {
        // Only Serv-Id as positive reply no further data required.
        unResponseLength = (uint16)0;
        while (ulNumOfBytes-- > 0U)
        {
          *pDest = *pSrc;
            pDest++;  pSrc++;
        }

        (void) DIAG_Send_Diag_Response(NULL_PTR, unResponseLength);
      }
      else
      {
        ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT
      }
    }
    else
    {
      // Keep last ResponseCode (DCM_E_REQUESTOUTOFRANGE || DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT)
    }
  }

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

  // Switch back to user mode
  if (boIsMcuPrivilege == FALSE)
  {
    ApplCmd_Rdm_UserSwitch();
  }

#endif

  return ResponseCode;
} // PRQA S 5310 1 // architecture, library

#if 0
//-----------------------------------------------------------------------------
/// \brief  DiagR_CalcSrcAddressForVirtID
///
/// \descr  This function compute an address for a virtual location
///
/// \param  -ppSrc: Source address
///         -pfnGetVirtData: Pointer to a function used to get data
///         -ulAdr: Address
///         -ulNumOfBytes: Bytes number
///         -ucMaxTableEntries:
///
/// \return -ResponseCode: it returns a response code
//-----------------------------------------------------------------------------
STATIC_AL uint8 DiagR_CalcSrcAddressForVirtID(uint8**          ppSrc,
    const tpfnGetVirtData* pfnGetVirtData,
    uint32           ulAdr,
    uint32           ulNumOfBytes,
    uint8            ucMaxTableEntries)
{
    uint8 ResponseCode = 0x22;
    uint8 ucVirtID = (uint8)((ulAdr >> RDM_BITPOS_VIRT_ID) & RDM_VIRT_ID_MASK);
    uint16 ulAddressOffset = (uint16)(ulAdr &  RDM_ADDROFFSET_MASK);

    /* ID is in range? */
    if (ucVirtID < ucMaxTableEntries)
    {
        uint32 ulSize = 0;
        uint8* pucStartAddress = (uint8*)0;

        /* Check if entry exists in table. Reserved entries have NULL as value. */
        if (pfnGetVirtData[ucVirtID] != NULL_PTR)
        {
            /* Get the start address. */
            pucStartAddress = (uint8*)(pfnGetVirtData[ucVirtID])(&ulSize);
        }
        else
        {
            //nothing to do
        }
        /* Verify address and length. */
        if ((pucStartAddress != (uint8*)0) &&
            ((ulAddressOffset + ulNumOfBytes) <= ulSize))
        {

            *ppSrc = (uint8*)&pucStartAddress[ulAddressOffset];

            ResponseCode = 0;
        }
        else
        {
            //nothing to do
        }
    }
    else
    {
        //nothing to do
    }
    return ResponseCode;
}

#endif 

#endif

uint8  ApplCmd_Rdm_StartSession( MsgContextType *const pMsgContext )
{
  (void)pMsgContext;

  return 0U;
}

uint8  ApplCmd_Rdm_SecurityAccess( MsgContextType *const pMsgContext )
{
  (void)pMsgContext;

  return 0U;
}

void* Diag_GetVirtData_OsSystemCounter(uint32* pulSize)
{
  (void)pulSize;

  return NULL_PTR;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_GetMcuPrivilegeStatus
///
/// \descr Get Core Master Privilege bit from control register
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ApplCmd_Rdm_GetMcuPrivilegeStatus(void)
{
#ifndef UNIT_TEST
  // ASM routine
  __asm volatile
  (
    " push {r0-r1}                              \n"
    " mrs r0, control                           \n"
    " ldr r1, =ApplCmd_Rdm_ulMcuPrivStatus    \n"
    " eor r0, r0, #~0x0                         \n"
    " and r0, r0, #0x1                          \n"
    " str r0, [r1]                              \n"
    " pop {r0-r1}                               \n"
    );
#endif
  // PRQA S 5334 1 // program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief ApplCmd_Rdm_UserSwitch
///
/// \descr Set Core Master Handler (USER) mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ApplCmd_Rdm_UserSwitch(void)
{
#ifndef UNIT_TEST
  // ASM routine
  __asm volatile
  (
    " push {r0}                        \n"
    " mrs r0, control                  \n"
    " orr r0, r0, #0x1                 \n"
    " msr control, r0                  \n"
    " pop {r0}                         \n"
    );
#endif
  // PRQA S 5334 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief ApplCmd_Rdm_PrivilegeSwitch
///
/// \descr Set Core Master Privilege (PRIVILEGE) mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ApplCmd_Rdm_PrivilegeSwitch(void)
{
#ifndef UNIT_TEST
  // ASM routine
  __asm volatile
  (
    " push {r12}                                \n"
    " ldr r12, =ApplCmd_Rdm_PrivilegeUpdate   \n"
    // System call for supervison switch
    " svc #0x0                                  \n"
    " pop {r12}                                 \n"
    );
#endif
  // PRQA S 5334 1 // program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief ApplCmd_Rdm_PrivilegeUpdate
///
/// \descr Privilege update in control register, routine called by SVC_Handler (System Call)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ApplCmd_Rdm_PrivilegeUpdate(void)
{
#ifndef UNIT_TEST
  // ASM routine
  __asm volatile
  (
    " push {r0}                        \n"
    " mrs r0, control                  \n"
    " and r0, r0, #~0x1                \n"
    " msr control, r0                  \n"
    " pop {r0}                         \n"
    );
#endif
  // PRQA S 5334 1 // program architecture and readability
}
