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
/// \file  ApplCmd.c
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

// PRQA S 306 EOF // Direct memory access required
#include <Swc/ApplCmd/ApplCmd_AlFlasher.h>
#include <string.h>               /* memcpy, memcmp, ...                      */
#include <Bsw/Com/ComBuf/ComBuf.h>            
#include <Swc/ApplCmd/ApplCmd_AlFlasherCfg.h>
#include <Can.h>
#include <Swc/Appl/Appl.h>

//=============================================================================
//typedefs 
//=============================================================================
typedef void(*function_type)(void);

//=============================================================================
//setting section for EcuInformation 
//=============================================================================
//#pragma segment DATA=USER_DATA ????no section at the moment. Usage of this feature unclear.
static uint32 EftEcuInformation;
// #pragma segment DATA=DATA    ??????


//=============================================================================
// Variable declaration extern 
//=============================================================================
//extern char __ghsbegin_SBL_AREA[], __ghsend_SBL_AREA[];

//=============================================================================
// Variable declaration intern 
//=============================================================================
static boolean boCrcOk          = FALSE;


//=============================================================================
// function prototypes internal 
//=============================================================================
static uint32 ApplCmd_ByteArrayToUint32   ( const uint8* data, boolean LSBfirst );
static uint8  ApplCmd_Uint32ToByteArray   ( uint8* dest, const uint32 src, boolean LSBfirst );

