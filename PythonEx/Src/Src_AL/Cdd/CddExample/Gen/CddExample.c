
#include <AL_Helper.h>
#include <CddExample.h>
#include <stdio.h>


volatile boolean CddExample_boOneTestCondition = FALSE;
volatile boolean CddExample_boOtherTestCondition = TRUE;
volatile boolean CddExample_boControl = FALSE;
volatile uint8   CddExample_ErrorState = 0;


boolean CddExample_Init(void)
{
  //printf("CddExample_Init called\n");

  boolean retVal = FALSE;

  if ((CddExample_boOneTestCondition && CddExample_boOtherTestCondition) == TRUE)
  {
    retVal = TRUE;
  }
  return retVal;
}


void CddExample_Config(uint8 ubParam1, uint8 ubParam2)
{
  (void)ubParam1;
  (void)ubParam2;
}


void CddExample_Statemachine_ExecState1(void)
{
  //execute State 1 activities
  CddExample_boOneTestCondition = TRUE;
}


void CddExample_Statemachine_ExecState2(void)
{
  //execute State 2 activities
  CddExample_boOneTestCondition = FALSE;
}


void CddExample_Statemachine(void)
{
  //static uint8 CddExample_Statemachine_State = 1;
  STATIC_UT(uint8, CddExample_Statemachine_State, 1);

  switch(CddExample_Statemachine_State)
  {
  case 1:
    CddExample_Statemachine_ExecState1();
    CddExample_Statemachine_State = 2;
    break;
  case 2:
    CddExample_Statemachine_ExecState2();
    CddExample_Statemachine_State = 1;
    break;
  default:
    CddExample_ErrorState = CDD_EXAMPLE_STATEMACHINE_UNKNOWN_STATE;
    break;
  }
}


void CddExample_Init_SetControl(const boolean boControl)
{
  CddExample_boControl = boControl;
}


uint8 CddExample_VoltageGet(void)
{
  //static uint8 voltage = 0;
  STATIC_UT(uint8, voltage, 0);

  uint8 retVal;

  retVal = voltage;

  voltage++;

  return retVal;
}

