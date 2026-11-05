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
/// \file  CddSpi.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_SPI_2021_01_27_H_
#define CDD_SPI_2021_01_27_H_

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <CddSpi_Cfg.h>

//=============================================================================
// Public preprocessor definitions
//=============================================================================
#define CDDSPI_DEVICE(dev)  (CddSpi_eDev_##dev)

//CddSpi States
#define CDDSPI_STATE_RESET                             0x00U
#define CDDSPI_STATE_SINGLE_OPERATION                  0x01U
#define CDDSPI_STATE_CYCLIC_OPERATION                  0x02U

//CddSpi Status Fault
#define CDDSPI_STATUS_FAULT_SA_MSK                     0x80U  //Signal Available
#define CDDSPI_STATUS_FAULT_SA_POS                     7U
#define CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK   0x40U  //Dynamic Configuration Error
#define CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_POS   6U

//=============================================================================
// Public type definitions
//=============================================================================
//Device enum
#define CDDSPI_MAC_DECL_DEV_ENUM
#include <CddSpi_Cfg.h>
#undef  CDDSPI_MAC_DECL_DEV_ENUM

//=============================================================================
// Public function declarations
//=============================================================================

#if defined(__cplusplus)
extern "C"
{
#endif

  //Module APIS
  void  CddSpi_Init(void);
  void  CddSpi_DeInit(void);
  uint8 CddSpi_GetState(void);

#if (CDDSPI_SINGLE_OPERATION == STD_ON) 
  boolean CddSpi_TransferMsg(uint8 ucDevice, uint16* punData);
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
  void CddSpi_Start(void);
  void CddSpi_Stop(void);
  void CddSpi_Cycle(void);
#endif

  //RTE-Runnables
#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
  void riCddSpiInit(void); //Start Cyclic Operation
  void rpCddSpi_Cycle(void);
#endif

#if defined(__cplusplus)
}
#endif

#endif // CDD_SPI_2021_01_27_H_
