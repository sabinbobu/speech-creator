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
/// \file  Spi.c
///
/// \brief  
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Mcal/Spi/Spi.h>
#include <Cfg/Cfg.h>
#include <stddef.h>
#include <lpspi_shared_function.h>
#include <lpspi_master_driver.h>
#include <string.h>
#include <UtilUtility.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//=============================================================================
// Private macros
//=============================================================================
#define SPI_PARITY_CHECK_MASK 0x0001U
#define SPI_BIT_FRAME_LENGTH 16U
#define INST_LPSPI_0  0U
#define INST_LPSPI_1  1U
#define TIMEOUT 1000U

//=============================================================================
// Public variables definitions
//=============================================================================
extern uint8 ApplCmd_HWVariant;

//=============================================================================
// Private variables definitions
//=============================================================================


//=============================================================================
// Public functions definitions
//=============================================================================
//-----------------------------------------------------------------------------
// \brief   spi_init
//
// \descr   Initialized Spi peripheral
//
// \param   void
//
// \return  -
//-----------------------------------------------------------------------------
void Spi_Init(const Spi_ConfigType* ConfigPtr)
{
  const spi_config_map_t* p = (const spi_config_map_t*)ConfigPtr->spi_map;
  
  LPSPI_DRV_MasterInit(0U, 
                      (lpspi_state_t*)p[0].spi_state, 
                      (const lpspi_master_config_t*)p[0].Spi_Cfg_atyCharacteristics);

  LPSPI_DRV_MasterSetDelay(0U, 10U, 10U, 10U);
    
  LPSPI_DRV_MasterInit(1U, 
                       (lpspi_state_t*)p[Spi_Config.ucCountOfSpiInstances - 1U].spi_state, 
                       (const lpspi_master_config_t*)p[Spi_Config.ucCountOfSpiInstances - 1U].Spi_Cfg_atyCharacteristics);

  LPSPI_DRV_MasterSetDelay(1U, 10U, 10U, 10U);
}

//-----------------------------------------------------------------------------
// \brief   spi_transmit
//
// \descr   Transmits data over the spi
//
// \param   *base   base address of the SPI instance
// \param   *tx_buf  data to be transmitted 
// \param   *rx_buf  received data
// \param   size    size of the data
//
// \return  -
//-----------------------------------------------------------------------------
uint8 Spi_Transmit(te_active_configuration active_config, uint16 *tx_buf, uint16 * const rx_buf, uint32 size)
{
  volatile uint32_t i = 0;
  typedef struct
  {
    uint8 tx[NUMBER_OF_FRAMES];
    uint8 rx[NUMBER_OF_FRAMES];
  } spi_buffer_t;

  spi_buffer_t master_buffer = { 0U };


  for ( i = 0; i < size; ++i)
  { 
    master_buffer.tx[(2U * i) + 1U] = ((tx_buf[i] >> 8U) & 0xFFU);
    master_buffer.tx[(2U * i)] = ((tx_buf[i]) & 0xFFU);
  }


  for (i = 0; i < Spi_Config.ucCountOfSpiInstances; ++i)
  {
    if (Spi_Config.spi_map[i].config == active_config)
    {
      LPSPI_DRV_MasterInit(Spi_Config.spi_map[i].spi_instance, 
                          (lpspi_state_t*)Spi_Config.spi_map[i].spi_state, 
                          (const lpspi_master_config_t*)Spi_Config.spi_map[i].Spi_Cfg_atyCharacteristics);
      LPSPI_DRV_MasterSetDelay(Spi_Config.spi_map[i].spi_instance, 10U, 10U, 10U);
      break;
    }
  } 

  status_t status = LPSPI_DRV_MasterTransferBlocking(Spi_Config.spi_map[i].spi_instance, 
                                   (const uint8_t*)&master_buffer.tx[0], 
                                   (uint8_t*)&master_buffer.rx[0], 
                                   size * 2U, 
                                   TIMEOUT);

  for (i = 0; i < size; ++i)
  {
    rx_buf[i] = (uint16)((uint16)master_buffer.rx[i * 2U + 1U] << 8) |
              ((uint16)master_buffer.rx[i * 2U] & 0x00FF);
       
  }
  return status;
}


//-----------------------------------------------------------------------------
// \brief   spi_set_parity_bit
//
// \descr   Set the parity bit
//
// \param   *u16FrameData        frame of data
// \param   u8ParityBitPosition  position of the parity bit to be set 
//
// \return  -
//-----------------------------------------------------------------------------
//PRQA S 1503 1 //The function is actually  used to calculate the parity bit
void spi_set_parity_bit(uint16 *u16_frame_data, uint8 u8_parity_bit_position)
{
  uint8 u8idx;
  uint8 u8frameParity = 0U;

  //get the number of b1 form the received frames
  for (u8idx = 0U; u8idx < SPI_BIT_FRAME_LENGTH; u8idx++)
  {
    if (((*u16_frame_data >> u8idx) & (uint16)SPI_PARITY_CHECK_MASK) != 0U)
    {
      u8frameParity++;
    }
  }
  
  //if the frame has even b1, set parity bit
  if ((u8frameParity % 2U) == 0U)
  {
    *u16_frame_data |= (uint16)((uint16)1U << u8_parity_bit_position);
  }

}
