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
/// \file  CddStp.cpp
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
#include <Cfg/Cfg.h>
#ifdef SAMPLE_FULL
#include <CddStp.h>
#include <CddStp_Cfg.h>
#ifdef CDDSTP_TI8899
  #include <TI8899/CddStp_TI8899.h>
#endif


//=============================================================================
// variables
//=============================================================================
#ifdef CDDSTP_CYCLIC
  t_cdd_stp_cycle_run_params cdd_stp_cycle_params = {0u, false, false, 0u, 0u, 0u, 100};
#endif

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
// \brief  task_cdd_stp_func
//
// \descr  This function is part of the Os and is called cyclicly according to the
//         Os config. Depending on the driver configuration, this task can handle 
//         the cyclic movement of one stepper.
//         
// \param  void
//
// \return void
//-----------------------------------------------------------------------------

void TaskCddStp_Func(void)
{
#ifdef CDDSTP_CYCLIC
  if (cdd_stp_cycle_params.b_start == true)
  {
    // start stepper on
    if (cdd_stp_cycle_params.un_current_time_ms == 1)
    {
      //Enable the motor
      if (cdd_stp_cycle_params.un_stepper_id != 0xFFU)
      {
        cdd::stp::TI8899::start_stop((te_cdd_stp_id)cdd_stp_cycle_params.un_stepper_id, 1U);
      }
      else
      {
        for (uint8 idx = 0; idx < CDDSTP_DRVNR; idx++)
        {
          cdd::stp::TI8899::start_stop((te_cdd_stp_id)idx, 1U);
        }
      }

      cdd_stp_cycle_params.un_current_time_ms++;
    }
    else
    {
      if (cdd_stp_cycle_params.un_current_time_ms == cdd_stp_cycle_params.un_cycle_on_time_ms)
      {
        //on time expired, stop motor
        if (cdd_stp_cycle_params.un_stepper_id != 0xFFU)
        {
          cdd::stp::TI8899::start_stop((te_cdd_stp_id)cdd_stp_cycle_params.un_stepper_id, 1U);
        }
        else
        {
          for (uint8 idx = 0; idx < CDDSTP_DRVNR; idx++)
          {
            cdd::stp::TI8899::start_stop((te_cdd_stp_id)idx, 0U);
          }
        }
      }
      if (cdd_stp_cycle_params.un_current_time_ms == cdd_stp_cycle_params.un_cycle_duration_ms)
      {
        //one cyle finished, reset timer
        cdd_stp_cycle_params.un_current_time_ms = 0;

        //Change dirrection of stepper
        if (cdd_stp_cycle_params.un_stepper_id != 0xFFU)
        {
          cdd::stp::TI8899::change_dirrection((te_cdd_stp_id)cdd_stp_cycle_params.un_stepper_id);
        }
        else
        {
          for (uint8 idx = 0; idx < CDDSTP_DRVNR; idx++)
          {
            cdd::stp::TI8899::change_dirrection((te_cdd_stp_id)idx);
          }
        }

        //check for stop request.
        if (!cdd_stp_cycle_params.b_activation)
        {
          //Stop cycle, Stop Stepper
          cdd_stp_cycle_params.b_start = false;

          //disable mottor
          if (cdd_stp_cycle_params.un_stepper_id != 0xFFU)
          {
            cdd::stp::TI8899::start_stop((te_cdd_stp_id)cdd_stp_cycle_params.un_stepper_id, 1U);
          }
          else
          {
            for (uint8 idx = 0; idx < CDDSTP_DRVNR; idx++)
            {
              cdd::stp::TI8899::start_stop((te_cdd_stp_id)idx, 0U);
            }
          }
        }
       
      }
      //increment time
      cdd_stp_cycle_params.un_current_time_ms++;
    }
  }
  else
  {
    //reinitialize timer
    cdd_stp_cycle_params.un_current_time_ms = 1u;
  }

  cdd::stp::TI8899::refresh_errors();
#endif
}

//-----------------------------------------------------------------------------
// \brief  task_cdd_stp_init
//
// \descr  This function is part of the Os and is called at the init phase of Os
//         and will initialize all configured stepper drivers.
//         
// \param  void
//
// \return void
//-----------------------------------------------------------------------------
void TaskCddStp_Init(void)
{
  uint8 index;
  for (index = 0U; index < CDDSTP_DRVNR; index++)
  {
    switch (cdd_stp_config[index].e_drv_type)
    {
    case e_cdd_stp_TI8899:
      {
        cdd::stp::TI8899::init(CDDSTP_INIT_REG_VAL == e_cdd_stp_init_reg_specific);
      }
    default:
    {
      //nothing to do here
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
// \return uc_ret - error code
//-----------------------------------------------------------------------------
uint8 cdd::stp::start_stop(te_cdd_stp_id stp_id, boolean start_stp)
{
  te_cdd_stp_status uc_ret = e_cdd_stp_EOK;

  switch (cdd_stp_config[stp_id].e_drv_type)
  {
    case e_cdd_stp_TI8899:
    {
      cdd::stp::TI8899::start_stop(stp_id, start_stp);
      break;
    }
    default:
    {
      uc_ret = e_cdd_stp_device_not_supported;
      break;
    }
  }

  return uc_ret;
}

//-----------------------------------------------------------------------------
// \brief  change_dirrection
//
// \descr  This function is responsible for changinf the dirrection of the stepper.
//         
// \param  stp_id - Stepper ID configured in CddStp_Cfg.h
//
// \return uc_ret - error code
//-----------------------------------------------------------------------------
uint8  cdd::stp::change_dirrection(te_cdd_stp_id StpID)
{
  te_cdd_stp_status ucRet = e_cdd_stp_EOK;

  switch (cdd_stp_config[StpID].e_drv_type)
  {
    case e_cdd_stp_TI8899:
    {
      cdd::stp::TI8899::change_dirrection(StpID);
      break;
    }
    default:
    {
      ucRet = e_cdd_stp_device_not_supported;
      break;
    }
    
  }

  return ucRet;
}

//-----------------------------------------------------------------------------
// \brief  read_write_reg
//
// \descr  This function is responsible writing and reading the stepper registers
//         
// \param  stp_id - Stepper ID configured in CddStp_Cfg.h
//         spi_request - type of request Read - 0, write - 1
//         puc_addr - pointer to Stp reg addr
//         puc_tx_data - pointer to data to be sent ovet SPI, discarded if read request
//         pun_rx_data - pinter to received data over SPI
//
// \return uc_ret - error code
//-----------------------------------------------------------------------------
uint8 cdd::stp::read_write_reg(te_cdd_stp_id StpID, te_cdd_stp_spi_req_type SpiRequest, uint8 pucAddr, uint8 *pucTxData, uint16 *punRxData)
{

  te_cdd_stp_status ucRet = e_cdd_stp_EOK;

  switch (cdd_stp_config[StpID].e_drv_type)
  {
    case e_cdd_stp_TI8899:
    {
      cdd::stp::TI8899::read_write_reg(StpID, SpiRequest, pucAddr, pucTxData, punRxData);
      break;
    }
    default:
    {
      ucRet = e_cdd_stp_device_not_supported;
      break;
    }
  }

  return ucRet;
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
// \return uc_ret - error code
//-----------------------------------------------------------------------------
uint8  cdd::stp::read_write_reg_all(te_cdd_stp_id stp_id, te_cdd_stp_spi_req_type spi_request, uint8* puc_tx_data, uint16* pun_rx_data, uint8* response_len)
{
  return cdd::stp::TI8899::read_write_reg_all(stp_id, spi_request, puc_tx_data, pun_rx_data, response_len);
}
#endif