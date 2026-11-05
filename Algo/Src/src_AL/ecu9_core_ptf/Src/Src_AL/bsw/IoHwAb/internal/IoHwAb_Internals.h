/******************************************************************************/
/*
| (C) Marelli Automotive Lighting - ALIT-TO                                    |
|     Strada del Drosso 29, 10135 Torino (IT)                                  |
|                                                                              |
| Marelli Automotive Lighting owns all the rights to this work.                |
| This work shall not be copied, reproduced, used, modified, transferred       |
| or its information shall not be disclosed without the prior written          |
| authorization of Marelli Automotive Lighting.                                |
*/
/******************************************************************************/
/*!
* \file     IoHwAb_Internals.h
*
* \brief    BSW IoHwAb internal
*
* \descr    Internal header for IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef IOHWAB_INTERNALS_H
#define IOHWAB_INTERNALS_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* Analog APIs */
extern FUNC(void, IOHWAB_CODE) IoHwAb_AnalogInit(void);
extern FUNC(void, IOHWAB_CODE) IoHwAb_AnalogMainFunction(void);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_AnalogReadConverted
(
  VAR(IoHwAb_AnalogChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_ConvertedValueType, AUTOMATIC, IOHWAB_APPL_DATA) OutPtr
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_AnalogReadRaw
(
  VAR(IoHwAb_AnalogChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_RawValueType, AUTOMATIC, IOHWAB_APPL_DATA) OutPtr
);

/* Digital APIs */
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DigitalRead
(
    VAR(IoHwAb_DigitalChannelIdType, AUTOMATIC) ChId,
    P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) LevelPtr
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DigitalWrite
(
    VAR(IoHwAb_DigitalChannelIdType, AUTOMATIC) ChId,
    VAR(IoHwAb_LevelType, AUTOMATIC) Level
);

/* Timing APIs */
extern FUNC(void, IOHWAB_CODE) IoHwAb_TimingInit(void);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingSetDutyCycle
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId,
  VAR(IoHwAb_DutyCycleType, AUTOMATIC) DutyCycle
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingStopActuation
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingGetDutyCycle
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_DutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCyclePtr
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingStartMeasurement
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingStopMeasurement
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId
);

/* External interfaces */
extern FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogAcquireExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId
);
extern FUNC(void, IOHWAB_CODE) IoHwAb_DigitalWriteExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId,
  VAR(IoHwAb_LevelType, AUTOMATIC) Level
);
extern FUNC(IoHwAb_LevelType, IOHWAB_CODE) IoHwAb_DigitalReadExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId
);
extern FUNC(void, IOHWAB_CODE) IoHwAb_SetDutyCycleExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId,
  VAR(IoHwAb_DutyCycleType, AUTOMATIC) DutyCycle
);
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_GetDutyCycleExternal
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_DutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCycle
);

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/
