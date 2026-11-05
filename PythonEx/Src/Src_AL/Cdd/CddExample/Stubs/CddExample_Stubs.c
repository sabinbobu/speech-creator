
#include <Std_Types.h>
#include <stdio.h>


volatile boolean CddExample_boOneTestCondition = FALSE;
volatile boolean CddExample_boOtherTestCondition = TRUE;
volatile boolean CddExample_boControl = FALSE;
volatile uint8   CddExample_ErrorState = 0;

boolean CddExample_Init_retVal = FALSE;

boolean CddExample_Init(void)
{
  //printf("CddExample_Init_Stubs called\n");

  return CddExample_Init_retVal;
}


void CddExample_Config(uint8 ubParam1, uint8 ubParam2)
{
  (void)ubParam1;
  (void)ubParam2;
}


void CddExample_Statemachine_ExecState1(void)
{
  //execute State 1 activities
}


void CddExample_Statemachine_ExecState2(void)
{
  //execute State 2 activities
}


void CddExample_Statemachine(void)
{
  //do nothing
}


void CddExample_Init_SetControl(const boolean boControl)
{
  (void) boControl;
}


//--------------------------------------
// This stub function returns simply a constant 0.
//--------------------------------------
uint8 CddExample_VoltageGet(void)
{
  return 0;
}

