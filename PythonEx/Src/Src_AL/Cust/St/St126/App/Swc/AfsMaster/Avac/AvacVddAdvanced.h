#ifndef __AVACVDD_ADVANCED_H
  #define __AVACVDD_ADVANCED_H

  #include <Cfg/Cfg.h>

  // -----------------------------------------------------------------------------
  // defines

  // scaling value: 0...100% represented by 0...128
  #define AVACVDD_ScalingValue                128u

  // states of vehicle dynamic
  #define AVACVDD_DynState_HighAccel      0x01
  #define AVACVDD_DynState_ConstSpeed     0x02
  #define AVACVDD_DynState_ZeroSpeed      0x04
  #define AVACVDD_DynState_Invalid        0x80

  #define AVACVDD_AccIndex_Invalid        0xFFu

  #define AVACVDD_BadStreetIndex_Invalid  0xFF


  #define AVACVDD_MinSpeed                      500  // [1/10 km/h]

#ifdef CFG_PRJ_Fa51
  #define AVACVDD_LowDynamicLimit               17  // acceleration limit for updating LD filter and road surface detection
#else
  #define AVACVDD_LowDynamicLimit                3  // acceleration limit for updating LD filter and road surface detection
#endif

  #define AVACVDD_AccelerationThreshold         16  // (2^x) saturation value for detecting acceleration index

  #define AVACVDD_SizeofAccelerationArray       11  // (11-1) * 40ms = 400ms interval for detecting acceleration index

  //#define AVACVDD_AccelPreDetectThresholdUp      5  // Delta of Pedal Position
  //#define AVACVDD_AccelPreDetectThresholdDown  -10

  //#define AVACVDD_BrakePreDetectThreshold        1  // digital switch on/off

#endif //__AVACVDD_ADVANCED_H
