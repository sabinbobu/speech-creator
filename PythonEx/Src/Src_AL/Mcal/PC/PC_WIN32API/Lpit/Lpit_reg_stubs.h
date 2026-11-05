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
/// \file  reg_stubs.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef REG_STUBS_2021_08_23_H_
#define REG_STUBS_2021_08_23_H_


/** LPIT - Size of Registers Arrays */
#define LPIT_TMR_COUNT                           4u

/** LPIT - Register Layout Typedef */
typedef struct {
  uint32 VERID;                             /**< Version ID Register, offset: 0x0 */
  uint32 PARAM;                             /**< Parameter Register, offset: 0x4 */
  uint32 MCR;                               /**< Module Control Register, offset: 0x8 */
  uint32 MSR;                               /**< Module Status Register, offset: 0xC */
  uint32 MIER;                              /**< Module Interrupt Enable Register, offset: 0x10 */
  uint32 SETTEN;                            /**< Set Timer Enable Register, offset: 0x14 */
  uint32 CLRTEN;                            /**< Clear Timer Enable Register, offset: 0x18 */
  uint8 RESERVED_0[4];
  struct {                                     /* offset: 0x20, array step: 0x10 */
     uint32 TVAL;                              /**< Timer Value Register, array offset: 0x20, array step: 0x10 */
     uint32 CVAL;                              /**< Current Timer Value, array offset: 0x24, array step: 0x10 */
     uint32 TCTRL;                             /**< Timer Control Register, array offset: 0x28, array step: 0x10 */
     uint8 RESERVED_0[4];
  } TMR[LPIT_TMR_COUNT];
} LPIT_Type, *LPIT_MemMapPtr;


volatile LPIT_Type                                dummyLPIT0;

#define LPIT0_BASE                               (&dummyLPIT0)
/** Peripheral LPIT0 base pointer */
#define LPIT0                                    ((LPIT_Type *)LPIT0_BASE)
/** Array initializer of LPIT peripheral base addresses */
#define LPIT_BASE_ADDRS                          { LPIT0_BASE }
/** Array initializer of LPIT peripheral base pointers */
#define LPIT_BASE_PTRS                           { LPIT0 }

#define LPIT_INSTANCE_COUNT                      (1u)

#endif // REG_STUBS_2021_08_23_H_