//=============================================================================
// Public functions definition
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_CheckKey( MsgContextType *const pMsgContext )
{
  uint8 ret =  0x31u; /*DCM_E_REQUESTOUTOFRANGE*/
  static const uint8 Key[5] = { 0xF8, 0x3F, 0x82, 0xF5, 0x1E };

  if( memcmp( pMsgContext->reqData, Key, (uint8)sizeof(Key) ) == (int)0 )
  {
    boLoginActivated = TRUE;
    ret = 0x00u;
  }

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_GetECUinfo( MsgContextType *const pMsgContext )
{ 
  uint8 ret;

  // BB FE VV(MSB) VV VV VV(LSB)
  if( pMsgContext->reqDataLen != 0u )
  {
    ret = 0x13u ;/*DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT*/
  }
  else
  {
    // BB FF
    pMsgContext->resDataLen = ApplCmd_Uint32ToByteArray( &pMsgContext->resData[0], EftEcuInformation, FALSE);     
    ret = 0;
  }
  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_SetECUinfo( MsgContextType *const pMsgContext )
{
  uint8 ret;

  // BB FE VV(MSB) VV VV VV(LSB)
  if( pMsgContext->reqDataLen != 4u )
  {
    ret = 0x13u ;/*DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT*/
  }
  else
  {
    EftEcuInformation = ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[0], FALSE);
    ret = 0;
  }
  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_GetSetECUinfo( MsgContextType *const pMsgContext )
{
  uint8 ret =  0x31u; /*DCM_E_REQUESTOUTOFRANGE*/

  switch( pMsgContext->reqData[0] )
  {
    case 0xFEU: // Set EcuInfo
    {
      // BB FE VV(MSB) VV VV VV(LSB)
      if( pMsgContext->reqDataLen != 5u )
      {
        ret = 0x13u ;/*DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT*/
      }
      else
      {
        EftEcuInformation = ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[1], FALSE);
        ret = 0;
      }
    }
    break;

    case 0xFFU: // Get EcuInfo
    {
      // BB FF
      pMsgContext->resDataLen = ApplCmd_Uint32ToByteArray( &pMsgContext->resData[0], EftEcuInformation, FALSE);     

      ret = 0;
    }
    break;

    default:
      break;
  }

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_DownloadToRam( MsgContextType *const pMsgContext )
{
  #define APPLCMD_0xBD_DATA_OFFSET (4U)

  uint8 ret                 = 0x31u;/*DCM_E_REQUESTOUTOFRANGE*/
  const uint32 Dest         = ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[0], FALSE);
  const uint32 Source       = (uint32) &pMsgContext->reqData[APPLCMD_0xBD_DATA_OFFSET];
  const uint16 unNumOfBytes = pMsgContext->reqDataLen - APPLCMD_0xBD_DATA_OFFSET;

  #undef APPLCMD_0xBD_DATA_OFFSET

  //set response to defined state
  pMsgContext->resData[0] = 0u;
  pMsgContext->resDataLen = 0u;

  //check for correct download area
  if(   ((uint32) (Dest + unNumOfBytes) <= (uint32) (APPLCMD_ALFLASHER_DOWNLOAD2RAM_END))
     &&           (Dest                 >= (uint32) (APPLCMD_ALFLASHER_DOWNLOAD2RAM_BEGIN)))
  {
    (void)memcpy((void*)Dest, (const void*)Source, (size_t)unNumOfBytes);

    ret = 0x0;
  }

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_CalcChecksum( MsgContextType *const pMsgContext )
{
  uint8 ret = 0x31u;/*DCM_E_REQUESTOUTOFRANGE*/

  if( pMsgContext->reqDataLen == 8u )
  {
    const uint32 unStartAddr = ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[0], FALSE);
    const uint32 Length      = ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[4], FALSE);
    uint32 crc32       = ApplCmd_AlFlasher_Crc32_Vector_AUTOSAR( (uint8 *)unStartAddr, Length, 0xFFFFFFFFuL, TRUE );
    
    pMsgContext->resDataLen = ApplCmd_Uint32ToByteArray( &pMsgContext->resData[0], crc32, TRUE);

    crc32 = ApplCmd_ByteArrayToUint32(&pMsgContext->resData[0], FALSE);

    if( crc32 == ( *(uint32*)( unStartAddr + Length ) ) )
    {
      boCrcOk = TRUE;
    }
    ret = 0x00u;
    Can_Cycle_SetDownloadIsInProgress(FALSE);
  }

  return ret;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pMsgContext 
///
/// \return uint8 
//-----------------------------------------------------------------------------
// PRQA S 1503 2 // not used at the moment
// PRQA S 3408 1 // It is actually being declared using macros
uint8  ApplCmd_AlFlasher_Jump2RamAppl( MsgContextType *const pMsgContext )
{
  uint8 ret = 0x31u;/*DCM_E_REQUESTOUTOFRANGE*/

  if( boCrcOk == FALSE )
  {
    ret = 0x10u;/*DCM_E_GENERALREJECT*/
  }
  else if( pMsgContext->reqData[0] == 0x1U ) // PAV mode
  {
    //Get the location of the startup code starting address in "emulated" ROM (RAM used as ROM for the RAM applications).
    uint32 * u32StartupCodeStartingAddress = (uint32 *) (4U + ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[1], FALSE));

#ifdef SIGNAL_RAM_APPL
    ApplCmd_SignalRunRamApplication( );
#endif

    //Use the location to read the startup code starting address.
    const uint32 u32JumpAddr = (uint32)*u32StartupCodeStartingAddress;

    //Chage value of CM0P_SCS_VTOR
     uint32 * CM0P_SCS_VTOR = (uint32 *) 0xE000ED08U;

     *CM0P_SCS_VTOR = ApplCmd_ByteArrayToUint32(&pMsgContext->reqData[1], FALSE);

    //lint -e611 Suspicious cast...
    //lint -e740 Unusual pointer cast (incompatible indirect types)...

    //Jump to startup code starting address. LSB must be set to b1 to signal the ARM CortexM0+ core we are using the thumb instruction set. 
    ((function_type) (u32JumpAddr | 0x1U))(); // PRQA S 305 1 // Cast from uint32 to function pointer type is required.

    //lint +e611
    //lint +e740

    ret = 0x0;

  }
  else
  {
    // do nothing
  }

  return ret;
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  dest 
/// \param  src 
/// \param  LSBfirst 
///
/// \return uint8 
//-----------------------------------------------------------------------------

//=============================================================================
// Private functions declaration
//=============================================================================

static uint8 ApplCmd_Uint32ToByteArray ( uint8* dest, const uint32 src, boolean LSBfirst)
{
  if (LSBfirst == TRUE)
  {
    dest[3] = (uint8)( src >> 24u );
    dest[2] = (uint8)( src >> 16u );
    dest[1] = (uint8)( src >>  8u );
    dest[0] = (uint8)( src        );
  }
  else
  {
    dest[0] = (uint8)( src >> 24u );
    dest[1] = (uint8)( src >> 16u );
    dest[2] = (uint8)( src >>  8u );
    dest[3] = (uint8)( src        );
  }

  return 4u;
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
/// \param  LSBfirst 
///
/// \return uint32 
//-----------------------------------------------------------------------------
static uint32 ApplCmd_ByteArrayToUint32 (const uint8* data, boolean LSBfirst)
{
  uint32 ulValue32;

  if (LSBfirst == TRUE)
  {
    ulValue32 = (  ((uint32)data[3] << 24u)
                 | ((uint32)data[2] << 16u)
                 | ((uint32)data[1] <<  8u)
                 | ((uint32)data[0]       ) );

  }
  else
  {
    ulValue32 = (  ((uint32)data[0] << 24u)
                 | ((uint32)data[1] << 16u)
                 | ((uint32)data[2] <<  8u)
                 | ((uint32)data[3]       ) );
  }

  return ulValue32;
}
