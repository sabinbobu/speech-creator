#ifndef __AVAC_DYN1_H
  #define __AVAC_DYN1_H

  #include <Cfg/Cfg.h>

  #define AVAC_ScalingValue            128u  // numbers from 0...100% are scaled to 0...128

  #define AVAC_StaticAngleGradNormal     1  // maximum gradient of AutoAngle [0.1 mrad / 20 ms] (default)
  #define AVAC_StaticAngleGradFast       5  // maximum gradient of AutoAngle [0.1 mrad / 20 ms] (for fast reaction)
  #define AVAC_DynamicAngleGrad         25  // maximum gradient of AutoAngle [0.1 mrad / 10 ms]

  #define AVAC_DynamicIndexDown          3  // 1,7s fall time for dynamic index (steps per 40ms, 128 --> 0)
  #define AVAC_DynamicIndexCtrStart     30  // 600ms / 20ms = 30 samples: delay until HD will be reduced

  #define AVAC_OutputAngleMax          875  // [(1/10) mrad]  5° max. regulation output (dyn + stat)
  #define AVAC_DynamicAngleMax         500  // [(1/10) mrad]  max. dynamic correction ( <512 overflow protection )

  #define AVAC_AngleMinChange           10  // [(1/10) mrad]
  #define AVAC_AngleRemainingError       5  // [(1/10) mrad]

  #define AVAC_AngleMinChangeZero        2  // [(1/10) mrad]
  #define AVAC_AngleRemainingErrorZero   0  // [(1/10) mrad]
  
  #define AVAC_MoveBackThreshold        20  // minimal angle that is treated as movement towards static position
  #define AVAC_MoveBackLimit            84u  // saturation value for recognizing movement towards static position
  // optimize: (AVAC_MoveBackThreshold - AVAC_MoveBackLimit) = 2^n

  #define AVAC_BadStreetFilterTime      32u  // [10 ms] (use 2^n)

#endif //__AVAC_DYN1_H
