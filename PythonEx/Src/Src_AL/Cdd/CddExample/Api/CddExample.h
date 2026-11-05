#ifndef CDD_EXAMPLE_2019_08_16_H_
  #define CDD_EXAMPLE_2019_08_16_H_

  #include <AL_Helper.h>

  #define CDD_EXAMPLE_STATEMACHINE_UNKNOWN_STATE   255

  boolean CddExample_Init(void);
  void    CddExample_Config(uint8 ubParam1, uint8 ubParam2);
  void    CddExample_Statemachine_ExecState1(void);
  void    CddExample_Statemachine_ExecState2(void);
  void    CddExample_Statemachine(void);
  void    CddExample_Init_SetControl(const boolean boControl);

#endif /* CDD_EXAMPLE_2019_08_16_H_ */
