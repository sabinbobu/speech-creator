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
/// \file  CddStp_TI8899.cpp
///
/// \brief  
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Spi.h>
#include <TI8899/CddStp_TI8899.h>
#include <CddStp_TI8899_Cfg.h>
#include <Spi_Cfg.h>
#include <string.h>
#include <Cfg/Cfg.h>

#ifdef SAMPLE_FULL

extern uint8 spi_stepper_chips;
static uint8 last_index_LWR;
static uint8 last_index_LLR;
static uint8 last_index_AHL;

//=============================================================================
// macros
//=============================================================================
#ifndef SPI_STEP_READ_FRAME
  #define SPI_STEP_READ_FRAME(addr)           ((uint16)((uint16)(addr) << 9U) | (uint16)(1U << 14U))
  #define SPI_STEP_WRITE_FRAME(addr, regval)  ((uint16)((uint16)(addr) << 9U) | (uint16)(regval)) & (uint16)(~(1U<<14U))
#endif
//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
// \brief  cdd::stp::TI8899::init
//
// \descr  This function will initialize the TI8899 drv registers.
//         
// \param  b_reg_val_type  specifies if specifc initialization has to be performed 
//                      on the driver or the default values are used(no init)
//
// \return void
//-----------------------------------------------------------------------------
void cdd::stp::TI8899::init(boolean b_reg_val_type)
{
  if (b_reg_val_type)
  {
    cdd::stp::TI8899::init_reg();
  }
  else
  {
    //do nothing default values are used
  }
}

//-----------------------------------------------------------------------------
// \brief  cdd::stp::TI8899::init_reg
//
// \descr  This function will write the TI8899 drv registers.
//         
// \param  void
//
// \return void
//-----------------------------------------------------------------------------
void cdd::stp::TI8899::init_reg(void)
{
  static uint8 cdd_stp_TI8899_reg_map[CDDSTP_TI8899_DRVNR][CDDSTP_TI8899_REGNR] = {0};       //map of STP_TI8899 registers
  uint8 index;                                                                             //index for each stepper [0, 1, 2]
  uint8 index1;                                                                            //index for registers
  uint16 u16RxData = 0U;
  
  //Fill every register of all steppers with Data
  for (index = 0; index < CDDSTP_TI8899_DRVNR; index++)
  {
    cdd_stp_TI8899_reg_map[index][FAULTsts] = cdd_stp_TI8899_reg_name[index].FaultStatus.Data;
    cdd_stp_TI8899_reg_map[index][DIAGsts1] = cdd_stp_TI8899_reg_name[index].DiagStatus1.Data;
    cdd_stp_TI8899_reg_map[index][DIAGsts2] = cdd_stp_TI8899_reg_name[index].DiagStatus2.Data;
    cdd_stp_TI8899_reg_map[index][CTRL1_macro] = cdd_stp_TI8899_reg_name[index].CTRL1.Data;
    cdd_stp_TI8899_reg_map[index][CTRL2_macro] = cdd_stp_TI8899_reg_name[index].CTRL2.Data;
    cdd_stp_TI8899_reg_map[index][CTRL3_macro] = cdd_stp_TI8899_reg_name[index].CTRL3.Data;
    cdd_stp_TI8899_reg_map[index][CTRL4_macro] = cdd_stp_TI8899_reg_name[index].CTRL4.Data;
    
    for (index1 = 0; index1 < CDDSTP_TI8899_REGNR; index1++)
    {
      //Check if the register [index1] of the stepper [index] has to be read
      if (cdd_stp_TI8899_reg_map[index][index1] == 0xFF)
      {
        cdd::stp::TI8899::read_write_reg((te_cdd_stp_id)index1, e_cdd_stp_read_reg, index, nullptr, &u16RxData);
        cdd_stp_TI8899_reg_map[index][index1] = (uint8)u16RxData;
      }
      else
      {
        cdd::stp::TI8899::read_write_reg((te_cdd_stp_id)index1, e_cdd_stp_write_reg, index, &cdd_stp_TI8899_reg_map[index][index1], &u16RxData);
      }
    }
  }
}

