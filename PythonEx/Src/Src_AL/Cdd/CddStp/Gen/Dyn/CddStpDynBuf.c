// ************************************************************************************************ 
//    (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
// ************************************************************************************************
       
///////////////////////////////////////////////////////////////////////////////////////////////////
///  \file    CddStpDynBuf.c
///
///  \author  Ott, Peter ALRT/EEG-PM2
///
///  \brief   Step buffer handling
///
///  \descr   This file provides the interface functions to fill and read the step buffer that
///           is used by CddStp88XX
///
   
#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL
#include <UtilUtility.h>

#include <UtilBase_Atomic.h>

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <../Cdd/CddStp/Cfg/CddStp_Cfg.h>
  #include <../Cdd/CddStp/CddStpPrj.h>
  #include <../Cdd/CddStp/CddStpData.h>
#else // Unit-Tests!
//  #define CFA_CNT_STP_88XX  (4u)
  #define CFA_CNT_STP_ONBRD (4u)
  #include <CddStpPrj.h>
  #include <CddStpData.h>
#endif

#include <CddStp8899Cfg.h>
#include <CddStp88XX_HalStp.h>
#include <CddStp8899Com.h>

#if(CFA_CNT_STP_ONBRD != 0)

  #include <Dyn/CddStpDynBuf.h>


  //  ---------------------------------------------------------------------------
  //  defines
  //  ---------------------------------------------------------------------------



  //  ---------------------------------------------------------------------------
  //  global variables (accessable for inline functions placed in header)
  //  ---------------------------------------------------------------------------

  // prqa ....
  uint32     CddStpDynBuf_ulAccStepTime;
  uint32     CddStpDynBuf_ulBufIx;
  tHsInfo*   CddStpDynBuf_pHsBuf;
  tHsInfo    CddStpDynBuf_HsEntry;


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Read last buffer entry
  ///
  /// \descr  Get buffer contents of the last halfstep that will be handled by HalStp.
  ///         This is needed to continue a previous movement using the same dynamic table entry.
  ///
  /// \param  
  ///
  /// \return 
  ///
  void CddStpDynBuf_ReadLastEntry(void)
  {
    // get buffer entry (n-1) for history data, put it into temporary storage
    CddStpDynBuf_HsEntry = CddStpDynBuf_pHsBuf[(CddStpDynBuf_ulBufIx - 1u) & CDDSTP_HsInfoBufMask];
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Read actual buffer entry
  ///
  /// \descr  Get buffer entry of the halfstep that should be processed next.
  ///
  /// \param  
  ///
  /// \return 
  ///
  void CddStpDynBuf_ReadActualEntry(void)
  {
    // get actual buffer entry, put it into temporary storage
    CddStpDynBuf_HsEntry = CddStpDynBuf_pHsBuf[CddStpDynBuf_ulBufIx];
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Write to buffer
  ///
  /// \descr  Copy temporary storage into buffer, increment index and wrap around using buffer size
  ///
  /// \param  
  ///
  /// \return 
  ///
  void CddStpDynBuf_WriteToBuffer(void)
  {
    CddStpDynBuf_HsEntry.Bit.biSet = 1;                                // validate buffer entry
#ifndef UNIT_TEST // build crashes due to pointer error
    CddStpDynBuf_pHsBuf[CddStpDynBuf_ulBufIx] = CddStpDynBuf_HsEntry;  // copy temporary storage to buffer
#endif
    CddStpDynBuf_ulBufIx++;
    CddStpDynBuf_ulBufIx &= CDDSTP_HsInfoBufMask;                      // buffer index wrap around
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Increment buffer index
  ///
  /// \descr  Increment index and wrap around using buffer size
  ///
  /// \param  
  ///
  /// \return 
  ///
  void CddStpDynBuf_IncBufIx(void)
  {
    CddStpDynBuf_ulBufIx++;
    CddStpDynBuf_ulBufIx &= CDDSTP_HsInfoBufMask;                        // buffer index wrap around
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Clear "Set" bit at buffer position after last entry
///
/// \descr  At the end of writing to the HS buffer the buffer index points to the next free entry.
///         At this location the "Set" bit must not be at "1" --> Clear this bit
///
/// \param  none
///
/// \return none
///
  void CddStpDynBuf_CloseBufferr(uint32 ulBufIx)
  {
    if (ulBufIx != CddStpDynBuf_ulBufIx)
    {
      CddStpDynBuf_pHsBuf[CddStpDynBuf_ulBufIx].Bit.biSet = 0;  // mark actual entry as invalid
    }
  }


#endif  // (CFA_CNT_STP_ONBRD != 0)

//EOF
