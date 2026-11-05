
#include <ALUnitTest_UserInterface.h>

#include <CddExample.h>

#include <stdio.h>

uint8 CddExample_Statemachine_State = 1;


extern volatile boolean CddExample_boControl;


void Mt_CddExample_Init(void)
{
  extern boolean CddExample_boOneTestCondition;
  extern boolean CddExample_boOtherTestCondition;

  {
    CddExample_boOneTestCondition = TRUE;
    CddExample_boOtherTestCondition = TRUE;
    const boolean boCddExample_InitResult = CddExample_Init();
    AL_UNITTEST_CHECK(boCddExample_InitResult, TRUE, == );
  }

  {
    CddExample_boOneTestCondition = FALSE;
    CddExample_boOtherTestCondition = FALSE;
    const boolean boCddExample_InitResult = CddExample_Init();
    AL_UNITTEST_CHECK(boCddExample_InitResult, FALSE, == );
  }
}


void Mt_CddExample_Config(void)
{
  CddExample_Config(1, 1);
  //AL_UNITTEST_CHECK(TRUE, TRUE, == );
}


void Mt_CddExample_Statemachine_ExecState1(void)
{
  CddExample_Statemachine_ExecState1();
}


void Mt_CddExample_Statemachine_ExecState2(void)
{
  // Note: This test fails on purpose in order to exemplify a failed assert.
  CddExample_Statemachine_ExecState2();
  AL_UNITTEST_CHECK(TRUE, FALSE, ==);
}


void Mt_CddExample_Statemachine(void)
{
  extern uint8 CddExample_Statemachine_State;
  extern volatile uint8 CddExample_ErrorState;

  CddExample_Statemachine_State = 0;
  CddExample_Statemachine();
  AL_UNITTEST_CHECK(CddExample_ErrorState, CDD_EXAMPLE_STATEMACHINE_UNKNOWN_STATE, == );

  CddExample_Statemachine_State = 1;
  CddExample_Statemachine();
  AL_UNITTEST_CHECK(CddExample_Statemachine_State, 2, == );

  CddExample_Statemachine_State = 2;
  CddExample_Statemachine();
  AL_UNITTEST_CHECK(CddExample_Statemachine_State, 1, == );
}


void Mt_CddExample_Init_SetControl(void)
{
  CddExample_Init_SetControl(TRUE);
  AL_UNITTEST_CHECK(CddExample_boControl, TRUE, == );

  CddExample_Init_SetControl(FALSE);
  AL_UNITTEST_CHECK(CddExample_boControl, FALSE, == );
}


void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_CddExample_Init"                   , Mt_CddExample_Init                    );
  ALUnitTest_AddFunction("Mt_CddExample_Config"                 , Mt_CddExample_Config                  );
  ALUnitTest_AddFunction("Mt_CddExample_Statemachine_ExecState1", Mt_CddExample_Statemachine_ExecState1 );
  ALUnitTest_AddFunction("Mt_CddExample_Statemachine_ExecState2", Mt_CddExample_Statemachine_ExecState2 );
  ALUnitTest_AddFunction("Mt_CddExample_Statemachine"           , Mt_CddExample_Statemachine            );
  ALUnitTest_AddFunction("Mt_CddExample_Init_SetControl"        , Mt_CddExample_Init_SetControl         );
}
