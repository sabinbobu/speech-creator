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
///         mailTo:johannes.heusel(at)al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Swc/ApplCmd/ApplCmd_Rdm.h>

//=============================================================================
// Public types
//=============================================================================

typedef void* (*tpfnGetVirtData)(uint32* pulSize);



#define MAC_APPLCMD_RDM_ENUM
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmd_RdmCfg.h> 
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_RDM_ENUM

#define APPLCMD_RDM_MAC_DECL_FCT
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmd_RdmCfg.h> 
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  APPLCMD_RDM_MAC_DECL_FCT

#define MAC_APPLCMD_RDM_LIST_CALLBACK
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Swc/ApplCmd/ApplCmd_RdmCfg.h> 
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  MAC_APPLCMD_RDM_LIST_CALLBACK

//============================================================================
// Preprocessor definitions
//=============================================================================

#ifndef APPLCMD_RDM_MESSAGE_OFFSET
  #define APPLCMD_RDM_MESSAGE_OFFSET             (0U)
#endif



#ifdef SUPPORT_RDM_SERVICES

static uint8 DiagR_CalcSrcAddressForVirtID(uint8**          ppSrc,
                                     const tpfnGetVirtData* pfnGetVirtData,
                                           uint32           ulAdr,
                                           uint32           ulNumOfBytes,
                                           uint8            ucMaxTableEntries);


//=============================================================================
// Public functions definition
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  DiagR_ReadMemByAddress
///
/// \descr  
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_Rdm_ReadMemByAddr( MsgContextType *const pMsgContext )
{
  uint8  ResponseCode = 0u;

  const uint8  *pucReqData      = pMsgContext->reqData;
  const uint16 unReqDataLen     = pMsgContext->reqDataLen;
  uint8 *pucResData             = pMsgContext->resData;


  // Evt. hier auch noch mit CallBack Technik arbeiten, fur den Fall das die Ausfuhrung langer dauert.  
  // Read Memory by Address mit Lange null wird ebenfalls positive Acknowledged.

  uint8 ucNumberOfBytesForAdr = pucReqData[0u + APPLCMD_RDM_MESSAGE_OFFSET] & 0x0fu;
  const uint8 ucNumberOfBytesForLen = (pucReqData[0U + APPLCMD_RDM_MESSAGE_OFFSET] >> 4U);
  const uint8 *const pucLenInfo     = &pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] + ucNumberOfBytesForAdr;
  uint32 ulNumOfBytes, ulAdr;
  uint8* pReadAddress = (uint8*) 0u;
  
  ulAdr = (ucNumberOfBytesForAdr == 1U) ? ((uint32)pucReqData[1U]<< 0U) :
    (ucNumberOfBytesForAdr == 2U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<< 8U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
    (ucNumberOfBytesForAdr == 3U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<<16U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET]<< 8U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
    (ucNumberOfBytesForAdr == 4U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<<24U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET]<<16U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET]<< 8U) | ((uint32)pucReqData[4U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
    (uint32)0xffffffffu;

  ulNumOfBytes = (ucNumberOfBytesForLen == 1U) ? ((uint32)pucLenInfo[0U] << 0U) :
    (ucNumberOfBytesForLen == 2U) ? ((uint32)pucLenInfo[0U] << 8U ) | ((uint32)pucLenInfo[1U] << 0U) :
    (ucNumberOfBytesForLen == 3U) ? ((uint32)pucLenInfo[0U] << 16U) | ((uint32)pucLenInfo[1U] << 8U)  | ((uint32)pucLenInfo[2U] << 0U) :
    (ucNumberOfBytesForLen == 4U) ? ((uint32)pucLenInfo[0U] << 24U) | ((uint32)pucLenInfo[1U] << 16U) | ((uint32)pucLenInfo[2U] << 8U) | ((uint32)pucLenInfo[3U] << 0U) :
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
    // do nothing
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

    if ( (boAddressIsInRam == TRUE)    // RAM area
      || (boAddressIsInRom == TRUE)    // ROM area
      || (boAddressIsInReg == TRUE))   // Register area
    {
      // PRQA S 306 1 // correct cast - working with actual address
      pReadAddress = (uint8*)(ulAdr);
    }
    else
    {
      /* User Data? */
      if ( ( RDM_VIRT_ID_BEGIN <= ulAdr ) && ( ulAdr < (RDM_VIRT_ID_END) ))
      {
        ResponseCode = DiagR_CalcSrcAddressForVirtID(&pReadAddress, apfnGetVirtDataUserStructs, ulAdr, ulNumOfBytes, (uint8)eMaxCmdRdmList);
      }
      else
      {
        ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT;
      }
    }

    /* Address is OK? */
    if (pReadAddress != (uint8*) 0)
    {
      pMsgContext->resDataLen = (uint16)ulNumOfBytes;

      while (ulNumOfBytes-- != 0U)
      {
        *pucResData = *pReadAddress;
          pucResData++;  pReadAddress++;
      }
    }
  }

  return ResponseCode;
}


