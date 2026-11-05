#ifndef CAN_2019_04_05_H_
  #define CAN_2019_04_05_H_

  #include <Std_Types.h>
  #include <Can_TargetTypes.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef Can_SpecificType Can_ConfigType;

  void Can_Init(const Can_ConfigType* ConfigPtr);

  #if defined(__cplusplus)
  }
  #endif

#endif // CAN_2019_04_05_H_