//-----------------------------------------------------------------------------
// \brief  start_stop
//
// \descr  This function is responsible for enabeling/disabeling the output of
//         the received stepper driver.
//         
// \param  stp_id - Stepper ID configured in CddStp_Cfg.h
//         start_stp - State of stepper 0 - Stop, !=0 Start
//
// \return ucRet - error code
//-----------------------------------------------------------------------------
uint8 cdd::stp::TI8899::start_stop(te_cdd_stp_id stp_id, boolean start_stp)
{
  uint8 uc_addr = 0x04;
  uint8 uc_reg_val = 0x80;
  uint16 un_rx_data[8];
  uint8 unRet = E_NOT_OK;

  //Read CTRL2 Reg
  unRet = cdd::stp::TI8899::read_write_reg(stp_id, e_cdd_stp_read_reg, uc_addr, &uc_reg_val, &un_rx_data[0]);
  //Set or clear DIS_OUT
  uc_reg_val = (start_stp == false) ? (un_rx_data[0U] | 0x80U) : (un_rx_data[0U] & 0x7FU);
  //Write back CTRL2 Reg
  unRet += cdd::stp::TI8899::read_write_reg(stp_id, e_cdd_stp_write_reg, uc_addr, &uc_reg_val, &un_rx_data[0]);
  
  return unRet;
}

//-----------------------------------------------------------------------------
// \brief  change_dirrection
//
// \descr  This function is responsible for changinf the dirrection of the stepper.
//         
// \param  stp_id - Stepper ID configured in CddStp_Cfg.h
//
// \return ucRet - error code
//-----------------------------------------------------------------------------
uint8  cdd::stp::TI8899::change_dirrection(te_cdd_stp_id stp_id)
{
  uint8 uc_addr = 0x05;
  uint8 uc_reg_val = 0xA0;
  uint16 un_rx_data[8];
  uint8 unRet = E_NOT_OK;

  //Read CTRL4 Reg
  unRet = cdd::stp::TI8899::read_write_reg(stp_id, e_cdd_stp_read_reg, uc_addr, &uc_reg_val, &un_rx_data[0]);

  //Set SPI_STEP and reverse DIR
  uc_reg_val = (un_rx_data[0] | 0x20U);
  uc_reg_val = (un_rx_data[0] & 0x80 ) ? (uc_reg_val & 0x7F) : (uc_reg_val | 0x80);
  unRet += cdd::stp::TI8899::read_write_reg(stp_id, e_cdd_stp_write_reg, uc_addr, &uc_reg_val, &un_rx_data[0]);

  return unRet;
}

