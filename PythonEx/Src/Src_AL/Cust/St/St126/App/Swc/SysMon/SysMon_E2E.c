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
/// \file  SysMon_E2E.c
///
/// \brief  This file contains the interfaces to integrate E2E library with SysMon
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#include <SysMon_E2E.h>
#include <ProcessE2E.h>
#include <RteCommonTypes.h>


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  SysMon_E2EInit
///
/// \descr  The function calls E2E initialization
///         This will initialize each element useful for PDU sampling and chunk
///         state machine management.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_E2EInit(void)
{
    EEPR_Init();
}


//-----------------------------------------------------------------------------
/// \brief  SysMon_E2ECycle10ms
///
/// \descr  The function calls E2E Main function.
///         The aim is to trigger PDU checking according to the received 
///         information given by the communication stack 
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_E2ECycle10ms(void)
{

    //call main function to check the status of the input PDU (HS6_VSM_DAT_34E)
    (void)EEPR_MainFunction();

}


//-----------------------------------------------------------------------------
/// \brief  SysMon_E2EGetChunkState
///
/// \descr  The function returns the state of a given safety-related data chunk
///
/// \param  unChunkId             : the chunk identifier
/// \param  pte_ChunkStateE2E     : variable where to read the chunk state
///
/// \return teRte_SigQty          : returned error status
//-----------------------------------------------------------------------------
teRte_SigQty SysMon_E2EGetChunkState(Tu8_Int CONST_AL unChunkId, EECO_TEP_ProfileOneChunkStatusPtr CONST_AL pte_ChunkStateE2E)
{

    teRte_SigQty  retVal = SIG_SNA;

    TE_ReturnType retStatus = EEPL_GetRawState(unChunkId, pte_ChunkStateE2E);

    if (retStatus == E_EXEC_OK)
    {
        if ((*pte_ChunkStateE2E == EECO_E_P01_OK) || (*pte_ChunkStateE2E == EECO_E_P01_SOME_LOST))
        {
            //PDU received successfully and integrity was checked
            retVal = SIG_VALID;
        }

        else if (*pte_ChunkStateE2E == EECO_E_P01_WRONG_CRC)
        {
            //PDU received, but CRC or Data is incorrect/corrupted 
            retVal = SIG_E2E_CRCERR;
        }

        else   /* other errors :  ((*pte_ChunkStateE2E == EECO_E_PO1_ERROR_COUNTER) || (*pte_ChunkStateE2E == EECO_E_PO1_SYNC) || (*pte_ChunkStateE2E == EECO_E_PO1_REPEATED) || (*pte_ChunkStateE2E == EECO_E_PO1_WRONG_SEQUENCE)) */
        {
            //PDU received, data has a correct CRC, the counter is in the expected range but : it's identical to the most recent counter or  incremented more than 1
            retVal = SIG_E2E_ALIVEERR;
        }
    }

    else /*  PDU is called with wrong parameters : wrong ID or address -> ( (retStatus == E_DATA_OUTBOUND) || (retStatus == E_ADDR_OUTBOUND) )*/
    {
        retVal = SIG_INVALID;
    }

    return retVal;
}



