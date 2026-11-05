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

/** PDB - Size of Registers Arrays */
#define PDB_CH_COUNT                             3u
#define PDB_DLY_COUNT                            8u
#define PDB_POnDLY_COUNT                         1u

/** PDB - Register Layout Typedef */
typedef struct {
   uint32 SC;                                /**< Status and Control register, offset: 0x0 */
   uint32 MOD;                               /**< Modulus register, offset: 0x4 */
   uint32 CNT;                               /**< Counter register, offset: 0x8 */
   uint32 IDLY;                              /**< Interrupt Delay register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x28 */
     uint32 C1;                                /**< Channel n Control register 1, array offset: 0x10, array step: 0x28 */
     uint32 S;                                 /**< Channel n Status register, array offset: 0x14, array step: 0x28 */
     uint32 DLY[PDB_DLY_COUNT];                /**< Channel n Delay 0 register..Channel n Delay 7 register, array offset: 0x18, array step: index*0x28, index2*0x4 */
  } CH[PDB_CH_COUNT];
  uint8 RESERVED_0[264];
  uint32 POEN;                              /**< Pulse-Out n Enable register, offset: 0x190 */
  union {                                          /* offset: 0x194, array step: 0x4 */
    uint32 PODLY;                             /**< Pulse-Out n Delay register, array offset: 0x194, array step: 0x4 */
    struct {                                         /* offset: 0x194, array step: 0x4 */
       uint16 DLY2;                              /**< PDB1_DLY2 register...PDB0_DLY2 register., array offset: 0x194, array step: 0x4 */
       uint16 DLY1;                              /**< PDB1_DLY1 register...PDB0_DLY1 register., array offset: 0x196, array step: 0x4 */
    } ACCESS16BIT;
  } POnDLY[PDB_POnDLY_COUNT];
} PDB_Type, *PDB_MemMapPtr;

/** Number of instances of the PDB module. */
#define PDB_INSTANCE_COUNT                       (2u)

typedef volatile uint32 vuint32;

PDB_Type Pdb0_sReg;
PDB_Type Pdb1_sReg;

#define   PDB0_BASE     &Pdb0_sReg
#define   PDB1_BASE     &Pdb1_sReg


#define PDB0                                     ((PDB_Type *)PDB0_BASE)
#define PDB1                                     ((PDB_Type *)PDB1_BASE)


#endif // REG_STUBS_2021_08_23_H_
