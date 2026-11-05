//-----------------------------------------------------------------------------
/// Animation Master interface: main interfaces needed to start and stop the animations

//-----------------------------------------------------------------------------

#ifndef ANIMMA_H
#define ANIMMA_H
#include <stdbool.h> // C99
#include "Std_Types.h"
#include <CodM.h>
#include "RteCommonTypes.h"

/// Number of pixels (register size)
#define ANIMMA_NR_PIXELS  103 

/// Number of coding bytes
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
#define ANIMMA_CODING_BYTES 12000 //full 8052B
#else
#define ANIMMA_CODING_BYTES 4000 //eco 3072B
#endif

/// Cycle time of animation updates [ms]
#define ANIMMA_CYCLE_TIME               50u
#define ANIMMA_CYCLE                    (ANIMMA_CYCLE_TIME/10u)


typedef enum
{
    Inactive = 0U,
    ActiveSeqRun = 1U,
    StopSeqRun = 2U
} tSequenceStatus;

/// convenient function: access to array of target intensities
const uint8 * AnimMa_GetPxlTgt(void);
/// convenient function: access to array of target increments
const uint8 * AnimMa_GetPxlInc(void);
/// convenient function: access to array of target decrements
const uint8 * AnimMa_GetPxlDec(void);
/// get the number of pixels that is used for the current active sequence(s)
sint32 AnimMa_GetPxlNr(void);

/// Start a sequence. Returns true if the sequence was not running and is started.
void AnimMa_startSequence(teRte_ExtLightingAnimationReq ucSeqId);
/// Start a sequence. Returns true if the sequence was running and is stopped.
void AnimMa_stopSequence(teRte_ExtLightingAnimationReq ucSeqId);
/// Soft stop a sequence (start end sequence). Returns true if the sequence was running and is soft stopped or stopped.
void AnimMa_softStopSequence(teRte_ExtLightingAnimationReq ucSeqId);

/// Get sequence ID
bool  AnimMa_isSequenceActive(teRte_ExtLightingAnimationReq ucSeqId);
bool  AnimMa_isStopSequenceActive(teRte_ExtLightingAnimationReq ucSeqId);
uint8 AnimMa_ActiveSeqNr(void);

/// Set the mounting side
void   AnimMa_setMountingSide(uint8 ucMountingSide);
uint8  AnimMa_getMountSide(void);
uint32 AnimMa_getElapsedTime(teRte_ExtLightingAnimationReq ucSeqId);
/// set the current coding data (or NULL if no valid coding data are available
void AnimMa_setCodingData(const tNvmPara_CodingArea * pData);
bool AnimMa_isSeqActivePhase_WithNoRunningIDs(teRte_ExtLightingAnimationReq ucSeqId);

/// initialize at startup
void rcAnimMaInit(void);

/// runable for updates
void rcAnimMa50(void);

#endif // ANIMMA_H