//-----------------------------------------------------------------------------
/// \brief  DiagR_WriteMemByAddress
///
/// \descr  
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros
uint8 ApplCmd_Rdm_WriteMemByAddr( MsgContextType* const pMsgContext )
{
  uint8 ResponseCode = 0;
  const uint8  *pucReqData      = pMsgContext->reqData;
  const uint16 unReqDataLen     = pMsgContext->reqDataLen;

  // Evt. hier auch noch mit CallBack Technik arbeiten, fur den Fall das die Ausfuhrung langer dauert.
  // Write Memory by Address mit Lange 0 wird ebenfalls aktzeptiert, aber 0 Bytes geschrieben.

  {
    const uint8 ucNumberOfBytesForLen = pucReqData[0U + APPLCMD_RDM_MESSAGE_OFFSET] >> 4U;
    const uint8 ucNumberOfBytesForAdr = pucReqData[0U + APPLCMD_RDM_MESSAGE_OFFSET] & 0x0fU;
    const uint8 *const pucLenInfo     = &pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET] + ucNumberOfBytesForAdr;
    uint32 ulNumOfBytes, ulAdr;

    ulAdr = (ucNumberOfBytesForAdr == 1U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
            (ucNumberOfBytesForAdr == 2U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<< 8U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
            (ucNumberOfBytesForAdr == 3U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<<16U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET]<< 8U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
            (ucNumberOfBytesForAdr == 4U) ? ((uint32)pucReqData[1U + APPLCMD_RDM_MESSAGE_OFFSET]<<24U) | ((uint32)pucReqData[2U + APPLCMD_RDM_MESSAGE_OFFSET]<<16U) | ((uint32)pucReqData[3U + APPLCMD_RDM_MESSAGE_OFFSET]<< 8U) | ((uint32)pucReqData[4U + APPLCMD_RDM_MESSAGE_OFFSET]<< 0U) :
            (uint32)0xffffffffU;

    ulNumOfBytes = (ucNumberOfBytesForLen == 1U) ? ((uint32)pucLenInfo[0U] << 0U) :
                   (ucNumberOfBytesForLen == 2U) ? ((uint32)pucLenInfo[0U] << 8U ) | ((uint32)pucLenInfo[1U] << 0U) :
                   (ucNumberOfBytesForLen == 3U) ? ((uint32)pucLenInfo[0U] << 16U) | ((uint32)pucLenInfo[1U] << 8U)  | ((uint32)pucLenInfo[2U] << 0U) :
                   (ucNumberOfBytesForLen == 4U) ? ((uint32)pucLenInfo[0U] << 24U) | ((uint32)pucLenInfo[1U] << 16U) | ((uint32)pucLenInfo[2U] << 8U) | ((uint32)pucLenInfo[3U] << 0U) :
                   (uint32)0xffffffffU;

    if ( (ulAdr == (uint32)0xffffffffU) || (ulNumOfBytes == (uint32)0xffffffffU) )
    {
      ResponseCode = 0x31u /*DCM_E_REQUESTOUTOFRANGE*/;
    }
    else if (unReqDataLen != (uint16)(1U + (uint16)ucNumberOfBytesForAdr + (uint16)ucNumberOfBytesForLen + (uint16)ulNumOfBytes))
    {
      ResponseCode = 0x13u /*DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT*/;
    }
    else
    {
      // do nothing
    }

    if (ResponseCode == 0U)
    {
      const uint8 *pSrc = &pucReqData[1] + ucNumberOfBytesForLen + ucNumberOfBytesForAdr;
      uint8 *pDest = NULL_PTR;

      if( ( RDM_RAM_BEGIN <= ulAdr ) && ( ulAdr < RDM_RAM_END ) )  // RAM area
      {
        // PRQA S 306 1 // correct cast - working with actual address
        pDest = (uint8*)(ulAdr);
      }
      else
      {
        if ( ( RDM_VIRT_ID_BEGIN <= ulAdr ) && ( ulAdr < RDM_VIRT_ID_END ))
        {
          ResponseCode = DiagR_CalcSrcAddressForVirtID(&pDest, apfnGetVirtDataUserStructs, ulAdr, ulNumOfBytes, (uint8)eMaxCmdRdmList);
        }
        else
        {
          ResponseCode = 0x22u; //DCM_E_CONDITIONSNOTCORRECT;
        }
      }

      if (pDest != NULL_PTR)
      {
        // Only Serv-Id as positive reply no further data required.
        pMsgContext->resDataLen = (uint16)0;
        while (ulNumOfBytes-- != 0U)
        {
          *pDest = *pSrc;
            pDest++;  pSrc++;
        }
      }
    }
  }
  return ResponseCode;
}


//-----------------------------------------------------------------------------
/// \brief  DiagR_CalcSrcAddressForVirtID
///
/// \descr  
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------

//=============================================================================
// Private functions definition
//=============================================================================

static uint8 DiagR_CalcSrcAddressForVirtID(uint8**          ppSrc,
                                     const tpfnGetVirtData* pfnGetVirtData,
                                           uint32           ulAdr,
                                           uint32           ulNumOfBytes,
                                           uint8            ucMaxTableEntries)
{
  uint8 ResponseCode = 0x22;
  uint8 ucVirtID         = (uint8)((ulAdr >> RDM_BITPOS_VIRT_ID) & RDM_VIRT_ID_MASK);
  uint16 ulAddressOffset = (uint16)(ulAdr &  RDM_ADDROFFSET_MASK);

  /* ID is in range? */
  if(ucVirtID < ucMaxTableEntries)
  {
      uint32 ulSize = 0;
      uint8* pucStartAddress = (uint8*)0;

      /* Check if entry exists in table. Reserved entries have NULL as value. */
      if (pfnGetVirtData[ucVirtID] != NULL_PTR)
      {
          /* Get the start address. */
          pucStartAddress = (uint8*)(pfnGetVirtData[ucVirtID])(&ulSize);
      }
      /* Verify address and length. */
      if ( (pucStartAddress != (uint8*)0) &&
         ( (ulAddressOffset + ulNumOfBytes) <= ulSize) )
      {

          *ppSrc = (uint8*)&pucStartAddress[ulAddressOffset];

          ResponseCode = 0;
      }
  }
  return ResponseCode;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  ApplCmd_Rdm_StartSession
///
/// \descr  
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros

//=============================================================================
// Public functions definition
//=============================================================================

// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_Rdm_StartSession( MsgContextType *const pMsgContext )
{
  uint8 cnt = 0U;
  
  pMsgContext->resData[cnt++] = pMsgContext->reqData[0];
  pMsgContext->resData[cnt++] = 0xFFu; // P2SERVER_MAX  MSB
  pMsgContext->resData[cnt++] = 0xFFu; // P2SERVER_MAX  LSB
  pMsgContext->resData[cnt++] = 0xFFu; // P2STRSERVER_MAX/10 MSB
  pMsgContext->resData[cnt++] = 0xFFu; // P2STRSERVER_MAX/10 LSB
	pMsgContext->resDataLen = cnt;
		
	return 0U;
}

//-----------------------------------------------------------------------------
/// \brief  ApplCmd_Rdm_SecurityAccess
///
/// \descr  
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_Rdm_SecurityAccess( MsgContextType *const pMsgContext )
{  
  uint8 cnt = 0U;
   
  pMsgContext->resData[cnt++] = pMsgContext->reqData[0U + APPLCMD_RDM_MESSAGE_OFFSET];
  pMsgContext->resData[cnt++] = pMsgContext->reqData[1U + APPLCMD_RDM_MESSAGE_OFFSET];
  pMsgContext->resData[cnt++] = pMsgContext->reqData[2U + APPLCMD_RDM_MESSAGE_OFFSET];
  pMsgContext->resData[cnt++] = 0U;  // Result code 0: No Erro
  pMsgContext->resDataLen = cnt;
	
	return 0U;
}
