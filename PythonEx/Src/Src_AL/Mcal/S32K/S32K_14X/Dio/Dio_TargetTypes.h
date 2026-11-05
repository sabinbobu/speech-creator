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
/// \file  Dio_TargetTypes.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef DIO_CFG_2020_11_18_H_
  #define DIO_CFG_2020_11_18_H_

  #include <Std_Types.h>
  #include <AL_Helper.h>
  #include <Cfg/Cfg.h>
  
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  #define DIO_CFG_CHANNEL_NUMBER 19u
#elif defined(SAMPLE_ECO) || defined (UNIT_TEST)
  #define DIO_CFG_CHANNEL_NUMBER 4u
#endif

  typedef uint32 Dio_PortType;

  typedef struct ChannelIdMap_t
  {
    uint32 ChannelId;
    void* PortBase;
    uint32 Pin;
  } ChannelIdMap_t;

  typedef struct Dio_ChannelGroupType
  {
    uint32       mask;
    uint8        offset;
    Dio_PortType port;
  } Dio_ChannelGroupType;

  extern CONST_AL ChannelIdMap_t Dio_ChannelMap[DIO_CFG_CHANNEL_NUMBER];


#endif // DIO_CFG_2020_11_18_H_
