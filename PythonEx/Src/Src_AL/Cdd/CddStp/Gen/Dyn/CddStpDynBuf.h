#ifndef __CDDSTPDYNBUF_H__
#define __CDDSTPDYNBUF_H__

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
  /// \file  CddStpDynBuf.h
  ///
  /// \brief  
  ///
  /// \descr  
  ///
  ///         Additional information can be found in the design description (Link:
  ///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
  ///
  /// \author Ott, Peter ALRT/EEG-PM2 *  (otp2rt)
  ///         mailTo:Peter.Ott@al-lighting.com       
  //-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <CddStpTypes.h>  // incl. '88XX/CddStp88XX_HalStp.h'

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <../Cdd/CddStp/CddStpPrj.h>
#else // Unit-Tests!
  #include <CddStpPrj.h>
#endif

  //  ---------------------------------------------------------------------------
  //  defines
  //  ---------------------------------------------------------------------------


  //  ---------------------------------------------------------------------------
  //  types
  //  ---------------------------------------------------------------------------


  //  ---------------------------------------------------------------------------
  //  constants
  //  ---------------------------------------------------------------------------


  //  ---------------------------------------------------------------------------
  //  externals (for use in INLINE functions only)
  //  ---------------------------------------------------------------------------

  extern uint32     CddStpDynBuf_ulAccStepTime;
  extern uint32     CddStpDynBuf_ulBufIx;
  extern tHsInfo*   CddStpDynBuf_pHsBuf;
  extern tHsInfo    CddStpDynBuf_HsEntry;

  //  ---------------------------------------------------------------------------
  //  inline functions
  //  ---------------------------------------------------------------------------

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  
  ///
  /// \descr  prepare buffer for read and write actions
  ///
  /// \param  
  ///
  /// \return 
  ///
  INLINE void CddStpDynBuf_OpenBuffer(tHsInfo* pHsBuf, uint32 ulBufIx, uint32 ulRemainingStepTime)
  {
    CddStpDynBuf_pHsBuf        = pHsBuf;
    CddStpDynBuf_ulBufIx       = ulBufIx;
    CddStpDynBuf_ulAccStepTime = ulRemainingStepTime;
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
  INLINE void CddStpDynBuf_CloseBuffer(uint32 ulBufIx)
  {
    if (ulBufIx != CddStpDynBuf_ulBufIx)
    {
      CddStpDynBuf_pHsBuf[CddStpDynBuf_ulBufIx].Bit.biSet = 0;  // mark actual entry as invalid
    }
  }




  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  Wite halfstep time
  ///
  /// \descr  Write halfstep time (number of ticks) into the preparation storage
  ///         Add this value to the accumulated step time
  ///
  /// \param  
  ///
  /// \return 
  ///
  INLINE void CddStpDynBuf_SetHsTime(uint16 un)
  {
    CddStpDynBuf_HsEntry.Val.unHsTime = ST_R_USEC(un);
  
    CddStpDynBuf_ulAccStepTime += CddStpDynBuf_HsEntry.Val.unHsTime;
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief  
  ///
  /// \descr  Check if there are enough contents in the step buffer
  ///
  /// \param  
  ///
  /// \return 
  ///
  INLINE boolean CddStpDynBuf_BufferFull(void)
  {
    boolean boRetVal = FALSE;

    // check for sufficient buffer contents
    if(CddStpDynBuf_ulAccStepTime > (ST_R_USEC(CDDSTP_DynCalcTime * 1000)))
    {
      boRetVal = TRUE;
    }

    return boRetVal;
  }




  // set and get functions
  INLINE void     CddStpDynBuf_ClrHsEntry    (void     )    { CddStpDynBuf_HsEntry.ulRaw = 0;                        }
  INLINE void     CddStpDynBuf_SetDynTableIx (uint8  uc)    { CddStpDynBuf_HsEntry.Val.ucDynTableIx = uc;            }
  INLINE void     CddStpDynBuf_SetDirection  (sint32  l )   { CddStpDynBuf_HsEntry.Bit.biDirection  = l > 0 ? 0 : 1; } // 0=pos, 1=neg
  INLINE void     CddStpDynBuf_SetPause      (boolean   bo) { CddStpDynBuf_HsEntry.Bit.biPause      = bo ? 1 : 0;    }
  INLINE void     CddStpDynBuf_SetFirstStep  (boolean   bo) { CddStpDynBuf_HsEntry.Bit.biFirstStep  = bo ? 1 : 0;    }
  INLINE void     CddStpDynBuf_SetLastStep   (boolean   bo) { CddStpDynBuf_HsEntry.Bit.biLastStep   = bo ? 1 : 0;    }
  INLINE void     CddStpDynBuf_SetAboveResF1 (boolean   bo) { CddStpDynBuf_HsEntry.Bit.biAboveResF1 = bo ? 1 : 0;    }
  INLINE void     CddStpDynBuf_SetAboveResF2 (boolean   bo) { CddStpDynBuf_HsEntry.Bit.biAboveResF2 = bo ? 1 : 0;    }

  INLINE uint16   CddStpDynBuf_GetHsTime     (void) { return (CddStpDynBuf_HsEntry.Val.unHsTime);                    }
  INLINE uint8    CddStpDynBuf_GetDynTableIx (void) { return (CddStpDynBuf_HsEntry.Val.ucDynTableIx);                }
  INLINE sint32   CddStpDynBuf_GetDirection  (void) { return (CddStpDynBuf_HsEntry.Bit.biDirection) ? -1 : 1;        } // 0=pos, 1=neg
  INLINE boolean  CddStpDynBuf_IsPause       (void) { return (CddStpDynBuf_HsEntry.Bit.biPause);                     }
  INLINE boolean  CddStpDynBuf_IsFirstStep   (void) { return (CddStpDynBuf_HsEntry.Bit.biFirstStep);                 }
  INLINE boolean  CddStpDynBuf_IsLastStep    (void) { return (CddStpDynBuf_HsEntry.Bit.biLastStep);                  }
  INLINE boolean  CddStpDynBuf_IsAboveResF1  (void) { return (CddStpDynBuf_HsEntry.Bit.biAboveResF1);                }
  INLINE boolean  CddStpDynBuf_IsAboveResF2  (void) { return (CddStpDynBuf_HsEntry.Bit.biAboveResF2);                }
  INLINE boolean  CddStpDynBuf_IsSet         (void) { return (CddStpDynBuf_HsEntry.Bit.biSet);                       }

  INLINE uint32   CddStpDynBuf_GetAccStepTime(void) { return (CddStpDynBuf_ulAccStepTime);                           }


  //  ---------------------------------------------------------------------------
  //  prototypes
  //  ---------------------------------------------------------------------------

  void CddStpDynBuf_ReadLastEntry  (void);
  void CddStpDynBuf_ReadActualEntry(void);
  void CddStpDynBuf_WriteToBuffer  (void);
  void CddStpDynBuf_IncBufIx       (void);
  void CddStpDynBuf_CloseBufferr(uint32 ulBufIx);


#endif // __CDDSTPDYNBUF_H__
