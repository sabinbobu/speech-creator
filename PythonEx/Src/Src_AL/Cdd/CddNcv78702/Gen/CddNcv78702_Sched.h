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
/// \file  CddNcv78702_Sched.h
///
/// \brief  Scheduling table for NCV78702
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_SCHED_2021_03_29_H_
#define CDD_NCV78702_SCHED_2021_03_29_H_


// Actions executed synchrone with SPI schedule Table before a SPI Tx
#define CDDNCV78702_ST_NO_ACT          0u
#define CDDNCV78702_ST_ACT_DIS_BOOST   1u
#define CDDNCV78702_ST_ACT_EN_BOOST    2u
#define CDDNCV78702_ST_ACT_BSTSYNC_50  3u
#define CDDNCV78702_ST_CHECK_START     4u
#define CDDNCV78702_ST_CHECK_STATUS    5u


//-----------------------------------------------------------------------------
//  SPI scheduling configuration
//-----------------------------------------------------------------------------
#define CDDNCV78702_Cfg_SpiSchedTableLen      34u
#define CDDNCV78702_Cfg_SpiSchedTableCycStart 14u

#define CDDNCV78702_Cfg_SpiSchedTable_Init                                                                                                                                 \
{                                                                                                                                                                           \
  /* next      Optional                       Read/Write                     Register                    Data                  Data                     */ \
  /* state     action                         command                        address                     to transmit           to receive               */ \
  /*--------------------- Init sequence ----------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_ReadCmd,     CDDNCV78702_ReadReg0x0DAddr,     CDDNCV78702_Zero_Tx,      CDDNCV78702_Reg0x0D_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_ReadCmd,     CDDNCV78702_ReadReg0x0AAddr,     CDDNCV78702_Zero_Tx,      CDDNCV78702_Reg0x0A_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_ReadCmd,     CDDNCV78702_ReadReg0x0BAddr,     CDDNCV78702_Zero_Tx,      CDDNCV78702_Reg0x0B_Rx    },  \
  {  +1, CDDNCV78702_ST_CHECK_START,     CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x06Addr,    CDDNCV78702_Reg0x06_Tx,   CDDNCV78702_Dummy_Rx      },  \
  {  +1, CDDNCV78702_ST_ACT_DIS_BOOST,   CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x01Addr,    CDDNCV78702_Reg0x01_Tx,   CDDNCV78702_Reg0x06_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x02Addr,    CDDNCV78702_Reg0x02_Tx,   CDDNCV78702_Reg0x01_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x03Addr,    CDDNCV78702_Reg0x03_Tx,   CDDNCV78702_Reg0x02_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x03_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x05Addr,    CDDNCV78702_Reg0x05_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x06Addr,    CDDNCV78702_Reg0x06_Tx,   CDDNCV78702_Reg0x05_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x07Addr,    CDDNCV78702_Reg0x07_Tx,   CDDNCV78702_Reg0x06_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x08Addr,    CDDNCV78702_Reg0x08_Tx,   CDDNCV78702_Reg0x07_Rx    },  \
  {  +1, CDDNCV78702_ST_ACT_BSTSYNC_50,  CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x05Addr,    CDDNCV78702_Reg0x05_Tx,   CDDNCV78702_Reg0x08_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_ReadReg0x00Addr,     CDDNCV78702_Reg0x00_Tx,   CDDNCV78702_Reg0x05_Rx    },  \
  /*--------------------- Cyclic 0ms -------------------------------------------------------------------------------------------------------------------*/ \
  {  +1, CDDNCV78702_ST_ACT_EN_BOOST,    CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Dummy_Rx      },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x01Addr,    CDDNCV78702_Reg0x01_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x01_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x02Addr,    CDDNCV78702_Reg0x02_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x02_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x03Addr,    CDDNCV78702_Reg0x03_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x03_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x05Addr,    CDDNCV78702_Reg0x05_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x05_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x06Addr,    CDDNCV78702_Reg0x06_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  /*--------------------- Cyclic 10ms -----------------------------------------------------------------------------------------------------------------*/  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x06_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x07Addr,    CDDNCV78702_Reg0x07_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x07_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x08Addr,    CDDNCV78702_Reg0x08_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Reg0x08_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_ReadCmd,     CDDNCV78702_ReadReg0x0AAddr,     CDDNCV78702_Zero_Tx,      CDDNCV78702_Reg0x0A_Rx    },  \
  {  +1, CDDNCV78702_ST_CHECK_STATUS,    CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Dummy_Rx      },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_ReadCmd,     CDDNCV78702_ReadReg0x0BAddr,     CDDNCV78702_Zero_Tx,      CDDNCV78702_Reg0x0B_Rx    },  \
  {  +1, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x04Addr,    CDDNCV78702_Reg0x04_Tx,   CDDNCV78702_Dummy_Rx      },  \
  { -19, CDDNCV78702_ST_NO_ACT,          CDDNCV78702_WriteCmd,    CDDNCV78702_WriteReg0x00Addr,    CDDNCV78702_Reg0x00_Tx,   CDDNCV78702_Reg0x04_Rx    },  \
  /*--------------------- Cyclic 20ms ------------------------------------------------------------------------------------------------------------------*/ \
}


#endif // CDD_NCV78702_SCHED_2021_03_29_H_