//-----------------------------------------------------------------------------
// \brief  read_write_reg
//
// \descr  This function is responsible writing and reading the stepper registers
//
// \param  stp_id - Stepper ID configured in CddStp_Cfg.h
//         spi_request - type of request Read - 0, Rrite - 1
//         puc_addr - pointer to Stp reg addr
//         puc_tx_data - pointer to data to be sent ovet SPI, discarded if read request
//         pun_rx_data - pinter to received data over SPI
//
// \return ucRet - error code
//-----------------------------------------------------------------------------
uint8 cdd::stp::TI8899::read_write_reg(te_cdd_stp_id stp_id, te_cdd_stp_spi_req_type spi_request, uint8 puc_addr, uint8 *puc_tx_data, uint16 *pun_rx_data)
{
  uint8 unRet = e_cdd_stp_EOK;

  if (cdd_stp_TI8899_config[stp_id].spi_topology == e_cdd_stp_spi_star)
  {
    uint16 un_spi_tx;

    if (spi_request == 0U)
    {
      un_spi_tx = SPI_STEP_READ_FRAME(puc_addr);
      Spi_Transmit(e_active_config_STEPPER, &un_spi_tx, pun_rx_data, 1U);
    }
    else
    {
      un_spi_tx = SPI_STEP_WRITE_FRAME(puc_addr, *puc_tx_data);
      Spi_Transmit(e_active_config_STEPPER, &un_spi_tx, pun_rx_data, 1U);
    }
  }
  else if (cdd_stp_TI8899_config[stp_id].spi_topology == e_cdd_stp_spi_daisy)
  {

    //must send 2 Header bytes + CDDSTP_TI8899_DRVNR address bytes + CDDSTP_TI8899_DRVNR data bytes
    const uint8 unSpiTotalLength = CDDSTP_TI8899_DRVNR * 2U + 2U;
    uint16 unSpiTx[unSpiTotalLength] = { 0U };
    uint16 unSpiRx[unSpiTotalLength] = { 0U };

    //Fill Header bytes
    unSpiTx[0] = (uint16)(0x80U | cdd_stp_TI8899_config[stp_id].u8DasyChainTotal) | (uint16)(0x8000U);
    unSpiTx[1] = 0x80U;

    //fill the address and data bytes with dummy data
    for (uint8 index = 2U; index < unSpiTotalLength; index++)
    {
      unSpiTx[index] = 0x00U;
    }

    //fill the address byte and the data byte if write request is received
    //the address byte has the following structure: 0 RW A4 A3 A2 A1 A0 X
    if (spi_request == 0U)
    {
      if (stp_id % 2 == 0)
      {
        unSpiTx[1U] = (uint16)(((0x7F  & (puc_addr << 1)) | 0x40) << 8U);
      }
      else
      {
        unSpiTx[1U] = (uint16)((0x7F  & (puc_addr << 1)) | 0x40);
      }
    }
    else
    {
      if (stp_id % 2 == 0)
      {
        unSpiTx[1] = (uint16)((0x7F  & (puc_addr << 1)) << 8U);
        unSpiTx[2] = (uint16)((uint16)*puc_tx_data << 8U);
      }
      else
      {
        unSpiTx[1] = (uint16)(0x7F  & (puc_addr << 1));
        unSpiTx[2] = (uint16)((uint16)*puc_tx_data);
      }
    }

    Spi_Transmit(e_active_config_STEPPER, (uint16 *)&unSpiTx, (uint16 *)&unSpiRx, 3U);
    if (stp_id % 2 == 0)
    {
      *pun_rx_data = (uint16)((unSpiRx[2] >> 8U) & 0x00FFU);
    } 
    else
    {
      *pun_rx_data = (uint16)(unSpiRx[2] & 0x00FFU);
    }
    
  }
  else
  {
    unRet = e_cdd_stp_device_not_supported;
  }
  return unRet;
}

//-----------------------------------------------------------------------------
// \brief  read_write_reg_all
//
// \descr  This function is responsible writing and reading all the stepper registers
//
// \param  stp_id - Stepper ID configured in CddStp_Cfg.h
//         spi_request - type of request Read - 0, Write - 1
//         puc_tx_data - pointer to data to be sent ovet SPI, discarded if read request
//         pun_rx_data - pointer to received data over SPI
//         response_len - pointer to total length
//
// \return ucRet - error code
//-----------------------------------------------------------------------------
uint8  cdd::stp::TI8899::read_write_reg_all(te_cdd_stp_id stp_id, te_cdd_stp_spi_req_type spi_request, uint8 *puc_tx_data, uint16* pun_rx_data, uint8* response_len)
{
  uint8 ret = e_cdd_stp_EOK;
  if (spi_request == e_cdd_stp_read_reg)
  {
    for (uint8 i = 0; i <  sizeof(reg_map_TI8899) / sizeof(reg_map_TI8899[0]); ++i)
    {
      if (reg_map_TI8899[i].read_write == reg_read_only || reg_map_TI8899[i].read_write == reg_read_write)
      {
        ret &= read_write_reg(stp_id,
                              e_cdd_stp_read_reg, 
                              reg_map_TI8899[i].reg_addr, 
                              (uint8 *)(puc_tx_data + (i * sizeof(*puc_tx_data))),
                              (uint16 *)(pun_rx_data + (i * sizeof(*pun_rx_data))));
        if (response_len)
        {
          *response_len += 1;
        }
      }
    }
  }
  
  if (spi_request == e_cdd_stp_write_reg)
  {
    for (uint8 i = 0; i <  sizeof(reg_map_TI8899) / sizeof(reg_map_TI8899[0]); ++i)
    {
      if (reg_map_TI8899[i].read_write == reg_write_only || reg_map_TI8899[i].read_write == reg_read_write)
      {
        ret &= read_write_reg(stp_id,
                              e_cdd_stp_write_reg, 
                              reg_map_TI8899[i].reg_addr,
                              (uint8 *)(puc_tx_data + (i * sizeof(*puc_tx_data))),
                              (uint16 *)(pun_rx_data + (i * sizeof(*pun_rx_data))));
      }
    }
  }

 return ret;
}

