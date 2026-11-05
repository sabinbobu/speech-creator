//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

#include <LgmDEHErrDsc.h>
#include <LgmDEHMainAPI.h>
#include <LgmDEHFifoMgt.h>
#include <LGM_types.h>
#include <LGM_OS.h>
#include <_DIAG_types.h>
#include <IL_types.h>
#include <p_IL_messages.h>
#include <_IL_types.h>
#include <s32_core_cm4.h>
#include <DrvCAN_Interrupt.h>
#include <ConfigE2E.h>

UINT8 Enter_intterupts = 1 ; //PRQA S 3408

static UINT16 timer = 0u;

void APPLI_CAN_disable_interrupt(void)
{
  if(Enter_intterupts == 0u)
  { 
    DRV_CAN_Disable_Interrupts();
  }
}

void APPLI_CAN_enable_interrupt(void)
{
  if(Enter_intterupts == 0u)
  { 
    DRV_CAN_Enable_Interrupts();
  }
}

void APPLI_DateUpdateNVM(LDEH_TS_DECtxt const * const PISP_DE)
{
  (void)PISP_DE;
}


void APPLI_CAN_Interrupt_Exit(void)
{
  Enter_intterupts =0;
}
void APPLI_CAN_Interrupt_Enter(void)
{
  Enter_intterupts =1;
}


void Set_Enable_Callback(UINT8 ui8_LineValue)
{
  (void)ui8_LineValue;
}
void APPLI_Timer_S3_Expired(void)
{
  (void)0;
}

void Set_StandBy_Callback(UINT8 ui8_LineValue)
{
  (void)ui8_LineValue;
  return;
}

void APPLI_disable_interrupt(void)
{
  (void)0;
}

void APPLI_enable_interrupt(void)
{
  (void)0;
}

void APPLI_StoreInNVM(LDEH_TS_DECtxt const * const PISP_DE)
{
  (void)PISP_DE;
}

// EOF
