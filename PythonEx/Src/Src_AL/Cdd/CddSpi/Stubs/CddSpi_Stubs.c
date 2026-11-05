#include <Std_Types.h>
#include <stdio.h>


//==============================================================================
// Extern Vars
//==============================================================================
//CddSpi_Init
uint16   CddSpi_Init_CallCounter = 0U;
//CddSpi_TransferMsg
uint16   CddSpi_TransferMsg_CallCounter = 0U;
boolean  CddSpi_TransferMsg_boRetVal;
uint8    CddSpi_TransferMsg_ucDevice;
uint16*  CddSpi_TransferMsg_punData;
uint16   CddSpi_TransferMsg_punDataDeRef;

//==============================================================================
// Stubs
//==============================================================================
//void CddSpi_Init(void)
//{
//  CddSpi_Init_CallCounter++;
//}