//-----------------------------------------------------------------------------
// \brief  refresh_errors
//
// \descr  This function is responsible for saving errors for each stepper
//
// \param  

// \return
//-----------------------------------------------------------------------------
void cdd::stp::TI8899::refresh_errors()
{
  static uint32 count;
  //TaskCddStp_Func has a freq of 1ms 
  // we want to check each 500ms
  //uint8 tx_data;
  //uint16_t rx_data;
  tFaultStatus rx_data;
  if (count++ > 500U)
  {
    count = 0;
    for (uint8 i = 0; i < spi_stepper_chips; ++i)
    {
      // this can be changed by monitoring ST_FAULT. Since B0 - B2 is not clarified, i'll stick to a polling aproach
      //cdd::stp::TI8899::read_write_reg((te_cdd_stp_id)i, e_cdd_stp_read_reg, tREG_TI8899_FAULT_STATUS, &tx_data, (uint16_t*)&rx_data.Data); 
      if (rx_data.Bit.FAULT1) 
      {
        // read all regs and store them


        //clear fault
      }
    }
  }
}

//-----------------------------------------------------------------------------
// \brief  store_error
//
// \descr  This function is responsible for saving errors for each stepper
//
// \param  

// \return
//-----------------------------------------------------------------------------
void cdd::stp::TI8899::store_error(uint8 stp_id)
{
  switch (stp_id)
  {
    case 0: // LWR
//      if (last_index_LLR < STP_STACK_SIZE)
//      {
//        cdd::stp::TI8899::read_write_reg_all((te_cdd_stp_id)stp_id, 
//                                             e_cdd_stp_read_reg, 
//                                             nullptr, 
//                                             (uint16*)&steppers_error.reg_snapshot_LWR[last_index_LLR].reg_snapshot[last_index_LLR], 
//                                             nullptr);
//        last_index_LLR++;
//      } 
//      else
//      {
//        memmove(&steppers_error.reg_snapshot_LWR[last_index_LLR].reg_snapshot[STP_STACK_SIZE - 1U],
//                &steppers_error.reg_snapshot_LWR[last_index_LLR].reg_snapshot[STP_STACK_SIZE - 1U],
//                sizeof(steppers_error.reg_snapshot_LWR) * (STP_STACK_SIZE - 1U));
//
//        cdd::stp::TI8899::read_write_reg_all((te_cdd_stp_id)stp_id, 
//                                     e_cdd_stp_read_reg, 
//                                     nullptr, 
//                                     (uint16*)&steppers_error.reg_snapshot_LWR[last_index_LLR].reg_snapshot[STP_STACK_SIZE - 1U], 
//                                     nullptr);
//
//      }
      break;
    case 1: // LLR
      break;
    case 2: // AHL
      break;
    default:
      break;
  }
}

void cdd::stp::TI8899::clear_errors(uint8 stp_id)
{
  (void) stp_id;
  //switch (stp_id)
  //{
  //  case 0: // LWR
  //    last_index_LWR = 0;
  //    memset(&cdd::stp::TI8899::steppers_error.reg_snapshot_LWR->reg_snapshot[0],  0x00, sizeof(steppers_error.reg_snapshot_LWR));
  //    break;
  //  case 1: // LLR
  //    last_index_LLR = 0;
  //    memset(&cdd::stp::TI8899::steppers_error.reg_snapshot_LLR->reg_snapshot[0],  0x00, sizeof(steppers_error.reg_snapshot_LLR));
  //    break;
  //  case 2: // AHL
  //    last_index_AHL = 0;
  //    memset(&cdd::stp::TI8899::steppers_error.reg_snapshot_AHL->reg_snapshot[0],  0x00, sizeof(steppers_error.reg_snapshot_AHL));
  //    break;
  //  default:
  //    break;
  //}
}

#endif